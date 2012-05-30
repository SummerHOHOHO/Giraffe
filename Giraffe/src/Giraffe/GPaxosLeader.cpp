#include "GPaxosLeader.h"
#include "Packets/Giraffe/paxos/PGRFPaxosPackets.h"
#include "Logger/PaxosLogger.h"

GPaxosLeader::GPaxosLeader(GPaxosState* paxos_state,GPaxosLeaderElection* election)
{
	m_pPaxosState = paxos_state;
	m_pComm = m_pPaxosState->getComm();
	m_pElectionInstance = election;
}

GPaxosLeader::~GPaxosLeader()
{

}

void GPaxosLeader::handleEvent(PaxosEvent pe)
{
	if (m_pPaxosState->m_state != PAXOS_STATE::LEADING)
	{
		//print warning
		cout << "unexpected event event type:" << GPaxosUtils::strEventType(pe.m_iEventType) << endl;
		return;
	}
	unsigned eventType = pe.m_iEventType;

	switch(eventType)
	{
	case PAXOS_EVENT::PING_LEADER_EVENT:
		handlePingFrmFollower(pe);
		break;

	case PAXOS_EVENT::UAB_PREPARE_EVENT:
		cout << "get prepare event from follower!!" << endl;
		handlePrepareEvent(pe);
		break;

	case PAXOS_EVENT::UAB_ACK_EVENT:
		cout << "get ack from follower" << endl;
		handleAckEvent(pe);
		break;

	default :
		assert(0);
		break;
	}
}

//following function is used for checking follower state,
//check out expired followers and  then renew the global membership
void GPaxosLeader::renewFollowerMembership()
{
	cout << "i am leader, renew global membership " << endl;
}

void GPaxosLeader::handlePingFrmFollower(PaxosEvent &pe)
{
	cout << "ping to follower!!" << endl;
	PPacketBase* pingPkt = (PGRFPaxosLeaderKeepAliveRes*)new PGRFPaxosLeaderKeepAliveRes();
	//PPacketBase* pingPkt = (PGRFPaxosEventPkt*)new PGRFPaxosEventPkt(PAXOS_EVENT::PING_LEADER_EVENT, m_pPaxosState->m_iMyid, m_pPaxosState->m_iCurrentEpoch, m_pPaxosState->m_iCurrentTxid, m_pPaxosState->m_oLocalPaxosAddr);
	m_pComm->tcpSend(pe.m_oFrmAddr, pingPkt);
}

//handle follower prepare event 
void GPaxosLeader::handlePrepareEvent(PaxosEvent &pe)
{
	cout<<endl<<endl;
	PeerAddrContainer::iterator cIterator;
	TXID paxosDecodeTxid =TXID::decodeID(pe.m_lTxid);
	//prepare broadcast event; set max zxid + 1; get followers list and broadcast pkt to them
	//���event��epoch��txidǰ32λ�Ƿ���ͬ���������¼��Ƿ��ʱ
	if(pe.m_iEpoch!=paxosDecodeTxid.m_epoch || pe.m_iEpoch!=m_pPaxosState->m_iLeaderEpoch )
	{
		cout << "this Prepare is invalid!" << endl;
		return;
	}

	if(m_pPaxosState->m_iTxCounter==0) pe.m_lTxid += 1;
	m_pPaxosState->m_iCurrentTxid +=1;
	m_pPaxosState->m_iTxCounter +=1;

	cout<<"���յ�һ����Ч�� Prepare�¼�: txid="<<pe.m_lTxid<<endl;
	cout<<"m_pPaxosState->m_iTxCounter="<<m_pPaxosState->m_iTxCounter<<endl;
	cout<<"m_pPaxosState->m_iCurrentTxid="<<m_pPaxosState->m_iCurrentTxid<<endl;
	cout<<"Prepare����������Ϊ��"<<pe.m_sValue<<endl;
	m_oAckCounter.insert(pair<U64,U32>(pe.m_lTxid,0));//Ack������

	//log���֣�����һ����־������commitflagΪ0
	//PPacketBase* pingPkt = (PGRFPaxosEventPkt*)new PGRFPaxosEventPkt(PAXOS_EVENT::PING_LEADER_EVENT, m_pPaxosState->m_iMyid, m_pPaxosState->m_iCurrentEpoch, m_pPaxosState->m_iCurrentTxid, m_pPaxosState->m_oLocalPaxosAddr);
	//��membership�л�ýڵ��б������д��ڵĽڵ����η���proposal��
	PaxosLogger::LogPaxosEvent(pe.m_lTxid, pe.m_iEventType, pe.m_sKey, pe.m_sValue);
	for(cIterator= m_pPaxosState->m_oReplicaTable.begin();cIterator!= m_pPaxosState->m_oReplicaTable.end();cIterator++)
	{
		if(cIterator->getPort()!=0 && !(cIterator->getAddr()==m_pPaxosState->m_oLeaderAddr.getAddr()&&cIterator->getPort()==m_pPaxosState->m_oLeaderAddr.getPort()))
		{
			PPacketBase* pingPkt = (PGRFBroadcastEventPkt*)new PGRFBroadcastEventPkt(PAXOS_EVENT::UAB_PROPOSAL_EVENT, m_pPaxosState->m_iMyid, pe.m_iEpoch, pe.m_lTxid, pe.m_sKey, pe.m_sValue);
			cout<<"��followers����proposal port:"<<cIterator->getPort()<<endl;
			m_pComm->tcpSend(*cIterator, pingPkt);
		}
	}
	cout<<"����������Proposal��"<<endl;
	cout<<endl<<endl;
}

void GPaxosLeader::handleAckEvent(PaxosEvent &pe)
{
	//check whether this pe has commit
	//if has committed then send commit event to the follower and return;
	//else increase the counter of this pe,if check counter greater than half number of follower, if more than half then broadcast the event to the followers who have sent ack

	PeerAddrContainer::iterator cIterator;
	//U32 membershipSize = m_pPaxosState->m_oReplicaTable.size();
	U32 membershipSize = 0;
	TXID paxosDecodeTxid =TXID::decodeID(pe.m_lTxid);
	cout<<endl<<endl;

	if(pe.m_iEpoch!=paxosDecodeTxid.m_epoch || pe.m_iEpoch!=m_pPaxosState->m_iLeaderEpoch )
	{
		cout << "this Ack is invalid!" << endl;
		return;
	}
	for(cIterator= m_pPaxosState->m_oReplicaTable.begin();cIterator!= m_pPaxosState->m_oReplicaTable.end();cIterator++)
	{
		if(cIterator->getPort() == 0)
			continue;
		membershipSize++;
	}
	cout<<"���յ�һ����Ч�� Ack �¼�: txid="<<pe.m_lTxid<<endl;
	if(m_oAckCounter.count(pe.m_lTxid)==1)
	{
		m_oAckCounter[pe.m_lTxid]+=1;
		cout<<"����Txid="<<pe.m_lTxid<<"��ack������"<<" ack="<<m_oAckCounter[pe.m_lTxid]<<endl;
	}
	else
		cout<<"Txid="<<pe.m_lTxid<<"����Ϣ�Ѿ�commit���ˣ�������Ӧ�ļ������������������"<<endl;

	if(m_oAckCounter[pe.m_lTxid]==(membershipSize/2+1))
	{
		if(pe.m_lTxid>m_pPaxosState->m_iMaxCommitTxid)m_pPaxosState->m_iMaxCommitTxid=pe.m_lTxid;
		for(cIterator= m_pPaxosState->m_oReplicaTable.begin();cIterator!= m_pPaxosState->m_oReplicaTable.end();cIterator++)
		{
			if(cIterator->getPort()!=0 && !(cIterator->getAddr()==m_pPaxosState->m_oLeaderAddr.getAddr() && cIterator->getPort()==m_pPaxosState->m_oLeaderAddr.getPort()))
			{
				PPacketBase* pingPkt = (PGRFBroadcastEventPkt*)new PGRFBroadcastEventPkt(PAXOS_EVENT::UAB_COMMIT_EVENT, m_pPaxosState->m_iMyid, pe.m_iEpoch, pe.m_lTxid,"",  "commit Packet");
				cout<<"����commit��followers!port:"<<cIterator->getPort()<<endl;
				m_pComm->tcpSend(*cIterator, pingPkt);//��membership�л�ýڵ��б����η���
			}

		}
		PaxosLogger::CommitPaxosEvent(pe.m_lTxid);
		cout<<"txid="<<pe.m_lTxid<<"��commit���Ѿ�������"<<endl<<endl;
	}  
}

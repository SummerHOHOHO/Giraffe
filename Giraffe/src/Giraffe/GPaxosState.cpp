#include "GPaxosState.h"

GPaxosState::GPaxosState(GPaxosComm *comm)
{
	m_oComm = comm;
	PSettings & settings = PSettings::getInstance();
	U32 tempIp = PUtils::addr2Long( settings.getConfig("local-ip").m_value.strvalue );
	U16 tempPort = settings.getConfig("paxos-tcp-port").m_value.intvalue;
	m_oLocalPaxosAddr.set(tempIp,tempPort);

	m_state = PAXOS_STATE::LOOKING;
	m_iMyid = settings.getConfig("giraffe-id").m_value.intvalue;
	m_iPaxosSyncLimit = settings.getConfig("giraffe-paxos-sync-interval").m_value.intvalue;
	m_iPrevTxid = 0;
	m_iCurrentTxid = 0;
	m_iMaxCommitTxid = 0;
	m_iCurrentEpoch = 0;
	m_iLeaderEpoch = 0;

	//get giraffe servers ,the following codes take 5 server for test,
	//it should be modified for dynamic membership in the future
	PInetAddr replica_addr;

	int number = settings.getConfig("giraffe-workers").m_value.intvalue ;
	string replica_ip_str = "replica.x-ip";
	string replica_port_str = "replica.x-port";

	for (int i = 1; i <= number; i++)
	{
		char num = '0' + i;
		replica_ip_str[8] = num;
		replica_port_str[8] = num;
		tempIp = PUtils::addr2Long( settings.getConfig(replica_ip_str).m_value.strvalue );
		tempPort = settings.getConfig(replica_port_str).m_value.intvalue;
		replica_addr.set(tempIp,tempPort);
		m_oReplicaTable.push_back(replica_addr);
	}
};

GPaxosState::~GPaxosState(void)
{

};

bool GPaxosState::get_leader_location(Network::PInetAddr	&addr)
{
	if(m_state == PAXOS_STATE::LOOKING)
	{
		return false;
	}
	else
	{
		addr = m_oLeaderAddr;
		return true;
	}
}

bool GPaxosState::setLeaderOrFolowerState(unsigned state, U32 leaderId, PInetAddr leader, U32 epoch, U64 txid)
{
	m_state = state;
	m_iCurrentEpoch = epoch;
	m_iLeaderEpoch = epoch;
	m_iLeaderId = leaderId;
	m_oLeaderAddr = leader;
	m_iMaxCommitTxid = txid;
	
	if (state == PAXOS_STATE::LEADING)
	{
		m_iCurrentTxid = TXID::encodeID(m_iLeaderEpoch, 0);
		m_iTxCounter = 0;
	}
	return true;
}

bool GPaxosState::setLookerState()
{
	if (m_state != PAXOS_STATE::LOOKING)
	{
		m_state = PAXOS_STATE::LOOKING;
		m_iCurrentEpoch++;
		m_iCurrentTxid = m_iMaxCommitTxid;//reset current txid
	}

	return true;
}

void GPaxosState::setComm(GPaxosComm* comm)
{
	m_oComm = comm;
}

GPaxosComm * GPaxosState::getComm()
{
	return m_oComm;
}



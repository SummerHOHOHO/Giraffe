#include "PaxosLogger.h"

Loggerhandle * PaxosLogger::m_pHandle = NULL;

PaxosLogger::PaxosLogger(void)
{
}


PaxosLogger::~PaxosLogger(void)
{
}


void  PaxosLogger ::Initial()
{
	if (m_pHandle == NULL)
	{
		m_pHandle = new Loggerhandle;
		assert(m_pHandle != NULL);
		m_pHandle->init();
	}
}

void  PaxosLogger::LogPaxosEvent(U64 tTxid,U32 event_tType,string kKey,string vValue)
{
	m_pHandle->saveItem(tTxid, event_tType, kKey, vValue,  false);
}

void  PaxosLogger::LogPaxosEvent(const PGRFPaxoesEventPkt & pgp)
{
	m_pHandle->saveItem(pgp);
}

void  PaxosLogger::CommitPaxosEvent(U64 txid)
{
	m_pHandle->setEventCommit(txid);
}


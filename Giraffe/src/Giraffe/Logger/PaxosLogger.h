#ifndef __GIRAFFE_PAXOS_LOGGER_LAYER_INTERFACE__H__
#define __GIRAFFE_PAXOS_LOGGER_LAYER_INTERFACE__H__

#include "Logger/Loggerhandle.h"
#include "Logger/PGRFLoggerEventPkt.h"

class PaxosLogger
{
public:
	PaxosLogger(void);
	~PaxosLogger(void);

	void static Initial();
	void static LogPaxosEvent(const PGRFLoggerEventPkt & pgp);
	void static LogPaxosEvent(U64 tTxid,U32 event_tType,string kKey,string vValue);
	void static CommitPaxosEvent(U64 txid);
	void static PrintPaxosEvent();

private :
	static Loggerhandle * m_pHandle ;
};
#endif //__GIRAFFE_PAXOS_LOGGER_LAYER_INTERFACE__H__


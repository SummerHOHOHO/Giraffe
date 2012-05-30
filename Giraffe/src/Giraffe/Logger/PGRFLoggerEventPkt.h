#pragma once
#include "Base/GHeader.h"

class PGRFLoggerEventPkt
{
	public:
		PGRFLoggerEventPkt();
		PGRFLoggerEventPkt(U64 txid,U32 paxoesType,string key, string value, B8 committed_flag);

           virtual string					toString() const ;

    public:
		virtual ~PGRFLoggerEventPkt(void);
public:
	U64 txid;
	U32 paxoesType;
	string key;
	string value;
	B8 committed_flag;
};
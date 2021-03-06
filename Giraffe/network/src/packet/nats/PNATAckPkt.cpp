// Huazhong Univserity of Science and Technology.
// project: Netlet Middleware
// author: tuxuping. 
// email:  xupingtu@gmail.com, 
// date:   2009-6-23
// all rights reserved.

#include "common/Header.h"
#include "packet/nats/PNATAckPkt.h"
#include <sstream>

PNATAckPkt::PNATAckPkt()
:PPacketBase(PPktDef::PEER_TO_NAT_SERVER,PPktDef::NAT_ACK)
{

}

using namespace Network;

PNATAckPkt::PNATAckPkt( const PAddressable & addr )
:PPacketBase(PPktDef::PEER_TO_NAT_SERVER,PPktDef::NAT_ACK),
m_oSenderAddress ( addr )
{


}


U32 PNATAckPkt::getLength( ) const
{
	return COMMON_HEAD_LENGTH + m_oSenderAddress.getLength();
}


U32 PNATAckPkt::serialize( S8 *  buf,  S32 offset ) const
{
	U32 cur_pos = PPacketBase::serialize( buf, offset );

	S8 * buff = buf + offset;

	this->m_oSenderAddress.serialize(buff + cur_pos , 0 );

	cur_pos+= m_oSenderAddress.getLength();

	return cur_pos;

}


U32 PNATAckPkt::deserialize( const S8 * buf, S32 offset )
{
	U32 cur_pos = PPacketBase::deserialize(buf, offset);

	const S8 * buff = buf+ offset;

	m_oSenderAddress.deserialize( buff +  cur_pos,0  );

	cur_pos += m_oSenderAddress.getLength();

	return cur_pos;
}

String  PNATAckPkt::toString() const
{
	std::ostringstream s;
	s<< PPacketBase::toString();
	s<< " addr: "<< m_oSenderAddress.toString();
	return s.str();
}

U32 PNATAckPkt::toString( S8 * str ) const
{
	std::ostringstream strstr; 
	strstr<<" type:"<<PPktDef::type2String(this->m_cType,this->m_cSubType)	
		<<" v:"<<this->m_sVersion;

	strstr<< "Sender Address:"<< m_oSenderAddress.toString();

	String str1 = strstr.str();	
	U32 len = U32( str1.length() + 1);
	memcpy(str, str1.c_str(), len );
	return len;
}

const PAddressable & PNATAckPkt::getSender() const
{
	return this->m_oSenderAddress;
}


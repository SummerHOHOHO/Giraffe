#ifndef  __GIRAFFE_APPLICATION_EVENT_H__
#define  __GIRAFFE_APPLICATION_EVENT_H__
#include "Base/GHeader.h"

namespace APPLICATION_EVENT
{
	enum
	{
		NODE_NEW,
		NODE_MODIFIED,
		NODE_DELET,
	};
};

class  GApplicationEvent
{
public:
	GApplicationEvent(U32 type, string key, string nodevalue)
	{
		m_applicationType = type;
		m_nodename = key;
		m_nodevalue = nodevalue;
	}
	~GApplicationEvent()
	{

	}
public:
	U32 m_applicationType;
	string m_nodename;
	string m_nodevalue;
};
#endif // __GIRAFFE_APPLICATION_EVENT_H__

#include "Base/GHeader.h"
#include "GMembershipConfig.h"


GMembershipConfig::GMembershipConfig(const std::string & config_file, int number):PIniReader(config_file)
{	
	string replica_ip_str = "replica.x-ip";
	string replica_port_str = "replica.x-port";

	for (int i = 1; i <= number; i++)
	{
		char num = '0' + i;
		replica_ip_str[8] = num;
		replica_port_str[8] = num;
		this->addWantedProperty(replica_ip_str,PConfigValue::STRING_TYPE);
		this->addWantedProperty(replica_port_str,PConfigValue::INT_TYPE);
	}
}

GMembershipConfig::~GMembershipConfig(void)
{

}

void GMembershipConfig::getClusterMembership(int size)
{

}

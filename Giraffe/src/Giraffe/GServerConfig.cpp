#include "Base/GHeader.h"
#include "GServerConfig.h"


GServerConfig::GServerConfig(const std::string & config_file):PIniReader(config_file)
{
	this->addWantedProperty("log-level", PConfigValue::INT_TYPE );
	this->addWantedProperty("paxos-tcp-port", PConfigValue::INT_TYPE );
	this->addWantedProperty("paxos-udp-port", PConfigValue::INT_TYPE );
	this->addWantedProperty("local-tcp-server-port", PConfigValue::INT_TYPE );
	this->addWantedProperty("local-udp-server-port", PConfigValue::INT_TYPE );
	this->addWantedProperty("giraffe-lease-interval", PConfigValue::INT_TYPE );
	this->addWantedProperty("giraffe-mode",PConfigValue::STRING_TYPE);
	this->addWantedProperty("giraffe-keepalive-interval", PConfigValue::INT_TYPE);
	this->addWantedProperty("giraffe-grace-period", PConfigValue::INT_TYPE);
	this->addWantedProperty("giraffe-workers",PConfigValue::INT_TYPE);
	this->addWantedProperty("giraffe-paxos-sync-interval",PConfigValue::INT_TYPE);
	this->addWantedProperty("giraffe-leader-lease-interval",PConfigValue::INT_TYPE);
	this->addWantedProperty("giraffe-id",PConfigValue::INT_TYPE);
}

GServerConfig::~GServerConfig(void)
{

}

void GServerConfig::getClusterMembership(int size)
{

}

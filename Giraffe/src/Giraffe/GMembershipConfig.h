# ifndef __GIRAFFE_MEMBERSHIP_CONFIG_H__
# define __GIRAFFE_MEMBERSHIP_CONFIG_H__

class GMembershipConfig :
	public PIniReader
{
public:

	GMembershipConfig(const std::string & config_file, int number);

	void getClusterMembership(int size);

	virtual ~GMembershipConfig(void);

};

#endif//__GIRAFFE_MEMBERSHIP_CONFIG_H__

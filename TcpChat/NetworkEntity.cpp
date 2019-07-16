#include "NetworkEntity.h"


NetworkEntity::NetworkEntity(std::string str) : username(str)
{
}


NetworkEntity::~NetworkEntity()
{
	std::cout << "Connection closed" << std::endl;
}

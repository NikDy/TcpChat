#include "NetworkEntity.h"


NetworkEntity::NetworkEntity(std::string str) : username(str)
{
}


NetworkEntity::~NetworkEntity()
{
	std::cout << "NE destuct" << std::endl;
}

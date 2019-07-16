#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include "boost/asio.hpp"
#include "session.h"

using namespace boost::asio;

class NetworkEntity
{
public:
	NetworkEntity(std::string);
	~NetworkEntity();
protected:

	std::string username;
	unsigned short port = 2001;
};

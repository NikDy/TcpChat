#pragma once
#include "NetworkEntity.h"

class Hoster :
	public NetworkEntity
{
public:
	Hoster(io_context&, const std::string&);
	~Hoster();
private:
	void start();

	ip::tcp::acceptor acceptor_;
};


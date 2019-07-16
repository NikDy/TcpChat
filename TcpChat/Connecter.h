#pragma once
#include "NetworkEntity.h"
class Connecter :
	public NetworkEntity
{
public:
	Connecter(io_context&, const std::string&, const std::string&);
	~Connecter();
private:
	void start();

	std::string address;
	ip::tcp::socket socket_;
};


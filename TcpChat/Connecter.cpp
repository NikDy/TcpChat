#include "Connecter.h"


Connecter::Connecter(io_context& ioc, const std::string& add, const std::string& name) : 
	NetworkEntity(name),
	socket_(ioc), 
	address(add)
{
	start();
}


void Connecter::start()
{
	ip::tcp::endpoint ep(ip::address::from_string(address), port);
	auto connector_ = std::make_shared<session>(std::move(socket_));
	connector_->start(ep);
}


Connecter::~Connecter()
{
}

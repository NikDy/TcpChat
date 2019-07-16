#include "Hoster.h"



Hoster::Hoster(io_context& ioc, const std::string& name) :
	NetworkEntity(name),
	acceptor_(ioc, tcp::endpoint(ip::tcp::v4(), port)) 
{
	start();
}


void Hoster::start()
{
	std::cout << "Wait for connect" << std::endl;
	acceptor_.async_accept(
		[this](boost::system::error_code ec, tcp::socket socket)
	{
		if (!ec)
		{
			std::make_shared<session>(std::move(socket))->start(username);
		}
	});
}


Hoster::~Hoster()
{
}

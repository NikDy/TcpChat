#include "session.h"

session::session(tcp::socket socket) : socket_(std::move(socket))
{
}


void session::start(const std::string& name)
{
	username = name;
	std::cout << "Connected" << std::endl;
	std::thread reading_t(&session::do_read, this);
	std::thread writing_t(&session::do_write, this);
	writing_t.detach();
	reading_t.detach();
}


void session::start(tcp::endpoint ep, const std::string& name)
{
	username = name;
	socket_.connect(ep);
	std::cout << "Connected" << std::endl;
	std::thread reading_t(&session::do_read, this);
	std::thread writing_t(&session::do_write, this);
	writing_t.detach();
	reading_t.detach();
}


void session::do_read()
{
	auto self(shared_from_this());
	socket_.async_read_some(boost::asio::buffer(data_, max_length),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			std::cout.write(data_, length);
			std::cout << " " << std::endl;
			do_read();
		}
		else
		{
			std::cout << ec << std::endl;
			socket_.close();
		}
	});
}


void session::do_write()
{
	while (true)
	{
		std::string message;
		std::cout << username + ": ";
		std::cin >> message;
		message = username + ": " + message;
		if (message.length() > max_length - username.length() - 3)
		{
			message = message.substr(0, max_length);
		}
		auto self(shared_from_this());
		boost::asio::async_write(socket_, boost::asio::buffer(message.c_str(), message.length()),
			[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (ec)
			{
				std::cout << "Tranmition error: " << ec << std::endl;
			}
		});
	}
}

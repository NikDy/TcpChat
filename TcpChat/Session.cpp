#pragma warning(disable: 4996) //TODO: fix buffer overflow
#include "session.h"

session::session(tcp::socket socket) : socket_(std::move(socket))
{
}


void session::start()
{
	std::cout << "in session" << std::endl;
	std::thread reading_t(&session::do_read, this);
	std::thread writing_t(&session::do_write, this);
	writing_t.detach();
	reading_t.detach();
}


void session::start(tcp::endpoint ep)
{
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
			std::cout << std::endl;
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
		std::cin >> message;
		if (message.length() > max_length)
		{
			std::vector<std::string> msg_vec;
			for (size_t i = 0; i < message.length(); i += max_length)
			{
				char buffer[max_length];
				if (max_length - 1 >= max_length) message.copy(buffer, i, max_length);
				else message.copy(buffer, i, i - max_length);
				msg_vec.push_back(buffer);
			}
			auto self(shared_from_this());
			for (auto t : msg_vec)
			{
				boost::asio::async_write(socket_, boost::asio::buffer(t, t.length()),
					[this, self](boost::system::error_code ec, std::size_t /*length*/)
				{
					if (ec)
					{
						std::cout << "Tranmition error: " << ec << std::endl;
					}
				});
			}
		}
		else
		{
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
}

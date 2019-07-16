#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <thread>
#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class session
	: public std::enable_shared_from_this<session>
{
public:
	session(tcp::socket);
	void start();
	void start(tcp::endpoint);

private:
	void do_read();
	void do_write();

	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
};
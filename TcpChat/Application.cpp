#include "NetworkEntity.h"
#include "Connecter.h"
#include "Hoster.h"


int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_context io_context;
		if (argc > 3)
		{
			return 1;
		}
		if (argc == 3)
		{
			Connecter ne(io_context, argv[1], argv[2]);
			io_context.run();
		}
		if (argc == 2)
		{
			Hoster ne(io_context, argv[1]);
			io_context.run();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
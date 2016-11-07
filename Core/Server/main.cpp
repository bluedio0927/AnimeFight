#include "Server.h"
#include "iostream"
#include <list>
#include <boost/asio.hpp>
using namespace AnimeFight;

int main(int argc, char* argv[])
{
	try {
		if (argc < 2) {
			std::cerr << "Usage: chat_server <port> [<port> ...]\n";
			return 1;
		}

		boost::asio::io_service io_service;
		std::cout << "Server Start....";
		std::list<Server> servers;
		for (int i = 1; i < argc; ++i) {
			boost::asio::ip::tcp::endpoint endpoint(
			    boost::asio::ip::tcp::v4(), std::atoi(argv[i]));
			std::cout << std::atoi(argv[i]) << " ";
			servers.emplace_back(io_service, endpoint);
		}
		std::cout << "\n";
		io_service.run();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	std::cerr << "End\n";
	return 0;
}

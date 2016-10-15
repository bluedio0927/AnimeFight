#include "Client.h"
#include <iostream>
#include <boost/thread.hpp>

using namespace AnimeFight;

int main(int argc, char* argv[])
{
	try {
		if (argc != 3) {
			std::cerr << "Usage: chat_client <host> <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		boost::asio::ip::tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
		Client c(io_service, endpoint_iterator);

		boost::thread t([&io_service]() {
			io_service.run();
		});

		char line[Command::max_command_length + 1];
		while (std::cin.getline(line, Command::max_command_length + 1)) {
			Command command;
			command.Contentlength(std::strlen(line));
			std::memcpy(command.Content(), line, std::strlen(line));
			command.encode();
			c.write(command);
		}

		c.close();
		t.join();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

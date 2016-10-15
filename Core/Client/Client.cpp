#include "Client.h"
#include <iostream>
namespace AnimeFight
{
Client::Client(boost::asio::io_service& io_service,
               boost::asio::ip::tcp::resolver::iterator endpoint_iterator):
	io_service_(io_service),
	socket_(io_service)
{
	connect(endpoint_iterator);
}
void Client::write(const Command& command)
{
	io_service_.post(
	[this, command]() {
		bool write_in_progress = !CommandQueue.empty();
		CommandQueue.push_back(command);
		if (!write_in_progress) {
			_write();
		}
	}
	);
}
void Client::close() {}
void Client::connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	boost::asio::async_connect(socket_, endpoint_iterator,
	[this](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator) {
		if (!ec) {
			_readHeader();
		}
	}
	                          );
}
void Client::_readHeader()
{
	boost::asio::async_read(socket_,
	                        boost::asio::buffer(inCommand.Raw(), Command::header_length),
	[this](boost::system::error_code ec, std::size_t) {
		if (!ec && inCommand.decode()) {
			_readContent();
		} else {
			socket_.close();
		}

	});
}
void Client::_readContent()
{
	boost::asio::async_read(socket_,
	                        boost::asio::buffer(inCommand.Content(), inCommand.Contentlength()),
	[this](boost::system::error_code ec, std::size_t) {
		if (!ec) {
			std::cout << "G: ";
			std::cout.write(inCommand.Content(), inCommand.Contentlength());
			std::cout << "\n";
			_readHeader();
		} else {
			socket_.close();
		}

	});
}
void Client::_write()
{
	std::cout << "S: " << CommandQueue.front().Content() << "\n";
	boost::asio::async_write(socket_,
	                         boost::asio::buffer(CommandQueue.front().Raw(),
	                                 CommandQueue.front().Rawlength()),
	[this](boost::system::error_code ec, std::size_t) {
		if (!ec) {
			CommandQueue.pop_front();
			if (!CommandQueue.empty()) {
				_write();
			}
		} else {
			socket_.close();
		}
	});
}
}

#include "Session.h"
#include <iostream>
namespace AnimeFight
{
Session::Session(boost::asio::ip::tcp::socket socket, Room& room):
	socket_(std::move(socket)),
	room_(room)
{
}
void Session::start()
{
	room_.join(shared_from_this());
	readHeader();
}
void Session::deliver(const Command& command)
{
	bool write_in_progress = !CommandQueue.empty();
	CommandQueue.push_back(command);
	if (!write_in_progress) {
		write();
	}
}
void Session::readHeader()
{
	auto self(shared_from_this());
	boost::asio::async_read(socket_,
	                        boost::asio::buffer(inCommand.Raw(), Command::header_length),
	[this, self](boost::system::error_code ec, std::size_t) {
		if (!ec && inCommand.decode()) {
			readContent();
		} else {
			room_.leave(shared_from_this());
		}
	});
}
void Session::readContent()
{
	std::cout << " From: ";
	std::cout << socket_.remote_endpoint().address().to_string() << ": ";
	auto self(shared_from_this());
	boost::asio::async_read(socket_,
	                        boost::asio::buffer(inCommand.Content(), inCommand.Contentlength()),
	[this, self](boost::system::error_code ec, std::size_t) {
		if (!ec) {
			std::cout  << inCommand.Raw() << "\n";
			room_.deliver(inCommand);
			readHeader();
		} else {
			room_.leave(shared_from_this());
		}
	});
}
void Session::write()
{
	auto self(shared_from_this());
	std::cout <<  " To: ";
	std::cout << socket_.remote_endpoint().address().to_string() << ": ";
	std::cout << CommandQueue.front().Content() << "\n";
	boost::asio::async_write(socket_,
	                         boost::asio::buffer(CommandQueue.front().Raw(),
	                                 CommandQueue.front().Rawlength()),
	[this, self](boost::system::error_code ec, std::size_t) {
		if (!ec) {
			CommandQueue.pop_front();
			if (!CommandQueue.empty()) {
				write();
			}
		} else {
			room_.leave(shared_from_this());
		}
	});
}
}

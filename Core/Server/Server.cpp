#include "Server.h"
#include <iostream>
namespace AnimeFight
{
Server::
Server(boost::asio::io_service& io_service,
       const boost::asio::ip::tcp::endpoint& endpoint):
	acceptor_(io_service, endpoint),
	socket_(io_service)
{
	accept();
}
void Server::accept()
{
	acceptor_.async_accept(socket_,
	[this](boost::system::error_code ec) {
		if (!ec) {
			std::make_shared<Session>(std::move(socket_), room_)->start();
		}
		accept();
	});
}
}

#pragma once
#include <boost/asio.hpp>
#include "Session.h"
#include "Room.h"
namespace AnimeFight
{

class Server
{
public:
	Server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);

protected:
	void accept();
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;
	Room room_;
};
}


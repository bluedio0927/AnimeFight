#pragma once
#include <deque>
#include <boost/asio.hpp>
#include "Command.h"

namespace AnimeFight
{

typedef std::deque<Command> Command_queue;
class Client
{
public:
	Client(boost::asio::io_service& io_service,
	       boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
	void write(const Command& command);
	void close();

protected:
	void connect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
	void _readHeader();
	void _readContent();
	void _write();
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::socket socket_;
	Command inCommand;
	Command_queue CommandQueue;
};

}

#pragma once
#include "IPlayer.h"
#include "Command.h"
#include "Room.h"
#include <deque>

namespace AnimeFight
{

typedef std::deque<Command> Command_queue;
class Session : public IPlayer,
	public std::enable_shared_from_this<Session>
{
public:
	Session(boost::asio::ip::tcp::socket socket, Room& room);
	void start();
	void deliver(const Command& Command);
protected:
	void readHeader();
	void readContent();
	void write();
	boost::asio::ip::tcp::socket socket_;
	Room& room_;
	Command_queue CommandQueue;
	Command inCommand;
};
}

#pragma once

#include "IPlayer.h"
#include "Command.h"
#include <set>

namespace AnimeFight
{
class Room
{
public:
	void join(IPlayer_ptr player);
	void leave(IPlayer_ptr player);
	void deliver(const Command& command);
protected:
	std::set<IPlayer_ptr> players;
	enum { max_players = 4};
};
}

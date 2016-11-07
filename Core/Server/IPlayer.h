#pragma once

#include <boost/asio.hpp>
#include "Command.h"

namespace AnimeFight
{

class IPlayer
{
public:
	virtual ~IPlayer() {}
	virtual void deliver(const Command& Command) = 0;
};
typedef std::shared_ptr<IPlayer> IPlayer_ptr;
}

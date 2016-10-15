#include "Room.h"
#include <iostream>
namespace AnimeFight
{
void Room::join(IPlayer_ptr player)
{
	std::cout <<  __func__ << players.size() << "\n";
	if (max_players > players.size()) {
		players.insert(player);
	}
}
void Room::leave(IPlayer_ptr player)
{
	std::cout <<  __func__ << "\n";
	players.erase(player);
}
void Room::deliver(const Command& command)
{
	std::cout <<  __func__ << "\n";
	for (auto player : players) {
		player->deliver(command);
	}
}
}

#pragma once
#include "Room.h"

ClearRoom::ClearRoom(Player* PlayerPtr)
	:RoomBase(PlayerPtr)
{
	m_RoomType = "C";
	//std::cout << PlayerPtr << std::endl;
	//Wand* WandNew = new  Wand(1, 1, "Basic", 5, false);
	//m_WandLoot.push_back(WandNew);
}

std::string ClearRoom::GetEnter()
{

	return "You enter the room to find that there is nothing too important, it looks like someone else has been here. Maybe it was you?";
}

void ClearRoom::Main()
{
	std::cout << GetEnter() << std::endl;
	
}
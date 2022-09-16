#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Rooms/Room.h"

class World {
public:

	World(Player* PlayerPtr);
	void Main();


	void progress();


	enum m_DirectionEnum { Left = 'l', Right = 'r', Down = 'd' };
	enum m_RoomEnum { Clear, Enemy, Loot, Shop, Boss,
		RoomMAX
	};

private:


	Player* m_PlayerPtr;

	void GenWorld(int Layer);

	void PrintWorld();

	std::vector<std::vector<RoomBase*>> m_WorldVec;

};
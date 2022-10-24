#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Rooms/Room.h"
namespace Number {
	enum m_RoomEnumLetter {
		Clear = 'C', Enemy = 'E', Loot = 'L', Shop = 'S', Boss = 'B'
	};
}
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

	void NextLayer();

	Player* m_PlayerPtr;

	void GenWorld(int Layer);

	void PrintWorld();

	std::vector<std::vector<RoomBase*>> m_WorldVec;


	void PrintRoomType(char RoomType);

	void CheckPlayerDeath();
	int m_Layer = 1;
};
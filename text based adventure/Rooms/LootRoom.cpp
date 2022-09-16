#include "Room.h"


LootRoom::LootRoom(Player* PlayerPtr) 
	:RoomBase(PlayerPtr)
{
	m_RoomType = "L";
	m_Gold = rand() % (500);
	int NumberOfWands = rand() % (10);
	int NumberOfSpells = rand() % (10);
	for (int w = 0; w < NumberOfWands; w++)
	{
		Wand* WandRand = new Wand();
		m_WandLoot.push_back(WandRand);
	}
	for (int s = 0; s < NumberOfSpells; s++)
	{
		m_SpellLoot.push_back(GenRandSpell());
	}
}

std::string LootRoom::GetEnter()
{
	return "You enter the room to find that it is filled with chests, maybe theres stuff in them?";
}

void LootRoom::Main()
{
	std::cout << GetEnter() << std::endl;

}

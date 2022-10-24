#include "Room.h"


LootRoom::LootRoom(Player* PlayerPtr, int layer)
	:RoomBase(PlayerPtr, layer)
{
	m_RoomType = 'L';
	m_Gold = rand() % (rand() % (rand() % (5000 * m_Layer) + 1) + 1);
	int NumberOfWands = rand() % (10);
	int NumberOfSpells = rand() % (10);
	for (int w = 0; w < NumberOfWands; w++)
	{
		Wand* WandRand = new Wand((rand() % (m_Layer)) + 1 + (rand() % (m_PlayerPtr->m_Luck)));
		m_WandLoot.push_back(WandRand);
	}
	for (int s = 0; s < NumberOfSpells; s++)
	{
		m_SpellLoot.push_back(GenRandSpell((rand() % (m_Layer + 1)) + (rand() % (m_PlayerPtr->m_Luck))));
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

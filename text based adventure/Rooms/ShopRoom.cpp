#include "World.h"


ShopRoom::ShopRoom(Player* PlayerPtr, int layer)
	:RoomBase(PlayerPtr, layer)
{
	m_RoomType = 'S';
	// adds Wands to the room
	int NumberOfWands = (rand() % (rand() % (8) + 1)) + 1;
	for (int i = 0; i < NumberOfWands; i++)
	{
		int Cost = 10000 + 5000 * m_Layer;
		for (int i = 0; i < 10 - m_Layer; i++)
		{
			Cost = (rand() % (Cost + 1)) + 1;
		}
		Cost = Cost * 1000;
		Cost = rand() % (Cost);


		Wand* Wand1 = new Wand(floor((float)Cost / (float)1000) + 1);
		m_WandLoot.push_back(Wand1);
		Wand1->m_Cost = floor(Cost - ((floor((float)Cost / (float)2000) + 1) * (m_PlayerPtr->m_Luck - 1)));;
	}
	int NumberOfSpells = (rand() % (8)) + 1;
	try {
		for (int i = 0; i < NumberOfWands; i++)
		{

			int Cost = rand() % (10000);
			m_SpellLoot.push_back(GenRandSpell((floor((float)Cost / (float)1000) + 1)));
			m_SpellLoot[i]->Cost = floor(Cost - ((floor((float)Cost / (float)2000) + 1) * (m_PlayerPtr->m_Luck - 1)));
		}
	}
	catch (...)
	{
		std::cout << "dasdas" << std::endl;
	}

}

std::string ShopRoom::GetEnter()
{
	return "You enter the room to find that there is a shop keeper selling some wands and spells.";
}

void ShopRoom::Main()
{
	std::cout << GetEnter() << std::endl;

	while (m_IsShopping)
	{
		Shop();
	}
}

void ShopRoom::Shop()
{
	std::cout << "There are some spells and wands in the shop, would you like to look at them (y/n)" << std::endl;

	Globals::ChangeColour(Globals::yellow);
	std::cout << "You currnetly have " << m_PlayerPtr->m_Gold << " coins of gold." << std::endl;
	Globals::ChangeColour(Globals::white);


	PlayerLoot();// this also deals with the shop, I hope :)

	m_IsShopping = false;

}

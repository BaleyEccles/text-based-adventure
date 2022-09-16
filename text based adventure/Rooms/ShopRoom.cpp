#include "World.h"


ShopRoom::ShopRoom(Player* PlayerPtr)
	:RoomBase(PlayerPtr)
{
	m_RoomType = "S";
	// adds Wands to the room
	int NumberOfWands = (rand() % (8)) + 1;
	for (int i = 0; i < NumberOfWands; i++)
	{
		Wand* Wand1 = new Wand();
		m_WandLoot.push_back(Wand1);
		Wand1->m_Cost = rand() % (200);
	}
	int NumberOfSpells = (rand() % (8)) + 1;
	for (int i = 0; i < NumberOfWands; i++)
	{
		Spell* Spell1 = new Spell();
		m_SpellLoot.push_back(Spell1);
		Spell1->Cost = rand() % (100);
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
	std::cout << "There are some spells and wands in the shop, here they are:" << std::endl;
	PrintLoot();

	PlayerLoot();// this also deals with the shop, I hope :)
	char ContShop;

	do {
		std::cout << "Would you like to continue shopping? (y/n)" << std::endl;
		std::cin >> ContShop;
		switch (ContShop)
		{
		case Globals::YES: case Globals::yes:
			break;
		case Globals::NO: case Globals::no:
			m_IsShopping = false;
			break;
		default:
			std::cout << "Please input y or n " << std::endl;
			break;
		}
	} while (ISYESNO(ContShop));


}

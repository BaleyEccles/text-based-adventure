#include "Player.h"

Player::Player()
{
	// generate starting wands
	Wand* StartingWand = new Wand(1, 1, "Basic", 5, Wand::None);
	m_InventoryWands.push_back(StartingWand);
}

bool Player::IsInventoryFull(char Type)
{
	switch (Type)
	{
	case Wand::WAND: case Wand::wand:
		if (m_InventoryWands.size() == m_InventorySizeWands)
		{
			std::cout << "Your wand inventory is full, you currnetly have " << m_InventorySizeWands << " wand slots." << std::endl;
			return true;
		}
		else {
			return false;
		}
		break;
	case Wand::SPELL: case Wand::spell:
		if (m_InventorySpells.size() == m_InventorySizeSpells)
		{
			std::cout << "Your spell inventory is full, you currnetly have " << m_InventorySizeSpells << " spell slots." << std::endl;
			return true;
		}
		else {
			return false;
		}
		break;
	default:
		if (m_InventorySpells.size() == m_InventorySizeSpells && m_InventoryWands.size() == m_InventorySizeWands)
		{
			std::cout << "Your spell inventory is full, you currnetly have " << m_InventorySizeSpells << " spell slots." << std::endl;
			std::cout << "Your wand inventory is full, you currnetly have " << m_InventorySizeWands << " wand slots." << std::endl;
			
			return true;
		}
		else {
			return false;
		}
		break;
	}

}

void Player::PrintInventory(char Type)
{
	switch (Type)
	{
	case Wand::wand: case Wand::WAND:
		std::cout << "In your wand slots you have..." << std::endl;
		for (int i = 0; i < m_InventoryWands.size(); i++)
		{
			std::cout << "Wand " << i << std::endl;
			m_InventoryWands[i]->PrintData();
		}
		break;
	case Wand::spell: case Wand::SPELL:
		std::cout << "In your spell slots you have..." << std::endl;
		for (int i = 0; i < m_InventorySpells.size(); i++)
		{
			std::cout << "Spell " << i << std::endl;
			std::cout << "Type: " << m_InventorySpells[i]->Type << std::endl;
			std::cout << "Damage: " << m_InventorySpells[i]->Damage << std::endl;
		}
		break;
	default:
		std::cout << "You currnetly have " << m_InventorySizeWands << " wand slots." << std::endl;
		std::cout << "You currnetly have " << m_InventorySizeSpells << " spell slots." << std::endl;

		std::cout << "In your wand slots you have..." << std::endl;
		for (int i = 0; i < m_InventoryWands.size(); i++)
		{
			std::cout << "Wand " << i << std::endl;
			m_InventoryWands[i]->PrintData();
		}
		std::cout << "In your spell slots you have..." << std::endl;
		for (int i = 0; i < m_InventorySpells.size(); i++)
		{
			std::cout << "Spell " << i << std::endl;
			std::cout << "Type: " << m_InventorySpells[i]->Type << std::endl;
			std::cout << "Damage: " << m_InventorySpells[i]->Damage << std::endl;
		}
		std::cout << "You currnetly have " << m_Gold << " coins of gold." << std::endl;
		break;
	}
	
}

void Player::ManageInventory()
{
	std::cout << "What would you like to do?\n You can:" << std::endl;
	std::cout << "1: Drop things." << std::endl;
	std::cout << "2: Move your obtained spells to your wands." << std::endl;
	std::cout << "3: Move the spells in your wands to your inventory." << std::endl;
	int NumberOfActions = 3;
	int ToDo;
	do {
		std::cin >> ToDo;
		switch (ToDo)
		{
		case 1:
			std::cout << "WARNING THE ITEMS YOU DROP WILL BE DESTROYED!!!" << std::endl;
			DropItems();
			break;
		case 2:
			SpellToWand();// TODO 
			break;
		case 3:
			WandToSpell();// TODO 
			break;
		default:
			std::cout << "Please input the desired action." << std::endl;
			break;
		}
	} while (ToDo > NumberOfActions);

}

void Player::DropItems()
{

	char ToDrop;
	do {
		std::cout << "Input the type of item you would like to drop (Wand: w | Spell: s)" << std::endl;
		std::cin >> ToDrop;
		switch (ToDrop)
		{
		case Wand::WAND: case Wand::wand:
			DropWands();
			break;
		case Wand::SPELL: case Wand::spell:
			DropSpells();
			break;
		default:
			std::cout << "Please input for wand: w or for spell: s" << std::endl;
			break;
		}
	} while (ToDrop != Wand::SPELL && ToDrop != Wand::spell && ToDrop != Wand::WAND && ToDrop != Wand::wand);
}

void Player::DropWands()
{
	int NumberToDrop;
	bool IsValidNumber = true;
	std::cout << "Input the number of the wand you would like to drop. (-1 to cancel)" << std::endl;
	do {

		std::cin >> NumberToDrop;
		if (NumberToDrop != -1)
		{

			if (NumberToDrop >= 0 && NumberToDrop <= m_InventoryWands.size())
			{
				m_InventoryWands.erase(m_InventoryWands.begin() + NumberToDrop);

				IsValidNumber = true;
			}
			else {
				std::cout << "Input the number of wand you would like to drop. (-1 to cancel)" << std::endl;
				IsValidNumber = false;
			}
		}

		
	} while (!IsValidNumber);
}

void Player::DropSpells()
{
	int NumberToDrop;
	bool IsValidNumber = true;
	std::cout << "Input the number of the spell you would like to drop. (-1 to cancel)" << std::endl;
	do {

		std::cin >> NumberToDrop;
		if (NumberToDrop != -1)
		{
			if (NumberToDrop >= 0 && NumberToDrop <= m_InventorySpells.size())
			{
				m_InventorySpells.erase(m_InventorySpells.begin() + NumberToDrop);

				IsValidNumber = true;
			}
			else {
				std::cout << "Input the number of spell you would like to drop. (-1 to cancel)" << std::endl;
				IsValidNumber = false;
			}
		}

	} while (!IsValidNumber);
}

void Player::SpellToWand()
{
}

void Player::WandToSpell()
{
}

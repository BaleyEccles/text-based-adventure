#include "Player.h"

Player::Player()
{
	// generate starting wands
	Wand* StartingWand = new Wand(1, 1, 1, "Basic", 5, Wand::None);
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
			Globals::PrintLine(Globals::red);
			std::cout << "Wand " << i << std::endl;
			m_InventoryWands[i]->PrintData();
		}
		break;
	case Wand::spell: case Wand::SPELL:
		std::cout << "In your spell slots you have..." << std::endl;
		for (int i = 0; i < m_InventorySpells.size(); i++)
		{
			Globals::PrintLine(Globals::blue);
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
			Globals::PrintLine(Globals::red);
			std::cout << "Wand " << i << std::endl;
			m_InventoryWands[i]->PrintData();
		}
		std::cout << "In your spell slots you have..." << std::endl;
		for (int i = 0; i < m_InventorySpells.size(); i++)
		{
			Globals::PrintLine(Globals::blue);
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
			SpellToWand();
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
		case 'c': case 'C':
			break;
		default:
			std::cout << "Please input for wand: w or for spell: s" << std::endl;
			break;
		}
	} while (ToDrop != Wand::SPELL && ToDrop != Wand::spell && ToDrop != Wand::WAND && ToDrop != Wand::wand && ToDrop != 'c' && ToDrop != 'C');
}

void Player::DropWands()
{
	int NumberToDrop;
	bool IsValidNumber = true;
	std::cout << "Input the number of the wand you would like to drop. (-1 to cancel)" << std::endl;
	do {
		PrintInventory(Wand::WandEnum::WAND);
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
		PrintInventory(Wand::WandEnum::SPELL);

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
	PrintInventory(Wand::SPELL);
	int NumberToMove;
	bool IsValidNumber = true;
	int NumberToUse;
	bool IsValidNumber2 = true;
	do {
		std::cout << "Which spell would you like to move? (-1 to cancel)" << std::endl;
		std::cin >> NumberToMove;
		if (NumberToMove != -1)
		{
			if (NumberToMove >= 0 && NumberToMove <= m_InventorySpells.size())
			{

				do {
					PrintInventory(Wand::WAND);

					std::cout << "Which wand would you like to move the spell to? (-1 to cancel)" << std::endl;

					std::cin >> NumberToUse;
					if (NumberToUse != -1)
					{
						if (NumberToUse >= 0 && NumberToUse <= m_InventoryWands.size())
						{
							if (m_InventoryWands[NumberToUse]->m_WandInv->Size == m_InventoryWands[NumberToUse]->m_WandInv->Spells.size())
							{
								std::cout << "This wand has no more spare slots, please choose a different wand." << std::endl;
								IsValidNumber2 = false;
							}
							else {
								m_InventoryWands[NumberToUse]->m_WandInv->Spells.push_back(m_InventorySpells[NumberToMove]);
								m_InventorySpells.erase(m_InventorySpells.begin() + NumberToMove);
								IsValidNumber2 = true;
							}
						}
						else {
							std::cout << "Which wand would you like to move the spell to? (-1 to cancel)" << std::endl;
							IsValidNumber2 = false;
						}
					}
					else {
						IsValidNumber2 = true;
					}

				} while (!IsValidNumber2);

				IsValidNumber = true;
			}
			else {
				std::cout << "Input the number of spell you would like to move. (-1 to cancel)" << std::endl;
				IsValidNumber = false;
			}
		}
		else {
			IsValidNumber = true;
		}

	} while (!IsValidNumber);
}

void Player::WandToSpell()
{
	PrintInventory(Wand::WAND);
	int NumberToMove;
	bool IsValidNumber = true;
	int NumberToUse;
	bool IsValidNumber2 = true;
	do {
		std::cout << "Which wand would you like to remove a spell from? (-1 to cancel)" << std::endl;
		std::cin >> NumberToMove;
		if (NumberToMove != -1)
		{
			if (NumberToMove >= 0 && NumberToMove <= m_InventoryWands.size())
			{

				do {
					m_InventoryWands[NumberToMove]->PrintData();

					std::cout << "Which spell would you like to remove? (-1 to cancel)" << std::endl;

					std::cin >> NumberToUse;
					if (NumberToUse != -1)
					{
						if (NumberToUse >= 0 && NumberToUse <= m_InventorySpells.size())
						{

							m_InventorySpells.push_back(m_InventoryWands[NumberToMove]->m_WandInv->Spells[NumberToUse]);
							m_InventoryWands[NumberToMove]->m_WandInv->Spells.erase(m_InventoryWands[NumberToMove]->m_WandInv->Spells.begin() + NumberToUse);


							IsValidNumber2 = true;
							

						}
						else {
							std::cout << "Which spell would you like to remove? (-1 to cancel)" << std::endl;
							IsValidNumber2 = false;
						}
					}
					else {
						IsValidNumber2 = true;
					}

				} while (!IsValidNumber2);

				IsValidNumber = true;
			}
			else {
				std::cout << "Which wand would you like to remove a spell from? (-1 to cancel)" << std::endl;
				IsValidNumber = false;
			}
		}
		else {
			IsValidNumber = true;
		}

	} while (!IsValidNumber);
}

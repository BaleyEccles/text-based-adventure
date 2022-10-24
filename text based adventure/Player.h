#pragma once
#include "Wands.h"

class Player
{
public:
	Player();

	bool IsInventoryFull(char Type = 'b');

	int m_XPos = 0;
	int m_YPos = 0;
	unsigned int m_InventorySizeWands = 5;
	unsigned int m_InventorySizeSpells = 5;
	std::vector<Wand*> m_InventoryWands;	
	std::vector<Spell*> m_InventorySpells;

	void PrintInventory(char Type = 'b');
	void ManageInventory();

	int m_Health = 50;
	int m_Gold = 0;

	int m_SightLenght = 2;

	int m_Luck = 1;

private:

	void DropItems();
	void DropWands();
	void DropSpells();

	void SpellToWand();
	void WandToSpell();
};
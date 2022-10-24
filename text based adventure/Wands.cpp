#include "Wands.h"


Wand::Wand(int Strength,int Size, int CoolDown, std::string Type, int Damage, int WandAtribute)
{
	WandData* WandInv = new WandData();
	m_WandInv = WandInv;
	m_WandAtributesNames.push_back(std::string("None"));
	m_WandAtributesNames.push_back(std::string("Area of Effect"));
	m_WandAtributesNames.push_back(std::string("Fire"));
	m_WandAtributesNames.push_back(std::string("Ice"));

	// generate random wand
	if (Size == 0 && CoolDown == -1 && Type == "" && Damage == 0 && WandAtribute == None)
	{
		m_WandInv = GenRandomWand(Strength);
	}
	else {
		Spell* GenSpell = new Spell();
		GenSpell->Type = Type;
		GenSpell->Damage = Damage;
		m_WandInv->CoolDown = CoolDown;
		m_WandInv->Size = Size;
		m_WandInv->WandAtribute = WandAtribute;
		m_WandInv->Spells.push_back(GenSpell);
	}

}

void Wand::PrintData()
{
	std::cout << "Size: " << m_WandInv->Size << std::endl;
	std::cout << "Cool down: " << m_WandInv->CoolDown << std::endl;
	if (m_WandInv->WandAtribute != None)
	{
		Globals::ChangeColour(Globals::green);
		std::cout << "Unique atribute: " << m_WandAtributesNames[m_WandInv->WandAtribute] << std::endl;
		Globals::ChangeColour(Globals::white);
	}

	if (m_WandInv->Spells.size() != 0)
	{
		std::cout << "Here are the spells in this wand" << std::endl;
		for (int p = 0; p < m_WandInv->Spells.size(); p++)
		{
			Globals::PrintLine(Globals::pink);
			std::cout << "spell " << p << std::endl;
			std::cout << "Type: " << m_WandInv->Spells[p]->Type << std::endl;
			std::cout << "Damage: " << m_WandInv->Spells[p]->Damage << std::endl;
		}
	}
	else {
		std::cout << "There are no spells in this wand." << std::endl;
	}
	if (m_Cost != 0)
	{
		Globals::ChangeColour(Globals::yellow);
		std::cout << "This wand costs " << m_Cost << " gold coins." << std::endl;
		Globals::ChangeColour(Globals::white);
	}

}

int Wand::GetDamage(int Luck)
{
	int DamageReturn = 0;
	for (int i = 0; i < m_WandInv->Spells.size(); i++)
	{
		if (m_WandInv->Spells[i]->Damage != 0)
		{
			DamageReturn += rand() % (m_WandInv->Spells[i]->Damage) + (Luck-1) * rand() % (Luck);
		}
	};
	return DamageReturn;
}

WandData* Wand::GenRandomWand(int Strenght)
{
	if (Strenght <= 0)
	{
		Strenght = 1;
	}
	WandData* RandWand = new WandData();
	RandWand->Size = rand() % (10 + (Strenght * 2));

	RandWand->CoolDown = rand() % (5 + (Strenght * 2));
	RandWand->WandAtribute = None;
	for (int i = 0; i < Strenght; i ++)
	{
		if (rand() % (8) == 4)
		{
			RandWand->WandAtribute = rand() % (AtribMAX - 1);
			break;
		}
	}

	for (int s = 0; s < RandWand->Size; s++)
	{
		for (int i = 0; i < Strenght; i++)
		{
			if (rand() % (8) == 4)
			{
				Spell* SpellNum = new Spell;
				SpellNum->Damage = rand() % (10 * Strenght);
				SpellNum->Type = "Random " + std::to_string(Strenght);
				RandWand->Spells.push_back(SpellNum);
				break;
			}
		}
	}

	return RandWand;
}

Spell* GenRandSpell(int Strenght)
{
	if (Strenght <= 0)
	{
		Strenght = 1;
	}
	Spell* RandSpell = new Spell();
	RandSpell->Damage = rand() % (10 * Strenght);
	RandSpell->Type = "Random " + std::to_string(Strenght);
	return RandSpell;
}
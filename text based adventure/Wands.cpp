#include "Wands.h"


Wand::Wand(int Size, int CoolDown, std::string Type, int Damage, int WandAtribute)
{

	m_WandAtributesNames.push_back(std::string("None"));
	m_WandAtributesNames.push_back(std::string("Area of Effect"));
	m_WandAtributesNames.push_back(std::string("Fire"));
	m_WandAtributesNames.push_back(std::string("Ice"));

	// generate random wand
	if (Size == 0 && CoolDown == -1 && Type == "" && Damage == 0 && WandAtribute == None)
	{
		WandInv = GenRandomWand();
	}
	else {
		Spell* GenSpell = new Spell;
		GenSpell->Type = Type;
		GenSpell->Damage = Damage;
		WandInv.CoolDown = CoolDown;
		WandInv.Size = Size;
		WandInv.WandAtribute = WandAtribute;
		WandInv.Spells.push_back(GenSpell);
	}

}

void Wand::PrintData()
{


	std::cout << "Here are the wand specifications: " << std::endl; 
	std::cout << "Size: " << WandInv.Size << std::endl;
	std::cout << "Cool down: " << WandInv.CoolDown << std::endl;
	if (WandInv.WandAtribute != None)
	{
		Globals::ChangeColour(Globals::green);
		std::cout << "Unique atribute: " << m_WandAtributesNames[WandInv.WandAtribute] << std::endl;
		Globals::ChangeColour(Globals::white);
	}

	std::cout << "Here are the spells in this wand" << std::endl;
	for (int p = 0; p < WandInv.Spells.size(); p++)
	{
		std::cout << "spell " << p << std::endl;
		std::cout << "Type: " << WandInv.Spells[p]->Type << std::endl;
		std::cout << "Damage: " << WandInv.Spells[p]->Damage << std::endl;
	}
	if (m_Cost != 0)
	{

		Globals::ChangeColour(Globals::yellow);
		std::cout << "This wand costs" << m_Cost << " gold coins." << std::endl;
		Globals::ChangeColour(Globals::white);
	}
}

int Wand::GetDamage()
{
	int DamageReturn = 0;
	for (int i = 0; i < WandInv.Spells.size(); i++)
	{
		DamageReturn += WandInv.Spells[i]->Damage;
	};
	return DamageReturn;
}

WandData Wand::GenRandomWand()
{
	WandData RandWand;
	RandWand.Size = rand() % (15);

	RandWand.CoolDown = rand() % (5);
	RandWand.WandAtribute = None;
	if (rand() % (8) == 4)
	{
		RandWand.WandAtribute = rand() % (AtribMAX - 1);
	}


	for (int s = 0; s < RandWand.Size; s++)
	{
		if (rand() % (8) == 4)
		{
			Spell* SpellNum = new Spell;
			SpellNum->Damage = rand() % (20);
			SpellNum->Type = "Random";
			RandWand.Spells.push_back(SpellNum);

		}
	}

	return RandWand;
}

Spell* GenRandSpell()
{
	Spell* RandSpell = new Spell();
	RandSpell->Damage = rand() % (10);
	RandSpell->Type = "Random";
	return RandSpell;
}

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Globals.h"


struct Spell
{
	std::string Type;
	int Damage;
	int Cost = 0;
};

Spell* GenRandSpell();


struct WandData
{
	int Size;
	int CoolDown;
	int WandAtribute;
	std::vector<Spell*> Spells;

};





class Wand
{
public:

	Wand(int Size = 0, int CoolDown = -1, std::string Type = "", int Damage = 0, int WandAtribute = None);
	//int DealDamage();

	void PrintData();

	WandData WandInv;

	enum WandEnum
	{
		WAND = 'W', wand = 'w', SPELL = 'S', spell = 's', gold = 'g', GOLD = 'G'
	};

	enum WandAtributes
	{
		None, AOE, Fire, Ice, 

		AtribMAX
	};

	std::vector<std::string> m_WandAtributesNames;

	int GetDamage();
	
	int m_Cost = 0;

private:


	WandData GenRandomWand();


};

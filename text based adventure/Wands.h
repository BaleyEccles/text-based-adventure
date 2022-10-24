#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Globals.h"


struct Spell
{
	std::string Type = "NULL";
	int Damage = 0;
	int Cost = 0;
};

Spell* GenRandSpell(int Strenght = 1);


struct WandData
{
	int Size = 0;
	int CoolDown = 0;
	int WandAtribute = 0;
	std::vector<Spell*> Spells;

};





class Wand
{
public:

	Wand(int Strength = 1, int Size = 0, int CoolDown = -1, std::string Type = "", int Damage = 0, int WandAtribute = None);
	//int DealDamage();

	void PrintData();

	WandData* m_WandInv = 0;

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

	int GetDamage(int Luck);
	
	int m_Cost = 0;

	int m_CoolDownLeft = 0;

private:


	WandData* GenRandomWand(int Strenght = 1);


};

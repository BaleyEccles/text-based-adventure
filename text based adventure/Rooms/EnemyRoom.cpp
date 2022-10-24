#pragma once 
#include "Room.h"


EnemyRoom::EnemyRoom(Player* PlayerPtr, int layer)
	:RoomBase(PlayerPtr, layer)
{
	m_RoomType = 'E';
	// adds enemies to the room

	int NumberOfEnemies = 300 + 50 * m_Layer;
	for (int i = 0; i < 10 - m_Layer; i++)
	{
		NumberOfEnemies = (rand() % (NumberOfEnemies + 1)) + 1;
	}
	if(NumberOfEnemies > 4)
	{
		NumberOfEnemies -= 3;
	}

	for(int i = 0; i < NumberOfEnemies; i++)
	{
		int RoomNumber = rand() % (EnemyBase::EnemiesEnum::EnemyMAX);
		if (RoomNumber != 0)
		{
			if (rand() % 3 == 2)
			{
				RoomNumber -= 1;
			}
		}

		switch (RoomNumber)
		{
		case EnemyBase::EnemiesEnum::Easy:
		{
			EasyEnemy* EasyEnemyPtr1 = new EasyEnemy(m_Layer);
			m_EnemyVec.push_back(EasyEnemyPtr1);
			break;
		}

		case EnemyBase::EnemiesEnum::Medium:
		{
			MedEnemy* MediumEnemyPtr1 = new MedEnemy(m_Layer);
			m_EnemyVec.push_back(MediumEnemyPtr1);
			break;
		}

		case EnemyBase::EnemiesEnum::Hard:
		{
			HardEnemy* HardEnemyPtr1 = new HardEnemy(m_Layer);
			m_EnemyVec.push_back(HardEnemyPtr1);
			break;

		}

		default:
		{
			EasyEnemy* EasyEnemyPtr2 = new EasyEnemy(m_Layer);
			m_EnemyVec.push_back(EasyEnemyPtr2);
			break;
		}
		}
		

	}
	m_Gold = rand() % (NumberOfEnemies * 100 + 1) * m_Layer;

}

std::string EnemyRoom::GetEnter()
{
	GetEnemiesAlive();
	switch (m_EnemiesAlive)
	{
	case 0:
		return "You enter the room to see " + std::to_string(m_EnemyVec.size()) + " dead creatures in the room";
		break;
	default:
		return "You enter the room to find that there are " + std::to_string(m_EnemiesAlive) + " aggressive creatures in the room.\n Theres no turning back, you must fight them.";
		break;
	}
}

void EnemyRoom::Main()
{
	std::cout << GetEnter() << std::endl;
	while (m_EnemiesAlive != 0)
	{
		GetEnemiesAlive();
		FightEnemies();
	}
	AddExtraPlayerStats();
}

void EnemyRoom::FightEnemies()
{
	if (m_EnemyVec.size() != 0)
	{
		int DamageToDeal;
		int WandNumberUse;
		GetWandAndDamage(DamageToDeal, WandNumberUse);
		
		PrintEnemies();

		TargetEnemy(DamageToDeal, WandNumberUse);
		
		// Enemies deal damage to player.
		DealDamageToPlayer();
		
	}

	//Prints players health
	Globals::ChangeColour(Globals::green);
	std::cout << "You currently have " << m_PlayerPtr->m_Health << " points of health" << std::endl;
	Globals::ChangeColour(Globals::white);
	CheckPlayerDeath();
}

void EnemyRoom::GetEnemiesAlive()
{
	m_EnemiesAlive = 0;
	for (int e = 0; e < m_EnemyVec.size(); e++)
	{
		if (m_EnemyVec[e]->m_IsDead == false)
		{
			m_EnemiesAlive += 1;
		}
	}

}

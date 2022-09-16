#pragma once 
#include "Room.h"


EnemyRoom::EnemyRoom(Player* PlayerPtr)
	:RoomBase(PlayerPtr)
{
	m_RoomType = "E";
	m_Gold = rand() % (100);
	// adds enemies to the room
	for(int i = 0; i < 2; i++)
	{
		int RoomNumber = rand() % (EnemyBase::EnemiesEnum::EnemyMAX - 1);
		switch (RoomNumber)
		{
		case EnemyBase::EnemiesEnum::Easy:
		{
			EasyEnemy* EasyEnemyPtr1 = new EasyEnemy();
			m_EnemyVec.push_back(EasyEnemyPtr1);
			break;
		}
			/*
		case EnemyBase::EnemiesEnum::Medium:
			MediumEnemy* MediumEnemyPtr1 = new MediumEnemy();
			m_EnemyVec.push_back(MediumEnemyPtr1);
			m_EnemyNumber += 1;
			break;
			*/
		default:
		{
			EasyEnemy* EasyEnemyPtr2 = new EasyEnemy();
			m_EnemyVec.push_back(EasyEnemyPtr2);
			break;
		}
		}
		

	}

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
		std::cout << "The creatures are still alive!!!" << std::endl;
		FightEnemies();
	}
}

void EnemyRoom::FightEnemies()
{
	int DamageToDeal;


	std::cout << "Which wand would you like to use?" << std::endl;
	m_PlayerPtr->PrintInventory(Wand::wand);
	int WandNumberUse;
	{
		bool IsValidNumber = true;
		std::cout << "Input the number of the wand you would like to use." << std::endl;
		// Gets the ammount of damage to deal to the enemy.
		do {

			Globals::InputNumber(WandNumberUse);

			if (WandNumberUse >= 0 && WandNumberUse <= m_PlayerPtr->m_InventoryWands.size())
			{
				DamageToDeal = m_PlayerPtr->m_InventoryWands[WandNumberUse]->GetDamage();
				IsValidNumber = true;
			}
			else {
				std::cout << "Input the number of the wand you would like to use." << std::endl;
				IsValidNumber = false;
			}

		} while (!IsValidNumber);
	}
	std::cout << "Here are the enemies in the room." << std::endl;
	for (int e = 0; e < m_EnemyVec.size(); e++)
	{
		std::cout << "Enemy " << std::to_string(e) << ":" << std::endl;
		m_EnemyVec[e]->PrintData();
	}

	std::cout << "Which enemy would you like to target?" << std::endl;

	Globals::ChangeColour(Globals::green);
	int Target;
	{
		bool IsValidNumber = true;
		do {

			Globals::InputNumber(Target);

			if (Target >= 0 && Target <= m_EnemyVec.size())
			{
				//Deal Damage
				// Can add switch to deal AOE/ fire/ ice damage
				m_EnemyVec[Target]->m_Health -= DamageToDeal;
				if (m_EnemyVec[Target]->m_Health <= 0)
				{
					m_EnemyVec[Target]->m_IsDead = true;
				}
				std::cout << "You deal " << DamageToDeal << " points of damage to ememy " << Target << "." << std::endl;
				IsValidNumber = true;
			}
			else {
				std::cout << "Input the number of the enemy you would like to attack." << std::endl;
				IsValidNumber = false;
			}
		} while (!IsValidNumber);
	}
	Globals::ChangeColour(Globals::white);

	// Enemies deal damage to player.
	Globals::ChangeColour(Globals::red);
	for (int e = 0; e < m_EnemyVec.size(); e++)
	{
		if (m_EnemyVec[e]->m_IsDead == false)
		{
			int DamageFromEnemy = m_EnemyVec[e]->GetDamage();
			m_PlayerPtr->m_Health -= DamageFromEnemy;
			std::cout << "You take " << DamageFromEnemy << " points of damage from enemy " << e << "." << std::endl;
		}
	}
	Globals::ChangeColour(Globals::white);

	//Prints players health
	Globals::ChangeColour(Globals::green);
	std::cout << "You currently have " << m_PlayerPtr->m_Health << " points of health" << std::endl;
	Globals::ChangeColour(Globals::white);


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

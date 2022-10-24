#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Globals.h"
#include "Player.h"
#include "Enemies/Enemies.h"





class RoomBase {
public:
	RoomBase(Player* PlayerPtr, int layer);

	virtual std::string GetEnter();
	virtual void Main();

	bool m_PlayerIsInRoom = true;
	void CheckLeave();
	std::vector<Spell*> m_SpellLoot;
	std::vector<Wand*> m_WandLoot;
	void PrintLoot(char Type = 'B');
	void PlayerLoot();
	Player* m_PlayerPtr;
	int m_Gold = 0;
	char m_RoomType;
	std::vector<EnemyBase*> m_EnemyVec;

	void TargetEnemy(int& DamageToDeal, int& WandNo);
	void CheckPlayerDeath();
	bool m_PlayerHasSeen = false;
	void PrintEnemies();
	void DealDamageToPlayer();
	void GetWandAndDamage(int& DamageToDeal, int& WandNumberUse);



	void DealAOE(int& DamageToDeal);
	void DealFire(int& DamageToDeal, int &Target);
	void DealIce(int& DamageToDeal, int &Target);

	void AddExtraPlayerStats();


	bool m_PlayerHasBeenInRoom = false;

	int m_Layer = -1;
};

class ClearRoom : public RoomBase {
public:
	ClearRoom(Player* PlayerPtr, int layer);

	std::string GetEnter() override;
	void Main() override;

};


class EnemyRoom : public RoomBase {
public:
	EnemyRoom(Player* PlayerPtr, int layer);

	std::string GetEnter() override;
	void Main() override;
	void FightEnemies();
	unsigned int m_EnemiesAlive = 0;
	void GetEnemiesAlive();
};

class LootRoom : public RoomBase {
public:
	LootRoom(Player* PlayerPtr, int layer);

	std::string GetEnter() override;
	void Main() override;


};

class ShopRoom : public RoomBase {
public:
	ShopRoom(Player* PlayerPtr, int layer);

	std::string GetEnter() override;
	void Main() override;
	bool m_IsShopping = true;
	void Shop();
};


class BossRoom : public RoomBase {
public:
	BossRoom(Player* PlayerPtr, int layer);

	std::string GetEnter() override;
	void Main() override;
	void FightEnemies();
	unsigned int m_EnemiesAlive = 0;
	void GetEnemiesAlive();

};
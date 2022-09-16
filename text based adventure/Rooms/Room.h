#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Globals.h"
#include "Player.h"
#include "Enemies/Enemies.h"

class RoomBase {
public:
	RoomBase(Player* PlayerPtr);

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
	std::string m_RoomType;

};

class ClearRoom : public RoomBase {
public:
	ClearRoom(Player* PlayerPtr);

	std::string GetEnter() override;
	void Main() override;

};


class EnemyRoom : public RoomBase {
public:
	EnemyRoom(Player* PlayerPtr);

	std::string GetEnter() override;
	void Main() override;
	void FightEnemies();
	std::vector<EnemyBase*> m_EnemyVec;
	unsigned int m_EnemiesAlive = 0;
	void GetEnemiesAlive();
};

class LootRoom : public RoomBase {
public:
	LootRoom(Player* PlayerPtr);

	std::string GetEnter() override;
	void Main() override;


};

class ShopRoom : public RoomBase {
public:
	ShopRoom(Player* PlayerPtr);

	std::string GetEnter() override;
	void Main() override;
	bool m_IsShopping = true;
	void Shop();
};
/*

class BossRoom : public RoomBase {
public:
	BossRoom();

	std::string GetEnter() override;
	void Main() override;


};*/
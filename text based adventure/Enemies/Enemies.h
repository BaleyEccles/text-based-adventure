#pragma once
#include <iostream>
#include "Globals.h"

class EnemyBase {
public:
	EnemyBase(int Layer);


	virtual int GetDamage();

	void PrintData();
	int m_Health;
	int m_Damage;

	bool m_IsDead = false;

	int m_Fire = 0;
	int m_Ice = 0;

	enum EnemiesEnum
	{
		Easy, Medium, Hard, Boss,

		EnemyMAX
	};
	int m_Layer = 0;
};


class EasyEnemy : public EnemyBase {
public:

	EasyEnemy(int Layer);
	int GetDamage() override;

};

class MedEnemy : public EnemyBase {
public:

	MedEnemy(int Layer);
	int GetDamage() override;

};
class HardEnemy : public EnemyBase {
public:

	HardEnemy(int Layer);
	int GetDamage() override;

};
class BossEnemy : public EnemyBase {
public:

	BossEnemy(int Layer);
	int GetDamage() override;

};

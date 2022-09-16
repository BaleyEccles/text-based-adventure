#pragma once
#include <iostream>
#include "Globals.h"

class EnemyBase {
public:
	EnemyBase();


	virtual int GetDamage();

	void PrintData();
	unsigned int m_Health;
	int m_Damage;

	bool m_IsDead = false;

	enum EnemiesEnum
	{
		Easy, Medium,

		EnemyMAX
	};

};


class EasyEnemy : public EnemyBase {
public:

	EasyEnemy();
	int GetDamage() override;

};
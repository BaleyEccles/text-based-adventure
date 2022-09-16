#include "Enemies.h"


EasyEnemy::EasyEnemy()
{
	m_Health = 20;
	m_Damage = 3;
}


int EasyEnemy::GetDamage()
{
	int PercentOfDamage = rand() % (100);
	int ReturnValue = (int)floor(((float)PercentOfDamage / 100.0f) * (float)m_Damage);
	return ReturnValue;
}

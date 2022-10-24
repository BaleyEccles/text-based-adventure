#include "Enemies.h"


HardEnemy::HardEnemy(int Layer)
	:EnemyBase(Layer)
{
	m_Health = rand() % (150) * (m_Layer);
	m_Damage = rand() % (30) *  (m_Layer);
}


int HardEnemy::GetDamage()
{
	if (m_Ice == 0)
	{
	int PercentOfDamage = rand() % (200);
	int ReturnValue = (int)floor(((float)PercentOfDamage / 100.0f) * (float)m_Damage);
	return ReturnValue;
	}
	else {
		m_Ice -= 1;
		return 0;
	}
}
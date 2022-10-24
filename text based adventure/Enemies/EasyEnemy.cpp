#include "Enemies.h"


EasyEnemy::EasyEnemy(int Layer)
	:EnemyBase(Layer)
{
	m_Health = rand() % (50) * (m_Layer);
	m_Damage = rand() % (7)  * (m_Layer);
}


int EasyEnemy::GetDamage()
{
	if (m_Ice == 0)
	{
		int PercentOfDamage = rand() % (100);
		int ReturnValue = (int)floor(((float)PercentOfDamage / 100.0f) * (float)m_Damage);
		return ReturnValue;
	}
	else {
		m_Ice -= 1;
		return 0;
	}
}

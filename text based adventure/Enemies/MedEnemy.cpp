#include "Enemies/Enemies.h"



MedEnemy::MedEnemy(int Layer)
	:EnemyBase(Layer)
{
	m_Health = rand() % (100) * (m_Layer);
	m_Damage = rand() % (19)  * (m_Layer);
}

int MedEnemy::GetDamage()
{
	if (m_Ice == 0)
	{
		int PercentOfDamage = rand() % (150);
		int ReturnValue = (int)floor(((float)PercentOfDamage / 100.0f) * (float)m_Damage);
		return ReturnValue;
	}
	else {
		m_Ice -= 1;
		return 0;
	}
}

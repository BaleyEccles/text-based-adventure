#include "Enemies.h"


BossEnemy::BossEnemy(int Layer)
	:EnemyBase(Layer)
{
	m_Health = rand() % (1500 *( m_Layer + 1)) * (m_Layer);
	m_Damage = rand() % (70 *( m_Layer + 1))   * (m_Layer);
}


int BossEnemy::GetDamage()
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

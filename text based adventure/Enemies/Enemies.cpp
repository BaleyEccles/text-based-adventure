#include "Enemies.h"

EnemyBase::EnemyBase()
{
}

int EnemyBase::GetDamage()
{
    return 0;
}

void EnemyBase::PrintData()
{
    std::cout << "Dead: " << (m_IsDead == true ? "Yes" : "No") << std::endl;
    Globals::ChangeColour(Globals::red);
    std::cout << "Damage: "  << m_Damage << std::endl;
    Globals::ChangeColour(Globals::green);
    std::cout << "Health: " << m_Health << std::endl;
    Globals::ChangeColour(Globals::white);

}



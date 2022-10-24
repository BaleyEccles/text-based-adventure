#pragma once
#include "Room.h"

RoomBase::RoomBase(Player* PlayerPtr, int layer)
    :m_Layer(layer), m_RoomType(-1)
{
    m_PlayerPtr = PlayerPtr;
    //std::cout << m_PlayerPtr << std::endl;
}

std::string RoomBase::GetEnter()
{
	return std::string();
}

void RoomBase::Main()
{

}

void RoomBase::CheckLeave()
{
    char Leave;
    std::cout << "Would you like to leave the room? (y/n)" << std::endl;
    do {
        std::cin >> Leave;
        switch (Leave)
        {
        case Globals::yes:case Globals::YES:
            m_PlayerIsInRoom = false;
            break;
        case Globals::no:case Globals::NO:
            m_PlayerIsInRoom = true;
            break;
        default:
            std::cout << "Please enter y or n" << std::endl;
            break;
        }
    } while (ISYESNO(Leave));
}

void RoomBase::PrintLoot(char Type)
{
    switch (Type)
    {
    case Wand::SPELL:
        for (int i = 0; i < m_SpellLoot.size(); i++)
        {
            Globals::PrintLine(Globals::blue);
            std::cout << "Spell " << i << std::endl;
            std::cout << "Type: " << m_SpellLoot[i]->Type << std::endl;
            std::cout << "Damage: " << m_SpellLoot[i]->Damage << std::endl;
            if (m_SpellLoot[i]->Cost != 0)
            {
                Globals::ChangeColour(Globals::yellow);
                std::cout << "This spell costs " << m_SpellLoot[i]->Cost << " gold coins" << std::endl;
                Globals::ChangeColour(Globals::white);
                Globals::PrintLine(Globals::black);
                Globals::PrintLine(Globals::black);
                Globals::PrintLine(Globals::black);
            }
            else {
                Globals::PrintLine(Globals::black);
                Globals::PrintLine(Globals::black);
                Globals::PrintLine(Globals::black);
            }
        }
        break;
    case Wand::WAND:
        std::cout << m_WandLoot.size() << std::endl;
        for (int i = 0; i < m_WandLoot.size(); i++)
        {
            std::cout << "Wand " << i << std::endl;
            m_WandLoot[i]->PrintData();
            Globals::PrintLine(Globals::black);
            Globals::PrintLine(Globals::black);
            Globals::PrintLine(Globals::black);
        }
    case Wand::GOLD:
        Globals::PrintLine(Globals::yellow);

        Globals::ChangeColour(Globals::yellow);
        std::cout << "There are " << m_Gold << " gold coins in here." << std::endl;
        Globals::ChangeColour(Globals::white);
        Globals::PrintLine(Globals::black);
        Globals::PrintLine(Globals::black);
        Globals::PrintLine(Globals::black);
        break;
    default:
        for (int i = 0; i < m_WandLoot.size(); i++)
        {
            Globals::PrintLine();
            std::cout << "Wand " << i << std::endl;
            m_WandLoot[i]->PrintData();
            Globals::PrintLine(Globals::black);
            Globals::PrintLine(Globals::black);
            Globals::PrintLine(Globals::black);
        }
        for (int i = 0; i < m_SpellLoot.size(); i++)
        {
            Globals::PrintLine(Globals::blue);
            std::cout << "Spell " << i << std::endl;
            std::cout << "Type: " << m_SpellLoot[i]->Type << std::endl;
            std::cout << "Damage: " << m_SpellLoot[i]->Damage << std::endl;
            
            if (m_SpellLoot[i]->Cost != 0)
            {
                Globals::ChangeColour(Globals::yellow);
                std::cout << "This spell costs " << m_SpellLoot[i]->Cost << " gold coins" << std::endl;
                Globals::ChangeColour(Globals::white);
                Globals::PrintLine(Globals::black);
                Globals::PrintLine(Globals::black);
                Globals::PrintLine(Globals::black);
            }
            else {
                Globals::PrintLine(Globals::black);
                Globals::PrintLine(Globals::black);
                Globals::PrintLine(Globals::black);
            }

        }
        if (m_Gold != 0)
        {
            Globals::PrintLine(Globals::yellow);
            Globals::ChangeColour(Globals::yellow);
            std::cout << "There are " << m_Gold << " gold coins in here." << std::endl;
            std::cout << "You currnetly have " << m_PlayerPtr->m_Gold << " coins of gold." << std::endl;
            Globals::ChangeColour(Globals::white);
            Globals::PrintLine(Globals::black);
            Globals::PrintLine(Globals::black);
            Globals::PrintLine(Globals::black);
        }
        break;
    }
    Globals::ChangeColour(Globals::yellow);
    std::cout << "You currnetly have " << m_PlayerPtr->m_Gold << " coins of gold." << std::endl;
    Globals::ChangeColour(Globals::white);
    Globals::PrintLine(Globals::black);
    Globals::PrintLine(Globals::black);
    Globals::PrintLine(Globals::black);
}

void RoomBase::PlayerLoot()
{
    char LootTheRoom;
    int VecPosToRemove = -1;
    if (m_SpellLoot.size() == 0 && m_WandLoot.size() == 0)
    {
        std::cout << "Theres nothing in this room." << std::endl;
    }
    else {
        if (m_RoomType == 'S')// check if shop
        {
            std::cout << "Would you like to buy something? (y/n)" << std::endl;
        }
        else {
            std::cout << "Would you like to loot the room? (y/n)" << std::endl;
        }
        do {
            std::cin >> LootTheRoom;
            switch (LootTheRoom)
            {
            case Globals::YES: case  Globals::yes:
                std::cout << "You currnetly have " << m_PlayerPtr->m_Gold << " coins of gold." << std::endl;
                PrintLoot();

                std::cout << "What loot would you like? (Spell: s  | Wand: w | Cancel: c)" << std::endl;

                char lootType;
                do {
                    std::cin >> lootType;
                    switch (lootType)
                    {
                    case 'c':case 'C':
                    {
                        break;
                    }
                    case Wand::wand:case Wand::WAND:
                    {
                        PrintLoot(Wand::WAND);
                        std::cout << "Please input the number associated with the wand." << std::endl;
                        int lootNumber;
                        bool IsValidNumber = true;
                        do {
                            if (!m_PlayerPtr->IsInventoryFull())
                            {
                                std::cin >> lootNumber;
                                if (lootNumber >= 0 && lootNumber <= m_WandLoot.size())
                                {
                                    if (m_WandLoot[lootNumber]->m_Cost == 0)
                                    {
                                        m_PlayerPtr->m_InventoryWands.push_back(m_WandLoot[lootNumber]);
                                        VecPosToRemove = lootNumber;

                                        IsValidNumber = true;
                                    }
                                    if (m_WandLoot[lootNumber]->m_Cost > 0 && m_PlayerPtr->m_Gold > m_WandLoot[lootNumber]->m_Cost)
                                    {
                                        m_PlayerPtr->m_Gold -= m_WandLoot[lootNumber]->m_Cost;
                                        m_PlayerPtr->m_InventoryWands.push_back(m_WandLoot[lootNumber]);
                                        VecPosToRemove = lootNumber;
                                        IsValidNumber = true;

                                    }

                                }
                                else {
                                    std::cout << "Please input the number associated with the wand." << std::endl;
                                    IsValidNumber = false;
                                }
                            }
                        } while (!IsValidNumber);
                        if (VecPosToRemove != -1)// remvoes the wand from room
                        {
                            m_WandLoot.erase(m_WandLoot.begin() + lootNumber);
                        }
                    }
                    break;
                    case Wand::spell:case Wand::SPELL:
                    {
                        if (m_SpellLoot.size() != 0)
                        {
                            PrintLoot(Wand::SPELL);
                            std::cout << "Please input the number associated with the spell." << std::endl;
                            int lootNumber;
                            bool IsValidNumber = true;
                            do {
                                if (!m_PlayerPtr->IsInventoryFull())
                                {
                                    std::cin >> lootNumber;
                                    if (lootNumber >= 0 && lootNumber <= m_SpellLoot.size())
                                    {
                                        if (m_SpellLoot[lootNumber]->Cost == 0)
                                        {
                                            m_PlayerPtr->m_InventorySpells.push_back(m_SpellLoot[lootNumber]);
                                            VecPosToRemove = lootNumber;

                                            IsValidNumber = true;
                                        }
                                        if (m_SpellLoot[lootNumber]->Cost > 0 && m_PlayerPtr->m_Gold > m_SpellLoot[lootNumber]->Cost)
                                        {
                                            m_PlayerPtr->m_Gold -= m_SpellLoot[lootNumber]->Cost;
                                            m_PlayerPtr->m_InventorySpells.push_back(m_SpellLoot[lootNumber]);
                                            VecPosToRemove = lootNumber;
                                            IsValidNumber = true;

                                        }
                                    }
                                    else {
                                        std::cout << "Please input the number associated with the spell." << std::endl;
                                        IsValidNumber = false;
                                    }
                                }
                            } while (!IsValidNumber);
                            if (VecPosToRemove != -1)// remvoes the spell from room
                            {
                                m_SpellLoot.erase(m_SpellLoot.begin() + lootNumber);
                            }
                        }
                    }
                    break;
                    default:
                        std::cout << "please enter (Spell: s  | Wand: w)" << std::endl;
                        break;
                    }
                } while (lootType != Wand::SPELL && lootType != Wand::spell && lootType != Wand::WAND && lootType != Wand::wand && lootType != 'c' && lootType != 'C');
                std::cout << "Would you like to loot the room again? (y or n)" << std::endl;
                char LootAgain;
                do {
                    std::cin >> LootAgain;
                    switch (LootAgain)
                    {
                    case Globals::yes: case Globals::YES:
                        PlayerLoot();
                        break;
                    case Globals::no: case Globals::NO:
                        break;
                    default:
                        std::cout << "please enter y or n" << std::endl;
                        break;
                    }
                } while (ISYESNO(LootAgain));
                break;
            case Globals::no: case Globals::NO:
                std::cout << LootTheRoom << std::endl;
                break;
            default:
                std::cout << "please enter y or n" << std::endl;
                break;

            }
        } while (ISYESNO(LootTheRoom));
    }
    if (m_Gold != 0)
    {
        Globals::ChangeColour(Globals::yellow);
        std::cout << "You find " << m_Gold << " coins of gold in the room, obviously you take them." << std::endl;
        m_PlayerPtr->m_Gold += m_Gold;
        m_Gold = 0;
        Globals::ChangeColour(Globals::white);

    }
}

void RoomBase::TargetEnemy(int &DamageToDeal, int &WandNo)
{
    std::cout << "Which enemy would you like to target?" << std::endl;

    Globals::ChangeColour(Globals::green);
    int Target;
    {
        bool IsValidNumber = true;
        do {

            Globals::InputNumber(Target);


            if (Target >= 0 && Target < m_EnemyVec.size())
            {
                //Deal Damage
                switch (m_PlayerPtr->m_InventoryWands[WandNo]->m_WandInv->WandAtribute)
                {
                case Wand::WandAtributes::AOE:
                    DealAOE(DamageToDeal);

                    break;
                case Wand::WandAtributes::Fire:
                    DealFire(DamageToDeal, Target);

                    break;
                case Wand::WandAtributes::Ice:
                    DealIce(DamageToDeal, Target);

                    break;
                case Wand::WandAtributes::None:
                    m_EnemyVec[Target]->m_Health -= DamageToDeal;
                    std::cout << "You deal " << DamageToDeal << " points of damage to ememy " << Target << "." << std::endl;

                    break;
                default:
                    m_EnemyVec[Target]->m_Health -= DamageToDeal;
                    std::cout << "You deal " << DamageToDeal << " points of damage to ememy " << Target << "." << std::endl;

                    break;
                }

                // Deals Fire damage
                //for (int e = 0; e < m_EnemyVec.size(); e++)
                //{
                //    if (m_EnemyVec[e]->m_Fire =! 0)
                //    {
                //        if (DamageToDeal != 0)
                //        {
                //            int RandDamageToDeal = rand() % (DamageToDeal);
                //            if (RandDamageToDeal != 0)
                //            {
                //                m_EnemyVec[e]->m_Health -= RandDamageToDeal;
                //                std::cout << "You deal " << RandDamageToDeal << " points of damage to ememy " << e << " due to fire." << std::endl;
                //            }
                //
                //        }
                //        else {
                //            std::cout << "You deal " << DamageToDeal << " points of damage to ememy " << e << " due to fire." << std::endl;
                //        }
                //        m_EnemyVec[e]->m_Fire -= 1;
                //        std::cout << m_EnemyVec[e]->m_Fire << std::endl;
                //    }
                //}

                for (int e = 0; e < m_EnemyVec.size(); e++)
                {
                    if (m_EnemyVec[e]->m_Health <= 0)
                    {
                        m_EnemyVec[e]->m_IsDead = true;
                        m_EnemyVec.erase(m_EnemyVec.begin() + Target);

                    }
                }
                IsValidNumber = true;
            }
            else {
                std::cout << "Input the number of the enemy you would like to attack." << std::endl;
                IsValidNumber = false;
            }
        } while (!IsValidNumber);
    }

    Globals::ChangeColour(Globals::white);
}

void RoomBase::CheckPlayerDeath()
{
    if (m_PlayerPtr->m_Health <= 0)
    {
        while (true) {
            Globals::ChangeColour(Globals::red);
            std::cout << "You are dead!!!" << std::endl;
            Globals::ChangeColour(Globals::white);
        }
    }
    
}

void RoomBase::PrintEnemies()
{
    std::cout << " There are " << m_EnemyVec.size() << " enemies in this room." << std::endl;
    std::cout << "Here are the enemies in the room." << std::endl;
    for (int e = 0; e < m_EnemyVec.size(); e++)
    {
        if (!m_EnemyVec[e]->m_IsDead)
        {
            std::cout << "Enemy " << std::to_string(e) << ":" << std::endl;
            m_EnemyVec[e]->PrintData();
        }
    }
}

void RoomBase::DealDamageToPlayer()
{
    Globals::ChangeColour(Globals::red);
    for (int e = 0; e < m_EnemyVec.size(); e++)
    {
        if (m_EnemyVec[e]->m_IsDead == false)
        {
            int DamageFromEnemy = m_EnemyVec[e]->GetDamage();
            m_PlayerPtr->m_Health -= DamageFromEnemy;
            std::cout << "You take " << DamageFromEnemy << " points of damage from enemy " << e << "." << std::endl;
        }
    }
    Globals::ChangeColour(Globals::white);

    // Sets wands cool down lower by 1
    for (int w = 0; w < m_PlayerPtr->m_InventoryWands.size(); w++)
    {
        if (m_PlayerPtr->m_InventoryWands[w]->m_CoolDownLeft > 0)
        {
            m_PlayerPtr->m_InventoryWands[w]->m_CoolDownLeft -= 1;
        }
    }
}

void RoomBase::DealAOE(int &DamageToDeal)
{
    for (int e = 0; e < m_EnemyVec.size(); e++)
    {
        if (rand() % (5) == 1)// one in five chance for AOE to work
        {
            if (DamageToDeal != 0)
            {
                int RandDamageToDeal = rand() % (DamageToDeal);
                if (RandDamageToDeal != 0)
                {
                    m_EnemyVec[e]->m_Health -= RandDamageToDeal;
                }
                std::cout << "You deal " << RandDamageToDeal << " points of damage to ememy " << e << "." << std::endl;
            }
            else {
                std::cout << "You deal " << DamageToDeal << " points of damage to ememy " << e << "." << std::endl;

            }
        }

    }
}
void RoomBase::DealFire(int& DamageToDeal, int &Target)
{
    if (DamageToDeal != 0)
    {
        m_EnemyVec[Target]->m_Health -= rand() % (DamageToDeal);
    }    
    std::cout << "You deal " << DamageToDeal << " points of damage to ememy " << Target << " and set it on fire." << std::endl;
    m_EnemyVec[Target]->m_Fire += rand() % (10);
}
void RoomBase::DealIce(int& DamageToDeal, int &Target)
{
    if (DamageToDeal != 0)
    {
        m_EnemyVec[Target]->m_Health -= rand() % (DamageToDeal);
    }
    std::cout << "You deal " << DamageToDeal << " points of damage to ememy " << Target << " and freeze it." << std::endl;
    m_EnemyVec[Target]->m_Ice += rand() % (10);

}

void RoomBase::AddExtraPlayerStats()
{
    Globals::ChangeColour(Globals::green);
    if (rand() % 20 == 1)
    {
        m_PlayerPtr->m_SightLenght += 1;
        std::cout << "You feel better and gain extra eye sight. You can now see " << m_PlayerPtr->m_SightLenght << " rooms ahead." << std::endl;
    }
    if (rand() % 20 == 1)
    {
        m_PlayerPtr->m_InventorySizeWands += 1;
        std::cout << "You feel stronger and gain an extra wand slot. You can now carry " << m_PlayerPtr->m_InventorySizeWands << " wands." << std::endl;
    }
    if (rand() % 20 == 1)
    {
        m_PlayerPtr->m_InventorySizeSpells += 1;
        std::cout << "You feel stronger and gain an extra spell slot. You can now carry " << m_PlayerPtr->m_InventorySizeSpells << " spells." << std::endl;
    }

    if (rand() % 20 == 1)
    {
        m_PlayerPtr->m_Luck += 1;
        std::cout << "You feel luckier." << std::endl;
    }
    Globals::ChangeColour(Globals::white);

}



void RoomBase::GetWandAndDamage(int &DamageToDeal, int &WandNumberUse)
{
    std::cout << "Which wand would you like to use?" << std::endl;
    m_PlayerPtr->PrintInventory(Wand::wand);
    {
        bool IsValidNumber = true;
        std::cout << "Input the number of the wand you would like to use." << std::endl;
        // Gets the ammount of damage to deal to the enemy.
        do {

            Globals::InputNumber(WandNumberUse);
            if (WandNumberUse >= 0 && WandNumberUse < m_PlayerPtr->m_InventoryWands.size())
            {
                if (m_PlayerPtr->m_InventoryWands[WandNumberUse]->m_CoolDownLeft == 0)
                {
                    DamageToDeal = m_PlayerPtr->m_InventoryWands[WandNumberUse]->GetDamage(m_PlayerPtr->m_Luck);
                    m_PlayerPtr->m_InventoryWands[WandNumberUse]->m_CoolDownLeft = m_PlayerPtr->m_InventoryWands[WandNumberUse]->m_WandInv->CoolDown;
                    IsValidNumber = true;
                }
                else {
                    std::cout << "This wand Still has a cool down, it has " << m_PlayerPtr->m_InventoryWands[WandNumberUse]->m_CoolDownLeft << " left." << std::endl;
                    IsValidNumber = false;
                }
            }
            else {
                std::cout << "Input the number of the wand you would like to use." << std::endl;
                IsValidNumber = false;
            }

        } while (!IsValidNumber);
    }
}


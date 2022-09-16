#pragma once
#include "Room.h"

RoomBase::RoomBase(Player* PlayerPtr)
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
            std::cout << "please enter y or n" << std::endl;
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
            std::cout << "Spell " << i << std::endl;
            std::cout << "Type: " << m_SpellLoot[i]->Type << std::endl;
            std::cout << "Damage: " << m_SpellLoot[i]->Damage << std::endl;
            std::cout << "" << std::endl;
        }
        break;
    case Wand::WAND:
        std::cout << m_WandLoot.size() << std::endl;
        for (int i = 0; i < m_WandLoot.size(); i++)
        {
            std::cout << "Wand " << i << std::endl;
            m_WandLoot[i]->PrintData();
        }
    case Wand::GOLD:
        Globals::ChangeColour(Globals::yellow);
        std::cout << "There are " << m_Gold << " gold coins in here." << std::endl;
        Globals::ChangeColour(Globals::white);
        break;
    default:
        for (int i = 0; i < m_WandLoot.size(); i++)
        {
            std::cout << "Wand " << i << std::endl;
            m_WandLoot[i]->PrintData();
        }
        for (int i = 0; i < m_SpellLoot.size(); i++)
        {
            std::cout << "Spell " << i << std::endl;
            std::cout << "Type: " << m_SpellLoot[i]->Type << std::endl;
            std::cout << "Damage: " << m_SpellLoot[i]->Damage << std::endl;
            if (m_SpellLoot[i]->Cost != 0)
            {
                Globals::ChangeColour(Globals::yellow);
                std::cout << "This spell costs" << m_SpellLoot[i]->Cost << " gold coins" << std::endl;
                Globals::ChangeColour(Globals::white);
            }

        }
        if (m_Gold != 0)
        {
            Globals::ChangeColour(Globals::yellow);
            std::cout << "There are " << m_Gold << " gold coins in here." << std::endl;
            Globals::ChangeColour(Globals::white);
        }
        break;
    }

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
        std::cout << "Would you like to loot the room? (y/n)" << std::endl;
        do {
            std::cin >> LootTheRoom;
            switch (LootTheRoom)
            {
            case Globals::YES: case  Globals::yes:
                PrintLoot();

                std::cout << "What loot would you like? (Spell: s  | Wand: w)" << std::endl;

                char lootType;
                do {
                    std::cin >> lootType;
                    switch (lootType)
                    {
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
                        PrintLoot(Wand::WAND);
                        std::cout << "Please input the number associated with the spell." << std::endl;
                        int lootNumber;
                        bool IsValidNumber = true;
                        do {
                            if (!m_PlayerPtr->IsInventoryFull())
                            {
                                std::cin >> lootNumber;
                                if (lootNumber >= 0 && lootNumber <= m_PlayerPtr->m_InventorySpells.size())
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
                    PrintLoot(Wand::SPELL);
                    break;
                    default:
                        std::cout << "please enter (Spell: s  | Wand: w)" << std::endl;
                        break;
                    }
                } while (lootType != Wand::SPELL && lootType != Wand::spell && lootType != Wand::WAND && lootType != Wand::wand);
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
                std::cout << "dasdasd" << std::endl;
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
        m_PlayerPtr->m_Gold == m_Gold;
        m_Gold = 0;
        Globals::ChangeColour(Globals::white);

    }
}


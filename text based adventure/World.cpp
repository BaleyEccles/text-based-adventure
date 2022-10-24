#pragma once
#include "World.h"

World::World(Player* PlayerPtr)
    :m_PlayerPtr(PlayerPtr)
{
    GenWorld(1);

}

void World::Main()
{
    std::cout << "What would you like to do?\n You can:" << std::endl;
    std::cout << "1: Search the room." << std::endl;
    std::cout << "2: manage your inventory." << std::endl;
    std::cout << "3: move to another room." << std::endl;
    int NumberOfActions = 3;
    int ToDo = 0;
    do {

        Globals::InputNumber(ToDo);
        switch (ToDo)
        {
        case 1:
            std::cout << "You rumage the room and you find..." << std::endl;
            m_WorldVec[m_PlayerPtr->m_XPos][m_PlayerPtr->m_YPos]->PrintLoot();
            m_WorldVec[m_PlayerPtr->m_XPos][m_PlayerPtr->m_YPos]->PlayerLoot();
            break;
        case 2:
            m_PlayerPtr->PrintInventory();
            m_PlayerPtr->ManageInventory();
            break;
        case 3:
            progress();
            break;
        default:
            std::cout << "Please input the desired action." << std::endl;
            break;
        }
    } while (ToDo > NumberOfActions);


    CheckPlayerDeath();

}

void World::NextLayer()
{
    if (m_Layer == 10)
    {
        std::cout << "You WIN... but you can keep going." << std::endl;
    }
    if (m_PlayerPtr->m_YPos >= m_WorldVec[0].size())
    {
        //m_PlayerPtr->m_SightLenght += 1;
        m_WorldVec.clear();
        m_Layer += 1;
        GenWorld(m_Layer);
        Globals::ChangeColour(Globals::red);
        std::cout << "You find a end to this layer of the cave, it looks like things are going to get harder. You are now on layer " << m_Layer << "." << std::endl;
        Globals::ChangeColour(Globals::white);

    }
}


void World::progress()
{
    PrintWorld();
    char Direction;
    std::cout << "Which direction would you like to go? (left: l | right: r | down:d | cancel: c)" << std::endl;
    bool CanGoThatWay = false;
    bool IsAtBottom = false;
    do {
        std::cin >> Direction;
        switch (Direction)
        {
        case 'c':
            CanGoThatWay = true;
            break;
        case World::Left:
            if (m_PlayerPtr->m_XPos - 1 < 0)
            {
                CanGoThatWay = false;
            }
            else {
                CanGoThatWay = true;
            }
            break;

        case World::Down:   
            if (m_PlayerPtr->m_YPos + 1 > m_WorldVec[0].size())
            {
                CanGoThatWay = false;
                IsAtBottom = true;
            }
            else {
                CanGoThatWay = true;
            }
            break;

        case World::Right:
            if (m_PlayerPtr->m_XPos + 1 > m_WorldVec.size())
            {
                CanGoThatWay = false;
            }
            else {
                CanGoThatWay = true;
            }
            break;
        default:
            std::cout << "Please input l r or d" << std::endl;
            break;
        }

    } while (Direction != World::Left && Direction != World::Right && Direction != World::Down && CanGoThatWay == false);
    switch (Direction)
    {
    case World::Left:
        
        m_PlayerPtr->m_XPos -= 1;
        break;
    case World::Right:
        m_PlayerPtr->m_XPos += 1;
        break;
    case World::Down:
        m_PlayerPtr->m_YPos += 1;
        NextLayer();
        break;
    };
    if (m_PlayerPtr->m_YPos < m_WorldVec[0].size())
    {
        // Heals Player after entering a new room
        if (m_WorldVec[m_PlayerPtr->m_XPos][m_PlayerPtr->m_YPos]->m_PlayerHasBeenInRoom == false)
        {
            int HealthGain = 0;
            m_WorldVec[m_PlayerPtr->m_XPos][m_PlayerPtr->m_YPos]->m_PlayerHasBeenInRoom = true;
            switch (m_WorldVec[m_PlayerPtr->m_XPos][m_PlayerPtr->m_YPos]->m_RoomType)
            {
            case Number::Enemy:
            {
                HealthGain = rand() % (100);
                break;
            }
            default:
                HealthGain = rand() % (35);
                break;
            }
            Globals::ChangeColour(Globals::green);
            std::cout << "As you enter the new room you feel better and gain " << HealthGain << " health." << std::endl;
            m_PlayerPtr->m_Health += HealthGain;
            std::cout << "You now have " << m_PlayerPtr->m_Health << " points of health." << std::endl;
            Globals::ChangeColour(Globals::white);
        }

        m_WorldVec[m_PlayerPtr->m_XPos][m_PlayerPtr->m_YPos]->Main();// Loop for enemy fighting and stuff, ie FORCED things
    }

}



void World::GenWorld(int Layer)
{
    int XLength = 19;
    int YLength = 8 * Layer;
    m_PlayerPtr->m_XPos = floor((float)XLength/2);
    m_PlayerPtr->m_YPos = 0;
    for (int i = 0; i < XLength; i++)
    {
        // construct a vector of ints with the given default value
        std::vector<RoomBase*> v;
        for (int j = 0; j < YLength; j++) {
            int RoomNumber = rand() % (RoomMAX);
            switch (RoomNumber)
            {
            case Clear:
            {

                if (rand() % (10 - Layer) == 0)
                {
                    EnemyRoom* EnemyRoomPtr = new EnemyRoom(m_PlayerPtr, m_Layer);
                    v.push_back(EnemyRoomPtr);
                    break;
                }
                else {
                    ClearRoom* ClearRoomPtr1 = new ClearRoom(m_PlayerPtr, m_Layer);
                    v.push_back(ClearRoomPtr1);
                    break;
                }

            }
            case Enemy:
            {
                EnemyRoom* EnemyRoomPtr = new EnemyRoom(m_PlayerPtr, m_Layer);
                v.push_back(EnemyRoomPtr);
                break;
            }

            case Loot:
            {
                if (rand() % (10 - Layer) == 0)
                {
                    EnemyRoom* EnemyRoomPtr = new EnemyRoom(m_PlayerPtr, m_Layer);
                    v.push_back(EnemyRoomPtr);
                    break;
                }
                else {
                    LootRoom* LootRoomPtr = new LootRoom(m_PlayerPtr, m_Layer);
                    v.push_back(LootRoomPtr);
                    break;
                }
            }
            case Shop:
            {
                if (rand() % (10 - Layer) == 0)
                {
                    EnemyRoom* EnemyRoomPtr = new EnemyRoom(m_PlayerPtr, m_Layer);
                    v.push_back(EnemyRoomPtr);
                    break;
                }
                else {
                    ShopRoom* ShopRoomPtr = new ShopRoom(m_PlayerPtr, m_Layer);
                    v.push_back(ShopRoomPtr);
                    break;
                }
            }
            case Boss:
            {
                if (rand() % (10 - Layer) == 0)
                {
                    BossRoom* BossRoomPtr = new BossRoom(m_PlayerPtr, m_Layer);
                    v.push_back(BossRoomPtr);
                    break;
                }
                else {
                    EnemyRoom* EnemyRoomPtr = new EnemyRoom(m_PlayerPtr, m_Layer);
                    v.push_back(EnemyRoomPtr);
                    break;
                }


            }
            default:
            {
                ClearRoom* ClearRoomPtr2 = new ClearRoom(m_PlayerPtr, m_Layer);
                v.push_back(ClearRoomPtr2);
                break;
            }
            }
        }

        // push back above one-dimensional vector
        m_WorldVec.push_back(v);
    }


    //Sets starting room to clear
    ClearRoom* ClearRoomPtr3 = new ClearRoom(m_PlayerPtr, m_Layer);
    m_WorldVec[floor(XLength / 2)][0] = ClearRoomPtr3;

}

void World::PrintWorld()
{

    for (int y = 0; y < m_WorldVec[0].size(); y++)
    {
        std::cout << "|";

        for (int x = 0; x < m_WorldVec.size(); x++)
        {
            if ((y < m_PlayerPtr->m_YPos + m_PlayerPtr->m_SightLenght && y > m_PlayerPtr->m_YPos - m_PlayerPtr->m_SightLenght) && (x < m_PlayerPtr->m_XPos + m_PlayerPtr->m_SightLenght && x > m_PlayerPtr->m_XPos - m_PlayerPtr->m_SightLenght))
            {
                m_WorldVec[x][y]->m_PlayerHasSeen = true;
                if (m_PlayerPtr->m_XPos == x && m_PlayerPtr->m_YPos == y)
                {
                    Globals::ChangeColour(Globals::pink);
                    PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                    Globals::ChangeColour(Globals::white);

                }
                else
                {
                    switch (m_WorldVec[x][y]->m_RoomType)
                    {
                    case Number::Boss:
                        Globals::ChangeColour(Globals::red);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;

                    case Number::Clear:
                        Globals::ChangeColour(Globals::white);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;

                    case Number::Enemy:
                        Globals::ChangeColour(Globals::red);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;

                    case Number::Loot:
                        Globals::ChangeColour(Globals::green);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);                        
                        break;

                    case Number::Shop:
                        Globals::ChangeColour(Globals::yellow);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;

                    default:
                        Globals::ChangeColour(Globals::white);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;
                    }

                }
                
            }
            else {
                if (m_WorldVec[x][y]->m_PlayerHasSeen)
                {
                    switch (m_WorldVec[x][y]->m_RoomType)
                    {
                    case Number::Boss:
                        Globals::ChangeColour(Globals::red);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;

                    case Number::Clear:
                        Globals::ChangeColour(Globals::white);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;

                    case Number::Enemy:
                        Globals::ChangeColour(Globals::red);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;

                    case Number::Loot:
                        Globals::ChangeColour(Globals::green);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;

                    case Number::Shop:
                        Globals::ChangeColour(Globals::yellow);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;

                    default:
                        Globals::ChangeColour(Globals::white);
                        PrintRoomType(m_WorldVec[x][y]->m_RoomType);
                        Globals::ChangeColour(Globals::white);
                        break;
                    }
                }
                else {
                        std::cout << "      ";
                }
            }
        }

        std::cout << "|";
        std::cout << "\n";
        
    }
    
}

void World::PrintRoomType(char RoomType)
{
    switch (RoomType)
    {
    case Number::Shop:
        std::cout << "Shop  ";
        break;

    case Number::Enemy:
        std::cout << "Enemy ";
        break;

    case Number::Boss:
        std::cout << "Boss  ";
        break;

    case Number::Clear:
        std::cout << "Clear ";        
        break;

    case Number::Loot:
        std::cout << "Loot  ";
        break;

    default:
        std::cout << "NULL  ";
        break;
    }

}

void World::CheckPlayerDeath()
{
    if (m_PlayerPtr->m_Health <= 0)
    {
        while (true) {
            std::cout << "You are dead!!!" << std::endl;
        }
    }
}


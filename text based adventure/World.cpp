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


}


void World::progress()
{
    PrintWorld();
    char Direction;
    std::cout << "Which direction would you like to go? (left: l | right: r | down:d)" << std::endl;
    bool CanGoThatWay = false;
    bool IsAtBottom = false;
    do {
        std::cin >> Direction;
        switch (Direction)
        {
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
            if (m_PlayerPtr->m_YPos + 1 > 10)//Add Somthing to get max index, so can have floors of diff sizes
            {
                CanGoThatWay = false;
                IsAtBottom = true;
            }
            else {
                CanGoThatWay = true;
            }
            break;

        case World::Right:
            if (m_PlayerPtr->m_XPos + 1 > 10)
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
        break;
    };
    m_WorldVec[m_PlayerPtr->m_XPos][m_PlayerPtr->m_YPos]->Main();// Loop for enemy fighting and stuff, ie FORCED things

}



void World::GenWorld(int Layer)
{
    for (int i = 0; i < 10; i++)
    {
        // construct a vector of ints with the given default value
        std::vector<RoomBase*> v;
        for (int j = 0; j < 10; j++) {
            int RoomNumber = rand() % (RoomMAX - 1);
            switch (RoomNumber)
            {
            case Clear:
            {
                ClearRoom* ClearRoomPtr1 = new ClearRoom(m_PlayerPtr);
                v.push_back(ClearRoomPtr1);
                break;
            }

            case Enemy:
            {
                EnemyRoom* EnemyRoomPtr = new EnemyRoom(m_PlayerPtr);
                v.push_back(EnemyRoomPtr);
                break;
            }

            case Loot:
            {
                LootRoom* LootRoomPtr = new LootRoom(m_PlayerPtr);
                v.push_back(LootRoomPtr);
                break;

            }
            case Shop:
            {
                ShopRoom* ShopRoomPtr = new ShopRoom(m_PlayerPtr);
                v.push_back(ShopRoomPtr);
                break;

            }
            /*
            case Boss:
            {
                BossRoom* BossRoomPtr = new BossRoom();
                v.push_back(BossRoomPtr);
                break;

            }*/
            default:
            {

                ClearRoom* ClearRoomPtr2 = new ClearRoom(m_PlayerPtr);
                v.push_back(ClearRoomPtr2);
                break;
            }
            }
        }

        // push back above one-dimensional vector
        m_WorldVec.push_back(v);
    }





    //Sets starting room to clear
    ClearRoom* ClearRoomPtr3 = new ClearRoom(m_PlayerPtr);
    m_WorldVec[5][0] = ClearRoomPtr3;

}

void World::PrintWorld()
{
    for (int y = 0; y < m_WorldVec.size(); y++)
    {
        for (int x = 0; x < m_WorldVec[y].size(); x++)
        {
            if (m_PlayerPtr->m_XPos == x && m_PlayerPtr->m_YPos == y)
            {
                Globals::ChangeColour(Globals::pink);
                std::cout << m_WorldVec[x][y]->m_RoomType << " ";
                Globals::ChangeColour(Globals::white);

            }
            else
            {
                std::cout << m_WorldVec[x][y]->m_RoomType << " ";
            }

        }
        std::cout << "\n";
    }
}


#pragma once
#include <iostream>
#include "Player.h"
#include "World.h"



/*
- 2d Array will store the room data
    random ?union? will define the room type.
    10 by 10 array until they have reached the bottom
    it will get harder.


*/


void BeginGame(Player* Player) {

    std::cout <<
        "You start of your adventure facing a cave with intentions of finding the hidden treasure. You take your first step into the cave wondering what you may encounter, all you have is your trusty wand and your ambitions."
        << std::endl;
    std::cout <<
        "As you enter the cave you see three paths you can take left, right or down. You know you must go down to progress to the treasure, but you wonder what you may find if you go the other directions."
        << std::endl;

}

int main()
{
    srand(time(NULL));
    Player* PlayerMain = new Player();
    World* WorldMain = new World(PlayerMain);

    BeginGame(PlayerMain);

    // Main loop
    while (true)
    {
        WorldMain->Main();
    }
}


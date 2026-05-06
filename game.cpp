#include "game.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Game Class
Game::Game(const char* gameName)
{
    score=0;
    strncpy(name,gameName,sizeof(name)-1);
    name[sizeof(name)-1]='\0'; 
}

Game::~Game() {}

void Game::endGame()
{
   cout<<"Game "<<name<<" ended. Final Score: "<<score<<endl;
}

const char* Game::get_name() const 
{
    return name;
}

int Game::get_score() const 
{
    return score;
}


// Leaderboard class
Leaderboard::Leaderboard() 
{
  entryCount=0;
}

void Leaderboard::addScore(const char* player, int score)
{
    if (entryCount>=MAX_ENTRIES) 
    {
        std::cerr<<"Leaderboard is full! Cannot add more entries.\n";
        return;
    }

    strncpy(entries[entryCount].player,player,sizeof(entries[entryCount].player)-1);
    entries[entryCount].player[sizeof(entries[entryCount].player)-1]='\0';
    entries[entryCount].score = score;
    entryCount++;

    cout<<"Score added for player: "<<player<<" Score: "<<score<<endl;
}

void Leaderboard::displayLeaderboard() 
{
    cout << "Leaderboard:\n";
    for (int i=0;i<entryCount;i++)
    {
       cout<<"Player: "<<entries[i].player<<" Score: "<<entries[i].score<<endl;
    }
}


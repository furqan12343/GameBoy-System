#ifndef GAME_H
#define GAME_H

#include <string>

class Game
{
protected:
    char name[40]; 
    int score;

public:
    Game(const char* gameName); // constructor declaration
    virtual ~Game();           // virtual destructor

    virtual void startGame()=0; // virtual function its the main function to start any game 
    virtual void endGame();
    virtual void render()=0;

    const char* get_name() const;
    int get_score() const;
};

class Leaderboard
{
private:
    static const int MAX_ENTRIES=100; 
    struct Entry 
    {
        char player[50];
        int score;
    };
    Entry entries[MAX_ENTRIES];
    int entryCount;

public:
    Leaderboard();
    void addScore(const char* player, int score);
    void displayLeaderboard();
};

#endif // GAME_H


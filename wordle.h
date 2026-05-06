#ifndef WORDLE_H
#define WORDLE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include "game.h"         // this is the Game base class
using namespace std;

struct Bool 
{
    bool _levels[6]={true, true, true, true, true, true}; 
    bool _is_won = false;
    bool _is_lose = false;
    bool _is_last_index = false;
    bool _is_all_inserted = false;
    bool _is_update = true;

    // Function to update a specific level's state
    void setLevelState(int level, bool state)
    {
        if (level>=0&&level<6)
        {
           _levels[level]=state; 
        }
    }

    bool getLevelState(int level) const
    {
       if(level>=0 &&level<6)
       {
         return _levels[level];
       }
        return false;
    }
};


class Box 
{
public:
    Box();
    sf::Vector2f get_size();

    void set_Pos(float x, float y);
    sf::Vector2f get_pos(void);

    void setup(short index);

    void update(sf::RenderWindow& window, sf::Event& event1, std::string& str, int& level, Bool& b);
    void draw(sf::RenderWindow& window);
    void get_input(sf::Event& event1, Bool& b, std::string& str);
    void check_character(std::string& str);

    bool _is_input=false;         // True if the box is ready for user input
    bool _is_mouse_pressed=false;
    bool _is_mouse_released=false;
    bool _is_mouse_hovered=false;
    bool _is_mouse_idle=true;
    bool _is_inserted=false;
    bool _is_correct=false;
    bool _is_exists=false;
    bool _is_wrong=false;
    bool _is_update=true;

    short _index;

private:
    sf::Text _text;
    sf::Font _font;
    sf::RectangleShape _box;
};

class Word 
{
public:
    Word();
    ~Word();

    void setup(int size, float x, float y);
    void update(sf::RenderWindow& window, sf::Event& event1,string& str, int& level, Bool& b);
    void draw(sf::RenderWindow& window);
    void set_pos(float x, float y);

private:
    Box* array; 
    int _size;
};

class WordleGame : public Game
{
private:
    int _level;
    Word* array;
    int _size;
    sf::Text* text;
    sf::Font _font;
    sf::SoundBuffer _winBuffer;
    sf::SoundBuffer _loseBuffer;
    sf::Sound _winSound;
    sf::Sound _loseSound;

public:
    WordleGame(const char* gameName); 
    ~WordleGame(); // Destructor

    void setup(int size, float x, float y);
    void update(sf::RenderWindow& window, sf::Event& event, std::string& str, Bool& b);
    void draw(sf::RenderWindow& window, Bool& b);
    void set_pos(float x, float y);
    
    void setLevel(int level) 
    {
       if (level>=0&&level<6)
       { 
         _level = level;
       }
    }

    int getLevel() const
    {
        return _level;
    }

    void startGame() override;  
    void endGame() override;    
    void render() override;     
};


#endif

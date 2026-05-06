#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "game.h"
#include "wordle.h"
#include "snake.h"
#include "hangman.h"
using namespace std;

class Player 
{
    string name;
    int score;

public:
    Player(const string& name="Player",int score=0);
    void set_name(const string& name);
    void set_score(int score);
    string get_name() const;
    int get_score() const;
};

// Screen class to manage the game screen
class Screen 
{
    sf::RenderWindow window;

public:
    Screen(int width=800,int height=600,const string& title="GameBoy");
    void display();
    void clear();
    sf::RenderWindow& getWindow();
};

// InputSystem class to handle player input
class InputSystem 
{
public:
    bool isKeyPressed(sf::Keyboard::Key key);
};

// SoundSystem class to handle game sounds
class SoundSystem
{
    sf::SoundBuffer buffer;
    sf::Sound sound;

public:
    bool loadSound(const std::string& filepath);
    void playSound();
    void stopSound();
};

// Menu class to handle and display menu options
class Menu 
{
    sf::Text text;  // Text object to display messages

public:
    sf::Font font;
    Menu();       
    void displayMenu(sf::RenderWindow& window, const string& title,const string& option1,const string& option2,const string& option3);
};

// GameBoy class to manage the game system
class GameBoy 
{
    Player player;
    Screen screen;
    InputSystem inputSystem;
    SoundSystem soundSystem;
    Menu menu;

    Game* c_game;  // Composition: GameBoy owns a Game object ,c=current game

    void splashScreen(sf::RenderWindow& window);
    void loadingScreen(sf::RenderWindow& window);
    void getPlayerName(sf::RenderWindow& window);

public:
     GameBoy();
    ~GameBoy(); 
    void switchGame(int choice);  
    void start();                 
    void shutdown();              
};

#endif 


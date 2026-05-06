#ifndef HANGMAN_H
#define HANGMAN_H

#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include"game.h"
#include<SFML/Audio.hpp>
#include<ctime>
#include<cstring>

class Hangman : public Game
{
private:
    sf::Sprite sprite;
    sf::Texture textures[9];

public:
    Hangman(const char* gameName); 
    ~Hangman();

    void startGame() override; 
    void render() override {}  
    //void endGame() override; 
    void updateStage(int stage);
    void draw(sf::RenderWindow &window);
};

#endif // HANGMAN_H


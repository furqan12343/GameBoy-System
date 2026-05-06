#ifndef SNAKE_H
#define SNAKE_H
#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include"game.h"
#include<SFML/Audio.hpp>
#include<ctime>
#include<cstring>
using namespace std;
class Fruit
{
	public:
		sf::CircleShape apple;
		Fruit();
		void set_apple();
		sf::CircleShape get_apple();
};
class Snake
{
	private:
		sf::Sprite head ,body , tail;
		sf::Texture head_up , head_down ,head_left, head_right, hor_body, ver_body, body_top_left, body_top_right, body_bottom_left, body_bottom_right, tail_up, tail_down, tail_left, tail_right;
		sf::Vector2f direction;
	public:
		Snake(const string&, const string&,const string&, const string&,const string&, const string&,const string&, const string&,const string&, const string&,const string&, const string&,const string&, const string&);
		void move();
		void change_direction(float,float);
		void set_head(const sf::Texture & t);
		void set_body(const sf::Texture & t);
		void set_tail(const sf::Texture & t);
		sf::Sprite & get_head();
		//getter functions for textures
		sf::Texture& get_head_up();
		sf::Texture& get_head_down();
    		sf::Texture& get_head_left();
		sf::Texture& get_head_right();
		sf::Texture& get_hor_body();
		sf::Texture& get_ver_body();
		sf::Texture& get_tail_down();
		sf::Texture& get_tail_up();
		sf::Texture& get_tail_left();
		sf::Texture& get_tail_right();
		sf::Sprite & get_body();
		sf::Sprite & get_tail();

};
class Snake_game
{
	private:
		sf::RenderWindow window;
		sf::Texture back_texture;
		sf::Sprite back;
		Fruit apple;
		Snake snake;
		int score;
		sf::Font font;
		sf::Text score_text;

	public:
		Snake_game(); // constructor
		void run();//run windows
		void handle_events();
		void check_collsion();
		void game_over();
		void reset_game();
		void update();
		void render_w();
		sf::Sprite& get_head();
		sf::Vector2f get_direction() const;
};
class main_snake : public Game
{
	public:
	main_snake(const char * );
	void startGame();
	void endGame();
	void render();

};
#endif

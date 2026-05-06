#include"snake.h"
Fruit::Fruit()
{
	apple.setRadius(15.f);
	apple.setFillColor(sf::Color::Red);
	set_apple();		
}
void Fruit::set_apple()
{
	float x = static_cast<float>(rand() % static_cast<int>(800-apple.getRadius()*2));
	float y = static_cast<float>(rand() % static_cast<int>(600-apple.getRadius()*2)); 
	apple.setPosition(x, y);
}
sf::CircleShape Fruit::get_apple()
{
	return apple;
}
Snake::Snake(const string & h_u, const string & h_d, const string & h_l, const string & h_r , const string & h_b, const string & v_b, const string & b_t_l, const string & b_t_r, const string & b_b_l , const string & b_b_r, const string & t_u, const string & t_d, const string & t_l, const string & t_r)
		{
			if(!head_up.loadFromFile(h_u) || !head_down.loadFromFile(h_d) || !head_left.loadFromFile(h_l) || !head_right.loadFromFile(h_r) || !hor_body.loadFromFile(h_b) || !ver_body.loadFromFile(v_b) || !body_top_left.loadFromFile(b_t_l) || !body_top_right.loadFromFile(b_t_r) || !body_bottom_left.loadFromFile(b_b_l) || !body_bottom_right.loadFromFile(b_b_r) || !tail_up.loadFromFile(t_u) || !tail_down.loadFromFile(t_d) || !tail_left.loadFromFile(t_l) || !tail_right.loadFromFile(t_r))
			{
				cout << "Error Loading Texture "<< endl;
				exit(0);
			}
			head.setTexture(head_right);
			body.setTexture(hor_body);
			tail.setTexture(tail_left);
			head.setPosition(400.f ,300.f);
			body.setPosition(399.f,300.f);
			tail.setPosition(398.f,300.f);
			direction = sf::Vector2f(0.5f,0.0f);			
		}
void Snake::move()
{
    // Move the head
    head.move(direction);

    // Move the body to the previous position of the head
    body.setPosition(head.getPosition().x, head.getPosition().y);

    // Move the tail to the previous position of the body
    tail.setPosition(body.getPosition().x, body.getPosition().y);

    // Adjust the positions based on direction for accurate spacing
    if (direction.y != 0.f)
    {
        body.setPosition(head.getPosition().x, head.getPosition().y + (direction.y > 0.f ? 50.f : -50.f));
        tail.setPosition(body.getPosition().x, body.getPosition().y + (direction.y > 0.f ? -50.f : 50.f));
    }
    else
    {
        body.setPosition(head.getPosition().x + (direction.x > 0.f ? 50.f : -50.f), head.getPosition().y);
        tail.setPosition(body.getPosition().x + (direction.x > 0.f ? 50.f : -50.f), body.getPosition().y);
    }
}

void Snake::change_direction(float x,float y)
		{
			direction = sf::Vector2f(x,y);
		}
		void Snake::set_head(const sf::Texture & t)
		{
			head.setTexture(t);
		}
		void Snake::set_body(const sf::Texture & t)
		{
			body.setTexture(t);
		}
		void Snake::set_tail(const sf::Texture & t)
		{
			tail.setTexture(t);
		}
		sf::Sprite & Snake::get_head()
		{
			return head;
		}
		//getter functions for textures
		sf::Texture& Snake::get_head_up()
		{
			return head_up;
		}
		sf::Texture& Snake::get_head_down()
		{
			return head_down;
		}
    		sf::Texture& Snake:: get_head_left()
    		{
    			return head_left;
    		}
		sf::Texture& Snake::get_head_right()
		{	
			return head_right;
		}
		sf::Texture& Snake:: get_hor_body()
		{
			return hor_body;
		}
		sf::Texture& Snake:: get_ver_body()
		{
			return ver_body;
		}
		sf::Texture& Snake::get_tail_down()
		{
			return tail_down;
		}
		sf::Texture& Snake:: get_tail_up()
		{
			return tail_up;
		}
		sf::Texture& Snake:: get_tail_left()
		{
			return tail_left;
		}
		sf::Texture& Snake:: get_tail_right()
		{
			return tail_right;
		}
		sf::Sprite & Snake::get_body()
		{
			return body;
		}
		sf::Sprite & Snake::get_tail()
		{
			return tail;
		}
Snake_game::Snake_game(): snake("/home/noor/oop/projectDemo/head_up.png", "/home/noor/oop/projectDemo/head_down.png","/home/noor/oop/projectDemo/head_left.png","/home/noor/oop/projectDemo/head_right.png","/home/noor/oop/projectDemo/body_horizontal.png", "/home/noor/oop/projectDemo/body_vertical.png","/home/noor/oop/projectDemo/body_topleft.png", "/home/noor/oop/projectDemo/body_topright.png","/home/noor/oop/projectDemo/body_bottomleft.png", "/home/noor/oop/projectDemo/body_bottomright.png","/home/noor/oop/projectDemo/tail_up.png", "/home/noor/oop/projectDemo/tail_down.png","/home/noor/oop/projectDemo/tail_left.png", "/home/noor/oop/projectDemo/tail_right.png"), window(sf::VideoMode(800,600),"Snake Game")
		{
			if(!back_texture.loadFromFile("/home/noor/oop/projectDemo/background.jpg"))
			{
				cout << "Error loading background texture" << endl;
				exit(0);
			}
			back.setTexture(back_texture);
			if(!font.loadFromFile("/home/noor/oop/projectDemo/arial.ttf"))
			{
				cout << "Error loading font for scores" << endl;
				exit(-1);			
			}
			score_text.setFont(font);
			score_text.setCharacterSize(26);
			score_text.setFillColor(sf::Color::White);
			score_text.setPosition(10.f,10.f);
			score=0;
		}
void Snake_game::run()
		{
			while(window.isOpen())
			{
				handle_events();
				update();
				render_w();
			}
		}
		void Snake_game:: handle_events()
		{
			sf::Event event;
			while(window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
				{
					window.close();
				}
			}
		}
		void Snake_game::check_collsion()
		{
			if(snake.get_head().getGlobalBounds().intersects(apple.get_apple().getGlobalBounds()))
			{
				score++;
				apple.set_apple();
			}
			sf::Vector2f head_pos = snake.get_head().getPosition();
			sf::FloatRect head_b = snake.get_head().getLocalBounds();
			float head_width = head_b.width * snake.get_head().getScale().x;
			float head_height = head_b.height * snake.get_head().getScale().y;
			// condidion
			if(head_pos.x<0 || head_pos.x>window.getSize().x - head_width or head_pos.y<0 || head_pos.y>window.getSize().y - head_height)
			{
				game_over();
			}
			score_text.setString("Score: " + std::to_string(score));
		}
		void Snake_game::game_over()
		{
    sf::Font font;
    if (!font.loadFromFile("/home/noor/oop/projectDemo/arial.ttf")) {
        cout << "Error loading font!" << endl;
        return;
    }
    sf::Text text("Game Over!\nPress R to Restart or Q to Quit", font, 30);
    text.setPosition(200, 250);
    text.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        window.clear();
        window.draw(text);
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                reset_game(); // Restart the game
                return;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                window.close();
                return;
            }
        }
    }
}
		void Snake_game:: reset_game()
		{
			score = 0;
			snake.get_head().setPosition(400.f,300.f);
			snake.get_body().setPosition(399.f,300.f);
			snake.get_tail().setPosition(398.f,300.f);
			snake.change_direction(0.5f,0.0f);
		}

		void Snake_game::update()
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{	
				snake.change_direction(0.f,0.2f);
				snake.set_head(snake.get_head_down());
				snake.set_body(snake.get_ver_body());
				snake.set_tail(snake.get_tail_up());
}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				snake.change_direction(0.0f,-0.2f);
				snake.set_head(snake.get_head_up());
				snake.set_body(snake.get_ver_body());
				snake.set_tail(snake.get_tail_down());
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				snake.change_direction(-0.2f,0.0f);
				snake.set_head(snake.get_head_left());
				snake.set_body(snake.get_hor_body());
				snake.set_tail(snake.get_tail_right());
					
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				snake.change_direction(0.2f,0.0f);
				snake.set_head(snake.get_head_right());
				snake.set_body(snake.get_hor_body());
				snake.set_tail(snake.get_tail_left());
			}
		snake.move();
		check_collsion();
		}
		void Snake_game::render_w()
		{
			window.clear(sf::Color::Black);
			window.draw(back);
			window.draw(apple.get_apple());
			window.draw(snake.get_head());
			window.draw(snake.get_body());
			window.draw(snake.get_tail());
			window.draw(score_text);
			window.display();
		}
	main_snake::main_snake(const char * n) : Game(n)
	{
	}
	void main_snake::startGame()
	{
		Snake_game g;
		g.run();
	}
	void main_snake::endGame()
	{
    	Game::endGame();             // Call the base class method
    	cout<< "Snake game ended!"<<endl;
	}
	void main_snake::render() 
	{
		cout << "Rendering Snake game: "<<get_name()<<endl;
	}


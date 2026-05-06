#include<SFML/Graphics.hpp>
#include<iostream>
#include"wordle.h"
#include"game.h"
#include<fstream>
#include<time.h>
using namespace std;

string	get_random_string(std::ifstream& input_file)
{
	string str;
	str.resize(5);
	int index=0;
	int count=0;
	
	srand(time(0));
	index = rand() % 500;
	
	for (int i=1;i<=index;i++)
		getline(input_file, str);
	return str;
}

Box::Box()
{
	if (!_font.loadFromFile("/home/noor/gameboy/arial.ttf"))
	{
            cout<<"font failed to load"<<endl;
	}
	_index=0;
}

void Box::setup(short index)
{
	_index = index;
	_box.setPosition(0, 0);
	_box.setSize(sf::Vector2f(73.f, 73.f));
	_box.setFillColor(sf::Color::White);
	_box.setOutlineColor(sf::Color(200,200,200,255));
	_box.setOutlineThickness(2.f);


	_text.setFont(_font);
	_text.setString(" ");
	_text.setCharacterSize(65);

	_text.setFillColor(sf::Color::Black);
	_text.setPosition((_box.getPosition().x+13),_box.getPosition().y-8);
};

void Box::update(sf::RenderWindow& window,sf::Event& event1,string& str,int& level,Bool& b)
{
	if (b._is_update)
	{

		if (_is_update)
		{
			int mouse_X = sf::Mouse::getPosition(window).x;
			int mouse_Y = sf::Mouse::getPosition(window).y;
			if (!_is_input)
			{
				if (mouse_X <= _box.getGlobalBounds().left + _box.getGlobalBounds().width - 10 &&
					mouse_X >= _box.getGlobalBounds().left + 10 &&
					mouse_Y <= _box.getGlobalBounds().top + _box.getGlobalBounds().height - 10 &&
					mouse_Y >= _box.getGlobalBounds().top + 10)
				{

					switch (event1.type)
					{
						case sf::Event::MouseButtonPressed:
						{
							_is_mouse_pressed=true;
							_is_mouse_released=false;
							_is_mouse_hovered=false;
							_is_mouse_idle=false;
							_box.setFillColor(sf::Color(125, 125, 125));
							break;
						}
						case sf::Event::MouseButtonReleased:
						{
							_is_mouse_pressed=false;
							_is_mouse_released=true;
							_is_mouse_hovered=false;
							_is_mouse_idle=false;
							if (!_is_inserted)
							{
								_is_input=true;
								b._is_update=true;
							}
							_box.setFillColor(sf::Color::White);
							break;
						}
						default:
						{
							_is_mouse_pressed=false;
							_is_mouse_released=false;
							_is_mouse_hovered=true;
							_is_mouse_idle=false;
							_box.setFillColor(sf::Color(200, 200, 200));
							break;
						}
					}
				}
				else
				{
					_is_mouse_idle=true;
					_box.setFillColor(sf::Color::White);
				}
			}
			get_input(event1, b, str);
			if (_is_inserted)
			{
				check_character(str);
				if (_is_correct)
				{
					_box.setFillColor(sf::Color::Green);
				}
				else if(_is_exists)
				{
					_box.setFillColor(sf::Color::Yellow);
				}
				else
				{
					_box.setFillColor(sf::Color(125, 125, 125));
				}
				_is_update = false;

			}
		}
	}
}

void Box::check_character(string &str)
{

	if (str[_index]==_text.getString()[0])
	{
		_is_correct = true;
		return;
	}
	for (int i=0;i<str.size();i++)
	{
		if (str[i]==_text.getString()[0])
		{
			_is_exists= true;
			return;
		}
	}
	_is_wrong=true;
}

void Box::get_input(sf::Event& event1, Bool& b, std::string &str)
{
    char tmp=str[_index];

    if ((tmp>='a' && tmp<='z') || (tmp>='A' && tmp<='Z'))
    {
        if (_is_input)
        {
            switch (event1.type)
            {
                case sf::Event::TextEntered:
                {
                    _text.setString((char)event1.text.unicode);
                    _box.setFillColor(sf::Color(125, 125, 125));
                    _is_input=false;
                    _is_inserted=true;
                    b._is_update=true;
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
}

void Box::draw(sf::RenderWindow& window)
{ 
     window.draw(_box);
     window.draw(_text);
}

void Box::set_Pos(float x, float y)
{
     _box.setPosition(x, y);
     _text.setPosition((_box.getPosition().x+13),_box.getPosition().y-8);
}

sf::Vector2f Box::get_pos(void)
{
      return _box.getPosition();
}

sf::Vector2f Box::get_size()
{
      return _box.getSize();
}

Word::Word()
{
  array=nullptr;
  _size=0;
}

Word::~Word()
{
   delete[] array; 
}

void Word::setup(int size, float x, float y)
{
    _size=size;
    array=new Box[_size];    
    for (int i=0;i<_size;i++)
    {
        array[i].setup(i);
    }
    sf::Vector2f pos_temp=array[0].get_size();
    for (int i=0;i<_size;i++)
    {
        array[i].set_Pos((pos_temp.x*i),0);
    }
}

void Word::update(sf::RenderWindow& window, sf::Event& event1,string& str,int& level,Bool& b)
{
    for (int i=0;i<_size;i++)
    {
        array[i].update(window, event1, str, level, b);
    }

    if (b._is_all_inserted)
    {
        if (level == 5)
        {
            b._is_won=true;
            for (int i=0;i<_size;i++)
            {
                if (!array[i]._is_correct)
                {
                    b._is_lose = true;
                    b._is_won = false;
                    return;
                }
            }
        }
        else
        {
            b._is_won=true;
            for (int i=0;i<_size;i++)
            {
                if (!array[i]._is_correct)
                {
                    b._is_won=false;
                }
            }
        }

        if (!b._is_won)
        {
           
        if (level != 5) 
        {
          level+=1; 
        }
        }
        b._is_all_inserted=false;
    }
    else
    {
        for (int i=0;i< _size;i++)
        {
            if (!array[i]._is_inserted)
            {
                b._is_all_inserted=false;
                return;
            }
        }
        b._is_all_inserted=true;
    }
}

void Word::draw(sf::RenderWindow& window)
{
    for (int i=0;i<_size;i++)
    {
        array[i].draw(window);
    }
}

void Word::set_pos(float x, float y)
{
    sf::Vector2f pos_temp=array[0].get_size();
    for (int i=0;i<_size;i++)
    {
        array[i].set_Pos(x+(i*73),y);
    }
}

WordleGame::WordleGame(const char* gameName) : Game(gameName) {
    array=nullptr;
    _size=0;
    text=new sf::Text;
    if (!_font.loadFromFile("/home/noor/gameboy/arial.ttf")) 
    {
        cout<<"Font failed to load" << endl;
    }

   if (!_winBuffer.loadFromFile("/home/noor/gameboy/winw.wav")) 
    {
        cout<<"Failed to load win sound!" << endl;
    }
    if (!_loseBuffer.loadFromFile("/home/noor/gameboy/winw.wav"))
    {
        cout<<"Failed to load lose sound!" << endl;
    }

    _winSound.setBuffer(_winBuffer);
    _loseSound.setBuffer(_loseBuffer);
}

WordleGame::~WordleGame()
{
    delete[] array; 
    delete text;    
}


void WordleGame::startGame() 
{
    cout<<"Starting Wordle game: "<<get_name()<<endl;

    //creating a window
    sf::RenderWindow window(sf::VideoMode(720, 960),"Wordle Game",sf::Style::Resize | sf::Style::Close);

    sf::Font font;
    if(!font.loadFromFile("/home/noor/gameboy/arial.ttf"))
    {
        cout<<"Error: Unable to load font!"<<endl;
        return;
    }

    // Setup for buttons
    sf::RectangleShape playButton(sf::Vector2f(200, 60));
    playButton.setPosition(260, 500);
    playButton.setFillColor(sf::Color(0, 0, 0));  

    sf::RectangleShape cancelButton(sf::Vector2f(200, 60));
    cancelButton.setPosition(260, 580);
    cancelButton.setFillColor(sf::Color(255, 0, 0)); 

    sf::RectangleShape howToPlayButton(sf::Vector2f(200, 60));  
    howToPlayButton.setPosition(260, 660);
    howToPlayButton.setFillColor(sf::Color(255, 204, 0));  

    sf::Text playText("Play", font, 24);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(310, 510);

    sf::Text cancelText("Cancel", font, 24);
    cancelText.setFillColor(sf::Color::White);
    cancelText.setPosition(300, 590);

    sf::Text howToPlayText("How to Play", font, 24);
    howToPlayText.setFillColor(sf::Color::Black);
    howToPlayText.setPosition(270, 680);

    sf::RectangleShape backbutton(sf::Vector2f(200, 60));
    backbutton.setPosition(260, 800); 
    backbutton.setFillColor(sf::Color(0, 204, 204));  

    sf::Text backtext("Back", font, 24);
    backtext.setFillColor(sf::Color::White);
    backtext.setPosition(330, 810);

    // Load sound buffers
    sf::SoundBuffer _winBuffer, _loseBuffer;
    sf::Sound _winSound, _loseSound;

    if (!_winBuffer.loadFromFile("/home/noor/gameboy/winw.wav") || !_loseBuffer.loadFromFile("/home/noor/gameboy/winw.wav")) {
        cout<<"Error: Unable to load sound files!"<<endl;
        return;
    }

    _winSound.setBuffer(_winBuffer);
    _loseSound.setBuffer(_loseBuffer);

    ifstream file("/home/noor/gameboy/dictionary.txt");
    if (!file.is_open()) 
    {
        cout<<"Error: Unable to open dictionary file!"<<endl;
        return;
    }

    string str=get_random_string(file);

    bool inst=false;  
    bool game_s=false; 

    sf::Texture image;
    if (!image.loadFromFile("/home/noor/gameboy/image1.png"))
    {
        cout<<"Error: Unable to load PNG image!"<<endl;
        return;
    }
    sf::Sprite pngSprite(image);

    pngSprite.setPosition(310, 380); 

    // Main game loop
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check for button clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !inst) {
                    
                    this->setup(6, 0, 0);
                    this->set_pos(180, 300);
                    game_s = true;

                    Bool b;
                    while (window.isOpen()) 
                    {
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                            if (event.type == sf::Event::Closed)
                                window.close();
                            this->update(window, event, str, b);
                        }

                        window.clear(sf::Color(255, 255, 255, 255));  
                        this->draw(window, b);
                        window.display();  
                   }
                }
                else if (cancelButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !inst)
                {
                    window.close();
                }
                else if (howToPlayButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                { 
                    inst=true;
                }
                else if (backbutton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && inst)
                {
                   inst=false;
                }
            }
        }

        window.clear(sf::Color(255, 255, 255)); //background color

        if (!inst) 
        {
            window.draw(playButton);
            window.draw(cancelButton);
            window.draw(howToPlayButton);
            window.draw(playText);
            window.draw(cancelText);
            window.draw(howToPlayText);
            window.draw(pngSprite); 
        }
        else
        {
            sf::Text inst_data("First, click on a box to enter the alphabet.\n\n"
            "Wordle is a game where you guess a 5-letter word in 6 tries.\n"
            "Each guess must be a valid word. After each guess:\n"
            "1. If the letter is in the word and in the correct position, it turns green.\n"
            "2. If the letter is in the word but in the wrong position, it turns yellow.\n"
            "3. If the letter is not in the word, it turns gray.\n"
            "Try to guess the word in as few guesses as possible.", font, 20);

            inst_data.setFillColor(sf::Color::Black);
            inst_data.setPosition(
                (window.getSize().x - inst_data.getLocalBounds().width) / 2,  
                (window.getSize().y - inst_data.getLocalBounds().height) / 4  
            );

 
            sf::RectangleShape inst_bground(sf::Vector2f(inst_data.getLocalBounds().width + 20, inst_data.getLocalBounds().height + 20));
            inst_bground.setPosition(inst_data.getPosition().x - 10, inst_data.getPosition().y - 10);
            inst_bground.setFillColor(sf::Color(255, 255, 255, 200));  
            inst_bground.setOutlineColor(sf::Color::Black);
            inst_bground.setOutlineThickness(2);

 
            window.draw(inst_bground);  
            window.draw(inst_data);  

            backbutton.setPosition((window.getSize().x - backbutton.getSize().x) / 2, window.getSize().y - 120);
            window.draw(backbutton);

            backtext.setFillColor(sf::Color::White);
            backtext.setPosition(
                backbutton.getPosition().x +(backbutton.getSize().x - backtext.getLocalBounds().width)/2, 
                backbutton.getPosition().y +(backbutton.getSize().y - backtext.getLocalBounds().height)/2 
            );
            window.draw(backtext);  
        }

        window.display();
    }

    file.close();
}



void WordleGame::setup(int size, float x, float y)
{
    _level=0; // LEVEL_1
    _size=size;
    array=new Word[_size]; // Allocate memory for the array of Word objects.

    for (int i=0;i<_size;i++) 
    {
        array[i].setup(5,0,0);
        array[i].set_pos(0,i*73);
    }

    text->setFont(_font);
    text->setString("WORDLE");
    text->setCharacterSize(80);
    text->setFillColor(sf::Color::Black);
    text->setPosition(175, 100);
}

void WordleGame::update(sf::RenderWindow& window, sf::Event& event1,string& str,Bool& b)
{
    if(b._is_won) 
    {
        text->setFillColor(sf::Color::Green);
        text->setString("You Win :) \n😊😊😊");
        text->setCharacterSize(50);
        _winSound.play(); 
    } 
    else if(b._is_lose) 
    {
        text->setPosition(100, 90);
        text->setFillColor(sf::Color::Red);
        text->setString("You Lost :( \nThe word was: " + str + " \n😢😢😢");
        text->setCharacterSize(50);
        _loseSound.play(); 
    } 
    else
    {
        if(_level >= 0 && _level <= 5) // LEVEL_1 to LEVEL_6

        {
            array[static_cast<int>(_level)].update(window, event1, str, _level, b);
        }
    }
}

void WordleGame::draw(sf::RenderWindow& window, Bool& b)
{
    for (int i=0;i<=static_cast<int>(_level);i++)
    {
        array[i].draw(window);
    }
    window.draw(*text);
}

void WordleGame::set_pos(float x,float y)
{
    for (int i=0;i<_size;i++)
    {
        array[i].set_pos(x,y+(i*73));
    }
}

void WordleGame::endGame()
{
    Game::endGame();             // Call the base class method
    cout<< "Wordle game ended!"<<endl;
}

void WordleGame::render() 
{
    cout << "Rendering Wordle game: "<<get_name()<<endl;
}


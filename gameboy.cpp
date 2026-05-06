#include "gameboy.h"
#include <SFML/Window.hpp>
#include <iostream>
// Player class methods


Player::Player(const std::string& name, int score)
{
  this->name=name;
  this->score=score;
}

void Player::set_name(const string& name)
{
    this->name = name;
}

void Player::set_score(int score)
{
    this->score=score;
}

std::string Player::get_name() const 
{
   return name;
}

int Player::get_score() const 
{
    return score;
}

Screen::Screen(int width, int height, const std::string& title) 
    : window(sf::VideoMode(width, height), title) {}

// Display the contents of the window
void Screen::display() 
{
    window.display();
}

void Screen::clear()
{
    window.clear();
}

sf::RenderWindow& Screen::getWindow() 
{
    return window;
}

// Menu class methods

Menu::Menu()
{
    if(!font.loadFromFile("/home/noor/oop/Project/2/Orbitron-VariableFont_wght.ttf")) 
    { 
       cerr<<"Error loading font!"<<endl;
    }
}

//display the menu screen
void Menu::displayMenu(sf::RenderWindow& window,const string& title,const string& option1, const string& option2, const string& option3) 
{
    window.clear(sf::Color(43, 0, 79));  

    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setPosition(100, 50);

    string currentTitle = "";
    for (int i=0;i<title.size();i++)
    {
        currentTitle += title[i];
        text.setString(currentTitle);
        window.clear(sf::Color(43,0,79)); 
        window.draw(text);
        window.display();
        sf::sleep(sf::milliseconds(100)); 
    }

    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Green);
    text.setPosition(100, 150);
    
    string currentOption;
    for (size_t i=0;i<option1.size();++i)
    {
        currentOption += option1[i];
        text.setString(currentOption);
        window.draw(text);
        window.display();
        sf::sleep(sf::milliseconds(100));
    }

    text.setPosition(100, 200);
    currentOption.clear();
    for (int i=0;i<option2.size();i++)
    {
        currentOption+=option2[i];
        text.setString(currentOption);
        window.draw(text);
        window.display();
        sf::sleep(sf::milliseconds(100));
    }

    text.setPosition(100, 250);
    currentOption.clear();
    for (int i=0;i<option3.size();i++) 
    {
        currentOption+=option3[i];
        text.setString(currentOption);
        window.draw(text);
        window.display();
        sf::sleep(sf::milliseconds(100));
    }

    text.setPosition(100, 300);
    text.setFillColor(sf::Color::Blue);
    text.setString("Press 1, 2, or 3 to select a game or Q to quit");
    window.draw(text);
    window.display();
}

// Constructor for GameBoy class
GameBoy::GameBoy() : screen(1024, 768, "GameBoy System")
{
  c_game=nullptr;
}


void GameBoy::start()
{
    sf::RenderWindow& window=screen.getWindow();
	sf:: Music music;
	if(!music.openFromFile("/home/noor/gameboy/music_loop.wav"))
	{
		cout << "Error loading music "<< endl;
		exit(-1);
	}
	music.setLoop(true);
	music.play();
    // Show splash screen
    splashScreen(window);

    // Show loading screen
    loadingScreen(window);

    // Get player name
    getPlayerName(window);

    // Main menu options with animation
    menu.displayMenu(window, "GameBoy System", 
                     "1. Snake Game", "2. Wordle Game", "3. Hang-man Game");

    while (window.isOpen())
    {
    	music.play();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type==sf::Event::Closed) 
            {
                window.close();
            }
            if(event.type==sf::Event::KeyPressed)
            {
                // Handle key presses for selecting a game
                if (event.key.code==sf::Keyboard::Num1)
                {
                    music.stop();
                    switchGame(1); 
                }
                if (event.key.code==sf::Keyboard::Num2) 
                {
                    music.stop();
                    switchGame(2);
                }
                if (event.key.code==sf::Keyboard::Num3)
                {
                    music.stop();
                    switchGame(3);
                }
                if (event.key.code == sf::Keyboard::Q)
                {
                    window.close();
                }
            }
        }
    }
    music.play();
}
void GameBoy::splashScreen(sf::RenderWindow& window)
{
    sf::Texture texture;
    if (!texture.loadFromFile("/home/noor/oop/Project/2/image.png"))
    {
        cerr<<"Error loading PNG image!"<<endl;
        return;
    }
    sf::Sprite sprite(texture);

    // Get the size of the window
    sf::Vector2u windowSize=window.getSize();
    
    // Scale the sprite to fit the window size
    sprite.setScale(
        static_cast<float>(windowSize.x)/texture.getSize().x, 
        static_cast<float>(windowSize.y)/texture.getSize().y  
    );

    window.clear(sf::Color(169,169,169)); 

    window.draw(sprite);
    window.display();

    sf::sleep(sf::seconds(1));
    sf::Font font;
    if (!font.loadFromFile("/home/noor/oop/Project/2/Orbitron-VariableFont_wght.ttf")) 
    {  
        cerr<<"Error loading font!"<<endl;
        return;
    }

    sf::Text line1;
    line1.setFont(font);
    line1.setString("Press any key to continue");
    line1.setCharacterSize(30);

    line1.setFillColor(sf::Color::Yellow); 

    line1.setOutlineColor(sf::Color::Black);
    line1.setOutlineThickness(2);

    // for the position of the message
    line1.setPosition(windowSize.x/2-line1.getLocalBounds().width/2,windowSize.y-50);  

    window.clear(sf::Color(169,169,169)); 
    window.draw(sprite);
    window.draw(line1);  
    window.display();

    bool key_pressed=false;
    while (!key_pressed)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type==sf::Event::KeyPressed)
            {
                key_pressed=true;
            }
        }

       
        window.clear(sf::Color(169,169,169));
        window.draw(sprite);  
        window.draw(line1); 
        window.display();
    }
}

// Show loading screen
void GameBoy::loadingScreen(sf::RenderWindow& window)
{
    sf::Text line2("Loading", menu.font, 30);
    line2.setFillColor(sf::Color::Green);
    line2.setPosition(250, 250);

    window.clear(sf::Color(43, 0, 79)); 
    window.draw(line2);
    window.display();

    sf::Clock clock;
    string dots="";
    float dotDelay=0.5f;    // time interval for adding dots
    int maxdots=4;         
    float lastUpdate=0.0f;

    while (clock.getElapsedTime().asSeconds()<6.0f)
    {
        float elapsed = clock.getElapsedTime().asSeconds();
        if (elapsed - lastUpdate >= dotDelay)
        {
            // Add a dot or reset dots
            if (dots.length()<maxdots) 
            {
                dots+=".";
            }
            else 
            {
               dots=""; 
            }

            line2.setString("Loading" + dots);
            
            window.clear(sf::Color(43, 0, 79)); 
            window.draw(line2);
            window.display();

            lastUpdate = elapsed;
        }
    }

    line2.setString("Loading....");
    window.draw(line2); 
    window.display();
}

// Get player name
void GameBoy::getPlayerName(sf::RenderWindow& window)
{
    sf::Text line3("Enter your name: ",menu.font,30);
    line3.setFillColor(sf::Color::Yellow);
    line3.setPosition(100, 100);

    sf::Text d_name("", menu.font, 30);
    d_name.setFillColor(sf::Color::White);
    d_name.setPosition(100, 150);

    std::string player_name="";
    bool check_name=false;

    while (!check_name) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type==sf::Event::Closed)
            {
                window.close();
            }
            if (event.type==sf::Event::TextEntered) 
            {
                if (event.text.unicode==8 && !player_name.empty())
                {  // Handle backspace
                    player_name.pop_back();
                } 
                else if (event.text.unicode==13)
                {  // Handle Enter key
                    check_name = true;
                } 
                else if(event.text.unicode<128 && event.text.unicode!=8)
                {  // Accept printable characters
                    player_name += static_cast<char>(event.text.unicode);
                }
            }
        }

        d_name.setString(player_name);
        window.clear(sf::Color(43,0,79));
        window.draw(line3);
        window.draw(d_name);
        window.display();
    }

    player.set_name(player_name); 
}

// switch game which game to play
void GameBoy::switchGame(int choice)
{
    if(c_game!=nullptr)
    {
        delete c_game;
    }
    switch (choice)
    {
        case 1:
            cout << "Starting Snake Game..."<<endl;
            c_game = new main_snake("Snake...");
            c_game->startGame();
            break;
        case 2:
            cout<<"Starting Wordle Game..."<<endl;
            c_game=new WordleGame("Wordle");  
            c_game->startGame();        
            break;
        case 3:
            cout<<"Starting Hang-man Game..." <<endl;
            c_game=new Hangman("Hangman");
            c_game->startGame();
            break;
        default:
            cout<<"Invalid selection!"<<endl;
            break;
    }
}

GameBoy::~GameBoy() 
{
    if(c_game!=nullptr)
    {
        delete c_game; 
        c_game = nullptr;
    }
}

int main() 
{
    GameBoy gameboy;
    gameboy.start();
    return 0;
}


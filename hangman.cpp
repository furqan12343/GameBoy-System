#include"hangman.h"


using namespace std;

Hangman::Hangman(const char* gameName) : Game(gameName) // Updated constructor
{
    for (int i = 0; i < 9; ++i)
    {
        std::string filename = "/home/noor/oop/Project/2/HangMan (" + std::to_string(i + 1) + ").png";
        if (!textures[i].loadFromFile(filename))
        {
            std::cerr << "Failed to load " << filename << std::endl;
            exit(1);
        }
    }
    sprite.setPosition(500, 50);
    sprite.setScale(0.5, 0.5);
}

Hangman::~Hangman() {}

void Hangman::updateStage(int stage)
{
    if (stage >= 0 && stage < 9)
    {
        sprite.setTexture(textures[stage]);
    }
}

void Hangman::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Hangman::startGame()
{
    sf::RenderWindow window(sf::VideoMode(1080, 820), "Hangman Game");

    // Background setup
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("/home/noor/oop/Project/2/background1.png"))
    {
        std::cerr << "Failed to load background image" << std::endl;
        return;
    }
    sf::Sprite background(backgroundTexture);

    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    background.setScale(scaleX, scaleY);

    sf::SoundBuffer winBuffer, loseBuffer;
    if (!winBuffer.loadFromFile("/home/noor/oop/Project/2/win.wav") ||
        !loseBuffer.loadFromFile("/home/noor/oop/Project/2/die.wav"))
    {
        std::cerr << "Failed to load sound files" << std::endl;
        return;
    }
    sf::Sound winSound(winBuffer);
    sf::Sound loseSound(loseBuffer);

    sf::Font font;
    if (!font.loadFromFile("/home/noor/oop/Project/2/font.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    sf::Text wordText("", font, 50);
    wordText.setPosition(100, 200);
    wordText.setFillColor(sf::Color::Black);

    sf::Text guessedText("", font, 50);
    guessedText.setPosition(100, 400);
    guessedText.setFillColor(sf::Color::Black);

    sf::Text winText, loseText, correctWordText, pressEsc, startMessage;

    // Start message
    startMessage.setString("Press your first guess letter to start the game");
    startMessage.setFont(font);
    startMessage.setCharacterSize(40);
    startMessage.setFillColor(sf::Color::Black);
    startMessage.setPosition(100, 100);

    // List of words to guess
    std::string words[] = {
        "biryani", "karahi", "haleem", "nihari", "chapli", "qorma",
        "ibrahim", "furqan", "noor", "pakistan", "roti", "korma", "chai"};

    srand(time(nullptr));
    std::string word = words[rand() % (sizeof(words) / sizeof(words[0]))];

    // Game state
    std::string guessedLetters = "";
    int numIncorrectGuesses = 0;
    bool gameStarted = false;
    bool gameOver = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered && !gameOver)
            {
                if (event.text.unicode >= 'a' && event.text.unicode <= 'z')
                {
                    gameStarted = true;

                    char letter = static_cast<char>(event.text.unicode);
                    if (guessedLetters.find(letter) == std::string::npos)
                    {
                        guessedLetters += letter;

                        if (word.find(letter) == std::string::npos)
                        {
                            numIncorrectGuesses++;
                            updateStage(numIncorrectGuesses);
                        }

                        std::string displayedWord = "";
                        for (char c : word)
                        {
                            if (guessedLetters.find(c) != std::string::npos)
                            {
                                displayedWord += c;
                            }
                            else
                            {
                                displayedWord += "_";
                            }
                        }

                        wordText.setString(displayedWord);

                        if (displayedWord.find("_") == std::string::npos)
                        {
                            winSound.play();
                            gameOver = true;
                            winText.setString("You Win!");
                            winText.setFont(font);
                            winText.setCharacterSize(100);
                            winText.setFillColor(sf::Color::Black);
                            winText.setPosition(100, 50);
                            pressEsc.setString("Press Esc to exit");
                            pressEsc.setFont(font);
                            pressEsc.setCharacterSize(50);
                            pressEsc.setFillColor(sf::Color::Black);
                            pressEsc.setPosition(100, 700);
                        }

                        if (numIncorrectGuesses == 8)
                        {
                            loseSound.play();
                            gameOver = true;

                            loseText.setString("You Lose!");
                            loseText.setFont(font);
                            loseText.setCharacterSize(100);
                            loseText.setFillColor(sf::Color::Black);
                            loseText.setPosition(100, 50);

                            correctWordText.setString("The correct word was: " + word);
                            correctWordText.setFont(font);
                            correctWordText.setCharacterSize(50);
                            correctWordText.setFillColor(sf::Color::Black);
                            correctWordText.setPosition(100, 600);

                            pressEsc.setString("Press Esc to exit");
                            pressEsc.setFont(font);
                            pressEsc.setCharacterSize(50);
                            pressEsc.setFillColor(sf::Color::Black);
                            pressEsc.setPosition(100, 700);
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(background);

        if (gameStarted)
        {
            window.draw(wordText);
            window.draw(guessedText);
            draw(window);
        }
        else
        {
            window.draw(startMessage);
        }

        if (gameOver)
        {
            window.draw(winText);
            window.draw(loseText);
            window.draw(correctWordText);
            window.draw(pressEsc);
        }

        window.display();
    }
}


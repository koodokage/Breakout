
#include "SFML/Graphics.hpp"
#include "GameScreen.h"
#include "Player.h"
#include "Ball.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "Brick.h"
#include "UIManager.h"

sf::Color generateRandomColor() {
    int r, g, b;

    // Generate random values for red, green, and blue components
    do {
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
    } while ((r <= 50 && g <= 50 && b <= 50) ||  // Avoiding blackish colors
        (r >= 220 && g <= 50 && b <= 50) ||  // Avoiding reddish colors
        (r >= 220 && g >= 220 && b <= 50)); // Avoiding yellowish colors

    return sf::Color(r, g, b);
}

int main()
{
    srand(time(nullptr));
    sf::Clock clock;
    float deltaTime = 0.0f;

    GameScreen::GetInstance()->CreateWindow(910,512, "BREAKOUT!");
    sf::RenderWindow& currentWindow = GameScreen::GetInstance()->GetRenderWindow();

    UIManager::GetInstance()->SetPanel(EWidgetPanelState::HUD);

    //PLAYER INSTANCE
    sf::RectangleShape* shapePlayer = new sf::RectangleShape(sf::Vector2f(125,5));
    sf::Vector2f startLoc = sf::Vector2f((currentWindow.getSize().x) / 2 - (shapePlayer->getSize().x / 2),
        currentWindow.getSize().y - (25) - 10);

    Player* playerInstance = new Player(shapePlayer, sf::Color::Yellow, startLoc);

    //BALL INSTANCE
    startLoc = sf::Vector2f(currentWindow.getSize().x / 2 - (shapePlayer->getSize().x / 2) + 50,
        currentWindow.getSize().y - (shapePlayer->getSize().y) - 100);
    sf::CircleShape* shapeBall = new sf::CircleShape(10);

    Ball* ballInstance = new Ball(shapeBall,sf::Color::Red, startLoc,6000.0f);


    std::vector<Brick*> bricks;

    //Scripted Level
    bool birckBoard[8][8] = {   {false,false,false,false,false,false,false,false},
                                {false,true,true,true,true,true,true,false},
                                {false,true,true,true,true,true,true,false},
                                {false,false,false,false,false,false,false,false},
                                {false,true,true,true,true,true,true,false},
                                {false,true,true,true,true,true,true,false},
                                {false,true,true,true,true,true,true,false},
                                {false,true,true,true,true,true,true,false},
    };

    Brick* brick;
    sf::RectangleShape* shapeBrick = new sf::RectangleShape(sf::Vector2f(100, 25));
    for (int8_t x = 0; x < 8; x++)
    {
        for (int8_t y = 0; y < 8; y++)
        {
            if (birckBoard[x][y] == true) {
                sf::Vector2f location = sf::Vector2f(15 + y * (100 + 10), 10 + x * (25 + 5));
                brick = new Brick(shapeBrick, generateRandomColor(), location);
                bricks.push_back(brick);
            }
        }
    }


    while (currentWindow.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        float fps = 1.f / deltaTime;
        //printf("FPS : %f \n", fps); 

        sf::Event event;
        while (currentWindow.pollEvent(event))
        {
            UIManager::GetInstance()->GetGUI().handleEvent(event);
            if (event.type == sf::Event::Closed)
                currentWindow.close();
        }


        if (playerInstance->IsCollide(ballInstance)){
            ballInstance->ReflectMovement();
        }

        for (int i = 0; i < bricks.size(); i++)
        {
            if (ballInstance->IsCollide(bricks[i])) {
                ballInstance->ReflectMovement();
                bricks.erase(bricks.begin() + i);
                break;
            }
        }

        playerInstance->Update(deltaTime);
        ballInstance->Update(deltaTime);
        

        currentWindow.clear();
        
        playerInstance->Draw();
        ballInstance->Draw();
        for (Brick* shape : bricks)
        {
            shape->Draw();
        }

        UIManager::GetInstance()->Update(deltaTime);

        currentWindow.display();


    }

    return 0;
}
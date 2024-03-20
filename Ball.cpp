#include "Ball.h"
#include "GameScreen.h"
#include <iostream>
#include "UIManager.h"

Ball::Ball(const sf::CircleShape* shape, const sf::Color color, const sf::Vector2f startLocation, const float ballSpeed){
    m_CircleShape = std::make_shared< sf::CircleShape>(*shape);
    m_CircleShape->setFillColor(color);
    m_CircleShape->setPosition(sf::Vector2f(startLocation.x, startLocation.y));
    M_BallVelocity = sf::Vector2f(-0.04f, -0.06f);
    m_BallSpeed = ballSpeed;
}

void Ball::Update(float deltaTime){

    // LEFT
    if (m_CircleShape->getPosition().x < 0) {
        M_BallVelocity.x *= -1;
    }
    // RIGHT
    else if (m_CircleShape->getPosition().x > GameScreen::GetInstance()->GetRenderWindow().getSize().x - m_CircleShape->getRadius()) {
        M_BallVelocity.x *= -1;
    }
    // TOP
    else if (m_CircleShape->getPosition().y < 0)
    {
        M_BallVelocity.y *= -1;
    }
    // BOT
    else if (m_CircleShape->getPosition().y > GameScreen::GetInstance()->GetRenderWindow().getSize().y - m_CircleShape->getRadius()) {
        //std::cout << "GAMEOVER" << std::endl;
        UIManager::GetInstance()->SetPanel(EWidgetPanelState::GameOver);

    }

    m_CircleShape->move(M_BallVelocity*m_BallSpeed*deltaTime);
}

sf::FloatRect Ball::GetBounds(){
    return m_CircleShape.get()->getGlobalBounds();
}

void Ball::Draw(){
    GameScreen::GetInstance()->GetRenderWindow().draw(*(m_CircleShape.get()));
}

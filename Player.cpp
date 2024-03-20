#include "Player.h"
#include "GameScreen.h"
#include <iostream>

Player::Player(const sf::RectangleShape* shape, const sf::Color color, const sf::Vector2f startLocation){
    m_RectangleShape = std::make_shared< sf::RectangleShape>(*shape);
    m_RectangleShape->setFillColor(color);
    m_RectangleShape->setPosition(startLocation);
}

void Player::Update(float deltaTime){

    m_PlayerHorizontalVelocity = 0.0f;

    //Listen Input Events 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_PlayerHorizontalVelocity = -m_PlayerSpeed * deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_PlayerHorizontalVelocity = m_PlayerSpeed * deltaTime;
    }

    //Move
    m_RectangleShape->move(m_PlayerHorizontalVelocity, 0.0f);

    //Clamp player shape position on screen view
    if (m_RectangleShape->getPosition().x < 0) {
        m_RectangleShape->setPosition(0, m_RectangleShape->getPosition().y);
    }
    else if (m_RectangleShape->getPosition().x + m_RectangleShape->getGlobalBounds().width > GameScreen::GetInstance()->GetRenderWindow().getSize().x)
    {
        m_RectangleShape->setPosition(GameScreen::GetInstance()->GetRenderWindow().getSize().x - m_RectangleShape->getGlobalBounds().width,
            m_RectangleShape->getPosition().y);
    }
}

sf::FloatRect Player::GetBounds(){
    return m_RectangleShape.get()->getGlobalBounds();
}

void Player::Draw() {
    GameScreen::GetInstance()->GetRenderWindow().draw(*(m_RectangleShape.get()));
}

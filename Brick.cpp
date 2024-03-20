#include "Brick.h"
#include "GameScreen.h"

Brick::Brick(const sf::RectangleShape* shape, const sf::Color color, const sf::Vector2f location){
    m_RectangleShape = std::make_shared< sf::RectangleShape>(*shape);
    m_RectangleShape->setFillColor(color);
    m_RectangleShape->setPosition(location);
}

sf::FloatRect Brick::GetBounds(){
    return (m_RectangleShape.get()->getGlobalBounds());
}

void Brick::Draw() {
    GameScreen::GetInstance()->GetRenderWindow().draw(*(m_RectangleShape.get()));
}
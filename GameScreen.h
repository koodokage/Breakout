#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class GameScreen{

public:
	 static inline GameScreen* GetInstance() {
		 return s_Instance = (s_Instance != nullptr) ? s_Instance : new GameScreen();
	}	

	 inline void CreateWindow(int width,int height,const char* gameTitle) {

		 m_Window = std::make_unique<sf::RenderWindow>(
			 sf::VideoMode(width, height), gameTitle, sf::Style::Close);
	 }

	 inline sf::RenderWindow& GetRenderWindow() const {
		 if (!m_Window) {
			 std::cerr << ("GAMESCREEN] WINDOW NOT CREATED") << std::endl;
		 }
		 return *m_Window.get();
	 }


private:
	GameScreen() {};
	static GameScreen* s_Instance;
	std::unique_ptr<sf::RenderWindow> m_Window;

};


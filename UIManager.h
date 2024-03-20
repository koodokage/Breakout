#pragma once
#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include "TGUI/Backend/SFML-Graphics.hpp"
#include <vector>

enum EWidgetPanelState {
	HUD,
	MainMenu,
	GameOver,
	Win,
	Pause
};

class UIManager{

public:
	static inline UIManager* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new UIManager();
	}

	void Update(float deltaTime);
	void SetPanel(EWidgetPanelState panel);
	tgui::Gui& GetGUI() const;

public:
	inline const EWidgetPanelState GetCurrentPanelState() const {
		return m_CurrentPanel;
	}
	inline const bool IsGamePaused() const {
		return m_IsPaused;
	}

private:
	UIManager();
	static UIManager* s_Instance;

private:
	sf::Time m_CurrentTime;
	sf::Clock m_Clock;
	sf::Font m_Font;
	std::vector<sf::Text> m_Texts;
	std::unique_ptr<tgui::Gui> m_Gui;
	EWidgetPanelState m_CurrentPanel = HUD;
	bool m_IsPaused;

private:
	void CreateText(const char* message, sf::Vector2f position, short charSize, sf::Color fillColor);
	tgui::Button::Ptr CreateWigetButton(const char* text, sf::Vector2f position,short charSize, sf::Vector2f size, sf::Color fillColor);
	void OpenHUDPanel();
	void OpenMainMenuPanel();
	void OpenGameOverPanel();
	void OpenWinPanel();
	void OpenPausePanel();
	void ClearElements();
	sf::Font LoadFont(const char* fileName);

};


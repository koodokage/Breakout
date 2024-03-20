#include "UIManager.h"
#include "GameScreen.h"

UIManager* UIManager::s_Instance = nullptr;
void UIManager::CreateText(const char* message, sf::Vector2f position, short charSize, sf::Color fillColor){


	tgui::Label::Ptr label = tgui::Label::create();
	label->setText(message);
	label->setPosition(position.x,position.y);
	label->setTextSize(charSize);

	tgui::Theme::Ptr theme = tgui::Theme::create("./Resources/themes/Black.txt");
	label->setRenderer(theme->getRenderer("Label"));
	label->getRenderer()->setTextColor(fillColor); // Change the text color to red


	m_Gui -> add(label);
	//sf::Text text;
	//text.setString(message);
	//text.setPosition(position);
	//text.setCharacterSize(charSize);
	//text.setFillColor(fillColor);
	//text.setFont(m_Font);

	//m_Texts.push_back(text);

}

tgui::Button::Ptr UIManager::CreateWigetButton(const char* text, sf::Vector2f position, short charSize, sf::Vector2f size, sf::Color fillColor){
	tgui::Button::Ptr btn = tgui::Button::create();
	btn->setText(text);
	btn->setTextSize(charSize);
	btn->setSize(size.x, size.y);
	btn->setPosition(position.x, position.y);
	m_Gui->add(btn);
	return btn;
}

void UIManager::OpenHUDPanel(){
	std::string str = "TIME: " + std::to_string(int(m_CurrentTime.asSeconds()));
	CreateText(str.c_str(), sf::Vector2f(GameScreen::GetInstance()->GetRenderWindow().getSize().x /2, 30), 42, sf::Color::White);
}

void UIManager::OpenMainMenuPanel(){
	CreateText("BREAKOUT! - MAINMENU", sf::Vector2f(30, 30), 32, sf::Color::White);
}

void UIManager::OpenGameOverPanel(){
	CreateText("GAME OVER", sf::Vector2f(30, 30), 32, sf::Color::White);
}

void UIManager::OpenWinPanel(){
	CreateText("WINNER", sf::Vector2f(30, 30), 32, sf::Color::White);
}

void UIManager::OpenPausePanel(){

}

void UIManager::ClearElements(){
	m_Texts.clear();
	m_Gui -> removeAllWidgets();
}

sf::Font UIManager::LoadFont(const char* fileName){
	sf::Font font;

	if (!font.loadFromFile(fileName)) {
		std::cout << "[FONT LOAD ERROR] " << fileName << std::endl;
	}

	return font;
}

UIManager::UIManager(){
	m_Gui = std::make_unique<tgui::Gui>(GameScreen::GetInstance()->GetRenderWindow());
	m_Font = LoadFont("./Resources/Anta-Regular.ttf");
}

void UIManager::Update(float deltaTime){

	m_CurrentTime = m_Clock.getElapsedTime();
	SetPanel(HUD);
	for (int i = 0; i < m_Texts.size(); i++)
	{
		GameScreen::GetInstance()->GetRenderWindow().draw(m_Texts[i]);
	}
	m_Gui->draw();
}

void UIManager::SetPanel(EWidgetPanelState panel){
	ClearElements();

	switch (panel)
	{
	case HUD:
		OpenHUDPanel();
		m_IsPaused = false;
		break;
	case MainMenu:
		OpenMainMenuPanel();
		m_IsPaused = true;
		break;
	case GameOver:
		OpenGameOverPanel();
		m_IsPaused = true;
		break;
	case Win:
		OpenWinPanel();
		m_IsPaused = true;
		break;
	case Pause:
		OpenPausePanel();
		m_IsPaused = true;
		break;
	default:
		break;
	}

	m_CurrentPanel = panel;
}

tgui::Gui& UIManager::GetGUI() const{

	if (m_Gui.get() == nullptr) {
		std::cerr<<("[UIMANAGER] GUI NOT CREATED")<<std::endl;
	}

	return *m_Gui.get();
}

#include "MainMenuScreen.h"



MainMenuScreen::MainMenuScreen(Bengine2::Window* window) : m_window(window) {
	m_screenIndex = SCREEN_INDEX_MAINMENU;
}


MainMenuScreen::~MainMenuScreen() {
	//Empty
}

int MainMenuScreen::getNextScreenIndex() const {
	return m_nextScreenIndex;
}
int MainMenuScreen::getPreviousScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

void MainMenuScreen::build() {

}
void MainMenuScreen::destroy() {

}

void MainMenuScreen::onEntry() {
	//init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(32.0f);	//32 pixels per meter

	initUI();
}

void MainMenuScreen::onExit() {
	m_gui.destroy();
}

void MainMenuScreen::update() {
	m_camera.update();
	checkInput();
}

void MainMenuScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	m_gui.draw();

}

void MainMenuScreen::initUI() {
	//init the UI
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.setFont("DejaVuSans-10");
	CEGUI::PushButton* newGameButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.45f, 0.5f, 0.1f, 0.05f), glm::vec4(0.0f), "NewGameButton"));
	newGameButton->setText("New Game");
	//set the event to be called when we click
	newGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreen::onNewGameClicked, this));

	CEGUI::PushButton* exitButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.45f, 0.62f, 0.1f, 0.05f), glm::vec4(0.0f), "ExitButton"));
	exitButton->setText("Exit Game");
	//set the event to be called when we click
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuScreen::onExitClicked, this));



	//CEGUI::Combobox* testCombobox = static_cast<CEGUI::Combobox*>(m_gui.createWidget("TaharezLook/Combobox", glm::vec4(0.2f, 0.2f, 0.1f, 0.05f), glm::vec4(0.0f), "TestCombobox"));
	//test
	//CEGUI::Editbox* testEditbox = static_cast<CEGUI::Editbox*>(m_gui.createWidget("AlfiskoSkin/Editbox", glm::vec4(0.4f, 0.2f, 0.1f, 0.05f), glm::vec4(0.0f), "TestEditBox"));


	m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	m_gui.showMouseCursor();
	SDL_ShowCursor(0);	//turns the default cursor off, so we're only seeing one cursor on the screen
}

void MainMenuScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_gui.onSDLEvent(evnt);
		switch (evnt.type) {
		case SDL_QUIT:
			onExitClicked(CEGUI::EventArgs());
			break;
		}
	}
}

bool MainMenuScreen::onNewGameClicked(const CEGUI::EventArgs& e) {
	m_nextScreenIndex = SCREEN_INDEX_GAMEPLAY;
	m_currentState = Bengine2::ScreenState::CHANGE_NEXT;
	return true;
}


bool MainMenuScreen::onExitClicked(const CEGUI::EventArgs& e) {
	m_currentState = Bengine2::ScreenState::EXIT_APPLICATION;
	return true;
}
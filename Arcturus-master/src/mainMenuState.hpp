#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "gameState.hpp"
#include <iostream>
#include "mainMenuUI.hpp"

class MainMenuState : public GameState
{
public:
  MainMenuState() : GameState(), UI_(std::make_shared<MainMenuUI>()){}
  void pause();
  void resume();

  void handleEvents(GameEngine &game, sf::Event event);
  void update(GameEngine &game, float &deltaTime);
  void draw(GameEngine &game);

private:

  std::shared_ptr<MainMenuUI> UI_;
};

#endif

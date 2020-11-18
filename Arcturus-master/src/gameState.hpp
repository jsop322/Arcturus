#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "gameEngine.hpp"

class GameEngine;

class GameState
{
public:

  virtual void pause() = 0;
  virtual void resume() = 0;
  virtual void handleEvents(GameEngine &game, sf::Event event) = 0;
  virtual void update(GameEngine &game, float &deltaTime) = 0;
  virtual void draw(GameEngine &game) = 0;

  //This function MIGHT be obsolete, not sure. Will figure it out... -AH
  void changeState(GameEngine &game, std::shared_ptr<GameState> state) { game.changeState(state); }

private:
};

#endif

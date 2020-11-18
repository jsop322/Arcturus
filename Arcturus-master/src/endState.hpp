#ifndef ENDSTATE_H
#define ENDSTATE_H
#include <SFML/Graphics.hpp>
#include "gameState.hpp"

class EndState : public GameState
{
public:
  EndState(bool playerWin);

  virtual void pause();
  virtual void resume();
  virtual void handleEvents(GameEngine &game, sf::Event event);
  virtual void update(GameEngine &game, float &deltaTime);
  virtual void draw(GameEngine &game);

private:

  sf::Texture winScreen_;
  sf::Sprite winScreenSprite_;
};

#endif

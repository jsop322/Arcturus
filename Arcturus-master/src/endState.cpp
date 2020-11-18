#include "endState.hpp"
#include <iostream>

EndState::EndState(bool playerWin)
{
  if(playerWin)
  {

    winScreen_.loadFromFile("resources/graphics/VictoryScreen.png");
    winScreenSprite_.setTexture(winScreen_);
  }

  if(!playerWin)
  {
    winScreen_.loadFromFile("resources/graphics/DefeatScreen.png");
    winScreenSprite_.setTexture(winScreen_);
  }
  std::cout<< "YALLAH"<<std::endl;
}

void EndState::draw(GameEngine &game)
{
  game.getWindow()->clear();
  game.getWindow()->draw(winScreenSprite_);
  game.getWindow()->display();
}

void EndState::pause()
{

}
void EndState::resume()
{

}
void EndState::handleEvents(GameEngine &game, sf::Event event)
{
  if (event.type == sf::Event::Closed)
      game.quit();
  if(event.type == sf::Event::KeyReleased)
  {
      if (event.key.code == sf::Keyboard::Escape)
      {
          game.previousState();
          game.previousState();
      }
  }
}
void EndState::update(GameEngine &game, float &deltaTime)
{

}

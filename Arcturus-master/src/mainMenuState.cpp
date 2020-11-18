#include "gameEngine.hpp"
#include "gameState.hpp"
#include "mainMenuState.hpp"
#include "playState.hpp"
#include "mainMenuUI.hpp"

/*
** Sets the game on pause.
** Might be used just to set game time. Should concider using proper pauseState.
*/

void MainMenuState::pause()
{
  std::cout << "PELI PIIP!" << std::endl;
}

/*
** Resumes the game.
** Might be used just to set game time. Should concider using proper pauseState.
*/
void MainMenuState::resume()
{
  std::cout << "JATKUU!" << std::endl;
}

/*
** Handles user input in the main menu. Clicking "start game" or "quit game"
*/
void MainMenuState::handleEvents(GameEngine &game, sf::Event event)
{
  (*UI_).handleEvents(game, event);
/*  if (event.type == sf::Event::Closed)
      game.quit();
  if(event.type == sf::Event::KeyReleased)
  {
    if (event.key.code == sf::Keyboard::Return)
        game.nextState(std::make_shared<PlayState>());
  } */
}

/*
** Updates game logic/state/map? TODO: Write description for update function
*/
void MainMenuState::update(GameEngine &game, float &deltaTime)
{

}

/*
** Calls UI calss to draw main menu.
*/
void MainMenuState::draw(GameEngine &game)
{
  (*UI_).draw(game);

  //sf::CircleShape shape(32*5); //Placeholder command, only for testing
  //game.getWindow()->clear();
  //game.getWindow()->draw(shape);
  //game.getWindow()->display();
}

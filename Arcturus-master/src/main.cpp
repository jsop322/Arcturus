#include "gameEngine.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
int main()
{

  //Inits the game engine
  GameEngine game;
  //Starts the game clock
  sf::Clock clock;
  //play the main theme
  sf::Music Music;
  int statecount;
  /*if(!mainMenuTheme.openFromFile("resources/audio/arctumenu.ogg"))
  {
    return -1; //ERROR
  }
  mainMenuTheme.play();
  mainMenuTheme.setLoop(true);*/

  while (game.isRunning())
  {
    //if the gamestate changes, change the music
    if (game.changeMusic() == true)
    {
      statecount = game.getStateCount();
      switch(statecount)
      {
        case 1 :
          game.setMusicFalse();
          if(!Music.openFromFile("resources/audio/arctumenu.ogg")) //main menu theme
          {
            return -1; //ERROR
          }
          Music.play();
          Music.setLoop(true);
          break;
        case 2 :
          game.setMusicFalse();
          if(!Music.openFromFile("resources/audio/arcturusbassoaah.ogg")) //ingame music
          {
            return -1; //ERROR
          }
          Music.play();
          Music.setLoop(true);
          break;
      }
    }
    //Between each loop the clock is restarted to get the time elapsed during each loop.
    sf::Time deltaTime = clock.restart();
    float deltaTimeAsSeconds = deltaTime.asSeconds();

    //Check what player wants to do
    game.handleEvents();
    //Update gamestate accordingly
    game.update(deltaTimeAsSeconds); //NOTE: I'm not 100% sure about running it in as seconds but we'll see. -AH
    //Draw out everything so that the player can see the changes in state
    game.draw();
  }
  return 0;
}

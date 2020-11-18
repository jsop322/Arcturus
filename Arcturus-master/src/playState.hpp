#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gameEngine.hpp"
#include <iostream>
#include "gameState.hpp"
#include "endState.hpp"
#include "map.hpp"
#include "playUI.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <string>
#include <iostream>

class PlayState : public GameState
{
public:
  PlayState(std::string mapName, sf::Texture* mapTexture, sf::Texture* unitTexture, sf::Texture* buildingTexture,
    Animation* soldierWalking, Animation* soldierShooting, Animation* workerWalking, Animation* workerAct, Animation* tankDriving, Animation* tankShooting, Animation* mainBuilding,
    Animation* unitBuilding, Animation* factoryBuilding, Animation* resourceBuilding, Animation* esoldierWalking, Animation* esoldierShooting, Animation* eworkerWalking, Animation* eworkerAct, Animation* eTankDriving,
    Animation* eTankShooting, Animation* emainBuilding, Animation* eunitBuilding, Animation* efactoryBuilding);

  void pause();
  void resume();

  void handleEvents(GameEngine &game, sf::Event event);
  void handleViewEvents(GameEngine &game, sf::Event event);
  void update(GameEngine &game, float &deltaTime);
  void draw(GameEngine &game);
  sf::Vector2f convertPos(GameEngine &game, sf::Vector2i inputPos);


private:
  Map map;
  std::shared_ptr<PlayUI> UI_;
  Player player;
  Enemy enemy;
  sf::Vector2i mousepos_;
  bool viewMoved_;

};

#endif

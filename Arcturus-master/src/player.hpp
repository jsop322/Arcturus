#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <iostream>
#include "map.hpp"
#include "unit.hpp"
#include "workerUnit.hpp"
#include "soldierUnit.hpp"
#include "building.hpp"
#include "mainBuilding.hpp"
#include "unitBuilding.hpp"
#include "factoryBuilding.hpp"
#include "resourceBuilding.hpp"
#include "workerUnit.hpp"
#include "tankUnit.hpp"


class Player
{

public:
  //consturctor for the player class, one test unit initialized and position set
  Player();
  ~Player();

  void setTextures(Animation* soldierWalking, Animation* soldierShooting, Animation* workerWalking,
    Animation* workerAct, Animation* tankDriving, Animation* tankShooting, Animation* mainBuilding,
    Animation* resourceBuilding, Animation* unitBuilding, Animation* factoryBuilding);
  //void moveUnits();
  //update unit positions, buildings etc. called once every frame
  void update(float &deltaTime, Map* map);
  //player's mouse input handling
  void posCmd(sf::Vector2f mousepos, Map* map);
  //attack command
  bool attackCmd(sf::Vector2f mousepos);
  //draw units
  void draw(GameEngine &game);
  //test function for spawning units
  void spawnUnit();
  void addUnit(std::shared_ptr<Unit> unit);
  void removeUnit(Map* map);
  void removeBuilding();

  void makeStartingBase(float x, float y, Map* map);
  void buildBarracks(Map* map);
  void buildFactory(Map* map);
  void buildThreeDprinter(Map* map);
  void startUnitProduction();
  void produceUnit();
  void upgradeBuilding();
  bool isBaseDestroyed();

  //return the list containing units
  //std::vector<Unit> getUnits();
  void selectUnitsAndBuildings(sf::Vector2f mapPos);

  std::vector<Unit*> getSelectedUnits();
  std::vector<Building*> getSelectedBuilding();
  //returns a reference to the player unit vector
  std::vector<std::shared_ptr<Unit>>* getUnits();
  std::vector<std::shared_ptr<Building>>* getBuildings();

  void passEnemyUnits(std::vector<std::shared_ptr<Unit>>* enemyUnits);
  void passEnemyBuildings(std::vector<std::shared_ptr<Building>>* enemyBuildings);

  void clearSelectedUnits();

  bool addResource(int amount, int type);
  bool removeResource(int amount, int type);
  std::pair<int, int> currentResources(){ return std::pair<int,int>(gold_, silver_); }

private:
  float PI = 3.14159265;
  //TEST UNITS
  //soldierUnit unit;
  //soldierUnit newUnit;
  //unit position
  sf::Vector2f position_;
  //clock for updating animations
  sf::Clock frameClock;
  sf::Time frameTime;
  sf::Clock attackDelay;
  sf::Time baseAttackTime;
  //unit desired m_position
  sf::Vector2f des_position_;
  //unit's attack target position
  sf::Vector2f targetPosition_;
  //for dem right clickz
  bool rightclk_ = false;
  //TODO resurssit ym
  std::vector<std::shared_ptr<Unit>> playerUnits_;
  std::vector<std::shared_ptr<Unit>>* enemyUnits_;
  std::vector<Unit*> selectedUnits_;

  std::vector<std::shared_ptr<Building>> playerBuildings_;
  std::vector<std::shared_ptr<Building>>* enemyBuildings_;
  std::vector<Building*> selectedBuilding_;

  //sprite and texture for the selection indicator, these might be moved in the future
  sf::Sprite unitIndicatorSprite_;
  sf::Sprite buildingIndicatorSprite_;
  sf::Sprite tankIndicatorSprite_;
  sf::Texture unitIndicators_;
  sf::Texture buildingIndicator_;

  //current walking animation
  Animation* currentAnimation_;
  //current shooting animation
  Animation* currentShooting_;

  Animation* soldierWalking_;
  Animation* workerWalking_;
  Animation* workerAct_;
  Animation* tankDriving_;
  Animation* tankShooting_;
  Animation* soldierShooting_;
  Animation* mainBuilding_;
  Animation* unitBuilding_;
  Animation* factoryBuilding_;
  Animation* resourceBuilding_;

  bool isMoving;
  bool unitsAdded;
  bool buildingAdded;

  int silver_;
  int gold_;
};


#endif

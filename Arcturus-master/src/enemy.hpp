#ifndef ENEMY_H
#define ENEMY_H
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
#include "workerUnit.hpp"
#include "tankUnit.hpp"


class Enemy
{

public:
  //consturctor and destructor for the enemy class
  Enemy();
  ~Enemy();

  void setTextures(Animation* esoldierWalking, Animation* esoldierShooting,
  Animation* eworkerWalking, Animation* eworkerAct, Animation* etankDriving, Animation* etankShooting,
  Animation* emainBuilding, Animation* eunitBuilding, Animation* efactoryBuilding);
  //void moveUnits();
  //update unit positions, buildings etc. called once every frame
  void update(float &deltaTime, Map* map);
  //player's mouse input handling
  //void posCmd(sf::Vector2f mousepos, Map* map);
  //draw units
  void draw(GameEngine &game);
  //test function for spawning units
  void spawnUnit();
  //void addUnit(std::shared_ptr<Unit> unit);
  void produceUnit(Map* map, UnitType type);
  void removeUnit();
  //returns a reference to the enemy unit vector
  std::vector<std::shared_ptr<Unit>>* getUnits();
  std::vector<std::shared_ptr<Building>>* getBuildings();
  void passPlayerUnits(std::vector<std::shared_ptr<Unit>>* playerUnits);
  void passPlayerBuildings(std::vector<std::shared_ptr<Building>>* playerBuildings);
  //void makeStartingBase(float x, float y, Map* map);
  void makeStartingBase(float x, float y, Map* map);
  void posCmd(sf::Vector2f position, Map* map, int i);
  void moveUnit(int i, float &deltaTime);

  void buildBarracks(Map* map);
  void buildFactory(Map* map);
  bool isBaseDestroyed();
  //void startWorkerProduction();
  //void produceWorker();

  //return the list containing units
  //std::vector<Unit> getUnits();
  //void selectUnitsAndBuildings(sf::Vector2f mapPos);

  //std::vector<Unit*> getSelectedUnits();
  //std::vector<Building*> getSelectedBuilding();

  //void clearSelectedUnits();

  //void spawnDummyUnit();
  bool addResource(int amount, int type);
  std::pair<int, int> currentResources(){ return std::pair<int,int>(gold_, silver_); }

private:
  float PI = 3.14159265;
  float dx;
  float dy;
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
  //player unit position
  sf::Vector2f playerUnitPosition_;
  //player building position
  sf::Vector2f playerBuildingPosition_;
  //enemy unit position
  sf::Vector2f enemyUnitPosition_;
  //unit's attack target position
  sf::Vector2f targetPosition_;
  //for dem right clickz

  //TODO resurssit ym
  std::vector<std::shared_ptr<Unit>> enemyUnits_;
  //std::vector<Unit*> selectedEnemyUnits_;
  std::vector<std::shared_ptr<Unit>>* playerUnits_;
  std::vector<std::shared_ptr<Building>>* playerBuildings_;
  std::vector<std::shared_ptr<Building>> enemyBuildings_;
  //std::vector<Building*> selectedEnemyBuilding_;

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

  bool isMoving;
  bool unitsAdded;
  bool buildingAdded;
  bool attackingUnits_;

  int silver_;
  int gold_;

  sf::Clock soldierClock_;
  sf::Clock tankClock_;
  sf::Clock actionClock_;

  float spawntime1_ = 61;
  float spawntime2_ = 103;
};


#endif

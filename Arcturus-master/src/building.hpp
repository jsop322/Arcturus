#ifndef BUILDING_H
#define BUILDING_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <utility>
#include <iostream> //for printing to console (in problem cases)
#include <deque>
#include "gameEngine.hpp"
#include "map.hpp"
#include "Animation.hpp"

enum StructureType
{
  Mainbuilding, //main building type
  Unitbuilding, //unit production
  Factorybuilding,      //tank production
  Resourcebuilding //resource productionTime
};

class Building
{
public: //destructors still missing
  Building(){}
  Building(Map* gameMap, int size, std::vector<sf::Sprite> pictures, sf::Vector2f coords);
  virtual void update(){} //as time passes for buildings, resources/units get produced
  //update function also handles the construction of the building
  void draw(GameEngine &game);
  const StructureType getType() const;
  const float getMaxHealth() const;
  const float getCurrentHealth() const;
  void damageBuilding(unsigned int dmg){ curHP -= dmg; }
  const int getLevel() const;
  const bool isComplete() const;
  const std::string getName() const;
  const float getBuildTime() const;
  void completeConstruction();
  bool canUpgradeBuilding();
  void upgradeBuilding(); //return whether building was upgraded
  bool takeDamage(int damage); //return whether building was destroyed
  const sf::Vector2f getLocation() const;
  const sf::Sprite getSprite() const;
  AnimatedSprite& getAnimatedSprite();
  const bool ownedByPlayer() const;
  //const std::pair<Resource, int> getConstCost() const; //NOTE: cost will be implemented as simple int or pair of ints (silver/gold)
  sf::Vector2f findFreeLocation();
  bool canSpawn() const;
  void setCanSpawn(bool setTo) {canSpawn_ = setTo;}
  bool getAnimationStatus(){ return playAnimation_; }
  sf::Vector2f getSpawnLocation() const;
  virtual void produceUnit(){}

  virtual std::pair <bool, int> getResources() = 0;

  virtual int unitCost() {return unitCost_;}
  virtual int upgradeCost() {return upgradeCost_;}
  float getProduceTime(){ return unitSpawnTime_; }
  float getCurrentTime(){ return clock.getElapsedTime().asSeconds(); }
  bool isProducing(){ return producing_; }
  int getBuildingCost() const {return buildingCost_;}

protected: //put upgrade cost somewhere?
  sf::Clock clock;
  sf::Clock animationClock;
  int i; //
  Map* tileMap;
  //if multiple different kinds of resources required, the above will need to be a vector probably
  bool ownedByPlayer_;
  float buildTime;
  std::string name_;
  float maxHP;
  float curHP;
  int maxLevel;
  int level; //at higher level more/stronger units available, maybe faster resource production too
  int size_; //building takes up size x size tiles
  bool complete; //false if building is still being built
  bool producing_;
  bool canSpawn_;
  bool playAnimation_;
  sf::Vector2f spawnLocation_;
  StructureType type_;

  float unitSpawnTime_;
  int unitCost_;
  int upgradeCost_;
  int buildingCost_;

  std::vector<sf::Sprite> sprites; //contains size x size sprites
  sf::Vector2f location_; //probably referring to the center coordinates (or maybe a corner)
  //some kind of hitbox is certainly necessary but maybe it will work through the tile class instead

  sf::Texture* buildingTileset_;
  sf::Sprite buildingSprite_;
  //replace the normal sprites with these
  AnimatedSprite animatedSprite_;
  Animation animation_;
};

#endif

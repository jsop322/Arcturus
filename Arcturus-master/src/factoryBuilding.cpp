#include "factoryBuilding.hpp"

FactoryBuilding::FactoryBuilding(Map* gameMap, bool ownedByPlayer, Animation* factoryBuilding, sf::Vector2f coords, bool isComplete)
{
  tileMap = gameMap;
  ownedByPlayer_ = ownedByPlayer;
  location_ = coords;
  complete = isComplete;

  AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
  animatedSprite_ = animatedSprite;
  animatedSprite_.setPosition(location_.x*32, location_.y*32);
  animatedSprite_.play(*factoryBuilding);

  size_ =  3;
  //size for factory is actually 3 x 2, but need to change building class first
  type_ = Factorybuilding;

  maxHP = 400;
  curHP = maxHP;
  buildTime = 15;
  buildingCost_ = 250;

  level = 1;
  maxLevel = 4;
  upgradeCost_ = 50;

  canSpawn_ = false;
  unitSpawnTime_ = 10;
  unitCost_ = 150;

  playAnimation_ = false;
  producing_ = false;
 }

 void FactoryBuilding::setNonPassable()
 {
   tileMap->setTileNonPassable(sf::Vector2f(location_.x, location_.y));
   tileMap->setTileNonPassable(sf::Vector2f(location_.x+1, location_.y));
   tileMap->setTileNonPassable(sf::Vector2f(location_.x+2, location_.y));
   tileMap->setTileNonPassable(sf::Vector2f(location_.x, location_.y+1));
   tileMap->setTileNonPassable(sf::Vector2f(location_.x+1, location_.y+1));
   tileMap->setTileNonPassable(sf::Vector2f(location_.x+2, location_.y+1));
 }

 void FactoryBuilding::setPassable()
 {
   tileMap->setTilePassable(sf::Vector2f(location_.x, location_.y));
   tileMap->setTilePassable(sf::Vector2f(location_.x+1, location_.y));
   tileMap->setTilePassable(sf::Vector2f(location_.x+2, location_.y));
   tileMap->setTilePassable(sf::Vector2f(location_.x, location_.y+1));
   tileMap->setTilePassable(sf::Vector2f(location_.x+1, location_.y+1));
   tileMap->setTilePassable(sf::Vector2f(location_.x+2, location_.y+1));
 }

 void FactoryBuilding::produceUnit()
 {
   if (workQueue_.empty()) {
     clock.restart();
     //this is needed so that the unit is not produced instantly when no production has taken place for a while
   }
   workQueue_.push_back(unitSpawnTime_);
   producing_ = true;
 }

void FactoryBuilding::update()
{
  if( playAnimation_ == true )
  {

    if(i == 0)
    {
      animationClock.restart();
    }

    sf::Time animationTime = animationClock.getElapsedTime();
    i++;

    if(animationTime.asSeconds() > 0.98)
    {

      playAnimation_ = false;
    }
  }
  if (!this->isComplete())
  {
    sf::Time elapsedFromBuild = clock.getElapsedTime();
    if (elapsedFromBuild.asSeconds() >= buildTime)
    {
      this->completeConstruction();
    }
  } else { //if enough time has passed produce first unit in queue
    if (!workQueue_.empty())
    {
        sf::Time elapsedFromStart = clock.getElapsedTime();
        if (elapsedFromStart.asSeconds() >= workQueue_[0])
        {
          workQueue_.pop_front();

          //spawnLocation_ = findFreeLocation(); //TODO: Does not work currently, Check why and fix!
          spawnLocation_ = sf::Vector2f(location_.x*32+(size_/2)*32+16, location_.y*32+size_*32+16);
          //currently asssuming unit stacking is allowed
          canSpawn_ = true;
          i = 0;
          playAnimation_ = true;
          if(workQueue_.empty()){
            producing_ = false;
          }
          clock.restart(); //restart clock for next production
        }
    }
  }
}

 const std::deque<float> FactoryBuilding::getQueue() const
 {
   return workQueue_;
 }
/*
const std::vector< std::pair<int, Unit> > FactoryBuilding::getUnits() const
{
  return produceableUnits;
}
*/

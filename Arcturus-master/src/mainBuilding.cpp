#include "mainBuilding.hpp"

MainBuilding::MainBuilding(Map* gameMap, bool ownedByPlayer, Animation* mainBuilding, sf::Vector2f coords, bool isComplete)
{
    tileMap = gameMap;
    ownedByPlayer_ = ownedByPlayer;
    //buildingTileset_ = buildingTileset;
    location_ = coords;
    complete = isComplete;

    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite_ = animatedSprite;
    animatedSprite_.setPosition(location_.x*32, location_.y*32);
    animatedSprite_.play(*mainBuilding);

    /*buildingSprite_.setTexture(*buildingTileset_);
    buildingSprite_.setTextureRect(sf::IntRect(32,32,32*3,32*3));*/
    size_ = 3;
    type_ = Mainbuilding;

    maxHP = 500;
    curHP = maxHP;

    level = 1;
    maxLevel = 3;
    upgradeCost_ = 50;

    canSpawn_ = false;
    unitSpawnTime_ = 5;
    unitCost_ = 100;

    playAnimation_ = false;
    producing_ = false;
}

void MainBuilding::setPassable()
{
  tileMap->setTilePassable(sf::Vector2f(location_.x, location_.y));
  tileMap->setTilePassable(sf::Vector2f(location_.x+1, location_.y));
  tileMap->setTilePassable(sf::Vector2f(location_.x+2, location_.y));
  tileMap->setTilePassable(sf::Vector2f(location_.x, location_.y+1));
  tileMap->setTilePassable(sf::Vector2f(location_.x+1, location_.y+1));
  tileMap->setTilePassable(sf::Vector2f(location_.x+2, location_.y+1));
  tileMap->setTilePassable(sf::Vector2f(location_.x, location_.y+2));
  tileMap->setTilePassable(sf::Vector2f(location_.x+1, location_.y+2));
  tileMap->setTilePassable(sf::Vector2f(location_.x+2, location_.y+2));
}

void MainBuilding::produceUnit()
{
  if (workQueue_.empty()) {
    clock.restart();
    //this is needed so that worker is not produced instantly when no production has taken place for a while
  }
  workQueue_.push_back(unitSpawnTime_);
  producing_ = true;

}

void MainBuilding::update()
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
  if (this->isComplete() == false)
  {
    sf::Time elapsedFromBuild = clock.getElapsedTime();
    if (elapsedFromBuild.asSeconds() >= buildTime)
    {
      this->completeConstruction();
    }
  } else { //if enough time has passed produce first worker in queue
    if (!workQueue_.empty()) {
        sf::Time elapsedFromStart = clock.getElapsedTime();
        if (elapsedFromStart.asSeconds() >= workQueue_[0])
        {
          workQueue_.pop_front();
          //findFreeLocation does not handle bounds and passability yet!
          //spawnLocation_ = findFreeLocation(); //TODO: Does not work currently, Check why and fix!
          spawnLocation_ = sf::Vector2f(location_.x*32+32+16, location_.y*32+3*32+16);
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
    //maybe also produce some resources
  }
}

const std::deque<float> MainBuilding::getQueue() const
{
  return workQueue_;
}

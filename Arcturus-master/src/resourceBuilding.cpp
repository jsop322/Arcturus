#include "resourceBuilding.hpp"

ResourceBuilding::ResourceBuilding(Map* gameMap, bool ownedByPlayer, Animation* resourceBuilding, sf::Vector2f coords, bool isComplete, ResourceType produces)
{
    produce = produces;
    productionSpeed = 1; //time it takes to produce resources
    resourceReady = false;
    amount = 5;

    tileMap = gameMap;
    ownedByPlayer_ = ownedByPlayer;
    location_ = coords;
    complete = isComplete;

    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite_ = animatedSprite;
    animatedSprite_.setPosition(location_.x*32, location_.y*32);
    animatedSprite_.play(*resourceBuilding);


    size_ = 2;
    type_ = Resourcebuilding;

    maxHP = 300;
    curHP = maxHP;
    buildTime = 10;
    buildingCost_ = 300;

    level = 1;
    maxLevel = 4;
    upgradeCost_ = 50;

    canSpawn_ = false;
    unitSpawnTime_ = productionSpeed;
    unitCost_ = 0;
    producing_ = false;

    playAnimation_ = true;
  }

  void ResourceBuilding::setNonPassable()
  {
    tileMap->setTileNonPassable(sf::Vector2f(location_.x, location_.y));
    tileMap->setTileNonPassable(sf::Vector2f(location_.x+1, location_.y));
    tileMap->setTileNonPassable(sf::Vector2f(location_.x, location_.y+1));
    tileMap->setTileNonPassable(sf::Vector2f(location_.x+1, location_.y+1));
  }

  void ResourceBuilding::setPassable()
  {
    tileMap->setTilePassable(sf::Vector2f(location_.x, location_.y));
    tileMap->setTilePassable(sf::Vector2f(location_.x+1, location_.y));
    tileMap->setTilePassable(sf::Vector2f(location_.x, location_.y+1));
    tileMap->setTilePassable(sf::Vector2f(location_.x+1, location_.y+1));
  }

void ResourceBuilding::update()
{
  if (!this->isComplete())
  {
    sf::Time elapsedFromBuild = clock.getElapsedTime();
    if (elapsedFromBuild.asSeconds() >= buildTime)
    {
      this->completeConstruction();
    }
  } else {
    producing_ = true;
    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= unitSpawnTime_) {
      resourceReady = true;
      clock.restart();
    }
  }
  //if enough time has passed produce resource(s)
}

std::pair <bool, int> ResourceBuilding::getResources()
{
  if (resourceReady) {
    std::pair <bool, int> ret (resourceReady, amount);
    resourceReady = false;
    return ret;
  } else {
    std::pair <bool, int> ret (false, 0);
    return ret;
  }

}

const ResourceType ResourceBuilding::getResourceType() const
{
  return produce;
}

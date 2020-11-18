#include "building.hpp"

Building::Building(Map* gameMap, int size, std::vector<sf::Sprite> pictures, sf::Vector2f coords) {
  //does sf:clock need to be started manually here or does it start automatically?
  tileMap = gameMap;
  size_ = size;
  sprites = pictures;
  //does the sprite origin need to be initialised here as well or somewhere else?

  //this could also be done with a for loop and ifs, but since the number
  //of sprites is very limited, no for loop is really necessary
  if (size == 1) {
    sprites[0].setPosition(coords);
  } else if (size == 2) {
    sprites[0].setPosition(coords);
    sprites[1].setPosition(sf::Vector2f(coords.x + 32, coords.y));
    sprites[2].setPosition(sf::Vector2f(coords.x, coords.y + 32));
    sprites[3].setPosition(sf::Vector2f(coords.x + 32, coords.y +32));
  } else if (size == 3) {
    sprites[0].setPosition(coords);
    sprites[1].setPosition(sf::Vector2f(coords.x + 32, coords.y));
    sprites[2].setPosition(sf::Vector2f(coords.x + (32 * 2), coords.y));
    sprites[3].setPosition(sf::Vector2f(coords.x, coords.y +32));
    sprites[4].setPosition(sf::Vector2f(coords.x + 32, coords.y +32));
    sprites[5].setPosition(sf::Vector2f(coords.x + (32 * 2), coords.y + 32));
    sprites[6].setPosition(sf::Vector2f(coords.x, coords.y + (32 * 2)));
    sprites[7].setPosition(sf::Vector2f(coords.x + 32, coords.y + (32 * 2)));
    sprites[8].setPosition(sf::Vector2f(coords.x + (32 * 2), coords.y + (32 *2)));
  }
  location_ = coords;
  buildTime = 15; //Build time as seconds?
  complete = false;
  level = 1;
  name_ = "Building";
  maxLevel = 3;
}

void Building::draw(GameEngine &game) {
  //the positions of the sprites need to be handled somewhere still
  //also handling the sprites if they change depending on construction and production
  for(std::size_t i = 0; i < sprites.size(); i++) {
    game.getWindow()->draw(sprites[i]);
  }

}

const StructureType Building::getType() const {
  return type_;
}

const float Building::getMaxHealth() const {
  return maxHP;
}

const float Building::getCurrentHealth() const {
  return curHP;
}

const int Building::getLevel() const {
  return level;
}

const std::string Building::getName() const {
  return name_;
}

const bool Building::isComplete() const {
  return complete;
}

void Building::completeConstruction() {
  complete = true;
}

const float Building::getBuildTime() const{
  return buildTime;
}

bool Building::canUpgradeBuilding()
{
  if (level >= maxLevel) {
    return false;
  } else {
    return true;
  }
}

void Building::upgradeBuilding()
{
  level++;
  if(unitSpawnTime_ >= 3)
    unitSpawnTime_-= 2;
}

bool Building::takeDamage(int damage) {
  curHP = curHP - damage;
  if (curHP <= 0) {
    return true;
  } else {
    return false;
  }
}

const sf::Vector2f Building::getLocation() const {
  return location_;
}

const sf::Sprite Building::getSprite() const {
  return buildingSprite_;
}

AnimatedSprite& Building::getAnimatedSprite()
{
  return animatedSprite_;
}

const bool Building::ownedByPlayer() const {
  return ownedByPlayer_;
}

sf::Vector2f Building::findFreeLocation() {
  //if all adjacent tiles are blocked this function will fail!
  //default spawn location
  sf::Vector2f defLocation(location_.x*32 + ((size_ /2) *32), location_.y*32 + size_ *32);

  //currently made for 3 x 3 buildings (works for smaller ones too but won't be adjacent necesssarilys)
  // B building, d default spawn, numbers = order of checking other adjacent tiles
  //15 13 11 12 14
  // 10 B B B 7
  //  9 B B B 6
  //  8 B B B 5
  //  4 2 d 1 3
  std::vector<sf::Vector2f> adjacents;
  /*
  defLocation,
  (defLocation.x + 32, defLocation.y)
  (defLocation.x - 32, defLocation.y)
  (defLocation.x + 64, defLocation.y)
  (defLocation.x - 64, defLocation.y)
  (defLocation.x + 64, defLocation.y - 32)
  (defLocation.x + 64, defLocation.y - 64)
  (defLocation.x + 64, defLocation.y - 96)
  (defLocation.x - 64, defLocation.y - 32)
  (defLocation.x - 64, defLocation.y - 64)
  (defLocation.x - 64, defLocation.y - 96)
  (defLocation.x     , defLocation.y - 128)
  (defLocation.x + 32, defLocation.y - 128)
  (defLocation.x - 32, defLocation.y - 128)
  (defLocation.x + 64, defLocation.y - 128)
  (defLocation.x - 64, defLocation.y - 128)}
  */
  adjacents.push_back(defLocation);                                           //d
  adjacents.push_back(sf::Vector2f(defLocation.x + 32, defLocation.y));       //1
  adjacents.push_back(sf::Vector2f(defLocation.x - 32, defLocation.y));       //2
  adjacents.push_back(sf::Vector2f(defLocation.x + 64, defLocation.y));       //3
  adjacents.push_back(sf::Vector2f(defLocation.x - 64, defLocation.y));       //4
  adjacents.push_back(sf::Vector2f(defLocation.x + 64, defLocation.y - 32));  //5
  adjacents.push_back(sf::Vector2f(defLocation.x + 64, defLocation.y - 64));  //6
  adjacents.push_back(sf::Vector2f(defLocation.x + 64, defLocation.y - 96));  //7
  adjacents.push_back(sf::Vector2f(defLocation.x - 64, defLocation.y - 32));  //8
  adjacents.push_back(sf::Vector2f(defLocation.x - 64, defLocation.y - 64));  //9
  adjacents.push_back(sf::Vector2f(defLocation.x - 64, defLocation.y - 96));  //10
  adjacents.push_back(sf::Vector2f(defLocation.x     , defLocation.y - 128)); //11
  adjacents.push_back(sf::Vector2f(defLocation.x + 32, defLocation.y - 128)); //12
  adjacents.push_back(sf::Vector2f(defLocation.x - 32, defLocation.y - 128)); //13
  adjacents.push_back(sf::Vector2f(defLocation.x + 64, defLocation.y - 128)); //14
  adjacents.push_back(sf::Vector2f(defLocation.x - 64, defLocation.y - 128)); //15

  unsigned int i = 0;
  while (0 >= defLocation.y || defLocation.y >= tileMap->getMapSize().y ||
  !tileMap->getTile(defLocation.x, defLocation.y)->isPassable() ||
  0 >= defLocation .x || defLocation.x >= tileMap->getMapSize().x) {
    i++;
    defLocation = adjacents[i];
    if (i >= adjacents.size()) {
      std::cout << "No free adjacent tile found for unit spawn!" << std::endl;
      break;
    }
  }

  return defLocation;
}

bool Building::canSpawn() const
{
  return canSpawn_;
}
sf::Vector2f Building::getSpawnLocation() const
{
  return spawnLocation_;
}

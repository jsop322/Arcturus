#include "tile.hpp"

Tile::Tile(sf::Color terrainTypeColor, sf::Sprite terrainSprite, float x, float y)
{
  passable_ = true;
  setType(terrainTypeColor);
  sprite_ = terrainSprite;
  location_.x = x;
  location_.y = y;
  sprite_.setPosition(x*32, y*32);

}

void Tile::setType(sf::Color terrainType)
{
  if(terrainType == sf::Color(120,120,120)) type_ = MetalFloor;
  if(terrainType == sf::Color(0,255,0)) type_ = Grass;

  if(terrainType == sf::Color(0,0,0))
  {
    type_ = MetalWall;
    passable_ = false;
  }
  if(terrainType == sf::Color(255,120,0))
  {
    type_ = Mountain;
    passable_ = false;
  }
}

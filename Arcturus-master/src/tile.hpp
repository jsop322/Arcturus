#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <iostream>

enum TerrainType //terrain types, still need to decide on which to include
{
  Water,
  Grass,
  Mountain,
  MetalFloor,
  MetalWall
};

class Tile
{
public:
  Tile(){}
  Tile(sf::Color terrainTypeColor, sf::Sprite terrainSprite, float x, float y);
  //getOccupant
  sf::Vector2f getLocation(){return location_;}
  sf::Sprite getSprite(){return sprite_;}
  TerrainType getTerrain(){return type_;}
  bool isPassable() const{return passable_;}

  void setType(sf::Color terrainType);
  void setPassableToFalse(){passable_ = false;}
  void setPassableToTrue(){passable_ = true;}

private:
  TerrainType type_;
  //occupant need a class for these (buildings, units, resources) first
  sf::Vector2f location_; //(x, y)
  sf::Sprite sprite_;
  bool passable_;
};

#endif

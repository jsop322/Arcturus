#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include "tile.hpp"
#include "resource.hpp"
#include "gameEngine.hpp"

class Map
{
public:
  std::vector<sf::Vector2f> buildMap(std::string mapName, sf::Texture* mapTexture); //this method will create the map based on an image
  Tile* getTile(float x, float y); //accesses tile in certain location
  void draw(GameEngine &game);
  void setMapFeatures();
  std::vector<sf::Vector2f> setMapResources();
  sf::Sprite selectTileSprite(sf::Color terrainType, float x, float y);
  sf::Sprite checkNeighbours(float x, float y, sf::Sprite, sf::Color terrainType);
  sf::Vector2f getMapSize();
  void updateResources();
  int checkIfResource(sf::Vector2f location);
  float getResource(sf::Vector2f location, float amount);
  std::vector<std::vector<int>> getPassableMatrix();
  void printPassableMatrix();
  sf::Vector2f getStartLocation(){ return startLocations_[0]; }
  void setTileNonPassable(sf::Vector2f location);
  void setTilePassable(sf::Vector2f location);

private:
  float width_;
  float height_;
  sf::Image mapFeatures_;
  sf::Image mapResources_;
  sf::Texture* mapTileset_;
  std::vector<Tile> tiles_;
  std::vector<Resource> resources_;
  std::vector<sf::Vector2f> startLocations_;
};

#endif

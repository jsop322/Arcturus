#include "map.hpp"
#include <iostream>

std::vector<sf::Vector2f> Map::buildMap(std::string mapName, sf::Texture* mapTexture)
{
  mapFeatures_.loadFromFile("resources/graphics/"+mapName+"/"+mapName+"Features.png");
  mapResources_.loadFromFile("resources/graphics/"+mapName+"/"+mapName+"Resources.png");
  mapTileset_ = mapTexture;

  //The map size is read from the map name and then saved to width_ and height_.
  std::stringstream ss;
  ss << mapName;
  ss >> width_;
  height_ = width_; //Currently map templates are square for simplicity. We can decide on rectangular maps later.
  setMapFeatures();
  std::vector<sf::Vector2f> startingLocation = setMapResources();
  startLocations_ = startingLocation;
  return startingLocation;
}

Tile* Map::getTile(float x, float y)
{
  Tile* retTile;
  sf::Vector2f location(x,y);
  for(Tile tile : tiles_)
  {
    retTile = &tile;
    if(retTile->getLocation() == location)
    {
      return retTile;
    }
  }
  return retTile; //Returns the last tile if there was no correct location. Should never be called.
}

std::vector<std::vector<int>> Map::getPassableMatrix()
{
  std::vector<std::vector<int>> mapInfo(static_cast<int>(this->getMapSize().x), std::vector<int>(static_cast<int>(this->getMapSize().y)));
  for(Tile tile : tiles_){
    if(tile.isPassable()){
      mapInfo[static_cast<int>(tile.getLocation().x)][static_cast<int>(tile.getLocation().y)] = 0;
    }
    else{
      mapInfo[static_cast<int>(tile.getLocation().x)][static_cast<int>(tile.getLocation().y)] = 1;
    }
  }
  return mapInfo;
}

void Map::printPassableMatrix()
{
  std::vector<std::vector<int>> matrix = getPassableMatrix();
  for(size_t y = 0; y < 50; y++)
  {
    for(size_t x = 0; x < 50; x++)
    {
      std::cout << matrix[x][y];
    }
    std::cout << std::endl;
  }
}

void Map::setMapFeatures()
{
  for(float x = 0; x < width_; x++)
  {
    for(float y = 0; y < height_; y++)
    {
      sf::Color terrainType = mapFeatures_.getPixel(x+1,y+1); //Offset because there is extra transparent pixels around the map for easier neighbour detection.
      sf::Sprite terrainSprite = selectTileSprite(terrainType, x+1, y+1);
      Tile tile(terrainType, terrainSprite, x, y);
      tiles_.push_back(tile);
    }
  }
}

sf::Sprite Map::selectTileSprite(sf::Color terrainType, float x, float y)
{
  sf::Sprite sprite;
  sprite.setTexture(*mapTileset_);
  sprite.setTextureRect(sf::IntRect(0,0,32,32)); //If the sprite selection fails, will return X/Y sprite.

  //Metal floor
  if(terrainType == sf::Color(120,120,120))
  {
    //Always set all the four values to 32, then select the correct indices from
    //tileset for the first two values. In this case *2 and *2.
    sprite.setTextureRect(sf::IntRect(32*2,32*2,32,32));
    return sprite;
  }
  //Grass
  if(terrainType == sf::Color(0,255,0))
  {
    //Always set all the four values to 32, then select the correct indices from
    //tileset for the first two values. In this case *2 and *5.
    sprite.setTextureRect(sf::IntRect(32*2,32*5,32,32));
    return sprite;
  }

  //Metal wall
  if(terrainType == sf::Color(0,0,0))
  {
    sprite = checkNeighbours(x, y, sprite, terrainType);
    return sprite;
  }

  //Mountain
  if(terrainType == sf::Color(255,120,0))
  {
    sprite = checkNeighbours(x, y, sprite, terrainType);
    return sprite;
  }

  return sprite;
}

/* Checks neighbouring tiles and sets the tile sprite accordingly.
** Currently adding different terrain types is possibble but a huge pain in the ass.
** TODO: Concider some kind of rewrite.
**
**               (x, y-1)
**                  ^
**       (x-1, y) <---> (x+1, y)
**                  v
**               (x, y+1)
*/
sf::Sprite Map::checkNeighbours(float x, float y, sf::Sprite sprite, sf::Color terrainType)
{
  //Purkkajesari work around. 4-way junction used also for 3-way.
  int surrounded = 0;
  if(mapFeatures_.getPixel(x-1,y) == terrainType) surrounded++;
  if(mapFeatures_.getPixel(x,y-1) == terrainType) surrounded++;
  if(mapFeatures_.getPixel(x+1,y) == terrainType) surrounded++;
  if(mapFeatures_.getPixel(x,y+1) == terrainType) surrounded++;
  // Surrounded
  if(surrounded >= 3)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*4,32*2,32,32));
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*4,32*5,32,32));
      return sprite;
    }
  }
  //Top vertical end
  else if(mapFeatures_.getPixel(x-1,y) != terrainType
  && mapFeatures_.getPixel(x,y-1) != terrainType
  && mapFeatures_.getPixel(x+1,y) != terrainType)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*4,32*1,32,32));
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*4,32*4,32,32));
      return sprite;
    }
  }
  //Bottom vertical end
  else if(mapFeatures_.getPixel(x-1,y) != terrainType
  && mapFeatures_.getPixel(x,y+1) != terrainType
  && mapFeatures_.getPixel(x+1,y) != terrainType)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*4,32*3,32,32));
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*4,32*6,32,32));
      return sprite;
    }
  }
  //Right horizontal end
  else if(mapFeatures_.getPixel(x,y-1) != terrainType
  && mapFeatures_.getPixel(x+1,y) != terrainType
  && mapFeatures_.getPixel(x,y+1) != terrainType)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*5,32*2,32,32));
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*5,32*5,32,32));
      return sprite;
    }
  }
  //Left horizontal end
  else if(mapFeatures_.getPixel(x,y-1) != terrainType
  && mapFeatures_.getPixel(x-1,y) != terrainType
  && mapFeatures_.getPixel(x,y+1) != terrainType)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*5+32,32*2,-32,32)); //The addition +32 in x and -32 in x size is for flipping the sprite
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*5+32,32*5,-32,32)); //The addition +32 in x and -32 in x size is for flipping the sprite
      return sprite;
    }
  }
  //NW corner
  else if(mapFeatures_.getPixel(x,y-1) != terrainType
  && mapFeatures_.getPixel(x-1,y) != terrainType)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*1,32*1,32,32));
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*1,32*4,32,32));
      return sprite;
    }
  }
  //NE corner
  else if(mapFeatures_.getPixel(x,y-1) != terrainType
  && mapFeatures_.getPixel(x+1,y) != terrainType)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*3,32*1,32,32));
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*3,32*4,32,32));
      return sprite;
    }
  }
  //SE corner
  else if(mapFeatures_.getPixel(x+1,y) != terrainType
  && mapFeatures_.getPixel(x,y+1) != terrainType)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*3,32*3,32,32));
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*3,32*6,32,32));
      return sprite;
    }
  }
  //SW corner
  else if(mapFeatures_.getPixel(x,y+1) != terrainType
  && mapFeatures_.getPixel(x-1,y) != terrainType)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*1,32*3,32,32));
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*1,32*6,32,32));
      return sprite;
    }
  }
  //N and S wall
  else if(mapFeatures_.getPixel(x,y-1) != terrainType
  && mapFeatures_.getPixel(x,y+1) != terrainType)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*2,32*1,32,32));
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*2,32*4,32,32));
      return sprite;
    }
  }
  //E and W wall
  else if(mapFeatures_.getPixel(x-1,y) != terrainType
  && mapFeatures_.getPixel(x+1,y) != terrainType)
  {
    if(terrainType == sf::Color(0,0,0)) //Metal
    {
      sprite.setTextureRect(sf::IntRect(32*1,32*2,32,32));
      return sprite;
    }
    else if(terrainType == sf::Color(255,120,0)) //Mountain
    {
      sprite.setTextureRect(sf::IntRect(32*1,32*5,32,32));
      return sprite;
    }
  }

  return sprite; //Returns what was given, meaning the neighbour check failed.
}

std::vector<sf::Vector2f> Map::setMapResources()
{
  std::vector<sf::Vector2f> startingLocation(2);
  sf::Sprite resourceSprite(*mapTileset_);
  for(float x = 0; x < width_; x++)
  {
    for(float y = 0; y < height_; y++)
    {
      sf::Color resourceType = mapResources_.getPixel(x+1,y+1);
      //This IF only does resources. Will add another IF for starting bases.
      if(resourceType == sf::Color(230,230,230) || resourceType == sf::Color(255,255,0))
      {
        Resource resource(resourceType, resourceSprite, x, y);
        resources_.push_back(resource);
        //Sets the tile which the resource is on to not passable so that units cannot walk through them
        for(unsigned int i = 0; i < tiles_.size(); i++)
        {
          if(tiles_[i].getLocation().x == x && tiles_[i].getLocation().y == y)
          {
            tiles_[i].setPassableToFalse();
          }
        }
      }
      else if(resourceType == sf::Color(255,0,0)) //Calls player->makeBuilding to setup the starting base
      {
          sf::Vector2f playerStartingLocation;
          playerStartingLocation.x = x-1;
          playerStartingLocation.y = y-1;
          startingLocation[0] = playerStartingLocation;

          for(unsigned int i = 0; i < tiles_.size(); i++)
          {
            if((tiles_[i].getLocation().x == playerStartingLocation.x || tiles_[i].getLocation().x == playerStartingLocation.x+1 || tiles_[i].getLocation().x == playerStartingLocation.x+2)
            && (tiles_[i].getLocation().y == playerStartingLocation.y || tiles_[i].getLocation().y == playerStartingLocation.y+1 || tiles_[i].getLocation().y == playerStartingLocation.y+2))
            {
              tiles_[i].setPassableToFalse();
            }
          }
      }
      else if(resourceType == sf::Color(0,0,255))
      {
        sf::Vector2f enemyStartingLocation;
        enemyStartingLocation.x = x-1;
        enemyStartingLocation.y = y-1;
        startingLocation[1] = enemyStartingLocation;

        for(unsigned int i = 0; i < tiles_.size(); i++)
        {
          if((tiles_[i].getLocation().x == enemyStartingLocation.x || tiles_[i].getLocation().x == enemyStartingLocation.x+1 || tiles_[i].getLocation().x == enemyStartingLocation.x+2)
          && (tiles_[i].getLocation().y == enemyStartingLocation.y || tiles_[i].getLocation().y == enemyStartingLocation.y+1 || tiles_[i].getLocation().y == enemyStartingLocation.y+2))
          {
            tiles_[i].setPassableToFalse();
          }
        }
      }
    }
  }
  return startingLocation;
}

void Map::draw(GameEngine &game)
{
  for(auto tile : tiles_)
  {
    game.getWindow()->draw(tile.getSprite());
  }
  for(auto resource : resources_)
  {
    game.getWindow()->draw(resource.getSprite());
  }
}

sf::Vector2f Map::getMapSize()
{
  return sf::Vector2f(width_, height_);
}

void Map::updateResources(){
  for(unsigned int i = 0; i < resources_.size(); i++)
  {
    if(!resources_[i].updateResource())
    {

      sf::Vector2f freeTile = resources_[i].getLocation();
      for(size_t i = 0; i < tiles_.size() ; i++)
      {
        if(tiles_[i].getLocation() == freeTile)
        {
          tiles_[i].setPassableToTrue();
          break;
        }
      }
      resources_.erase(resources_.begin()+i);
    }
  }
}

int Map::checkIfResource(sf::Vector2f location)
{
  for(unsigned int i = 0; i < resources_.size(); i++)
  {
    int x = (static_cast<int>(location.x)-(static_cast<int>(location.x) % 32))/32;
    int y = (static_cast<int>(location.y)-(static_cast<int>(location.y) % 32))/32;
    //std::cout << "haluttu: " << x << "  " << y << std::endl;
    //std::cout << "resurssi: " << resources_[i].getLocation().x << "  " << resources_[i].getLocation().y << std::endl;
    if(x == static_cast<int>(resources_[i].getLocation().x) && y == static_cast<int>(resources_[i].getLocation().y)){
      if(resources_[i].getType() == Gold){
        return 1;
      }
      if(resources_[i].getType() == Silver){
        return 2;
      }
    }
  }
  return 0;
}


float Map::getResource(sf::Vector2f location, float amount)
{
  for(unsigned int i = 0; i < resources_.size(); i++)
  {
    int x = (static_cast<int>(location.x)-(static_cast<int>(location.x) % 32))/32;
    int y = (static_cast<int>(location.y)-(static_cast<int>(location.y) % 32))/32;
    if(x == static_cast<int>(resources_[i].getLocation().x) && y == static_cast<int>(resources_[i].getLocation().y)){
      return(resources_[i].gatherResource(amount));
    }
  }
  return 0;
}

void Map::setTileNonPassable(sf::Vector2f location)
{
  for(float i = 0; i < tiles_.size(); i++)
  {
    if(tiles_[i].getLocation() == location){
      tiles_[i].setPassableToFalse();
    }
  }
}


void Map::setTilePassable(sf::Vector2f location)
{
  for(float i = 0; i < tiles_.size(); i++)
  {
    if(tiles_[i].getLocation() == location){
      tiles_[i].setPassableToTrue();
    }
  }
}

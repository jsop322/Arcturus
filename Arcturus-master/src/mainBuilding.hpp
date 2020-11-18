#ifndef MAINBUILDING_H
#define MAINBUILDING_H

#include "building.hpp"

class MainBuilding: public Building
{
public:
  MainBuilding(Map* gameMap, bool ownedByPlayer, Animation* mainBuilding, sf::Vector2f coords, bool isComplete);
  ~MainBuilding(){if(isComplete()){setPassable();}}
  void update();
  void produceUnit(); //could also maybe be tied to buildLVL
  void setPassable();
  virtual std::pair <bool, int> getResources(){return std::pair <bool, int>(false, 0);}
  const std::deque< float > getQueue() const;

private:
  std::deque< float > workQueue_;
};

#endif

#ifndef FACTORYBUILDING_H
#define FACTORYBUILDING_H

#include <utility> //allows access to pair
#include "building.hpp"
#include "unit.hpp"
#include <deque>

class FactoryBuilding: public Building
{
public: //productionTime should be as seconds (float)
  FactoryBuilding(Map* gameMap, bool ownedByPlayer, Animation* factoryBuilding, sf::Vector2f coords, bool isComplete);
  ~FactoryBuilding(){if(isComplete()){setPassable();}}
  //unitBuilding constructor does not need type and size because they are constant for all unitBuildings
  void update();
  void produceUnit(); //starts producing unit
  void setNonPassable();
  void setPassable();
  virtual std::pair <bool, int> getResources(){return std::pair <bool, int>(false, 0);}
  //maybe produceUnit should contain cost and deduct it from player resources
  const std::deque< float > getQueue() const;
  //const std::vector< std::pair<int, Unit> > getUnits() const;

private:
  //std::vector< std::pair<int, Unit> > produceableUnits; // (buildLVL, unit)
  std::deque<float> workQueue_;
};

#endif

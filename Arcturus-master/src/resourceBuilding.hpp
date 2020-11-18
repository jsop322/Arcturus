#ifndef RESOURCEBUILDING_H
#define RESOURCEBUILDING_H

#include "building.hpp"
#include "resource.hpp"
#include <utility> //pair access

class ResourceBuilding: public Building
{
public: //should it be possible to upgrade ResourceBuildings?
  ResourceBuilding(Map* gameMap, bool ownedByPlayer, Animation* resourceBuilding, sf::Vector2f coords, bool isComplete, ResourceType produces);
  ~ResourceBuilding(){if(isComplete()){setPassable();}}
  void setNonPassable();
  void setPassable();
  void update();
  const ResourceType getResourceType() const;
  std::pair <bool, int> getResources();

private:
  ResourceType produce; //resource produced by building
  float productionSpeed; //how often resource is produced
  int amount; //how much resource is productionSpeed
  bool resourceReady; //when true building is ready to give out resources
};

#endif

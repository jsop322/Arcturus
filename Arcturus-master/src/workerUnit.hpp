#ifndef WORKERUNIT_H
#define WORKERUNIT_H

#include <SFML/Graphics.hpp>
#include "unit.hpp"
#include <iostream>
//#include "resourceManager.hpp"

class WorkerUnit : public Unit
{
public:
  //constructor
  WorkerUnit(sf::Vector2f spawnLocation);
  //Take resource and return the amount
  void gatherResource(float amount, int type, sf::Vector2f currentResourcePos);
  float getWorkingTime(){ return resourceGatherT_; }
  float getCurrentTime(){ return clock_.getElapsedTime().asSeconds(); }
  void setAnimation(Animation* workerWalking);
  std::pair<float, int> update();
  bool getAvailability();
  int getCapability(int type);
  bool gathering(){ return gathering_; }
  void stopGathering(){ gathering_ = false; }
  float getCurrentAmount(){return currentAmount_;}
  int getCurrentType(){return currentType_;}
  sf::Vector2f getCurrentResourcePos(){ return currentResourcePos_; }
  //identification for created units
  static int idcount_;

private:
  sf::Clock clock_;
  float resourceGatherT_;
  int silverAmount_;
  int goldAmount_;
  float currentAmount_;
  int currentType_;
  bool available_;
  bool gathering_;
  sf::Vector2f currentResourcePos_;
};


#endif

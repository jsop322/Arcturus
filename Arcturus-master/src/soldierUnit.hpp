#ifndef SOLDIERUNIT_H
#define SOLDIERUNIT_H

#include <SFML/Graphics.hpp>
#include "unit.hpp"
#include <iostream>



class soldierUnit : public Unit
{
public:
  //constructor
  soldierUnit(sf::Vector2f spawnLocation);
  void setAnimation(Animation* soldierWalking);
  bool canAttack();
  //return functions for different variables
  //identification for created units
  static int idcount_;

private:


};


#endif

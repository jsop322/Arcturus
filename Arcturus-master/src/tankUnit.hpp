#ifndef TANKUNIT_H
#define TANKUNIT_H

#include <SFML/Graphics.hpp>
#include "unit.hpp"
#include <iostream>

class TankUnit : public Unit
{
public:

  TankUnit(sf::Vector2f spawnLocation);
  void setAnimation(Animation* tankMoving);
  bool canAttack();
  static int idcount_;

private:


};


#endif

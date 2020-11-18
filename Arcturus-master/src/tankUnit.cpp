#include "tankUnit.hpp"

int TankUnit::idcount_ = 0;

TankUnit::TankUnit(sf::Vector2f spawnLocation)
{
  speed_ = 60;
  maxHealth_ = 200;
  currentHealth_ = 200;
  damage_ = 25;
  type_ = Tank;
  AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
  animatedSprite_ = animatedSprite;
  animatedSprite_.setPosition(spawnLocation.x, spawnLocation.y);
  animatedSprite_.setOrigin(32,32);
  attacking_ = false;
  attackRange_ = 200;

  idcount_++;
  id_ = idcount_;
  des_position_ = animatedSprite_.getPosition();
  current_path_.clear();

  attackTime_.restart();

}

void TankUnit::setAnimation(Animation* tankMoving)
{
  animatedSprite_.play(*tankMoving);
}

bool TankUnit::canAttack()
{
  baseAttackTime_ = attackTime_.getElapsedTime();
  if( baseAttackTime_.asSeconds() > 1.5)
  {
    attackTime_.restart();
    return true;
  }
  else
    return false;
}

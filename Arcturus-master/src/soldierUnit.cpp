#include "soldierUnit.hpp"

int soldierUnit::idcount_ = 0;
soldierUnit::soldierUnit(sf::Vector2f spawnLocation)
{

  //constructor, set the stats, texture and sprite
  speed_ = 90;
  maxHealth_ = 100;
  currentHealth_ = 100;
  damage_ = 20;
  type_ = Soldier;
  AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
  animatedSprite_ = animatedSprite;
  animatedSprite_.setPosition(spawnLocation.x, spawnLocation.y);
  animatedSprite_.setOrigin(16,16);
  attacking_ = false;
  attackRange_ = 160;

  idcount_++;
  id_ = idcount_;
  des_position_ = animatedSprite_.getPosition();
  current_path_.clear();

  attackTime_.restart();

}

void soldierUnit::setAnimation(Animation* soldierWalking)
{
  /*texture_ = unitTexture;
  sprite_.setTexture(*texture_);
  sprite_.setTextureRect(sf::IntRect(32, 32, 32, 32));*/
  animatedSprite_.play(*soldierWalking);
}

bool soldierUnit::canAttack()
{
  baseAttackTime_ = attackTime_.getElapsedTime();
  if( baseAttackTime_.asSeconds() > 0.5)
  {
    attackTime_.restart();
    return true;
  }
  else
    return false;
}

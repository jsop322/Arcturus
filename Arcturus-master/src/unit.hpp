#ifndef UNIT_H
#define UNIT_H

#include "gameEngine.hpp"
#include "Animation.hpp"
#include "aStar.hpp"

enum UnitType //unit types
{
  Soldier,
  Tank,
  Flying,
  Worker
};


class Unit
{
public:
  int getCurrentHealth(){ return currentHealth_; };
  int getMaxHealth(){ return maxHealth_; };
  unsigned int getDamage(){ return damage_; };
  sf::Sprite& getSprite(){ return sprite_; };
  float getSpeed(){ return speed_; };
  size_t getID(){ return id_; };
  void setDestination(sf::Vector2f position){ des_position_ = position; }
  void setCurrentPath(std::vector<sf::Vector2i> path){ current_path_ = path; }
  void setNextDestination(){ des_position_ = sf::Vector2f(static_cast<float>(current_path_[0].x*32+16), static_cast<float>(current_path_[0].y*32+16)); }
  void removePathPoint(){ current_path_.erase(current_path_.begin()); }
  std::vector<sf::Vector2i> getCurrentPath(){ return current_path_; }
  void clearPath(){ current_path_.clear(); }
  sf::Vector2f getDestination(){ return des_position_; }
  sf::Vector2f getPosition(){ return animatedSprite_.getPosition(); }
  virtual void setTexture(sf::Texture* unitTexture){ texture_ = unitTexture; }
  //animated sprite test
  AnimatedSprite& getAnimatedSprite(){ return animatedSprite_; }
  void setAnimation(Animation anim){ animation_ = anim; }
  UnitType getType(){ return type_; }
  void startAttack(){ attacking_ = true; }
  void stopAttack(){ attacking_ = false; }
  bool getAttackStatus(){ return attacking_; }
  float getAttackRange(){ return attackRange_; }
  void setAttackTarget(sf::Vector2f mousepos){ attackTarget_ = mousepos; }
  sf::Vector2f getAttackTarget(){ return attackTarget_; }
  void hurtUnit(unsigned int dmg){ currentHealth_ -= dmg; isUnderAttack_ = true; }
  virtual void gatherResource(float amount, int type, sf::Vector2f currentResourcePos){}
  virtual std::pair<float, int> update(){return std::pair<float, int>(0,0);}
  virtual bool getAvailability(){ return false; }
  virtual int getCapability(int type){ return 0; }
  virtual float getCurrentAmount(){ return 0; }
  virtual bool gathering(){ return false; }
  virtual void stopGathering(){}
  virtual sf::Vector2f getCurrentResourcePos(){ return sf::Vector2f(0,0); }
  virtual float getWorkingTime(){ return 0; }
  virtual float getCurrentTime(){ return 0; }
  void setAStar(AStar aStar){ aStar_ = aStar; aStarSet_ = true;}
  AStar* getAStar(){ return &aStar_; }
  bool aStarSet(){ return aStarSet_; }
  virtual bool canAttack(){ return false; }
  bool isUnderAttack(){ return isUnderAttack_; }
  void notUnderAttack(){ isUnderAttack_ = false; }

protected:
  UnitType type_;
  int maxHealth_;
  int currentHealth_;
  unsigned int damage_;
  //sprite
  sf::Sprite sprite_;
  //Texture
  sf::Texture* texture_;
  //unit speed
  float speed_;
  size_t id_;
  //unit's desired position through move order
  sf::Vector2f des_position_;
  //unit's attack target if attack command is given
  sf::Vector2f attackTarget_;
  //attack range
  float attackRange_;
  //clock for timing the attack commands
  sf::Clock attackTime_;
  sf::Time baseAttackTime_;
  //animated sprite test
  AnimatedSprite animatedSprite_;
  Animation animation_;
  std::vector<sf::Vector2i> current_path_;
  bool attacking_;
  AStar aStar_;
  bool aStarSet_ = false;
  bool isUnderAttack_ = false;

};

#endif

#include "workerUnit.hpp"

int WorkerUnit::idcount_ = 0;
WorkerUnit::WorkerUnit(sf::Vector2f spawnLocation)
{
  //constructor, set the stats, texture and sprite
  speed_ = 100;
  maxHealth_ = 100;
  currentHealth_ = maxHealth_;
  damage_ = 5;
  attackRange_ = 80;
  resourceGatherT_ = 5;   //This can be changed if someone wants
  silverAmount_ = 50;
  goldAmount_ = 5;
  type_ = Worker;
  AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
  animatedSprite_ = animatedSprite;
  animatedSprite_.setPosition(spawnLocation.x, spawnLocation.y);
  animatedSprite_.setOrigin(16,16);
  attacking_ = false;
  available_ = true;
  gathering_ = false;

  idcount_++;
  id_ = idcount_;

  des_position_ = animatedSprite_.getPosition();
  current_path_.clear();

  sf::Clock clock;
  std::cout << "Worker created" << std::endl;
}
/*

*/
int WorkerUnit::getCapability(int type)
{
    if(type == 1){
      return goldAmount_;
    }
    else{
      return silverAmount_;
    }
}
void WorkerUnit::gatherResource(float amount, int type, sf::Vector2f currentResourcePos)
{
    clock_.restart();
    currentAmount_ = amount;
    currentType_ = type;
    available_ = false;
    gathering_ = true;
    currentResourcePos_ = currentResourcePos;
}

bool WorkerUnit::getAvailability()
{
  return available_;
}

std::pair<float, int> WorkerUnit::update()
{
  sf::Time deltaTime = clock_.getElapsedTime();
  if(deltaTime.asSeconds() > resourceGatherT_){
    clock_.restart();
    available_ = true;
    float amount = currentAmount_;
    int type = currentType_;
    currentAmount_ = 0;
    currentType_ = 0;
    return std::pair<float, int>(amount, type);
  }
  else{
    return std::pair<float, int>(0, 0);
  }
}

void WorkerUnit::setAnimation(Animation* workerWalking)
{
  animatedSprite_.play(*workerWalking);
}

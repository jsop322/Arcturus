#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "aStar.hpp"

Player::Player()
{

  //playerUnits_.push_back(unit);
  //std::cout << "ONE SOLDIER CREATED, ID: " << playerUnits_[0].getID() << std::endl;
  unitIndicators_.loadFromFile("resources/graphics/unitTileset.png");
  unitIndicatorSprite_.setTexture(unitIndicators_);
  unitIndicatorSprite_.setTextureRect(sf::IntRect(32*10, 32, 32, 32));
  unitIndicatorSprite_.setOrigin(16,16);
  tankIndicatorSprite_.setTexture(unitIndicators_);
  tankIndicatorSprite_.setTextureRect(sf::IntRect(32*9, 32*6, 32*2, 32*2));
  tankIndicatorSprite_.setOrigin(32,32);
  buildingIndicator_.loadFromFile("resources/graphics/unitTileset.png",sf::IntRect(32*8, 32*3, 32*3, 32*3));
  buildingIndicatorSprite_.setTexture(buildingIndicator_);
  buildingIndicatorSprite_.setOrigin(0,0);
  gold_ = 0;
  silver_ = 200;

}

Player::~Player()
{
  selectedUnits_.clear();
  selectedBuilding_.clear();
  enemyUnits_->clear();
  enemyBuildings_->clear();
}

void Player::setTextures(Animation* soldierWalking,
Animation* soldierShooting, Animation* workerWalking, Animation* workerAct, Animation* tankDriving,
Animation* tankShooting, Animation* mainBuilding, Animation* unitBuilding, Animation* factoryBuilding,
Animation* resourceBuilding)
{
  //for animation implementations
  soldierWalking_ = soldierWalking;
  soldierShooting_ = soldierShooting;
  workerWalking_ = workerWalking;
  workerAct_ = workerAct;
  tankDriving_ = tankDriving;
  tankShooting_ = tankShooting;
  mainBuilding_ = mainBuilding;
  unitBuilding_ = unitBuilding;
  factoryBuilding_ = factoryBuilding;
  resourceBuilding_ = resourceBuilding;
}

void Player::update(float &deltaTime,  Map* map)
{

  //frameclock for animation updating
  frameTime = frameClock.restart();

  for(size_t i = 0; i < playerBuildings_.size(); i++)
  {
    if(playerBuildings_[i]->getCurrentHealth() <= 0)
    {
      bool wasSelected = false;
      for(std::size_t l = 0; l < selectedBuilding_.size(); l++)
      {
          selectedBuilding_.clear();
          playerBuildings_.erase(playerBuildings_.begin() + i);
          wasSelected = true;
      }
      if( wasSelected == false )
      {
        playerBuildings_.erase(playerBuildings_.begin() + i);
      }
    }
    //Check the current building type in order to play correct animations
    StructureType currentType = playerBuildings_[i]->getType();
    switch(currentType)
    {
      case Mainbuilding : currentAnimation_ = mainBuilding_; break;
      case Unitbuilding : currentAnimation_ = unitBuilding_; break;
      case Resourcebuilding : currentAnimation_ = resourceBuilding_; break;
      case Factorybuilding : currentAnimation_ = factoryBuilding_; break;
    }
    //update the building status
    playerBuildings_[i]->update();
    //if worker is produced, play animation
    if(playerBuildings_[i]->getAnimationStatus() == true)
    {
      playerBuildings_[i]->getAnimatedSprite().play(*currentAnimation_);
      playerBuildings_[i]->getAnimatedSprite().update(frameTime);
    }
    else
      playerBuildings_[i]->getAnimatedSprite().stop();
  }

  produceUnit();

  if(!playerUnits_.empty())
  {
    //Check if the unit's hp is below 0, if it is erase it. Another check is made that if the current selected unit dies, selectedUnits_ is cleared.
    for(std::size_t i = 0; i < playerUnits_.size(); i++)
    {
      if(playerUnits_[i]->getCurrentHealth() <= 0)
      {
        bool wasSelected = false;
        for(std::size_t l = 0; l < selectedUnits_.size(); l++)
        {
          if(playerUnits_[i]->getID() == selectedUnits_[l]->getID() && playerUnits_[i]->getType() == selectedUnits_[l]->getType())
          {
            // Get unit location as pixel coordinates
            sf::Vector2f position = selectedUnits_[l]->getDestination();
            // Convert position to tile coordinates
            position.x = (position.x-16)/32;
            position.y = (position.y-16)/32;
            // Set the tile where the unit was to passable
            map->setTilePassable(position);
            selectedUnits_.clear();
            playerUnits_.erase(playerUnits_.begin() + i);
            wasSelected = true;
          }
        }
        if( wasSelected == false )
        {
          // Get unit location as pixel coordinates
          sf::Vector2f position = playerUnits_[i]->getDestination();
          // Convert position to tile coordinates
          position.x = (position.x-16)/32;
          position.y = (position.y-16)/32;
          // Set the tile where the unit was to passable
          map->setTilePassable(position);
          playerUnits_.erase(playerUnits_.begin() + i);
        }
      }

      if(playerUnits_[i]->isUnderAttack() == true && playerUnits_[i]->getType() != Worker)
      {
        bool killed = true;
        for(std::size_t d = 0; d < enemyUnits_->size(); d++)
        {
          if(((*enemyUnits_)[d]->getAttackTarget()) == playerUnits_[i]->getAnimatedSprite().getPosition())
          {
            playerUnits_[i]->startAttack();
            playerUnits_[i]->setAttackTarget((*enemyUnits_)[d]->getAnimatedSprite().getPosition());
            killed = false;
            break;
          }
        }
        if(killed == true)
        {
          playerUnits_[i]->notUnderAttack();
        }
      }
      //get the required positions for movement commands and attack commands
      position_ = playerUnits_[i]->getAnimatedSprite().getPosition();
      des_position_ = playerUnits_[i]->getDestination();
      targetPosition_ = playerUnits_[i]->getAttackTarget();

      if(playerUnits_[i]->getCurrentPath().size() != 0){
        if( abs((position_.x) - (des_position_.x)) == 0 && abs((position_.y) - (des_position_.y)) == 0){          // Check if the unit has reached the next tile of the path
          playerUnits_[i]->setNextDestination();                                                                   // Set the next tile on path to destination
          playerUnits_[i]->removePathPoint();                                                                // Remove the already used tile from the path
        }
      }
      //Check the unit's type in order to play the correct animations
      UnitType currentType = playerUnits_[i]->getType();

      switch(currentType)
      {
        case Soldier : currentAnimation_ = soldierWalking_; currentShooting_ = soldierShooting_; break;
        case Worker : currentAnimation_ = workerWalking_; currentShooting_ = workerAct_; break;
        case Flying : break;
        case Tank : currentAnimation_ = tankDriving_; currentShooting_ = tankShooting_; break;
      }
      if(currentType == Worker)
      {
        std::pair<float, int> amount = playerUnits_[i]->update();
        if(amount.second != 0){
          this->addResource(static_cast<int>(amount.first), amount.second);
          float resourceAmount;
          int capab = playerUnits_[i]->getCapability(amount.second);
          resourceAmount = map->getResource(playerUnits_[i]->getCurrentResourcePos(), capab);
          if(resourceAmount != 0 && playerUnits_[i]->gathering()){
            playerUnits_[i]->gatherResource(resourceAmount, amount.second, playerUnits_[i]->getCurrentResourcePos());
          }
          else{
            playerUnits_[i]->stopGathering();
          }
        }
        if( playerUnits_[i]->gathering() == true )
          {
            playerUnits_[i]->getAnimatedSprite().play(*currentShooting_);
            playerUnits_[i]->getAnimatedSprite().update(frameTime);
          }

      }
      //This section is for checking if there is an enemy unit in the units desired position
      //If this is true, the unit plays attack animation and hurts the target unit.
      if(playerUnits_[i]->getAttackStatus() == true)
      {
        //sets the correct rotation for a unit
        float dx = targetPosition_.x - position_.x;
        float dy = targetPosition_.y - position_.y;
        float rotation = ( atan2 (dy,dx) + (3*PI)/2 )*180/PI;
        playerUnits_[i]->getAnimatedSprite().setRotation(rotation);
        //plays the shooting animation
        playerUnits_[i]->getAnimatedSprite().play(*currentShooting_);
        playerUnits_[i]->getAnimatedSprite().update(frameTime);
        playerUnits_[i]->getAnimatedSprite().update(frameTime);
        if( playerUnits_[i]->canAttack())
        {
          //go through enemy units and find the one that is targeted by the unit
          for(std::size_t a = 0; a < enemyUnits_->size(); a++)
          {
            if(((*enemyUnits_)[a]->getAnimatedSprite()).getGlobalBounds().contains(targetPosition_))
            {
              (*enemyUnits_)[a]->hurtUnit(playerUnits_[i]->getDamage());
              if((*enemyUnits_)[a]->getCurrentHealth() <= 0)
              {

                for(std::size_t z = 0; z < playerUnits_.size(); z++)
                  {
                    if(((*enemyUnits_)[a]->getAnimatedSprite()).getGlobalBounds().contains(playerUnits_[z]->getAttackTarget()))
                    {
                      playerUnits_[z]->clearPath();
                      playerUnits_[z]->stopAttack();
                      playerUnits_[z]->getAnimatedSprite().play(*currentAnimation_);
                    }
                  }
                  playerUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
              }
            }
          }
          //go through enemy buildings and find the one that is targeted by the unit
          for(std::size_t a = 0; a < enemyBuildings_->size(); a++)
          {
            if(((*enemyBuildings_)[a]->getAnimatedSprite()).getGlobalBounds().contains(targetPosition_))
            {
              (*enemyBuildings_)[a]->damageBuilding(playerUnits_[i]->getDamage());
              if((*enemyBuildings_)[a]->getCurrentHealth() <= 0)
              {
                for(std::size_t z = 0; z < playerUnits_.size(); z++)
                  {
                    if(((*enemyBuildings_)[a]->getAnimatedSprite()).getGlobalBounds().contains(playerUnits_[z]->getAttackTarget()))
                    {
                      playerUnits_[z]->clearPath();
                      playerUnits_[z]->stopAttack();
                      playerUnits_[z]->getAnimatedSprite().play(*currentAnimation_);
                    }
                  }
                  playerUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
              }
            }
          }
        }
      }
   // for movement - input update the x and y position every frame
      else if( (position_.x != des_position_.x || position_.y != des_position_.y) )
      {
          playerUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
          playerUnits_[i]->getAnimatedSprite().update(frameTime);

          //sets the correct rotation for a unit
          float dx = des_position_.x - position_.x;
          float dy = des_position_.y - position_.y;
          float rotation = ( atan2 (dy,dx) + (3*PI)/2 )*180/PI;
          playerUnits_[i]->getAnimatedSprite().setRotation(rotation);
          float alpha = atan2(dy,dx);
          //this mess below is for updating the units position in a constant speed
          if( position_.x < des_position_.x )
          {
              position_.x += cos(alpha)*playerUnits_[i]->getSpeed()*deltaTime;
              if( position_.y < des_position_.y )
              {
                  position_.y += sin(alpha)*playerUnits_[i]->getSpeed()*deltaTime;
                  if( position_.y > des_position_.y )
                  {
                    position_.y = des_position_.y;
                  }
              }

              if( position_.y > des_position_.y )
              {
                  position_.y += sin(alpha)*playerUnits_[i]->getSpeed()*deltaTime;

                  if( position_.y < des_position_.y )
                  {
                    position_.y = des_position_.y;
                  }
              }

              if( position_.x > des_position_.x )
              {
                position_.x = des_position_.x; //just to make sure we dont go over/under the final position
              }

          }

          if( position_.x > des_position_.x )
          {
              position_.x += cos(alpha)*playerUnits_[i]->getSpeed()*deltaTime;
              if( position_.x < des_position_.x )
              {
                position_.x = des_position_.x;
              }

              if( position_.y < des_position_.y )
              {
                  position_.y += sin(alpha)*playerUnits_[i]->getSpeed()*deltaTime;

                  if( position_.y > des_position_.y )
                  {
                    position_.y = des_position_.y;
                  }
              }

              if( position_.y > des_position_.y )
              {
                  position_.y += sin(alpha)*playerUnits_[i]->getSpeed()*deltaTime;
                  if( position_.y < des_position_.y )
                  {
                    position_.y = des_position_.y;
                  }
              }

              if( position_.x < des_position_.x )
              {
                position_.x = des_position_.x;
              }

          }
          if( position_.x == des_position_.x )
          {
              if( position_.y < des_position_.y )
              {
                  position_.y += sin(alpha)*playerUnits_[i]->getSpeed()*deltaTime;

                  if( position_.y > des_position_.y )
                  {
                    position_.y = des_position_.y;
                  }
              }

              if( position_.y > des_position_.y )
              {
                  position_.y += sin(alpha)*playerUnits_[i]->getSpeed()*deltaTime;
                  if( position_.y < des_position_.y )
                  {
                    position_.y = des_position_.y;
                  }
              }
          }
          playerUnits_[i]->getAnimatedSprite().setPosition(position_.x, position_.y); //update the final position
      }
    }
  }
}

void Player::posCmd(sf::Vector2f mousepos, Map* map)
{
    //get the mouse position from playState handleEvents, calculate the path for all the selected units
    //And initialize the path to the unit entity for movement.
    for(std::size_t i = 0; i < selectedUnits_.size(); i++)
    {
      if(selectedUnits_[i]->getType() == Worker && selectedUnits_[i]->gathering()){
        selectedUnits_[i]->stopGathering();
      }
      if(!selectedUnits_[i]->getCurrentPath().empty()){
        sf::Vector2i oldPath = selectedUnits_[i]->getCurrentPath().back();
        map->setTilePassable(sf::Vector2f(static_cast<float>(oldPath.x), static_cast<float>(oldPath.y)));     // If new position command is given when the path is not completed, this sets the old path destination to passable.
      }
      selectedUnits_[i]->clearPath();                   // Remove old path from the unit
      des_position_ = mousepos;
      position_ = selectedUnits_[i]->getAnimatedSprite().getPosition();
      int current_x = (static_cast<int>(position_.x) - ((static_cast<int>(position_.x)) % 32))/32;          // Calculate start and end positions for
      int current_y = (static_cast<int>(position_.y) - ((static_cast<int>(position_.y)) % 32))/32;
      int dest_x = (static_cast<int>(des_position_.x) - (static_cast<int>(des_position_.x) % 32))/32;
      int dest_y = (static_cast<int>(des_position_.y) - (static_cast<int>(des_position_.y) % 32))/32;
      // Create map of zeros and ones for A* algorithm
      std::vector<std::vector<int>> mapInfo;
      mapInfo = map->getPassableMatrix();
      std::vector<sf::Vector2i> new_path;
      new_path.push_back(sf::Vector2i(0,0));
      if(!selectedUnits_[i]->aStarSet()){
        AStar aStar;
        aStar.setMap(mapInfo);
        selectedUnits_[i]->setAStar(aStar);
        std::vector<sf::Vector2i> new_path;
        sf::Vector2i current_position(current_x, current_y);
        sf::Vector2i destination_position(dest_x, dest_y);
        new_path = selectedUnits_[i]->getAStar()->calcPath(current_position, destination_position);   // Calculate the path for moving the unit
        selectedUnits_[i]->clearPath();
        selectedUnits_[i]->setCurrentPath(new_path);
        selectedUnits_[i]->setNextDestination();
        map->setTilePassable(sf::Vector2f(current_x, current_y));
        map->setTileNonPassable(sf::Vector2f(dest_x, dest_y));
      }
      else{
        selectedUnits_[i]->getAStar()->clear();
        selectedUnits_[i]->getAStar()->setMap(mapInfo);
        std::vector<sf::Vector2i> new_path;
        sf::Vector2i current_position(current_x, current_y);
        sf::Vector2i destination_position(dest_x, dest_y);
        new_path = selectedUnits_[i]->getAStar()->calcPath(current_position, destination_position);   // Calculate the path for moving the unit
        selectedUnits_[i]->clearPath();
        selectedUnits_[i]->setCurrentPath(new_path);
        selectedUnits_[i]->setNextDestination();
        map->setTilePassable(sf::Vector2f(current_x, current_y));
        map->setTileNonPassable(sf::Vector2f(dest_x, dest_y));
      }
    }
}

bool Player::attackCmd(sf::Vector2f mousepos)
{
  //check if any enemy building or unit is in the mouse position where a right click
  //was made. If target is found, attack command is given.
  if( !enemyUnits_->empty() || !enemyBuildings_->empty())
  {
    for(std::size_t i = 0; i < enemyUnits_->size(); i++)
    {
      if(((*enemyUnits_)[i]->getAnimatedSprite()).getGlobalBounds().contains(mousepos))
      {
        for(std::size_t e = 0; e < selectedUnits_.size(); e++)
        {
          float dx = mousepos.x - selectedUnits_[e]->getAnimatedSprite().getPosition().x;
          float dy = mousepos.y - selectedUnits_[e]->getAnimatedSprite().getPosition().y;
          if( dx != 0 && dy != 0 )
            {
              if( sqrt(dx*dx+dy*dy) <= selectedUnits_[e]->getAttackRange() )
              {
                selectedUnits_[e]->startAttack();
                selectedUnits_[e]->setAttackTarget(mousepos);
              }
            }
          else if( dx == 0 && dy != 0)
          {
            if( abs(dy) <= selectedUnits_[e]->getAttackRange() )
            {
              selectedUnits_[e]->startAttack();
              selectedUnits_[e]->setAttackTarget(mousepos);
            }
          }

          else if( dy == 0 && dx != 0)
          {
            if( abs(dx) <= selectedUnits_[e]->getAttackRange() )
            {
              selectedUnits_[e]->startAttack();
              selectedUnits_[e]->setAttackTarget(mousepos);
            }
          }
        }
        return true;
      }
      else
      {
        for(std::size_t e = 0; e < selectedUnits_.size(); e++)
        {
          selectedUnits_[e]->stopAttack();
        }
      }
    }

    for(std::size_t i = 0; i < enemyBuildings_->size(); i++)
    {

      if(((*enemyBuildings_)[i]->getAnimatedSprite()).getGlobalBounds().contains(mousepos))
      {

        for(std::size_t e = 0; e < selectedUnits_.size(); e++)
        {
          float dx = mousepos.x - selectedUnits_[e]->getAnimatedSprite().getPosition().x;
          float dy = mousepos.y - selectedUnits_[e]->getAnimatedSprite().getPosition().y;
          if( dx != 0 && dy != 0 )
            {
              if( sqrt(dx*dx+dy*dy) <= selectedUnits_[e]->getAttackRange() )
              {
                selectedUnits_[e]->startAttack();
                selectedUnits_[e]->setAttackTarget(mousepos);
              }
            }
          else if( dx == 0 && dy != 0)
          {
            if( dy <= selectedUnits_[e]->getAttackRange() )
            {
              selectedUnits_[e]->startAttack();
              selectedUnits_[e]->setAttackTarget(mousepos);
            }
          }

          else if( dy == 0 && dx != 0)
          {
            if( dx <= selectedUnits_[e]->getAttackRange() )
            {
              selectedUnits_[e]->startAttack();
              selectedUnits_[e]->setAttackTarget(mousepos);
            }
          }
        }
        return true;
      }
      else
      {
        for(std::size_t e = 0; e < selectedUnits_.size(); e++)
        {
          selectedUnits_[e]->stopAttack();
        }
        return false;
      }
    }
  }
  return false;
}

void Player::spawnUnit()
{
  //just a test function for spawning a unit, called by playState handleEvents
  //when F key is pressed
  std::shared_ptr<soldierUnit> newUnit = std::make_shared<soldierUnit>(sf::Vector2f (500,500));
  newUnit->setAnimation(soldierWalking_);
  playerUnits_.push_back(newUnit);
  std::cout << "NEW SOLDIER SPAWNED, ID: " << newUnit->getID() << std::endl;
}

void Player::addUnit(std::shared_ptr<Unit> unit)
{
  //add player created units to the vector
  playerUnits_.push_back(unit);
}


void Player::removeUnit(Map* map)
{
  //erase unit if self-destruct button is pressed
  for(std::size_t i = 0; i < playerUnits_.size(); i++)
  {
    for(std::size_t d = 0; d < selectedUnits_.size(); i++)
    {
      if( playerUnits_[i]->getID() == selectedUnits_[d]->getID() && playerUnits_[i]->getType() == selectedUnits_[d]->getType() )
      {
        // Get unit location as pixel coordinates
        sf::Vector2f position = selectedUnits_[d]->getDestination();
        // Convert position to tile coordinates
        position.x = (position.x-16)/32;
        position.y = (position.y-16)/32;
        // Set the tile where the unit was to passable
        map->setTilePassable(position);
        selectedUnits_.clear();
        playerUnits_.erase( playerUnits_.begin() + i);
        break;
      }
    }
  }
}

void Player::removeBuilding()
{
  //erase building if self-destruct button is pressed
  for(std::size_t i = 0; i < playerBuildings_.size(); i++)
  {
    for(std::size_t d = 0; d < selectedBuilding_.size(); i++)
    {
      if( playerBuildings_[i]->getLocation() == selectedBuilding_[d]->getLocation())
      {
        selectedBuilding_.clear();
        playerBuildings_.erase( playerBuildings_.begin() + i);
        break;
      }
    }
  }
}
/*
** Will take care of placing the starting base. Called once when generating the map.
*/
void Player::makeStartingBase(float x, float y,  Map* map)
{
  std::shared_ptr<MainBuilding> startingBase = std::make_shared<MainBuilding>(map, true, mainBuilding_, sf::Vector2f(x,y), true);
  playerBuildings_.push_back(startingBase);
}

void Player::buildBarracks(Map* map)
{
  sf::Vector2f builderLocation = selectedUnits_[0]->getPosition(); //As pixel coordinates
  sf::Vector2f buildingLocation;
  buildingLocation.x = (builderLocation.x-16-32)/32;
  buildingLocation.y = (builderLocation.y-16-32*2)/32;
  std::shared_ptr<UnitBuilding> barracks = std::make_shared<UnitBuilding>(map, true, unitBuilding_, buildingLocation, false);

  if(map->getTile(buildingLocation.x, buildingLocation.y)->isPassable()
  && map->getTile(buildingLocation.x+1, buildingLocation.y)->isPassable()
  && map->getTile(buildingLocation.x, buildingLocation.y+1)->isPassable()
  && map->getTile(buildingLocation.x+1, buildingLocation.y+1)->isPassable())
  {
    if(removeResource(barracks.get()->getBuildingCost(), 2))
    {
      barracks.get()->setNonPassable();
      playerBuildings_.push_back(barracks);
    }else{
      std::cout << "Not enough silver!" << std::endl;
    }

  }else{
    std::cout << "INVALID POSITION FOR BUILDING" << std::endl;
  }
}

void Player::buildFactory(Map* map)
{
  sf::Vector2f builderLocation = selectedUnits_[0]->getPosition(); //As pixel coordinates
  sf::Vector2f buildingLocation;
  buildingLocation.x = (builderLocation.x-16-32)/32;
  buildingLocation.y = (builderLocation.y-16-32*2)/32;
  std::shared_ptr<FactoryBuilding> factory = std::make_shared<FactoryBuilding>(map, true, factoryBuilding_, buildingLocation, false);

  if(map->getTile(buildingLocation.x, buildingLocation.y)->isPassable()
  && map->getTile(buildingLocation.x+1, buildingLocation.y)->isPassable()
  && map->getTile(buildingLocation.x+2, buildingLocation.y)->isPassable()
  && map->getTile(buildingLocation.x, buildingLocation.y+1)->isPassable()
  && map->getTile(buildingLocation.x+1, buildingLocation.y+1)->isPassable()
  && map->getTile(buildingLocation.x+2, buildingLocation.y+1)->isPassable())
  {
    if(removeResource(factory.get()->getBuildingCost(), 2))
    {
      factory.get()->setNonPassable();
      playerBuildings_.push_back(factory);
    }else{
      std::cout << "Not enough silver!" << std::endl;
    }

  }else{
    std::cout << "INVALID POSITION FOR BUILDING" << std::endl;
  }
}

void Player::buildThreeDprinter(Map* map)
{
  sf::Vector2f builderLocation = selectedUnits_[0]->getPosition(); //As pixel coordinates
  sf::Vector2f buildingLocation;
  buildingLocation.x = (builderLocation.x-16-32)/32;
  buildingLocation.y = (builderLocation.y-16-32*2)/32;
  std::shared_ptr<ResourceBuilding> ThreeDprinter = std::make_shared<ResourceBuilding>(map, true, resourceBuilding_, buildingLocation, false, Silver);

  if(map->getTile(buildingLocation.x, buildingLocation.y)->isPassable()
  && map->getTile(buildingLocation.x+1, buildingLocation.y)->isPassable()
  && map->getTile(buildingLocation.x, buildingLocation.y+1)->isPassable()
  && map->getTile(buildingLocation.x+1, buildingLocation.y+1)->isPassable())
  {
    if(removeResource(ThreeDprinter.get()->getBuildingCost(), 2))
    {
      ThreeDprinter.get()->setNonPassable();
      playerBuildings_.push_back(ThreeDprinter);
    }else{
      std::cout << "Not enough silver!" << std::endl;
    }

  }else{
    std::cout << "INVALID POSITION FOR BUILDING" << std::endl;
  }
}

void Player::startUnitProduction()
{
  if(getSelectedBuilding()[0]->isComplete() && removeResource(getSelectedBuilding()[0]->unitCost(), 2))
  {
    getSelectedBuilding()[0]->produceUnit();
  }else{
    std::cout << "Not enough silver!" << std::endl;
  }
}

void Player::produceUnit()
{
  for(size_t i = 0; i < playerBuildings_.size(); i++)
  {
    if(playerBuildings_[i]->canSpawn() && playerBuildings_[i]->getType() == Mainbuilding)
    {
      std::shared_ptr<WorkerUnit> newUnit = std::make_shared<WorkerUnit>(playerBuildings_[i]->getSpawnLocation());
      newUnit->setAnimation(workerWalking_);
      playerUnits_.push_back(newUnit);
      playerBuildings_[i]->setCanSpawn(false);
    }

    if(playerBuildings_[i]->canSpawn() && playerBuildings_[i]->getType() == Unitbuilding)
    {
      std::shared_ptr<soldierUnit> newUnit = std::make_shared<soldierUnit>(playerBuildings_[i]->getSpawnLocation());
      newUnit->setAnimation(soldierWalking_);
      playerUnits_.push_back(newUnit);
      playerBuildings_[i]->setCanSpawn(false);
    }

    if(playerBuildings_[i]->canSpawn() && playerBuildings_[i]->getType() == Factorybuilding)
    {
      std::shared_ptr<TankUnit> newUnit = std::make_shared<TankUnit>(playerBuildings_[i]->getSpawnLocation());
      newUnit->setAnimation(tankDriving_);
      playerUnits_.push_back(newUnit);
      playerBuildings_[i]->setCanSpawn(false);
    }

    if(playerBuildings_[i]->getType() == Resourcebuilding)
    {
      std::pair <bool, int> resourcesAvailable = playerBuildings_[i]->getResources();
      if(resourcesAvailable.first)
      {
        this->addResource(resourcesAvailable.second, 2);
      }
    }
  }
}


void Player::upgradeBuilding()
{
  if (!getSelectedBuilding()[0]->isProducing() && getSelectedBuilding()[0]->canUpgradeBuilding() && removeResource(getSelectedBuilding()[0]->upgradeCost(), 1))
  {
    getSelectedBuilding()[0]->upgradeBuilding();
  }else{
    std::cout << "Max level reached or not enough gold!" << std::endl;
  }
}

/*std::vector<Unit> Player::getUnits(){
  //might be useless
  return playerUnits_;
}*/

void Player::selectUnitsAndBuildings(sf::Vector2f mapPos)
{
  //called by handleEvents everytime a left click occurs. If a unit is under the
  //mouse position while the click happens it is added to the selectedUnits_ vector,
  //and commands can be issued to it. If a click is made on the map the selection
  //is cleared.
  unitsAdded = false;
  buildingAdded = false;
  for(std::size_t i = 0; i < playerUnits_.size(); i++)
  {
    if((playerUnits_[i]->getAnimatedSprite()).getGlobalBounds().contains(mapPos))
    {
      selectedBuilding_.clear();
      selectedUnits_.clear();
      selectedUnits_.push_back(playerUnits_[i].get());
      std::cout << "UNIT SELECTED, ID: " << playerUnits_[i]->getID() << std::endl;
      unitsAdded = true;
    }
  }
  if(!unitsAdded)
  {
    selectedUnits_.clear();
    for(std::size_t i = 0; i < playerBuildings_.size(); i++)
    {
      if((playerBuildings_[i]->getAnimatedSprite()).getGlobalBounds().contains(mapPos))
      {
        selectedBuilding_.clear();
        selectedBuilding_.push_back(playerBuildings_[i].get());
        std::cout << "BUILDING SELECTED" << std::endl;
        buildingAdded = true;
      }
    }
    if(!buildingAdded)
    {
      selectedBuilding_.clear();
      std::cout << "SELECTION CLEAR" << std::endl;
    }
  }
}

void Player::draw(GameEngine &game){
  //draw function for every unit

  for(size_t i = 0; i < playerBuildings_.size(); i++)//
  {
    game.getWindow()->draw(playerBuildings_[i]->getAnimatedSprite());
  }

    for(std::size_t i = 0; i < playerUnits_.size(); i++)
    {
      game.getWindow()->draw(playerUnits_[i]->getAnimatedSprite());
    }

  if( !selectedUnits_.empty() )
  {
    for(std::size_t i = 0; i < selectedUnits_.size(); i++)
    {

      if(selectedUnits_[i]->getType() == Tank)
      {
        tankIndicatorSprite_.setPosition( selectedUnits_[i]->getAnimatedSprite().getPosition() );
        game.getWindow()->draw(tankIndicatorSprite_);
      }
      else
      {
        unitIndicatorSprite_.setPosition( selectedUnits_[i]->getAnimatedSprite().getPosition() );
        game.getWindow()->draw(unitIndicatorSprite_);
      }
    }
  }
  if( !selectedBuilding_.empty() )
  {
    for(std::size_t i = 0; i < selectedBuilding_.size(); i++)
    {
      buildingIndicatorSprite_.setPosition( selectedBuilding_[i]->getAnimatedSprite().getPosition() );
      game.getWindow()->draw(buildingIndicatorSprite_);
    }
  }



}

std::vector<Unit*> Player::getSelectedUnits()
{
  return selectedUnits_;
}

std::vector<Building*> Player::getSelectedBuilding()
{
  return selectedBuilding_;
}

std::vector<std::shared_ptr<Unit>>* Player::getUnits()
{
  return &playerUnits_;
}

std::vector<std::shared_ptr<Building>>* Player::getBuildings()
{
  return &playerBuildings_;
}

void Player::clearSelectedUnits()
{
  selectedUnits_.clear();
}

bool Player::addResource(int amount, int type)
{
  if(type == 1){
    gold_ = gold_ + amount;
    return true;
  }
  if(type == 2 && silver_ + amount < 9999){
    silver_ = silver_ + amount;
    return true;
  }else if(silver_ + amount >= 9999){
    silver_ = 9999;
    return true;
  }
  return false;
}
void Player::passEnemyUnits(std::vector<std::shared_ptr<Unit>>* enemyUnits)
{
  enemyUnits_ = enemyUnits;
}

void Player::passEnemyBuildings(std::vector<std::shared_ptr<Building>>* enemyBuildings)
{
  enemyBuildings_ = enemyBuildings;
}


bool Player::removeResource(int amount, int type)
{
  if(type == 1 && gold_ >= amount){
    gold_ = gold_ - amount;
    return true;
  }
  if(type == 2 && silver_ >= amount){
    silver_ = silver_ - amount;
    return true;
  }
  return false;
}

bool Player::isBaseDestroyed()
{
  if(!playerBuildings_.empty())
  {
    if(playerBuildings_[0]->getType() == Mainbuilding)
    {
      return false;
    }
    else
    {
      return true;
    }
  }
  else
  {
    return true;
  }
}

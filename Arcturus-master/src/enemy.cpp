#include "enemy.hpp"

Enemy::Enemy()
{
  /*
  unitIndicator_.loadFromFile("resources/graphics/unitTileset.png",sf::IntRect(320, 32, 32, 32));
  unitIndicatorSprite_.setTexture(unitIndicator_);
  unitIndicatorSprite_.setOrigin(16,16);
  buildingIndicator_.loadFromFile("resources/graphics/unitTileset.png",sf::IntRect(32*8, 32*3, 32*3, 32*3));
  buildingIndicatorSprite_.setTexture(buildingIndicator_);
  buildingIndicatorSprite_.setOrigin(0,0);
  gold_ = 1;
  silver_ = 200;*/
  soldierClock_.restart();
  tankClock_.restart();
  actionClock_.restart();

}

Enemy::~Enemy()
{

}

void Enemy::setTextures(Animation* esoldierWalking, Animation* esoldierShooting,
Animation* eworkerWalking, Animation* eworkerAct, Animation* etankDriving, Animation* etankShooting,
Animation* emainBuilding, Animation* eunitBuilding, Animation* efactoryBuilding)
{
  //for animation implementations
  soldierWalking_ = esoldierWalking;
  soldierShooting_ = esoldierShooting;
  workerWalking_ = eworkerWalking;
  workerAct_ = eworkerAct;
  tankDriving_ = etankDriving;
  tankShooting_ = etankShooting;
  mainBuilding_ = emainBuilding;
  unitBuilding_ = eunitBuilding;
  factoryBuilding_ = efactoryBuilding;
}

void Enemy::update(float &deltaTime,  Map* map)
{
  //frameclock for animation updating
  frameTime = frameClock.restart();
  if(!enemyBuildings_.empty())
  {

    for(std::size_t i = 0; i < enemyBuildings_.size(); i++)
    {
      StructureType currentType = enemyBuildings_[i]->getType();
      switch(currentType)
      {
        case Mainbuilding : currentAnimation_ = mainBuilding_; break;
        case Unitbuilding : currentAnimation_ = unitBuilding_; break;
        case Resourcebuilding : currentAnimation_ = unitBuilding_; break;
        case Factorybuilding : currentAnimation_ = factoryBuilding_; break;
      }

      if(enemyBuildings_[i]->getCurrentHealth() <= 0)
      {
        enemyBuildings_.erase(enemyBuildings_.begin() + i);
      }
    }
  }

  if(!enemyUnits_.empty())
  {
    for(std::size_t i = 0; i < enemyUnits_.size(); i++)
    {

      UnitType currentType = enemyUnits_[i]->getType();
      //erase dead units
      if(enemyUnits_[i]->getCurrentHealth() <= 0)
      {
        // Get unit location as pixel coordinates
        sf::Vector2f position = enemyUnits_[i]->getDestination();
        // Convert position to tile coordinates
        position.x = (position.x-16)/32;
        position.y = (position.y-16)/32;
        // Set the tile where the unit was to passable
        map->setTilePassable(position);
        enemyUnits_.erase(enemyUnits_.begin() + i);
      }

      switch(currentType)
      {
        case Soldier : currentAnimation_ = soldierWalking_; currentShooting_ = soldierShooting_; break;
        case Worker : currentAnimation_ = workerWalking_; currentShooting_ = workerAct_; break;
        case Flying : break;
        case Tank : currentAnimation_ = tankDriving_; currentShooting_ = tankShooting_; break;
      }

      attackingUnits_ = false;
      for(std::size_t a = 0; a < playerUnits_->size(); a++)
      {
        playerUnitPosition_ = (*playerUnits_)[a]->getAnimatedSprite().getPosition();
        position_ = enemyUnits_[i]->getAnimatedSprite().getPosition();
        dx = playerUnitPosition_.x - position_.x;
        dy = playerUnitPosition_.y - position_.y;

        if( dx != 0 && dy != 0 )
        {
          if( sqrt(dx*dx+dy*dy) <= enemyUnits_[i]->getAttackRange() )
          {
            float rotation = ( atan2 (dy,dx) + (3*PI)/2 )*180/PI;
            enemyUnits_[i]->getAnimatedSprite().setRotation(rotation);
            enemyUnits_[i]->startAttack();
            enemyUnits_[i]->setAttackTarget(playerUnitPosition_);
            attackingUnits_ = true;
            if( enemyUnits_[i]->canAttack() == true )
            {
              (*playerUnits_)[a]->hurtUnit(enemyUnits_[i]->getDamage());
              if((*playerUnits_)[a]->getCurrentHealth() <= 0)
              {
                for(std::size_t z = 0; z < enemyUnits_.size(); z++)
                  {
                    if(((*playerUnits_)[a]->getAnimatedSprite()).getGlobalBounds().contains(enemyUnits_[z]->getAttackTarget()))
                    {
                      enemyUnits_[z]->stopAttack();
                      enemyUnits_[z]->getAnimatedSprite().play(*currentAnimation_);
                      attackingUnits_ = false;
                    }
                  }
                enemyUnits_[i]->stopAttack();
                enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
                attackingUnits_ = false;
                break;
              }
            }
            break;
          }
          else
          {
            enemyUnits_[i]->stopAttack();
            enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
            attackingUnits_ = false;
          }
        }
        else if( dx == 0 && dy != 0)
        {
          if( abs(dy) <= enemyUnits_[i]->getAttackRange() )
          {
            float rotation = ( atan2 (dy,dx) + (3*PI)/2 )*180/PI;
            enemyUnits_[i]->getAnimatedSprite().setRotation(rotation);
            enemyUnits_[i]->startAttack();
            enemyUnits_[i]->setAttackTarget(playerUnitPosition_);
            attackingUnits_ = true;
            if( enemyUnits_[i]->canAttack() == true  )
            {
              (*playerUnits_)[a]->hurtUnit(enemyUnits_[i]->getDamage());
              if((*playerUnits_)[a]->getCurrentHealth() <= 0)
              {
                for(std::size_t z = 0; z < enemyUnits_.size(); z++)
                {
                    if(((*playerUnits_)[a]->getAnimatedSprite()).getGlobalBounds().contains(enemyUnits_[z]->getAttackTarget()))
                    {
                      enemyUnits_[z]->stopAttack();
                      enemyUnits_[z]->getAnimatedSprite().play(*currentAnimation_);
                      attackingUnits_ = false;
                    }
                }
                enemyUnits_[i]->stopAttack();
                enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
                attackingUnits_ = false;
                break;
              }
            }
            break;
          }
          else
          {
            enemyUnits_[i]->stopAttack();
            enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
            attackingUnits_ = false;
          }
        }

        else if( dy == 0 && dx != 0)
        {
          if( abs(dx) <= enemyUnits_[i]->getAttackRange() )
          {
            float rotation = ( atan2 (dy,dx) + (3*PI)/2 )*180/PI;
            enemyUnits_[i]->getAnimatedSprite().setRotation(rotation);
            enemyUnits_[i]->startAttack();
            enemyUnits_[i]->setAttackTarget(playerUnitPosition_);
            attackingUnits_ = true;
            if( enemyUnits_[i]->canAttack() == true  )
            {
              (*playerUnits_)[a]->hurtUnit(enemyUnits_[i]->getDamage());
              if((*playerUnits_)[a]->getCurrentHealth() <= 0)
              {
                for(std::size_t z = 0; z < enemyUnits_.size(); z++)
                  {
                    if(((*playerUnits_)[a]->getAnimatedSprite()).getGlobalBounds().contains(enemyUnits_[z]->getAttackTarget()))
                    {
                      enemyUnits_[z]->stopAttack();
                      enemyUnits_[z]->getAnimatedSprite().play(*currentAnimation_);
                      attackingUnits_ = false;
                    }
                  }
                enemyUnits_[i]->stopAttack();
                enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
                attackingUnits_ = false;
                break;
              }
            }
            break;
          }
          else
          {
            enemyUnits_[i]->stopAttack();
            enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
            attackingUnits_ = false;
          }
        }
      }

      if( attackingUnits_ == false )
      {
        for(std::size_t a = 0; a < playerBuildings_->size(); a++)
        {
          playerBuildingPosition_ = (*playerBuildings_)[a]->getAnimatedSprite().getPosition();
          position_ = enemyUnits_[i]->getAnimatedSprite().getPosition();
          dx = playerBuildingPosition_.x - position_.x;
          dy = playerBuildingPosition_.y - position_.y;

          if( dx != 0 && dy != 0 )
          {
            if( sqrt(dx*dx+dy*dy) <= enemyUnits_[i]->getAttackRange() )
            {
              float rotation = ( atan2 (dy,dx) + (3*PI)/2 )*180/PI;
              enemyUnits_[i]->getAnimatedSprite().setRotation(rotation);
              enemyUnits_[i]->startAttack();
              enemyUnits_[i]->setAttackTarget(playerBuildingPosition_);
              if( enemyUnits_[i]->canAttack() == true )
              {
                (*playerBuildings_)[a]->damageBuilding(enemyUnits_[i]->getDamage());
                if((*playerBuildings_)[a]->getCurrentHealth() <= 0)
                {
                  for(std::size_t z = 0; z < enemyUnits_.size(); z++)
                    {
                      if(((*playerBuildings_)[a]->getAnimatedSprite()).getGlobalBounds().contains(enemyUnits_[z]->getAttackTarget()))
                      {
                        enemyUnits_[z]->stopAttack();
                        enemyUnits_[z]->getAnimatedSprite().play(*currentAnimation_);
                      }
                    }
                  enemyUnits_[i]->stopAttack();
                  enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
                  break;
                }
              }
              break;
            }
            else
            {
              enemyUnits_[i]->stopAttack();
              enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
            }
          }
          else if( dx == 0 && dy != 0)
          {
            if( abs(dy) <= enemyUnits_[i]->getAttackRange() )
            {
              float rotation = ( atan2 (dy,dx) + (3*PI)/2 )*180/PI;
              enemyUnits_[i]->getAnimatedSprite().setRotation(rotation);
              enemyUnits_[i]->startAttack();
              enemyUnits_[i]->setAttackTarget(playerBuildingPosition_);
              if( enemyUnits_[i]->canAttack() == true  )
              {
                (*playerBuildings_)[a]->damageBuilding(enemyUnits_[i]->getDamage());
                if((*playerBuildings_)[a]->getCurrentHealth() <= 0)
                {
                  for(std::size_t z = 0; z < enemyUnits_.size(); z++)
                    {
                      if(((*playerBuildings_)[a]->getAnimatedSprite()).getGlobalBounds().contains(enemyUnits_[z]->getAttackTarget()))
                      {
                        enemyUnits_[z]->stopAttack();
                        enemyUnits_[z]->getAnimatedSprite().play(*currentAnimation_);
                      }
                    }
                  enemyUnits_[i]->stopAttack();
                  enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
                  break;
                }
              }
              break;
            }
            else
            {
              enemyUnits_[i]->stopAttack();
              enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
            }
          }

          else if( dy == 0 && dx != 0)
          {
            if( abs(dx) <= enemyUnits_[i]->getAttackRange() )
            {
              float rotation = ( atan2 (dy,dx) + (3*PI)/2 )*180/PI;
              enemyUnits_[i]->getAnimatedSprite().setRotation(rotation);
              enemyUnits_[i]->startAttack();
              enemyUnits_[i]->setAttackTarget(playerBuildingPosition_);
              if( enemyUnits_[i]->canAttack() == true  )
              {
                (*playerBuildings_)[a]->damageBuilding(enemyUnits_[i]->getDamage());
                if((*playerBuildings_)[a]->getCurrentHealth() <= 0)
                {
                  for(std::size_t z = 0; z < enemyUnits_.size(); z++)
                    {
                      if(((*playerBuildings_)[a]->getAnimatedSprite()).getGlobalBounds().contains(enemyUnits_[z]->getAttackTarget()))
                      {
                        enemyUnits_[z]->stopAttack();
                        enemyUnits_[z]->getAnimatedSprite().play(*currentAnimation_);
                      }
                    }
                  enemyUnits_[i]->stopAttack();
                  enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
                  break;
                }
              }
              break;
            }
            else
            {
              enemyUnits_[i]->stopAttack();
              enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
            }
          }
        }
      }

      if(enemyUnits_[i]->getAttackStatus() == true)
      {
        enemyUnits_[i]->getAnimatedSprite().play(*currentShooting_);
        enemyUnits_[i]->getAnimatedSprite().update(frameTime);
      }
      else
      {
        enemyUnits_[i]->stopAttack();
        enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
      }
      if(!enemyUnits_[i]->getCurrentPath().empty() && !enemyUnits_[i]->getAttackStatus()){
        this->moveUnit(i, deltaTime);
      }
      if(actionClock_.getElapsedTime().asSeconds() > 90 && enemyUnits_[i]->getCurrentPath().empty() && !enemyUnits_[i]->getAttackStatus()){
        sf::Vector2f destinationLoc = (*playerBuildings_)[0]->getLocation();
        if(map->getTile(destinationLoc.x-2, destinationLoc.y)->isPassable()){
          this->posCmd(sf::Vector2f(destinationLoc.x-2, destinationLoc.y), map, i);
        }
        else if(map->getTile(destinationLoc.x+2, destinationLoc.y)->isPassable()){
          this->posCmd(sf::Vector2f(destinationLoc.x+2, destinationLoc.y), map, i);
        }
        else if(map->getTile(destinationLoc.x, destinationLoc.y-2)->isPassable()){
          this->posCmd(sf::Vector2f(destinationLoc.x, destinationLoc.y-2), map, i);
        }
        else if(map->getTile(destinationLoc.x, destinationLoc.y+2)->isPassable()){
          this->posCmd(sf::Vector2f(destinationLoc.x, destinationLoc.y+2), map, i);
        }
      }
    }
  }
  if(soldierClock_.getElapsedTime().asSeconds() > spawntime1_){
    this->produceUnit(map, Soldier);
    soldierClock_.restart();
  }
  if(tankClock_.getElapsedTime().asSeconds() > spawntime2_){
    this->produceUnit(map, Tank);
    tankClock_.restart();
  }
  if(actionClock_.getElapsedTime().asSeconds() > 5*60 && spawntime1_ == 61){
    spawntime1_ = 29;
    spawntime2_ = 61;
  }
}

/*void Enemy::posCmd(sf::Vector2f mousepos, Map* map)
{

}*/

void Enemy::spawnUnit()
{
  //just a test function for spawning a unit, called by playState handleEvents
  //when E key is pressed
  std::shared_ptr<TankUnit> newUnit = std::make_shared<TankUnit>(sf::Vector2f(500,500));
  newUnit->setAnimation(tankDriving_);
  enemyUnits_.push_back(newUnit);
  std::cout << "NEW ENEMY TANK SPAWNED, ID: " << newUnit->getID() << std::endl;
}

void Enemy::produceUnit(Map* map, UnitType type)
{
  sf::Vector2f spawnLoc(enemyBuildings_[0]->getLocation().x + 3, enemyBuildings_[0]->getLocation().y);
  if(map->getTile(spawnLoc.x, spawnLoc.y)->isPassable()){
    if(type == Soldier){
      std::shared_ptr<soldierUnit> newUnit = std::make_shared<soldierUnit>(sf::Vector2f(spawnLoc.x*32, spawnLoc.y*32));
      newUnit->setAnimation(soldierWalking_);
      enemyUnits_.push_back(newUnit);
    }
    else if(type == Tank){
      std::shared_ptr<TankUnit> newUnit = std::make_shared<TankUnit>(sf::Vector2f(spawnLoc.x*32, spawnLoc.y*32));
      newUnit->setAnimation(tankDriving_);
      enemyUnits_.push_back(newUnit);
    }

  }
  else{
    sf::Vector2f spawnLoc(enemyBuildings_[0]->getLocation().x - 1, enemyBuildings_[0]->getLocation().y);
    if(map->getTile(spawnLoc.x, spawnLoc.y)->isPassable()){
      if(type == Soldier){
        std::shared_ptr<soldierUnit> newUnit = std::make_shared<soldierUnit>(sf::Vector2f(spawnLoc.x*32, spawnLoc.y*32));
        newUnit->setAnimation(soldierWalking_);
        enemyUnits_.push_back(newUnit);
      }
      else if(type == Tank){
        std::shared_ptr<TankUnit> newUnit = std::make_shared<TankUnit>(sf::Vector2f(spawnLoc.x*32, spawnLoc.y*32));
        newUnit->setAnimation(tankDriving_);
        enemyUnits_.push_back(newUnit);
      }
    }
  }
}

/*void Enemy::addUnit(std::shared_ptr<Unit> unit)
{
  //add player created units to the vector
  enemyUnits_.push_back(unit);
}*/

/*
** Will take care of placing the starting base. Called once when generating the map.
*/
void Enemy::makeStartingBase(float x, float y,  Map* map)
{
  std::shared_ptr<MainBuilding> startingBase = std::make_shared<MainBuilding>(map, false, mainBuilding_, sf::Vector2f(x,y), true);
  enemyBuildings_.push_back(startingBase);
}


/*void Enemy::startWorkerProduction()
{
  getSelectedBuilding()[0]->produceWorker();
}*/

/*void Enemy::produceWorker()
{
  for(size_t i = 0; i < playerBuildin:gs_.size(); i++)
  {
    if(playerBuildings_[i].getType() == Mainbuilding && playerBuildings_[i].canSpawn())
    {
      std::shared_ptr<WorkerUnit> newUnit = std::make_shared<WorkerUnit>(playerBuildings_[i].getSpawnLocation());
      //WorkerUnit worker(playerBuildings_[i].getSpawnLocation());
      newUnit->setAnimation(workerWalking_);
      playerUnits_.push_back(newUnit);
      playerBuildings_[i].setCanSpawn(false);
    }
  }
}*/

/*std::vector<Unit> Enemy::getUnits(){
  //might be useless
  return playerUnits_;
}*/

/*void Enemy::selectUnitsAndBuildings(sf::Vector2f mapPos)
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
      if((playerBuildings_[i].getAnimatedSprite()).getGlobalBounds().contains(mapPos))
      {
        selectedBuilding_.push_back(&playerBuildings_[i]);
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
}*/

void Enemy::draw(GameEngine &game)
{
  //draw function for every enemy unit and building

  for(size_t i = 0; i < enemyBuildings_.size(); i++)//
  {
    game.getWindow()->draw(enemyBuildings_[i]->getAnimatedSprite());
  }

  for(std::size_t i = 0; i < enemyUnits_.size(); i++)
  {
    game.getWindow()->draw(enemyUnits_[i]->getAnimatedSprite());
  }

}


/*std::vector<Unit*> Enemy::getSelectedUnits()
{
  //might be useless
  return selectedUnits_;
}*/

/*std::vector<Building*> Enemy::getSelectedBuilding()
{
  return selectedBuilding_;
}*/

/*void Enemy::clearSelectedUnits()
{
  //might be useless
  selectedUnits_.clear();
}*/

bool Enemy::addResource(int amount, int type)
{
  if(type == 1){
    gold_ = gold_ + amount;
    return true;
  }
  if(type == 2){
    silver_ = silver_ + amount;
    return true;
  }
  return false;
}

std::vector<std::shared_ptr<Unit>>* Enemy::getUnits()
{
  return &enemyUnits_;
}

std::vector<std::shared_ptr<Building>>* Enemy::getBuildings()
{
  return &enemyBuildings_;
}

void Enemy::passPlayerUnits(std::vector<std::shared_ptr<Unit>>* playerUnits)
{
  playerUnits_ = playerUnits;
}

void Enemy::posCmd(sf::Vector2f position, Map* map, int i)
{
  //get the mouse position from playState handleEvents, calculate the path for all the selected units
  //And initialize the path to the unit entity for movement.
  /*if(enemyUnits_[i]->getType() == Worker && enemyUnits_[i]->gathering()){
    enemyUnits_[i]->stopGathering();
  }*/
  if(!enemyUnits_[i]->getCurrentPath().empty()){
    sf::Vector2i oldPath = enemyUnits_[i]->getCurrentPath().back();
    map->setTilePassable(sf::Vector2f(static_cast<float>(oldPath.x), static_cast<float>(oldPath.y)));     // If new position command is given when the path is not completed, this sets the old path destination to passable.
  }
  enemyUnits_[i]->clearPath();                   // Remove old path from the unit
  des_position_ = position;
  //position_ = enemyUnits_[i]->getAnimatedSprite().getPosition();
  int current_x = (static_cast<int>(position_.x) - ((static_cast<int>(position_.x)) % 32))/32;          // Calculate start and end positions for
  int current_y = (static_cast<int>(position_.y) - ((static_cast<int>(position_.y)) % 32))/32;
  int dest_x = static_cast<int>(des_position_.x);
  int dest_y = static_cast<int>(des_position_.y);
  // Create map of zeros and ones for A* algorithm
  std::vector<std::vector<int>> mapInfo;
  mapInfo = map->getPassableMatrix();
  std::vector<sf::Vector2i> new_path;
  new_path.push_back(sf::Vector2i(0,0));
  if(!enemyUnits_[i]->aStarSet()){
    AStar aStar;
    aStar.setMap(mapInfo);
    enemyUnits_[i]->setAStar(aStar);
    std::vector<sf::Vector2i> new_path;
    sf::Vector2i current_position(current_x, current_y);
    sf::Vector2i destination_position(dest_x, dest_y);
    new_path = enemyUnits_[i]->getAStar()->calcPath(current_position, destination_position);   // Calculate the path for moving the unit
    enemyUnits_[i]->clearPath();
    enemyUnits_[i]->setCurrentPath(new_path);
    enemyUnits_[i]->setNextDestination();
    //map->setTilePassable(sf::Vector2f(current_x, current_y));
    //map->setTileNonPassable(sf::Vector2f(dest_x, dest_y));
  }

  else{
    enemyUnits_[i]->getAStar()->clear();
    enemyUnits_[i]->getAStar()->setMap(mapInfo);
    std::vector<sf::Vector2i> new_path;
    sf::Vector2i current_position(current_x, current_y);
    sf::Vector2i destination_position(dest_x, dest_y);
    new_path = enemyUnits_[i]->getAStar()->calcPath(current_position, destination_position);   // Calculate the path for moving the unit
    enemyUnits_[i]->clearPath();
    enemyUnits_[i]->setCurrentPath(new_path);
    enemyUnits_[i]->setNextDestination();
    map->setTilePassable(sf::Vector2f(current_x, current_y));
    map->setTileNonPassable(sf::Vector2f(dest_x, dest_y));
  }
}

void Enemy::moveUnit(int i, float &deltaTime)
{
  position_ = enemyUnits_[i]->getAnimatedSprite().getPosition();
  des_position_ = enemyUnits_[i]->getDestination();
  //std::cout << "destination: " << des_position_.x << "   " << des_position_.y << std::endl;
  //std::cout << "menee" << std::endl;
  if( ((position_.x) - (des_position_.x)) == 0 && ((position_.y) - (des_position_.y)) == 0 ){          // Check if the unit has reached the next tile of the path
    enemyUnits_[i]->removePathPoint();
    enemyUnits_[i]->setNextDestination();                                                                   // Set the next tile on path to destination
    //std::cout << "ei mene" << std::endl;                                                         // Remove the already used tile from the path
  }

  if( (position_.x != des_position_.x || position_.y != des_position_.y) )
  {
    enemyUnits_[i]->getAnimatedSprite().play(*currentAnimation_);
    enemyUnits_[i]->getAnimatedSprite().update(frameTime);
    //TODO joku järkevämpi rakenne
    //sets the correct rotation for a unit
    float dx = des_position_.x - position_.x;
    float dy = des_position_.y - position_.y;
    float rotation = ( atan2 (dy,dx) + (3*PI)/2 )*180/PI;
    enemyUnits_[i]->getAnimatedSprite().setRotation(rotation);
    float alpha = atan2(dy,dx);
    //this mess below is for updating the units position in a constant speed
    if( position_.x < des_position_.x )
    {
        position_.x += cos(alpha)*enemyUnits_[i]->getSpeed()*deltaTime;
        if( position_.y < des_position_.y )
        {
            position_.y += sin(alpha)*enemyUnits_[i]->getSpeed()*deltaTime;
            if( position_.y > des_position_.y )
            {
              position_.y = des_position_.y;
            }
        }

        if( position_.y > des_position_.y )
        {
            position_.y += sin(alpha)*enemyUnits_[i]->getSpeed()*deltaTime;

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
        position_.x += cos(alpha)*enemyUnits_[i]->getSpeed()*deltaTime;
        if( position_.x < des_position_.x )
        {
          position_.x = des_position_.x;
        }

        if( position_.y < des_position_.y )
        {
            position_.y += sin(alpha)*enemyUnits_[i]->getSpeed()*deltaTime;

            if( position_.y > des_position_.y )
            {
              position_.y = des_position_.y;
            }
        }

        if( position_.y > des_position_.y )
        {
            position_.y += sin(alpha)*enemyUnits_[i]->getSpeed()*deltaTime;
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
            position_.y += sin(alpha)*enemyUnits_[i]->getSpeed()*deltaTime;

            if( position_.y > des_position_.y )
            {
              position_.y = des_position_.y;
            }
        }

        if( position_.y > des_position_.y )
        {
            position_.y += sin(alpha)*enemyUnits_[i]->getSpeed()*deltaTime;
            if( position_.y < des_position_.y )
            {
              position_.y = des_position_.y;
            }
        }
    }
    enemyUnits_[i]->getAnimatedSprite().setPosition(position_.x, position_.y); //update the final position
  }
}
void Enemy::passPlayerBuildings(std::vector<std::shared_ptr<Building>>* playerBuildings)
{
  playerBuildings_ = playerBuildings;
}

void buildBarracks(Map* map){

}

void buildFactory(Map* map){

}

bool Enemy::isBaseDestroyed()
{
  if(!enemyBuildings_.empty())
  {
    if(enemyBuildings_[0]->getType() == Mainbuilding)
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

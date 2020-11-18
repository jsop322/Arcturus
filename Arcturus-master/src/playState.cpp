#include <string>
#include "playState.hpp"


PlayState::PlayState(std::string mapName, sf::Texture* mapTexture, sf::Texture* unitTexture, sf::Texture* buildingTexture,
  Animation* soldierWalking, Animation* soldierShooting, Animation* workerWalking, Animation* workerAct, Animation* tankDriving, Animation* tankShooting, Animation* mainBuilding,
  Animation* unitBuilding, Animation* factoryBuilding, Animation* resourceBuilding, Animation* esoldierWalking, Animation* esoldierShooting, Animation* eworkerWalking, Animation* eworkerAct, Animation* etankDriving,
  Animation* etankShooting, Animation* emainBuilding, Animation* eunitBuilding, Animation* efactoryBuilding)
{
  //std::string mapName = "50 exampleMap";
  std::vector<sf::Vector2f> startingLocation = map.buildMap(mapName, mapTexture); //Creates the map object. Should pass some map name previously chosen. Hardcoded for testing only!
  UI_ = std::make_shared<PlayUI>();
  viewMoved_ = true;
  player.setTextures(soldierWalking, soldierShooting, workerWalking, workerAct, tankDriving, tankShooting, mainBuilding, unitBuilding, factoryBuilding, resourceBuilding);
  enemy.setTextures(esoldierWalking, esoldierShooting, eworkerWalking, eworkerAct, etankDriving, etankShooting, emainBuilding, eunitBuilding, efactoryBuilding);
  player.makeStartingBase(startingLocation[0].x, startingLocation[0].y, &map);
  enemy.makeStartingBase(startingLocation[1].x, startingLocation[1].y, &map);
  player.passEnemyUnits(enemy.getUnits());
  player.passEnemyBuildings(enemy.getBuildings());
  enemy.passPlayerUnits(player.getUnits());
  enemy.passPlayerBuildings(player.getBuildings());
}
/*
** Sets the game on pause.
** Might be used just to set game time. Should concider using proper pauseState.
*/
void PlayState::pause()
{
  std::cout << "PELI PIIP!" << std::endl;
}

/*
** Resumes the game.
** Might be used just to set game time. Should concider using proper pauseState.
*/
void PlayState::resume()
{
  std::cout << "JATKUU!" << std::endl;
}

/*
** Handles user input in the game. Calls appropriate classes according to input.
*/
void PlayState::handleEvents(GameEngine &game, sf::Event event)
{
  if (event.type == sf::Event::Closed)
      game.quit();
  if(event.type == sf::Event::KeyReleased)
  {
      if (event.key.code == sf::Keyboard::Escape)
          game.previousState();

      /* // DEV H4X SHOULD BE DISABLED
      if (event.key.code == sf::Keyboard::F)
      {
          player.spawnUnit();
      }
      if (event.key.code == sf::Keyboard::E)
      {
          enemy.spawnUnit();
      }
      */
  }
  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(*game.getWindow()).y <= 600)
  {
    player.selectUnitsAndBuildings(convertPos(game, sf::Mouse::getPosition(*game.getWindow())));
  }

  //user inputs right click
  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right && sf::Mouse::getPosition(*game.getWindow()).y <= 600)
  {
    int resource = map.checkIfResource(convertPos(game, sf::Mouse::getPosition()));
    if( player.getSelectedUnits().size() == 1 &&  player.getSelectedUnits()[0]->getType() == Worker && resource != 0 ){     //Inside this loop is the functionality for gathering a resource
      if(abs(static_cast<int>(convertPos(game, sf::Mouse::getPosition()).x/32) - static_cast<int>(player.getSelectedUnits()[0]->getPosition().x/32)) <= 1 && abs(static_cast<int>(convertPos(game, sf::Mouse::getPosition()).y/32) - static_cast<int>(player.getSelectedUnits()[0]->getPosition().y/32)) <= 1){
        if(player.getSelectedUnits()[0]->getAvailability()){
          float amount;
          if(resource == 1){
            int capab = player.getSelectedUnits()[0]->getCapability(1);
            amount = map.getResource(convertPos(game, sf::Mouse::getPosition()), capab);
          }
          if(resource == 2){
            amount = map.getResource(convertPos(game, sf::Mouse::getPosition()), player.getSelectedUnits()[0]->getCapability(2));
          }
          player.getSelectedUnits()[0]->gatherResource(amount, resource, convertPos(game, sf::Mouse::getPosition()));
          float dx = convertPos(game, sf::Mouse::getPosition()).x - player.getSelectedUnits()[0]->getPosition().x;
          float dy = convertPos(game, sf::Mouse::getPosition()).y - player.getSelectedUnits()[0]->getPosition().y;
          float rotation = ( atan2 (dy,dx) + (3*3.14)/2 )*180/3.14;
          player.getSelectedUnits()[0]->getAnimatedSprite().setRotation(rotation);
        }
      }
    }
    else if ( !player.getSelectedUnits().empty() )
    {
      bool isAttacking = player.attackCmd(convertPos(game, sf::Mouse::getPosition(*game.getWindow())));
      if (isAttacking == false)
      {
        player.posCmd(convertPos(game, sf::Mouse::getPosition(*game.getWindow())), &map);  // Moving of unit
      }
    }
  }
  handleViewEvents(game, event);                                                            // This handles events of moving the view
  eventType type = (*UI_).handleEvents(game, event);
  switch(type)
  {
    case deleteUnit:
      player.removeUnit(&map);
      break;

    case emptyEvent:
      break;

    case produceUnit:
      player.startUnitProduction();
      break;

    case attack:
      break;

    case levelUp:
      player.upgradeBuilding();
      break;

    case buildBarracks:
      player.buildBarracks(&map);
      break;

    case buildFactory:
      player.buildFactory(&map);
      break;

    case buildResourcebuilding:
      // komennot tänne resurssiputkan kyhäämiSEKSI!
      player.buildThreeDprinter(&map);
      break;

    case deleteBuilding:
      player.removeBuilding();
      break;
  }
}

/*
** Updates game logic/state/map? TODO: Write description for update function
*/
void PlayState::update(GameEngine &game, float &deltaTime)
{

  //update the player class
  map.updateResources();
  player.update(deltaTime,  &map);
  enemy.update(deltaTime,  &map);

  if(enemy.isBaseDestroyed())
    {
      game.nextState(std::make_shared<EndState>(true));
    }

  if(player.isBaseDestroyed())
    {
      game.nextState(std::make_shared<EndState>(false));
    }
}


/*
** Calls UI/Map class to draw game view.
*/
void PlayState::draw(GameEngine &game)
{
  game.getWindow()->clear();
  map.draw(game);
  //buildings.draw(); OR player.drawBuildings();
  //units.draw(); OR player.drawUnits();
   // OR player.drawUnits();
  enemy.draw(game);
  player.draw(game);                                                                                 // First draw map, units buildings etc. to default view

  sf::View minimap(sf::FloatRect(1.f, 1.f, map.getMapSize().x*32, map.getMapSize().y*32));            // Sets the minimap view as whole map
  minimap.setViewport(sf::FloatRect(0.0125, 0.7375, 0.25, 0.25));                                     // Defines the position 10&110px and size 200*200px relative to source view
  game.getWindow()->setView(minimap);
  map.draw(game);
  //buildings.draw(); OR player.drawBuildings();
  //units.draw(); OR player.drawUnits();
   // OR player.drawUnits();
  enemy.draw(game);
  player.draw(game);
  sf::View UIview;                                                                                    // Then create new view for UI
  UIview.reset(sf::FloatRect(1.f, 1.f, 800.f, 800.f));
  game.getWindow()->setView(UIview);

  if( !player.getSelectedUnits().empty() ){
    (*UI_).draw(game, player.getSelectedUnits(), player.currentResources());
  }
  else if( !player.getSelectedBuilding().empty()){
    (*UI_).draw(game, player.getSelectedBuilding(), player.currentResources());
  }
  else{
    (*UI_).draw(game, player.currentResources());
  }
  game.getWindow()->display();
}
/*
Handles the events of moving the view (map in the window)
*/
void PlayState::handleViewEvents(GameEngine &game, sf::Event event)
{
  if(game.getView()->getCenter().x < 400){                                                  // These four if statements make sure the view is not moved outside the map
    game.getView()->move(1, 0);
  }
  if(game.getView()->getCenter().y < 400){
    game.getView()->move(0, 1);
  }
  if(game.getView()->getCenter().x > map.getMapSize().x*32-400)
  {
    game.getView()->move(-1, 0);
  }
  if(game.getView()->getCenter().y > (map.getMapSize().y*32 -168)){
    game.getView()->move(0, -1);
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)){                                       // Moving the view with middlemouse pressed
    if(viewMoved_ == true){
      mousepos_ = sf::Mouse::getPosition(*game.getWindow());
      viewMoved_ = false;
    }
    if (event.type == sf::Event::MouseMoved){
      sf::Vector2i mousepos2 = sf::Mouse::getPosition(*game.getWindow());
      if(game.getView()->getCenter().x >= 400 && game.getView()->getCenter().y >= 400       // If the view is inside the map, it is moved according to mouse position
        && game.getView()->getCenter().x <= (map.getMapSize().x*32 - 400) && game.getView()->getCenter().y <= (map.getMapSize().y*32 -168)){
        game.getView()->move(mousepos_.x-mousepos2.x, mousepos_.y-mousepos2.y);
      }
      mousepos_ = sf::Mouse::getPosition(*game.getWindow());
    }
  }
  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Middle){
    viewMoved_ = true;
  }
  if(event.type == sf::Event::KeyReleased)
  {
    if (event.key.code == sf::Keyboard::Space){
      sf::Vector2f defaultLocation = map.getStartLocation();
      std::cout << "default: " << defaultLocation.x << "  " << defaultLocation.y << std::endl;
      if(defaultLocation.x*32 < 400) { defaultLocation.x = 0; }
      if(defaultLocation.x*32 > (map.getMapSize().x*32-400)) { defaultLocation.x = (map.getMapSize().x*32-800); }
      if(defaultLocation.y*32 < 400) { defaultLocation.y = 0; }
      if(defaultLocation.y*32 > (map.getMapSize().y*32-400)) { defaultLocation.y = (map.getMapSize().y*32-800); }
      game.getView()->reset(sf::FloatRect(defaultLocation.x, defaultLocation.y, 800.f, 800.f));                     // This position should be changed according to where the default location of map is, base building maybe
    }
  }
}

/*
A function to convert window mouse position to actual position on map.
*/
sf::Vector2f PlayState::convertPos(GameEngine &game, sf::Vector2i inputPos){
  if (inputPos.y > 600){
    inputPos.y = 600;
  }
  sf::Vector2f viewMidpos = game.getView()->getCenter();                                  // Conversion from window/view coordinates to actual map coordinates
  sf::Vector2f viewsize = game.getView()->getSize();
  sf::Vector2f viewpos(viewMidpos.x-viewsize.x/2, viewMidpos.y-viewsize.y/2);
  sf::Vector2i mousepos = sf::Mouse::getPosition(*game.getWindow());
  sf::Vector2f mouseposf(mousepos.x, mousepos.y);
  sf::Vector2f mapPos(viewpos.x+mouseposf.x, viewpos.y+mouseposf.y);
  if(mapPos.y >= map.getMapSize().y*32){
    mapPos.y = map.getMapSize().y*32;
  }
  return mapPos;
}

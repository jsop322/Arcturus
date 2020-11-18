#ifndef RESOURCEMNGR_H
#define RESOURCEMNGR_H
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"

class ResourceManager
{
public:

  ResourceManager()
  {
    unitTexture.loadFromFile("resources/graphics/unitTileset.png");
    enemyUnitTexture.loadFromFile("resources/graphics/enemyTileset.png");
    buildingTexture.loadFromFile("resources/graphics/buildingTileset.png");
    enemyBuildingTexture.loadFromFile("resources/graphics/enemyBuildingTileset.png");
    mapTexture.loadFromFile("resources/graphics/mapTileset.png");

    //Build the animations for each unit
    soldierWalking_.setSpriteSheet(unitTexture);
    soldierWalking_.addFrame(sf::IntRect(32, 32, 32, 32));
    soldierWalking_.addFrame(sf::IntRect(64, 32, 32, 32));
    soldierWalking_.addFrame(sf::IntRect(32, 32, 32, 32));
    soldierWalking_.addFrame(sf::IntRect(96, 32, 32, 32));

    soldierShooting_.setSpriteSheet(unitTexture);
    soldierShooting_.addFrame(sf::IntRect(128, 32, 32, 32));
    soldierShooting_.addFrame(sf::IntRect(160, 32, 32, 32));

    workerWalking_.setSpriteSheet(unitTexture);
    workerWalking_.addFrame(sf::IntRect(32, 64, 32, 32));
    workerWalking_.addFrame(sf::IntRect(64, 64, 32, 32));
    workerWalking_.addFrame(sf::IntRect(32, 64, 32, 32));
    workerWalking_.addFrame(sf::IntRect(96, 64, 32, 32));

    workerAct_.setSpriteSheet(unitTexture);
    workerAct_.addFrame(sf::IntRect(32*4, 64, 32, 32));
    workerAct_.addFrame(sf::IntRect(32*5, 64, 32, 32));
    workerAct_.addFrame(sf::IntRect(32*6, 64, 32, 32));
    workerAct_.addFrame(sf::IntRect(32*5, 64, 32, 32));
    workerAct_.addFrame(sf::IntRect(32*4, 64, 32, 32));

    tankDriving_.setSpriteSheet(unitTexture);
    tankDriving_.addFrame(sf::IntRect(32, 32*3, 32*2, 32*2));
    tankDriving_.addFrame(sf::IntRect(32*3, 32*3, 32*2, 32*2));
    tankDriving_.addFrame(sf::IntRect(32*5, 32*3, 32*2, 32*2));

    tankShooting_.setSpriteSheet(unitTexture);
    tankShooting_.addFrame(sf::IntRect(32, 32*5, 32*2, 32*2));
    tankShooting_.addFrame(sf::IntRect(32*3, 32*5, 32*2, 32*2));
    tankShooting_.addFrame(sf::IntRect(32*5, 32*5, 32*2, 32*2));
    tankShooting_.addFrame(sf::IntRect(32, 32*3, 32*2, 32*2));
    tankShooting_.addFrame(sf::IntRect(32, 32*3, 32*2, 32*2));
    tankShooting_.addFrame(sf::IntRect(32, 32*3, 32*2, 32*2));
    tankShooting_.addFrame(sf::IntRect(32, 32*3, 32*2, 32*2));

    mainBuilding_.setSpriteSheet(buildingTexture);
    mainBuilding_.addFrame(sf::IntRect(32,32,32*3,32*3));
    mainBuilding_.addFrame(sf::IntRect(4*32, 32, 32*3, 32*3));
    mainBuilding_.addFrame(sf::IntRect(7*32, 32, 32*3, 32*3));
    mainBuilding_.addFrame(sf::IntRect(4*32, 32, 32*3, 32*3));
    mainBuilding_.addFrame(sf::IntRect(32,32,32*3,32*3));

    unitBuilding_.setSpriteSheet(buildingTexture);
    unitBuilding_.addFrame(sf::IntRect(32, 32*6,32*2,32*2));
    unitBuilding_.addFrame(sf::IntRect(3*32, 32*6,32*2, 32*2));
    unitBuilding_.addFrame(sf::IntRect(5*32, 32*6,32*2, 32*2));
    unitBuilding_.addFrame(sf::IntRect(3*32, 32*6, 32*2, 32*2));
    unitBuilding_.addFrame(sf::IntRect(32, 32*6, 32*2, 32*2));

    factoryBuilding_.setSpriteSheet(buildingTexture);
    factoryBuilding_.addFrame(sf::IntRect(32, 32*4,32*3,32*2));
    factoryBuilding_.addFrame(sf::IntRect(4*32, 32*4,32*3, 32*2));
    factoryBuilding_.addFrame(sf::IntRect(7*32, 32*4,32*3, 32*2));
    factoryBuilding_.addFrame(sf::IntRect(4*32, 32*4, 32*3, 32*2));
    factoryBuilding_.addFrame(sf::IntRect(32, 32*4, 32*3, 32*2));

    resourceBuilding_.setSpriteSheet(buildingTexture);
    resourceBuilding_.addFrame(sf::IntRect(32, 32*8,32*2,32*2));
    resourceBuilding_.addFrame(sf::IntRect(32*3, 32*8,32*2,32*2));
    resourceBuilding_.addFrame(sf::IntRect(32*5, 32*8,32*2,32*2));
    resourceBuilding_.addFrame(sf::IntRect(32*7, 32*8,32*2,32*2));
    resourceBuilding_.addFrame(sf::IntRect(32*9, 32*8,32*2,32*2));

    //animations for enemy units
    esoldierWalking_.setSpriteSheet(enemyUnitTexture);
    esoldierWalking_.addFrame(sf::IntRect(32, 32, 32, 32));
    esoldierWalking_.addFrame(sf::IntRect(64, 32, 32, 32));
    esoldierWalking_.addFrame(sf::IntRect(32, 32, 32, 32));
    esoldierWalking_.addFrame(sf::IntRect(96, 32, 32, 32));

    esoldierShooting_.setSpriteSheet(enemyUnitTexture);
    esoldierShooting_.addFrame(sf::IntRect(128, 32, 32, 32));
    esoldierShooting_.addFrame(sf::IntRect(160, 32, 32, 32));

    eworkerWalking_.setSpriteSheet(enemyUnitTexture);
    eworkerWalking_.addFrame(sf::IntRect(32, 64, 32, 32));
    eworkerWalking_.addFrame(sf::IntRect(64, 64, 32, 32));
    eworkerWalking_.addFrame(sf::IntRect(32, 64, 32, 32));
    eworkerWalking_.addFrame(sf::IntRect(96, 64, 32, 32));

    eworkerAct_.setSpriteSheet(enemyUnitTexture);
    eworkerAct_.addFrame(sf::IntRect(32*4, 64, 32, 32));
    eworkerAct_.addFrame(sf::IntRect(32*5, 64, 32, 32));
    eworkerAct_.addFrame(sf::IntRect(32*6, 64, 32, 32));
    eworkerAct_.addFrame(sf::IntRect(32*5, 64, 32, 32));
    eworkerAct_.addFrame(sf::IntRect(32*4, 64, 32, 32));

    etankDriving_.setSpriteSheet(enemyUnitTexture);
    etankDriving_.addFrame(sf::IntRect(32, 32*3, 32*2, 32*2));
    etankDriving_.addFrame(sf::IntRect(32*3, 32*3, 32*2, 32*2));
    etankDriving_.addFrame(sf::IntRect(32*5, 32*3, 32*2, 32*2));

    etankShooting_.setSpriteSheet(enemyUnitTexture);
    etankShooting_.addFrame(sf::IntRect(32, 32*5, 32*2, 32*2));
    etankShooting_.addFrame(sf::IntRect(32*3, 32*5, 32*2, 32*2));
    etankShooting_.addFrame(sf::IntRect(32*5, 32*5, 32*2, 32*2));
    etankShooting_.addFrame(sf::IntRect(32, 32*3, 32*2, 32*2));
    etankShooting_.addFrame(sf::IntRect(32, 32*3, 32*2, 32*2));
    etankShooting_.addFrame(sf::IntRect(32, 32*3, 32*2, 32*2));
    etankShooting_.addFrame(sf::IntRect(32, 32*3, 32*2, 32*2));

    emainBuilding_.setSpriteSheet(enemyBuildingTexture);
    emainBuilding_.addFrame(sf::IntRect(32,32,32*3,32*3));
    emainBuilding_.addFrame(sf::IntRect(4*32, 32, 32*3, 32*3));
    emainBuilding_.addFrame(sf::IntRect(7*32, 32, 32*3, 32*3));
    emainBuilding_.addFrame(sf::IntRect(4*32, 32, 32*3, 32*3));
    emainBuilding_.addFrame(sf::IntRect(32,32,32*3,32*3));

    eunitBuilding_.setSpriteSheet(enemyBuildingTexture);
    eunitBuilding_.addFrame(sf::IntRect(32, 32*6,32*2,32*2));
    eunitBuilding_.addFrame(sf::IntRect(3*32, 32*6,32*2, 32*2));
    eunitBuilding_.addFrame(sf::IntRect(5*32, 32*6,32*2, 32*2));
    eunitBuilding_.addFrame(sf::IntRect(3*32, 32*6, 32*2, 32*2));
    eunitBuilding_.addFrame(sf::IntRect(32, 32*6, 32*2, 32*2));

    efactoryBuilding_.setSpriteSheet(enemyBuildingTexture);
    efactoryBuilding_.addFrame(sf::IntRect(32, 32*4,32*3,32*2));
    efactoryBuilding_.addFrame(sf::IntRect(4*32, 32*4,32*3, 32*2));
    efactoryBuilding_.addFrame(sf::IntRect(7*32, 32*4,32*3, 32*2));
    efactoryBuilding_.addFrame(sf::IntRect(4*32, 32*4, 32*3, 32*2));
    efactoryBuilding_.addFrame(sf::IntRect(32, 32*4, 32*3, 32*2));
  }
  void buildAnimations();
  sf::Texture* getUnitTexture() {return &unitTexture;}
  sf::Texture* getBuildingTexture() {return &buildingTexture;}
  sf::Texture* getMapTexture() {return &mapTexture;}
  Animation* getSoldierWalking() { return &soldierWalking_; }
  Animation* getSoldierShooting() { return &soldierShooting_; }
  Animation* getWorkerWalking() { return &workerWalking_; }
  Animation* getWorkerAct() { return &workerAct_; }
  Animation* getTankDriving() { return &tankDriving_; }
  Animation* getTankShooting() { return &tankShooting_; }
  Animation* getMainBuilding() { return &mainBuilding_; }
  Animation* getUnitBuilding() { return &unitBuilding_; }
  Animation* getFactoryBuilding() { return &factoryBuilding_; }
  Animation* getResourceBuilding() { return &resourceBuilding_; }
  Animation* getEnemySoldierWalking() { return &esoldierWalking_; }
  Animation* getEnemySoldierShooting() { return &esoldierShooting_; }
  Animation* getEnemyWorkerWalking() { return &eworkerWalking_; }
  Animation* getEnemyWorkerAct() { return &eworkerAct_; }
  Animation* getEnemyTankDriving() { return &etankDriving_; }
  Animation* getEnemyTankShooting() { return &etankShooting_; }
  Animation* getEnemyMainBuilding() { return &emainBuilding_; }
  Animation* getEnemyUnitBuilding() { return &eunitBuilding_; }
  Animation* getEnemyFactoryBuilding() { return &efactoryBuilding_; }

private:
  sf::Texture unitTexture;
  sf::Texture enemyUnitTexture;
  sf::Texture buildingTexture;
  sf::Texture enemyBuildingTexture;
  sf::Texture mapTexture;
  //player units
  Animation soldierWalking_;
  Animation soldierShooting_;
  Animation workerWalking_;
  Animation workerAct_;
  Animation tankDriving_;
  Animation tankShooting_;
  Animation mainBuilding_;
  Animation unitBuilding_;
  Animation factoryBuilding_;
  Animation resourceBuilding_;
  //enemy units
  Animation esoldierWalking_;
  Animation esoldierShooting_;
  Animation eworkerWalking_;
  Animation eworkerAct_;
  Animation etankDriving_;
  Animation etankShooting_;
  Animation emainBuilding_;
  Animation eunitBuilding_;
  Animation efactoryBuilding_;

};


#endif

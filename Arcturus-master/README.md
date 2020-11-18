# Arcturus

RTS is not dead...

Arcturus is a scifi themed real-time strategy game where the objective is to destroy your enemy's base. Gather resources to build different unit production facilities and overwhelm your opponent with your forces. Only single-player is supported at the moment. 

The game is influenced by classic RTS games such as Starcraft and Warcraft and plays out in the same way.

# How to play

The game is controlled by mouse. Left mouse button is for unit/building selection and right click is for issuing commands to the units (such as attacking and movement). Camera can be moved when middle mouse button is held.

You start the game with only the main base building on the map. If your main building is destroyed, you lose. By selecting the main building with a left click and clicking the worker production icon, you will get a worker unit after the main building has finished producing it. Other unit production structures work with the same principle. 

The worker unit is capable of mining minerals and building structures. Each structure and unit costs a set ammount of silver mineral so careful resource management is required. Gold mineral can be used to upgrade buildings which speeds up unit production.

To gather minerals, issue an movement command to the worker unit so that it walks next to a mineral field. Then by right clicking the mineral while the worker is still selected, the unit starts mining. Mineral fields are depleted after a while, after which the worker has to be commanded to a new mineral field.

When you have enough minerals you can build different structures. Select a worker and click one of the three building icons shown on the UI: 

* B - Barracks, cost: 150. Produces soldiers, cost: 100. Upgradable with 50 gold.
* F - Factory, cost: 250. Produces tanks, cost: 150. Upgradable with 50 gold.
* R - Resource gathering building, cost: 300. boosts your silver income (5 silver/second).

Buildings have a brief activation delay simulating the construction time before they are able to produce units.

You cannot create a new main building. Main building is the only structure where you can produce worker units, cost: 100. Upgradable with 50 gold.

You can issue attack commands by selecting an unit with a left click, and then right clicking the target. The target has to be in the unit's attack range for this to work. If you are out of range, move closer! Soldiers and tanks are ranged units, while workers can only attack at melee range.

Defend yourself against the waves of the enemy units, and when you are ready push to the enemy's base and destroy the main building to achieve victory!

# Building the game

* Best odds for success are gained with Ubuntu 16.04 using SFML 2.3.2
* Custom install of SFML 2.3.2 is a pain in the back, so school linux computers
  are suggested, since they have it installed already.
* Open the master directory in terminal and type Make run.
  It builds and runs the game.

# Credits

Coding, graphics:

* Juuso Pulkkinen
* Toni Niinivirta
* Aleksi Heikkinen
* Tommi Salmensaari

Music:

* Juuso Pulkkinen
* Torsti Wikki

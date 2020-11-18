CC= g++
CPPFLAGS= -g -Wall -std=c++11
SFML= -lsfml-window  -lsfml-system  -lsfml-graphics -lsfml-audio
SRCDIR= src
OBJDIR= obj
EXECUTABLE= Arcturus

OBJECTS= $(OBJDIR)/main.o $(OBJDIR)/gameEngine.o $(OBJDIR)/mainMenuState.o $(OBJDIR)/playState.o $(OBJDIR)/mainMenuUI.o $(OBJDIR)/tile.o
OBJECTS+= $(OBJDIR)/playUI.o $(OBJDIR)/map.o $(OBJDIR)/soldierUnit.o $(OBJDIR)/Animation.o $(OBJDIR)/AnimatedSprite.o $(OBJDIR)/player.o
OBJECTS+= $(OBJDIR)/resource.o $(OBJDIR)/aStar.o $(OBJDIR)/workerUnit.o $(OBJDIR)/building.o $(OBJDIR)/mainBuilding.o $(OBJDIR)/enemy.o
OBJECTS+= $(OBJDIR)/unitBuilding.o $(OBJDIR)/mapEditorState.o
OBJECTS+= $(OBJDIR)/factoryBuilding.o $(OBJDIR)/resourceBuilding.o $(OBJDIR)/tankUnit.o $(OBJDIR)/endState.o

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
		$(CC) $(CPPFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(SFML)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
		$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

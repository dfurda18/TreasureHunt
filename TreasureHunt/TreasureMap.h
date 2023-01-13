#pragma once
#include <windows.h>
#include<iostream>
#include <vector>
#include "DieRoller.h"
#include "InfiniteRun.h"
#pragma comment(lib, "Winmm.lib")

#define NODES_SIZE 24

/**
* The class that represents the Treasure Map game.
*/
class TreasureMap {
private:
	// Enum for the color schema
	enum Colors { DEFAULT = 1, FRAME = 10, INSTRUCTIONS = 11, TITLE = 6, SELECTED_INSTRUCTION = 176, OCEAN = 1, LAND = 6, MARKS = 8, MARKS_VISITED = 4, CURRENT_POSITION = 20, SELECTED_NEIGHBOUR = 185 };
	// Enum for the game pages.
	enum StoryPages { START_PAGE = 0, START_NODE = 1, NO_STORY = 2, TREASURE_PAGE = 3 };
	// The consolde handle.
	HANDLE hConsole;
	// The console screen buffer information.
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	// Coordinates used to paint elements through the conolse screen.
	COORD coordCur;
	// The random generator.
	DieRoller dieRoller;
	// The current selected menu item.
	int mainMenuSelection;
	// The current position in the map.
	int currentPosition;
	// The map's graph nodes.
	int nodes[NODES_SIZE][4];  // Each node has X,Y,visited,Story.
	// The map's graph edges.
	int edges[NODES_SIZE][NODES_SIZE][5];   // Each edge has Active,LevelName, difficulty, number of enemies, distance.
	// The level names.
	std::string levelNames[NODES_SIZE] = {
		"The left path.", // (0,1)
		"The right path.", // (0,2)
		"Along the east coast.", // (1,3)
		"The edge of the woods.", // (1,7)
		"Marsh Frontier.", // (1,6) (2,6)
		"Along the west coast.", // (2,4)
		"Between the forest and the marsh.", // (6,7)
		"A swampy walk.", // (6,8)
		"Into the woods.", // (7,9) (7,13)
		"On the volcano.", // (7,11)
		"Base of left horn.", // 10 (10,17)
		"Cutting the left horn.", // 11 (10,14)
		"Base of right horn.", // 12
		"Cutting the right horn.", // 13
		"Along the north coast.", // 14
		"Up the right horn.", // 15
		"Up the left horn.", // 16
		"Deep into the right horn.", // 17
		"Deep into the left horn."
	};
	// The graph's neighbour relationships.
	std::vector<int> mapNeighbours;
	// The selected next level.
	int mapSelector;
	// Lets the game know if the game is over.
	bool gameOver;
	// The current level
	InfiniteRun infinityRun;
public:
	/**
	* Class constructor. Creates a Treasure Map game.
	* @return A new instance of the TreasureMap class.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	TreasureMap();
	/**
	* Loads the game.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void Init();
	/**
	* Hides the console cursor.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void Hidecursor();
	/**
	* Shows the title page.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void ShowTitlePage();
	/**
	* Shows the main menu page.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void ShowMainMenu();
	/**
	* Renders the main menu and the current selection.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void RenderMainMenu();
	/**
	* Shows the Credits screen.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void ShowCredits();
	/**
	* Shows the controls screen.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void ShowControls();
	/**
	* Sows the Game OVer screen.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void ShowGameOver();
	/**
	* Shows the Winning screen.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void ShowWinningScreen();
	/**
	* Shows the final story page.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void ShowFinalStoryPage();
	/**
	* Starts the gameplay.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void StartGame();
	/**
	* Shows the Initial story page.
	* @param int not used.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void ShowStory(int);
	/**
	* Shows the map page.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void ShowMap();
	/**
	* Generates the level graph with edges.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void GenerateNewNodes();
	/**
	* Returns the node's X value.
	* @param node The Position of the node int he list.
	* @return The node's X value.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	int GetNodeX(int node);
	/**
	* Returns the node's Y value.
	* @param node The Position of the node int he list.
	* @return The node's Y value.
	*
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	int GetNodeY(int node);
	/**
	* Returns if the node has been visited.
	* @param node The position of the node in the list.
	* @return 1 id the node has been visited and 0 otherwise.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	int GetNodeStory(int node);
	/**
	* Adds a node to the graph.
	* @param node The position of the node.
	* @param x The x position in the map.
	* @param y the y position in the map.
	* @param visited 1 if the node has been visited and 0 otherwise.
	* @param story Lets the game know if this node is the ending node.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void SetNode(int node, int x, int y, int visited, int story);
	/**
	* Set the ending page into the specified node.
	* @param location The location of the node in the list.
	* @param page The page enum number.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void SetNodeLocation(int location, int page);
	/**
	* Draws the map in the console.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void RenderMap();
	/**
	* Gets the neighbour list of a given node.
	* @param node The node to get the Neighbours.
	* @return A vector with all the node's neighbours.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	std::vector<int> GetNeighbours(int node);
	/**
	* Sets a node's visited status value.
	* @param location The location of the node in the list.
	* @param visited The value of the node's visited status.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void SetVisited(int location, int visited);
	/**
	* Moves the player to a specific node.
	* @param from The current node.
	* @return to The destination node.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void Move(int from, int to);
	/**
	* Creates an edge betwwn two nodes in both directions.
	* @param x The first node's position.
	* @param y The second node's position.
	* @param newLevelName The x node's level name.
	* @param difficulty The x's node's diffculty.
	* @param numberEnemies The x's node's number of enemies.
	* @param distance The distance between x and y.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void CreateEdge(int x, int y, int newLevelName, int difficulty, int numberEnemies, int distance);
	/**
	* Plays a looping sound.
	* @param mp3File The file to play.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void PlaySongLoop(std::wstring mp3File);
	/**
	* Plays a sound.
	* @param mp3File The sound to play.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void PlaySong(std::wstring mp3File);
	/**
	* Stops the current soung.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void StopSong();
};


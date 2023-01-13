#pragma once
#include <windows.h>
#include<iostream>
#include <string>
#include <chrono>
#include "DieRoller.h"

/**
* This class represents an infinite running level.
*/
class InfiniteRun {
private:
	// Enum for the color schema.
	enum Colors { GREEN = 10, WHITE = 15, YELLOW = 6, BLUE = 11, RED = 4, TURTLE_COLOUR = 2, RABBIT_COLOUR = 7, BIRD_COLOUR = 13, WIN = 11 };
	// Enum for the type of enemies.
	enum Enemies { TURTLE = 1, RABBIT = 2, BIRD = 3 };
	// Enum for the enemy status
	enum EnemyStatus { ACTIVE = 1, INACTIVE = 0 };
	// The console handle.
	HANDLE hConsole;
	//The console screen buffen info.
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	// A coordinate member used to set the painting location.
	COORD coordCur;
	// The platform level array made of 13 lines.
	std::string platform[13];
	// The random generator.
	DieRoller dieRoller;
	// Lets the game know if the level is advancing or not.
	bool advancing;
	// The level speed.
	int levelSpeed;
	// The level name.
	std::string name;
	// Define the clock
	typedef std::chrono::high_resolution_clock Clock;
	// The present moment.
	int nowTime;
	// The last time it was updated.
	int lastTime;
	// The character animation speed.
	int characterAnimationSpeed;
	// The enemy array.
	int enemies[10][3] = { {0,0,0}, 
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0}
	};//[type,position,active]
	// The level difficulty.
	int difficulty;
	// The number of enemies the level has.
	int numEnemies;
	// The distance required to reach the goal.
	int levelDistance;
	// Let's the game know ift he level is completed.
	bool completed;
	// Let's the game know if the game is not paused.
	bool playing;
	// Steps before the next hole.
	int holeCounter;
	// Hole's gap
	int holeGap;
	// The hole paining status: 0 = gap, 1 = pipe
	int holeStatus;
	// number of steps for next mountain.
	int mountainCounter;
	// The mountain height.
	int mountainHeight;
	// The height currently painting the mountain. 
	int mountainStatus;
	// True if paining up and fals if paining down.
	bool paintingMountain;
	// Cloud Height.
	int cloudLevel;
	// Cloud size.
	int cloudSize;
	// Cloud status paint state.
	int cloudStatus;
	// Steps remaining to paint he next cloud.
	int cloudCounter;
	// Tells if the character is running.
	bool isRunning;
	// Keeps track of the running animation state.
	bool runningState;
	// Lets the game know if the player is jumping.
	bool isJumping;
	// The jump current height.
	int jumpHeight;
	// True if the player has reached the max height.
	int falling;
	// True if the player has reached the max height.
	bool isFalling;
	// Max jump height
	const int MAX_JUMP_HEIGHT = 3;
	// The player's remaining lives
	int lives;
	// The steps before the player can receive another damage.
	int hitLagg;
	// True if the player is dead.
	bool dead;
	// The next enemy.
	int nextEnemy;
public:
	/**
	* Creates a new instance of the InfiniteRun class.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	InfiniteRun();
	/**
	* Loads the level.
	* @param name The level's name.
	* @param difficulty The game's difficulty.
	* @param newNumEnemies The numner of enemies.
	* @param newDistance The level's distance.
	* @return A new instance of the InifniteRun class.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void Init(std::string name, int difficulty, int newNumEnemies, int newDistance);
	/**
	* Renders the infinite run screen.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void Render();
	/**
	* Hides the console cursor.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void Hidecursor();
	/**
	* Decides the next step's character to print depending on the layer.
	* @param layer The layer that requests the next character.
	* @return A string with the next character for that later.
	* 
	*  @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	std::string AddNextChar(int layer);
	/**
	* Defines the next hole's information.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void NextHole();
	/**
	* Stops the game's scrolling.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void Stop();
	/**
	* Continues the game's scrolling.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void Continue();
	/**
	* Defines the information for the next mountain.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void NextMountain();
	/**
	* Moves the mountain status one step more.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void NextMountainStatus();
	/**
	* Defines the information for the next cloud.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void NextCloud();
	/**
	* Moves the cloud's status forward one step.
	*/
	void NextCloudStatus();
	/**
	* Draws the character for te given layer.
	* @param layer The layer to draw the caracter.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void RenderCharacter(int layer);
	/**
	* Lets the game know if the level is scrolling.
	* @return True if the level is not scrolling and false otherwise.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	bool IsPaused();
	/**
	* Makes the player jump.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void Jump();
	/**
	* Moves forward the jumping state one step.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void NextJumpingState();
	/**
	* Lets the game know if the player is jumping.
	* @return True if the player is jumping. False otherwise.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	bool IsJumping();
	/**
	* Let's the game know if the player hit something that would cause damage.
	* @return True if there's no collissions and false if the player hit an enemy or fell in a pit.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	bool NoCollisions();
	/**
	* Kills the enemy and paints it dead in the hole.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void DropPlayer();
	/**
	* Does the sequence for the player when they get hit.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void FallPlayer(int);
	/**
	* Spawns a new enemy.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void SpawnEnemy();
	/**
	* Gets the next available monster sport from the array.
	* @return The next empty spot for an enemy in the enemy array.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	int GetAvailableMonster();
	/**
	* Animates the enemies.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void AnimateEnemies();
	/**
	* Paints the enemies.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void RenderEnemies();
	/**
	* Runs the sequence when the level is finished.
	*/
	void WinLevel();
	/**
	* Starts or conitnues the game and checks for input.
	*/
	bool Play();
	/**
	* The sequence that runs when the player loses all their lives.
	* 
	* @author Dario Urdapilleta
	* @version 1.0
	* @since 01-06-2022
	*/
	void GameOver();
};




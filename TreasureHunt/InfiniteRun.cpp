#include "InfiniteRun.h"

#define SPEED 800000
#define CHARACTER_SPEED 1000000
#define MAX_SPACE 110
int steps = 0;
void InfiniteRun::Init(std::string name, int difficulty, int newNumEnemies, int newDistance) {
	system("cls");
	this->difficulty = difficulty;
	this->numEnemies = newNumEnemies;
	this->levelDistance = newDistance;
	this->completed = false;
	this->name = name;
	this->dead = false;
	this->lives = 6 - this->difficulty;
	this->levelSpeed = SPEED;
	this->characterAnimationSpeed = CHARACTER_SPEED;
	this->nowTime = std::chrono::system_clock::now().time_since_epoch().count();
	this->lastTime = this->nowTime;
	this->platform[0] = "Level: " + this->name + " Lives: " + std::to_string(this->lives) + " Distance: " + std::to_string(this->levelDistance);
	this->platform[1]  = "                                                                                                              ";
	this->platform[2]  = "                                                                                                              ";
	this->platform[3]  = "                                                                                                              ";
	this->platform[4]  = "                                                                                                              ";
	this->platform[5]  = "                                                                                                              ";
	this->platform[6]  = "                                                                                                              ";
	this->platform[7]  = "                                                                                                              ";
	this->platform[8]  = "                                                                                                              ";
	this->platform[9]  = "                                                                                                              ";
	this->platform[10] = "______________________________________________________________________________________________________________";
	this->platform[11] = "                                                                                                              ";
	this->platform[12] = "                                                                                                              ";
	for (int i = 0; i < 13; i++) {
		if (i == 0)
			SetConsoleTextAttribute(this->hConsole, this->BLUE);
		else if (i < 3 && i > 0)
			SetConsoleTextAttribute(this->hConsole, this->WHITE);
		else if (i < 10 && i > 2) 
			SetConsoleTextAttribute(this->hConsole, this->YELLOW);
		else
			SetConsoleTextAttribute(this->hConsole, this->GREEN);
		this->Hidecursor();
		coordCur.X = 0;
		coordCur.Y = i;
		SetConsoleCursorPosition(this->hConsole, this->coordCur);
		std::cout << this->platform[i];
	}
	this->NextHole();
	this->NextMountain();
	this->NextCloud();
	this->nextEnemy = 0;
	this->advancing = true;
	this->isRunning = true;
	this->runningState = true;
	this->isJumping = false;
	this->isFalling = false;
	this->hitLagg = 0;
}
int InfiniteRun::GetAvailableMonster() {
	for (int i = 0; i < 10; i++) {
		if (this->enemies[i][2] == 0) {
			return i;
		}
	}
	return -1;
}
void InfiniteRun::SpawnEnemy() {
	if (this->levelDistance <= MAX_SPACE - 9) {
		return;
	}
	int enemy = dieRoller.RollDN(this->numEnemies);
	int nextIndex = this->GetAvailableMonster();

	if (nextIndex != -1 && this->advancing) {
		this->enemies[nextIndex][0] = enemy;
		this->enemies[nextIndex][1] = MAX_SPACE - 2 + dieRoller.RollDN(2);
		this->enemies[nextIndex][2] = ACTIVE;
	}
	this->nextEnemy = 20+(dieRoller.RollDN(40) / this->difficulty);
}
void InfiniteRun::AnimateEnemies() {
	for (int i = 0; i < 10; i++) {
		if (this->enemies[i][2] == ACTIVE) {
			this->enemies[i][1] -= this->enemies[i][0];
		}
		if (this->enemies[i][1] <= 0) {
			this->enemies[i][2] == INACTIVE;
		}
	}
}
void InfiniteRun::RenderEnemies() {
	for (int i = 0; i < 10; i++) {
		if (this->enemies[i][2] == ACTIVE) {
			switch (this->enemies[i][0]) {
			case TURTLE:
				coordCur.X = this->enemies[i][1]-4;
				if (coordCur.X >= 0) {
					coordCur.Y = 10;
					SetConsoleCursorPosition(this->hConsole, this->coordCur);
					SetConsoleTextAttribute(this->hConsole, this->TURTLE_COLOUR);
					std::cout << "oMM,";
				}
				else {
					this->enemies[i][2] = INACTIVE;
				}
				
				break;
			case RABBIT:
				coordCur.X = this->enemies[i][1]-3;
				if (coordCur.X >= 0) {
					if (this->enemies[i][1] % 2 == 1) {
						if ((this->enemies[i][1] / 2) % 2 == 1) {
							coordCur.Y = 10;
						}
						else {
							coordCur.Y = 9;
						}
					}
					else {
						if ((this->enemies[i][1] / 2) % 2 == 1) {
							coordCur.Y = 9;
						}
						else {
							coordCur.Y = 10;
						}
					}
					SetConsoleCursorPosition(this->hConsole, this->coordCur);
					SetConsoleTextAttribute(this->hConsole, this->RABBIT_COLOUR);
					std::cout << "o'O"; 
				}
				else {
					this->enemies[i][2] = INACTIVE;
				}
				
				break;
			case BIRD:
				coordCur.X = this->enemies[i][1]-3;
				if (coordCur.X >= 0) {
					coordCur.Y = 9;
					SetConsoleCursorPosition(this->hConsole, this->coordCur);
					SetConsoleTextAttribute(this->hConsole, this->BIRD_COLOUR);
					std::cout << ".o";
					if (this->enemies[i][1] % 2 == 1) {
						std::cout << "F";
					}
					else {
						std::cout << "=";
					}
					break;
				}
				else {
					this->enemies[i][2] = INACTIVE;
				}
				
			}
		}
	}
}
void InfiniteRun::NextHole() {
	this->holeCounter = 5+dieRoller.RollDN(100)/this->difficulty;
	this->holeGap = -1;
	this->holeStatus = 0;
}

void InfiniteRun::NextMountain() {
	this->mountainCounter = dieRoller.RollDN(30);
	this->mountainHeight= 1+dieRoller.RollDN(4);
	this->mountainStatus = 0;
	this->paintingMountain = false;
}
void InfiniteRun::NextCloud() {
	this->cloudCounter = 1+ dieRoller.RollDN(15);
	this->cloudLevel = dieRoller.RollDN(2);
	this->cloudSize = 3 + dieRoller.RollDN(7);
	this->cloudStatus = 0;
}
void InfiniteRun::NextMountainStatus() {
	if (this->mountainCounter > 0) {
		this->mountainCounter--;
	}
	else {
		if (this->mountainCounter < 0) {
			this->mountainCounter = 0;
		}
		else {
			if (this->paintingMountain && this->mountainStatus == 0) {
				this->NextMountain();
			}
			else {
				if (this->mountainStatus == this->mountainHeight) {
					this->mountainStatus *= -1;
					this->paintingMountain = true;
				}
				this->mountainStatus++;
			}
		}
	}
}
void InfiniteRun::NextCloudStatus() {
	if (this->cloudCounter > 0) {
		this->cloudCounter--;
	}
	else if (this->cloudCounter < 0) {
		this->cloudCounter = 0;
	}
	else if (this->cloudStatus == this->cloudSize) {
		this->NextCloud();
	}
	else {
		this->cloudStatus++;
	}
}

InfiniteRun::InfiniteRun()
{
	this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	this->csbi = { 0 };
	GetConsoleScreenBufferInfo(this->hConsole, &this->csbi);
	this->coordCur = this->csbi.dwCursorPosition;
	this->Hidecursor();
	this->advancing = false;
	
}
void InfiniteRun::Hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

std::string InfiniteRun::AddNextChar(int layer) {
	switch (layer) {
	case 1:
	case 2:
	case 3:
		if (this->cloudCounter == 0) {
			if (this->cloudLevel == layer - 1) {
				if (this->cloudStatus == 0) {
					return "(";
				}
				if (this->cloudStatus == this->cloudSize) {
					return ")";
				}
				return "_";
			}
			if (this->cloudLevel == layer) {
				if (this->cloudStatus > 0 && this->cloudStatus < this->cloudSize) {
					return "_";
				}
			}
		}
		return " ";
		break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		if (this->levelDistance == MAX_SPACE - 9) {
			return "#";
		}
		if (this->mountainCounter == 0) {
			if (this->mountainStatus == -1 * (layer - 9) && this->mountainStatus < this->mountainHeight) {
				if (this->paintingMountain) {
					return "\\";
				}
				else {
					return "/";
				}
			}
			if (this->mountainStatus == -1 * (layer - 9) && this->mountainStatus == this->mountainHeight) {
				return "_";
			}
			if (this->mountainStatus == (layer - 9)) {
				return "\\";
			}
		}
		return " ";
		break;
	case 10:
		if (this->levelDistance <= MAX_SPACE - 9) {
			return "_";
		}
		if (this->holeCounter <= 0){
			if (this->holeGap > 0) {
				this->holeStatus = 0;
				this->holeGap--;
				return " ";
				
			}
			else if (this->holeGap == 0) {
				this->NextHole();
				this->holeStatus = 1;
				return ".";
			}
			else {
				this->holeGap = dieRoller.RollDN(4);
				this->holeStatus = 1;
				return ".";
			}
		} else  {
			this->holeStatus = 0;
			return "_";
		}
		break;
	case 11:
	case 12:
		if (this->levelDistance <= MAX_SPACE - 9) {
			return " ";
		}
		switch (this->holeStatus) {
		case 1:
			return "|";
			break;
		case 0:
			return " ";
			break;
		default:
			return " ";
			break;
		}
		break;
	default:
		return " ";
		break;
	}
	
}
void InfiniteRun::Stop() {
	this->advancing = false;
}
void InfiniteRun::Continue() {
	this->advancing = true;
}
void InfiniteRun::Jump() {
	this->isRunning = false;
	this->isJumping = true;
	this->jumpHeight = 0;
	this->falling = false;
}
void InfiniteRun::RenderCharacter(int layer) {
	if (this->completed && this->levelDistance <= -6) {
		coordCur.X = 6;
		coordCur.Y = layer;
		SetConsoleCursorPosition(this->hConsole, this->coordCur);
		switch (layer) {
		case 8:
			std::cout << " o/ ";
			break;
		case 9:
			std::cout << "/|";
			break;
		case 10:
			std::cout << "/ \\";
			break;
		default:
			break;
		}
		return;
	}
	if (this->isRunning) {
		coordCur.X = 6;
		coordCur.Y = layer;
		SetConsoleCursorPosition(this->hConsole, this->coordCur);
		switch (layer) {
		case 8:
			std::cout << " o";
			break;
		case 9:
			if (this->runningState) {
				std::cout << "<L";
			}
			else {
				std::cout << "/V";
			}
			break;
		case 10:
			if (this->runningState) {
				std::cout << "/>";
			}
			else {
				std::cout << "/\\";
			}
			break;
		default:
			break;
		}
		return;
	}
	if (this->isJumping) {
		coordCur.X = 6;
		coordCur.Y = layer;
		SetConsoleCursorPosition(this->hConsole, this->coordCur);
		switch (layer) {
		case 5:
			switch (this->jumpHeight) {
			case 3:
				if (this->falling) {
					std::cout << " o";
				}
				else {
					std::cout << "\\o/";
				}
				break;
			default:
				break;
			}
			break;
		case 6:
			switch (this->jumpHeight) {
			case 2:
				if (this->falling) {
					std::cout << " o";
				}
				else {
					std::cout << "\\o/";
				}
				break;
			case 3:
				if (this->falling) {
					std::cout << "/|\\";
				}
				else {
					std::cout << " |";
				}
				break;
			default:
				break;
			}
			break;
		case 7:
			switch (this->jumpHeight) {
			case 1:
				if (this->falling) {
					std::cout << " o";
				}
				else {
					std::cout << "\\o/";
				}
				break;
			case 2:
				if (this->falling) {
					std::cout << "/|\\";
				}
				else {
					std::cout << " |";
				}
				break;
			case 3:
				if (this->falling) {
					std::cout << "< >";
				}
				else {
					std::cout << "//";
				}
				break;
			default:
				break;
			}
			break;
		case 8:
			switch (this->jumpHeight) {
			case 1:
				if (this->falling) {
					std::cout << "/|\\";
				}
				else {
					std::cout << " |";
				}
				break;
			case 2:
				if (this->falling) {
					std::cout << "< >";
				}
				else {
					std::cout << "//";
				}
				break;
			default:
				break;
			}
			break;
		case 9:
			switch (this->jumpHeight) {
			case 0:
				std::cout << "_o";
				break;
			case 1:
				if (this->falling) {
					std::cout << "< >";
				}
				else {
					std::cout << "//";
				}
				break;
			default:
				break;
			}
			break;
		case 10:
			switch (this->jumpHeight) {
			case 0:
				std::cout << "<>";
				break;
			}
			break;
		default:
			break;
		}
		return;
	}
}
void InfiniteRun::NextJumpingState() {
	if (this->falling) {
		if (this->jumpHeight <= 0) {
			this->isJumping = false;
			this->isRunning = true;
		}
		else {
			this->jumpHeight--;
		}
	}
	else {
		if (this->jumpHeight == this->MAX_JUMP_HEIGHT) {
			this->falling = true;
		}
		else {
			this->jumpHeight++;
		}
	}
}
bool InfiniteRun::NoCollisions() {
	// Detect Floor;
	if (this->isRunning || (this->isJumping && this->jumpHeight == 0)) {
		if (this->platform[10][5] == ' ' || this->platform[10][6] == ' ') {
			this->isRunning = false;
			this->Stop();
			this->DropPlayer();
			return false;
		}
	}
	// Detect Enemies
	int enemyPosition;
	if (this->hitLagg <= 0) {
		for (int i = 0; i < 10; i++) {
			if (this->enemies[i][2] == ACTIVE) {
				enemyPosition = this->enemies[i][1];
				switch (this->enemies[i][0]) {
				case TURTLE: // oMM,
					if (this->isRunning || (this->isJumping && this->jumpHeight == 0)) {
						if (enemyPosition >= 7 && enemyPosition <= 11) {
							this->FallPlayer(0);
							return false;
						}
					}
					break;
				case RABBIT: // o´O
					if (enemyPosition >= 7 && enemyPosition <= 10) {
						if (this->isRunning) {
							this->FallPlayer(0);
							return false;
						}
						else if (this->isJumping) {
							if (this->jumpHeight < (2 - ((this->enemies[i][1] + 1) % 2))) {
								this->FallPlayer(this->jumpHeight);
								return false;
							}
						}
					}
					break;
				case BIRD: //.oF
					if (enemyPosition >= 7 && enemyPosition <= 10) {
						if (this->isRunning) {
							this->FallPlayer(0);
							return false;
						}
						if (this->isJumping && this->jumpHeight < 2) {
							this->FallPlayer(this->jumpHeight);
							return false;
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}
	
	return true;
}
void InfiniteRun::FallPlayer(int height) {
	if (this->lives > 1) {
		this->hitLagg = 5;
		this->lives--;
	}
	else {
		this->dead = true;
		this->lives--;
		coordCur.X = 0;
		coordCur.Y = 0;
		SetConsoleTextAttribute(this->hConsole, this->BLUE);
		SetConsoleCursorPosition(this->hConsole, this->coordCur);
		std::cout << "Level: " + this->name + " Lives: " + std::to_string(this->lives);
		this->isRunning = false;
		this->isFalling = true;
		SetConsoleTextAttribute(this->hConsole, this->RED);
		coordCur.X = 7;
		coordCur.Y = 10 + height;
		SetConsoleCursorPosition(this->hConsole, this->coordCur);
		if (height == 0) {
			std::cout << "L_o_";
			this->isFalling = false;
			this->Stop();
		}
		else {
			std::cout << ">-/o";
		}
		this->GameOver();
		
	}
	
	
}
void InfiniteRun::DropPlayer() {
	this->dead = true;
	SetConsoleTextAttribute(this->hConsole, this->RED);
	coordCur.X = 6;
	coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "  ";
	coordCur.X = 6;
	coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "  ";
	coordCur.X = 6;
	coordCur.Y = 10;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "\\o/";
	coordCur.X = 6;
	coordCur.Y = 11;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << " |";
	coordCur.X = 6;
	coordCur.Y = 12;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "/ \\";
	this->GameOver();
}
void InfiniteRun::Render()
{
	this->nowTime = std::chrono::system_clock::now().time_since_epoch().count();
	int deltaTime = this->nowTime - this->lastTime;
	if (this->levelDistance < 0) {
		this->completed = true;
	}
	if (this->advancing) {
		if (deltaTime > this->levelSpeed) {
			this->Hidecursor();
			coordCur.X = 0;
			coordCur.Y = 0;
			SetConsoleTextAttribute(this->hConsole, this->BLUE);
			SetConsoleCursorPosition(this->hConsole, this->coordCur);
			int dist = 0;
			if (this->levelDistance > 0) {
				dist = this->levelDistance;
			}
			std::cout << "Level: " + this->name + " Lives: " + std::to_string(this->lives) + " Distance: " + std::to_string(dist) + "         ";
			for (int i = 1; i < 13; i++) {

				this->platform[i].erase(0, 1);
				this->platform[i] = this->platform[i] + this->AddNextChar(i);
				if (i == 0)
					SetConsoleTextAttribute(this->hConsole, this->BLUE);
				else if (i < 4 && i > 0)
					SetConsoleTextAttribute(this->hConsole, this->WHITE);
				else if (i < 10 && i > 3)
					SetConsoleTextAttribute(this->hConsole, this->YELLOW);
				else
					SetConsoleTextAttribute(this->hConsole, this->GREEN);
				coordCur.X = 0;
				coordCur.Y = i;
				SetConsoleCursorPosition(this->hConsole, this->coordCur);
				std::cout << this->platform[i];
			}
			this->holeCounter--;
			this->levelDistance--;
			this->NextMountainStatus();
			this->NextCloudStatus();

		}
	}
	if (this->advancing) {
		if (deltaTime > this->levelSpeed) {
			if (this->nextEnemy <= 0) {
				this->SpawnEnemy();
			}
			else {
				this->nextEnemy--;
			}
			this->AnimateEnemies();
			this->RenderEnemies();
		}
	}
	if (this->advancing) {
		if (deltaTime > this->levelSpeed) {
			SetConsoleTextAttribute(this->hConsole, this->RED);
			if (this->levelDistance <= -6) {
				for (int i = 1; i < 13; i++) {
					this->RenderCharacter(i);
				}
				this->Stop();
				this->WinLevel();
			}
			else {
				
				if (this->hitLagg > 0) {
					this->hitLagg--;
				}
				if (this->isFalling) {
					this->FallPlayer(this->jumpHeight);
				}
				else {
					if (this->NoCollisions()) {
						for (int i = 1; i < 13; i++) {
							this->RenderCharacter(i);
						}
						if (this->runningState) {
							this->runningState = false;
						}
						else {
							this->runningState = true;
						}
						if (this->isJumping) {
							this->NextJumpingState();
						}
					}
				}
			}
		}
	}
	if (deltaTime > this->levelSpeed) {
		this->lastTime = this->nowTime;
	}
}
bool InfiniteRun::IsPaused() {
	return !this->advancing;
}
bool InfiniteRun::IsJumping() {
	return this->isJumping;
}
void InfiniteRun::GameOver(){
	coordCur.X = 25;
	coordCur.Y = 2;
	SetConsoleTextAttribute(this->hConsole, this->WIN);
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "##########################################################";
	coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#    ______                        ____                  #";
	coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#   / ____/___ _____ ___  ___     / __ \\_   _____  _____ #";
	coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#  / / __/ __ `/ __ `__ \\/ _ \\   / / / / | / / _ \\/ ___/ #";
	coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "# / /_/ / /_/ / / / / / /  __/  / /_/ /| |/ /  __/ /     #";
	coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "# \\____/\\__,_/_/ /_/ /_/\\___/   \\____/ |___/\\___/_/      #";
	coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                        #";
	coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#               Press enter to continue.                 #";
	coordCur.Y = 10;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                        #";
	coordCur.Y = 11;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "##########################################################";
}
void InfiniteRun::WinLevel() {
	coordCur.X = 20;
	coordCur.Y = 1;
	SetConsoleTextAttribute(this->hConsole, this->WIN);
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "##################################################################################";
	coordCur.Y = 2;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#    ______                             __        __      __  _                  #";
	coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#   / ____/___  ____  ____ __________ _/ /___  __/ /___ _/ /_(_)___  ____  _____ #";
	coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#  / /   / __ \\/ __ \\/ __ `/ ___/ __ `/ __/ / / / / __ `/ __/ / __ \\/ __ \\/ ___/ #";
	coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "# / /___/ /_/ / / / / /_/ / /  / /_/ / /_/ /_/ / / /_/ / /_/ / /_/ / / / (__  )  #";
	coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "# \\____/\\____/_/ /_/\\__, /_/   \\__,_/\\__/\\__,_/_/\\__,_/\\__/_/\\____/_/ /_/____/   #";
	coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                 /____/                                                         #";
	coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                #";
	coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                         Press enter to continue.                               #";
	coordCur.Y = 10;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                #";
	coordCur.Y = 11;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "##################################################################################";
}
bool InfiniteRun::Play() {
	this->playing = true;
	while (playing) {
		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{
			if (!this->completed && !this->dead) {
				if (this->IsPaused()) {
					this->Continue();
				}
				else {
					this->Stop();
				}
			}
		}
		if (GetKeyState(VK_SPACE) & 0x8000 || GetKeyState(VK_UP) & 0x8000)
		{
			if (!this->IsJumping()) {
				this->Jump();
			}

		}
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			if (this->completed || this->dead) {
				this->playing = false;
			}
		}
		this->Render();


	}
	return this->completed;
}

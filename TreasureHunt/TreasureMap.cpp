#include "TreasureMap.h"

TreasureMap::TreasureMap()
{
	this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	this->csbi = { 0 };
	GetConsoleScreenBufferInfo(this->hConsole, &this->csbi);
	this->coordCur = this->csbi.dwCursorPosition;
	this->Hidecursor();
	
}
void TreasureMap::Init() {
	this->mainMenuSelection = 0;
	this->currentPosition = 0;
	this->GenerateNewNodes();
	this->gameOver = false;
}
void TreasureMap::Hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void TreasureMap::PlaySongLoop(std::wstring mp3File) {
	std::wstring concatted_string = L"open \"" + mp3File + L"\" type mpegvideo alias mp3";
	LPCWSTR file = concatted_string.c_str();
	mciSendString(file, NULL, 0, NULL);
	mciSendString(L"play mp3 repeat", NULL, 0, NULL);
}
void TreasureMap::PlaySong(std::wstring mp3File) {
	std::wstring concatted_string = L"open \"" + mp3File + L"\" type mpegvideo alias mp3";
	LPCWSTR file = concatted_string.c_str();
	mciSendString(file, NULL, 0, NULL);
	mciSendString(L"play mp3", NULL, 0, NULL);
}
void TreasureMap::StopSong() {
	mciSendString(L"stop mp3", NULL, 0, NULL);
	mciSendString(L"close mp3", NULL, 0, NULL);
}
void TreasureMap::ShowTitlePage() {
	this->PlaySong(L"bgMusic.mp3");
	system("cls");
	this->Init();
	bool notDone = true;
	this->coordCur.X = 15;
	this->coordCur.Y = 1;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->FRAME);
	std::cout << "#####################################################################################";
	this->coordCur.Y = 2;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                   #";
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                   #";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                   #";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                   #";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                   #";
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                   #";
	this->coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                   #";
	this->coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                   #";
	this->coordCur.Y = 10;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                   #";
	this->coordCur.Y = 11;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#####################################################################################";
	SetConsoleTextAttribute(this->hConsole, this->TITLE);
	this->coordCur.X = 17;
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "  ______                                        ____";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << " /_  __/_______  ____ ________  __________     / __ \\__  ______  ____  ___  _____";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "  / / / ___/ _ \\/ __ `/ ___/ / / / ___/ _ \\   / /_/ / / / / __ \\/ __ \\/ _ \\/ ___/";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << " / / / /  /  __/ /_/ (__  ) /_/ / /  /  __/  / _, _/ /_/ / / / / / / /  __/ /    ";
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "/_/ /_/   \\___/\\__,_/____/\\__,_/_/   \\___/  /_/ |_|\\__,_/_/ /_/_/ /_/\\___/_/     ";
	this->coordCur.X = 45;
	this->coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	std::cout << "Press ENTER to start.";
	while (notDone) {
		Sleep(100);
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			notDone = false;
		}
	}
	this->ShowMainMenu();
}

void TreasureMap::ShowMainMenu() {
	this->StopSong();
	system("cls");
	this->coordCur.X = 50;
	this->coordCur.Y = 1;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->FRAME);
	std::cout << "################";
	this->coordCur.Y = 2;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#              #";
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#              #";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#              #";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#              #";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#              #";
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#              #";
	this->coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "################";
	bool notDone = true;
	
	while (notDone) {
		this->RenderMainMenu();
		Sleep(100);
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			notDone = false;
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			if (this->mainMenuSelection > 0) {
				this->mainMenuSelection--;
			}
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			if (this->mainMenuSelection < 3) {
				this->mainMenuSelection++;
			}
		}
	}
	switch (this->mainMenuSelection) {
	case 0:
		this->StartGame();
		break;
	case 1:
		this->ShowControls();
		break;
	case 2:
		this->ShowCredits();
		break;
	case 3:
	default:
		SetConsoleTextAttribute(this->hConsole, this->DEFAULT);
		break;
	}
}
void TreasureMap::RenderMainMenu() {
	

	this->coordCur.X = 53;
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	if (this->mainMenuSelection == 0) {
		SetConsoleTextAttribute(this->hConsole, this->SELECTED_INSTRUCTION);
	}
	else {
		SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	}
	std::cout << "Start";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	if (this->mainMenuSelection == 1) {
		SetConsoleTextAttribute(this->hConsole, this->SELECTED_INSTRUCTION);
	}
	else {
		SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	}
	std::cout << "Controls";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	if (this->mainMenuSelection == 2) {
		SetConsoleTextAttribute(this->hConsole, this->SELECTED_INSTRUCTION);
	}
	else {
		SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	}
	std::cout << "Credits";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	if (this->mainMenuSelection == 3) {
		SetConsoleTextAttribute(this->hConsole, this->SELECTED_INSTRUCTION);
	}
	else {
		SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	}
	std::cout << "Exit";
}

void TreasureMap::ShowCredits() {
	system("cls");
	this->coordCur.X = 40;
	this->coordCur.Y = 1;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->FRAME);
	std::cout << "#############################################";
	this->coordCur.Y = 2;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#############################################";

	SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	this->coordCur.X = 43;
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "       Created and developed by";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "          Dario Urdapilleta";
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "Press ENTER to return to the main menu.";
	bool notDone = true;
	while (notDone) {
		Sleep(100);
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			notDone = false;
		}
	}
	this->ShowMainMenu();
}

void TreasureMap::ShowControls() {
	system("cls");
	this->coordCur.X = 40;
	this->coordCur.Y = 1;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->FRAME);
	std::cout << "#############################################";
	this->coordCur.Y = 2;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                           #";
	this->coordCur.Y = 10;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#############################################";

	SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	this->coordCur.X = 43;
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "Menu navigarion: Up and Down keys";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "Accept selection: ENTER key";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "Jump: SPACE key";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "Pause: ESC key";
	this->coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "Press ENTER to return to the main menu.";
	bool notDone = true;
	while (notDone) {
		Sleep(100);
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			notDone = false;
		}
	}
	this->ShowMainMenu();
}

void TreasureMap::StartGame() {
	this->ShowStory(this->START_PAGE);
}

void TreasureMap::ShowStory(int page) {
	system("cls");
	this->coordCur.X = 0;
	this->coordCur.Y = 0;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	std::cout << "After years of research, you have finally arrived to Bull's Island. Your research points that the Pirate Barbarrasta" << std::endl;
	std::cout << "hid his treassue which is said to contain the Holy Grail." << std::endl << std::endl;
	
	std::cout << "A ship you hired dropped you off to the southest end of the island, and it will pick you up in a week. You have to " << std::endl;
	std::cout << "find this treasure before then, or it will be all for nothing." << std::endl << std::endl;

	std::cout << "Press ENTER to continue." << std::endl;
	bool notDone = true;
	while (notDone) {
		Sleep(100);
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			notDone = false;
		}
	}
	this->ShowMap();
}

void TreasureMap::ShowMap() {
	this->mapNeighbours = this->GetNeighbours(this->currentPosition);
	this->mapSelector = 0;
	system("cls");
	this->coordCur.X = 0;
	this->coordCur.Y = 0;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->OCEAN);
	for (int i = 0; i < 19; i++) {
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	}
	SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	this->coordCur.X = 13;
	this->coordCur.Y = 0;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "BULL'S ISLAND";
	SetConsoleTextAttribute(this->hConsole, this->LAND);
	this->coordCur.X = 2;
	this->coordCur.Y = 2;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "___";
	this->coordCur.X = 33;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "___";
	this->coordCur.X = 1;
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "|   |";
	this->coordCur.X = 32;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "/   |";
	this->coordCur.X = 1;
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "|    \\";
	this->coordCur.X = 31;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "/    |";
	this->coordCur.X = 1;
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "|     \\";
	this->coordCur.X = 30;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "/    /";
	this->coordCur.X = 2;
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "\\     \\";
	this->coordCur.X = 14;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "__________";
	this->coordCur.X = 29;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "/    |";
	this->coordCur.X = 3;
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "|     \\___/          \\___/     |";
	this->coordCur.X = 3;
	this->coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "|                              |";
	this->coordCur.X = 4;
	this->coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "\\                            /";
	this->coordCur.X = 5;
	this->coordCur.Y = 10;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "\\                          /";
	this->coordCur.X = 6;
	this->coordCur.Y = 11;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "|                        |";
	this->coordCur.X = 7;
	this->coordCur.Y = 12;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "\\                      /";
	this->coordCur.X = 8;
	this->coordCur.Y = 13;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "\\                    /";
	this->coordCur.X = 9;
	this->coordCur.Y = 14;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "\\_                _/";
	this->coordCur.X = 11;
	this->coordCur.Y = 15;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "\\__          __/";
	this->coordCur.X = 14;
	this->coordCur.Y = 16;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "(_________)";

	/*
	"~~~~~~~~~~~~~BULL'S ISLAND~~~~~~~~~~~~";0
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";1
	"~~___~~~~~~~~~~~~~~~~~~~~~~~~~~~~___~~";2
	"~| 2 |~~~~~~~~~~~~~~~~~~~~~~~~~~/ 3 |~";3
	"~|    \~~~~~~~~~~~~~~~~~~~~~~~~/    |~";4
	"~|  1  \~~~~~~~~~~~~~~~~~~~~~~/    /~~";5
	"~~\     \~~~~~__________~~~~~/  0 |~~~";6
	"~~~|  7  \___/ 8     9  \___/     |~~~";7
	"~~~|       4                5    6|~~~";8
	"~~~~\            3               /~~~~";9
	"~~~~~\ 0               1     2  /~~~~~";10
	"~~~~~~|     9                  |~~~~~~";11
	"~~~~~~~\         7        8   /~~~~~~~";12
	"~~~~~~~~\ 5          6       /~~~~~~~~";13
	"~~~~~~~~~\_   3           4_/~~~~~~~~~";14
	"~~~~~~~~~~~\__   1    2 __/~~~~~~~~~~~";15
	"~~~~~~~~~~~~~~(____0____)~~~~~~~~~~~~~";16
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";17
	"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";18
	*/
	bool notDone = true;
	while (notDone) {
		this->RenderMap();
		Sleep(80);
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			notDone = false;
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			if (this->mapSelector == 0) {
				this->mapSelector = this->mapNeighbours.size() - 1;
			}
			else {
				this->mapSelector--;
			}
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			if (this->mapSelector == this->mapNeighbours.size() - 1) {
				this->mapSelector = 0;
			}
			else {
				this->mapSelector++;
			}
		}
	}
	this->Move(this->currentPosition, this->mapNeighbours[this->mapSelector]);
	
}
void TreasureMap::RenderMap() {
	std::string markString = "";
	for (int i = 0; i < NODES_SIZE; i++) {
		if (this->nodes[i][2] == 1) {
			SetConsoleTextAttribute(this->hConsole, this->MARKS_VISITED);
			markString = "X";
		}
		else {
			SetConsoleTextAttribute(this->hConsole, this->MARKS);
			markString = "*";
		}
		if (i == this->currentPosition) {
			SetConsoleTextAttribute(this->hConsole, this->CURRENT_POSITION);
		}
		if (this->mapNeighbours[this->mapSelector] == i) {
			SetConsoleTextAttribute(this->hConsole, this->SELECTED_NEIGHBOUR);
		}
		this->coordCur.X = this->nodes[i][0];
		this->coordCur.Y = this->nodes[i][1];
		SetConsoleCursorPosition(this->hConsole, this->coordCur);
		std::cout << markString;
	}

}
int TreasureMap::GetNodeX(int node) {
	return this->nodes[node][0];
}
int TreasureMap::GetNodeY(int node) {
	return this->nodes[node][1];
}
int TreasureMap::GetNodeStory(int node) {
	return this->nodes[node][2];
}
void TreasureMap::SetNode(int node, int x, int y, int visited, int story) {
	this->nodes[node][0] = x;
	this->nodes[node][1] = y;
	this->nodes[node][2] = visited;
	this->nodes[node][3] = story;
}
void TreasureMap::SetNodeLocation(int location, int page) {
	this->nodes[location][3] = page;
}
void TreasureMap::SetVisited(int location, int visited) {
	this->nodes[location][2] = visited;
}
void TreasureMap::GenerateNewNodes() {
	this->SetNode(0, 19, 16, 1, this->NO_STORY);
	this->SetNode(1, 17, 15, 0, this->NO_STORY);
	this->SetNode(2, 22, 15, 0, this->NO_STORY);
	this->SetNode(3, 14, 14, 0, this->NO_STORY);
	this->SetNode(4, 26, 14, 0, this->NO_STORY);
	this->SetNode(5, 10, 13, 0, this->NO_STORY);
	this->SetNode(6, 21, 13, 0, this->NO_STORY);
	this->SetNode(7, 17, 12, 0, this->NO_STORY);
	this->SetNode(8, 26, 12, 0, this->NO_STORY);
	this->SetNode(9, 12, 11, 0, this->NO_STORY);
	this->SetNode(10, 7, 10, 0, this->NO_STORY);
	this->SetNode(11, 23, 10, 0, this->NO_STORY);
	this->SetNode(12, 29, 10, 0, this->NO_STORY);
	this->SetNode(13, 17, 9, 0, this->NO_STORY);
	this->SetNode(14, 11, 8, 0, this->NO_STORY);
	this->SetNode(15, 28, 8, 0, this->NO_STORY);
	this->SetNode(16, 33, 8, 0, this->NO_STORY);
	this->SetNode(17, 6, 7, 0, this->NO_STORY);
	this->SetNode(18, 15, 7, 0, this->NO_STORY);
	this->SetNode(19, 21, 7, 0, this->NO_STORY);
	this->SetNode(20, 32, 6, 0, this->NO_STORY);
	this->SetNode(21, 4, 5, 0, this->NO_STORY);
	this->SetNode(22, 3, 3, 0, this->NO_STORY);
	this->SetNode(23, 34, 3, 0, this->NO_STORY);
	int treasureLocation = this->dieRoller.RollDN(14)+9;
	this->SetNodeLocation(treasureLocation, TREASURE_PAGE);
	// Each edge has Active,LevelName, difficulty, number of enemies, distance
	this->CreateEdge(0, 1, 0, 1, 1, 300);
	this->CreateEdge(0, 2, 1, 1, 1, 300);
	this->CreateEdge(1, 3, 2, 1, 1, 350);
	this->CreateEdge(1, 7, 3, 1, 2, 350);
	this->CreateEdge(1, 6, 4, 1, 2, 350);
	this->CreateEdge(2, 6, 4, 1, 2, 350);
	this->CreateEdge(2, 4, 5, 1, 2, 350);
	this->CreateEdge(3, 5, 2, 1, 2, 350);
	this->CreateEdge(3, 7, 3, 1, 2, 350);
	this->CreateEdge(4, 6, 4, 1, 2, 350);
	this->CreateEdge(4, 8, 1, 1, 2, 350);
	this->CreateEdge(5, 10, 2, 1, 3, 400);
	this->CreateEdge(5, 9, 3, 1, 3, 400);
	this->CreateEdge(5, 7, 3, 1, 3, 400);
	this->CreateEdge(6, 7, 6, 1, 3, 400);
	this->CreateEdge(6, 8, 7, 1, 3, 400);
	this->CreateEdge(7, 9, 8, 2, 3, 400);
	this->CreateEdge(7, 13, 8, 2, 3, 400);
	this->CreateEdge(7, 11, 9, 2, 3, 500);
	this->CreateEdge(8, 11, 9, 2, 3, 500);
	this->CreateEdge(8, 12, 1, 2, 2, 450);
	this->CreateEdge(9, 10, 3, 2, 3, 400);
	this->CreateEdge(9, 14, 3, 3, 2, 400);
	this->CreateEdge(9, 13, 8, 3, 3, 400);
	this->CreateEdge(10, 17, 10, 3, 3, 450);
	this->CreateEdge(10, 14, 11, 3, 3, 400);
	this->CreateEdge(11, 13, 9, 3, 3, 500);
	this->CreateEdge(11, 19, 9, 3, 3, 500);
	this->CreateEdge(11, 12, 9, 3, 3, 500);
	this->CreateEdge(12, 15, 13, 3, 3, 400);
	this->CreateEdge(12, 16, 12, 3, 3, 450);
	this->CreateEdge(13, 14, 3, 3, 3, 400);
	this->CreateEdge(13, 19, 3, 3, 3, 400);
	this->CreateEdge(14, 17, 10, 3, 3, 400);
	this->CreateEdge(14, 18, 14, 3, 3, 400);
	this->CreateEdge(15, 19, 14, 3, 3, 500);
	this->CreateEdge(15, 20, 15, 3, 3, 450);
	this->CreateEdge(16, 20, 15, 3, 3, 450);
	this->CreateEdge(17, 21, 16, 3, 3, 450);
	this->CreateEdge(18, 19, 14, 3, 3, 500);
	this->CreateEdge(20, 23, 17, 3, 3, 550);
	this->CreateEdge(21, 22, 18, 3, 3, 550);
	
}
void TreasureMap::CreateEdge(int x, int y, int newLevelName, int difficulty, int numberEnemies, int distance) {
	this->edges[x][y][0] = 1;
	this->edges[x][y][1] = newLevelName;
	this->edges[x][y][2] = difficulty; 
	this->edges[x][y][3] = numberEnemies; 
	this->edges[x][y][4] = distance;
	this->edges[y][x][0] = 1;
	this->edges[y][x][1] = newLevelName;
	this->edges[y][x][2] = difficulty;
	this->edges[y][x][3] = numberEnemies;
	this->edges[y][x][4] = distance;
}

std::vector<int> TreasureMap::GetNeighbours(int node) {
	std::vector<int> neighbours = {};
	for (int i = 0; i < NODES_SIZE; i++) {
		if (this->edges[node][i][0] == 1) {
			neighbours.push_back(i);
		}
	}
	return neighbours;
}
void TreasureMap::Move(int from, int to) {
	this->mapSelector = 0;
	this->currentPosition = to;
	this->SetVisited(to, 1);
	this->infinityRun.Init(this->levelNames[this->edges[from][to][1]], this->edges[from][to][2], this->edges[from][to][3], this->edges[from][to][4]);
	this->gameOver = !this->infinityRun.Play();
	if (this->gameOver) {
		this->ShowGameOver();
	}
	else {
		switch (this->nodes[this->currentPosition][3]) {
		case TREASURE_PAGE:
			this->ShowFinalStoryPage();
			break;
		case NO_STORY:
		default:
			this->ShowMap();
			break;
		}
	}
}
void TreasureMap::ShowGameOver() {
	system("cls");
	bool notDone = true;
	this->coordCur.X = 15;
	this->coordCur.Y = 1;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->FRAME);
	std::cout << "#########################################################################";
	this->coordCur.Y = 2;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                       #";
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                       #";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                       #";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                       #";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                       #";
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                       #";
	this->coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                       #";
	this->coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                       #";
	this->coordCur.Y = 10;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                       #";
	this->coordCur.Y = 11;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                       #";
	this->coordCur.Y = 12;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#########################################################################";
	SetConsoleTextAttribute(this->hConsole, this->TITLE);
	this->coordCur.X = 17;
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "          ______                        ____                ";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "         / ____/___ _____ ___  ___     / __ \\_   _____  _____";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "        / / __/ __ `/ __ `__ \\/ _ \\   / / / / | / / _ \\/ ___/";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "       / /_/ / /_/ / / / / / /  __/  / /_/ /| |/ /  __/ /    ";
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "       \\____/\\__,_/_/ /_/ /_/\\___/   \\____/ |___/\\___/_/    ";
	this->coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	std::cout << "The boat picked up your fainted body. You couldn't find the treasure.";
	this->coordCur.X = 31;
	this->coordCur.Y = 10;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "Press ENTER to return to restart the game.";
	while (notDone) {
		Sleep(100);
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			notDone = false;
		}
	}
	this->ShowTitlePage();
}

void TreasureMap::ShowWinningScreen() {
	system("cls");
	bool notDone = true;
	this->coordCur.X = 15;
	this->coordCur.Y = 1;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->FRAME);
	std::cout << "#######################################################################################";
	this->coordCur.Y = 2;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 9;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 10;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 11;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 12;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#                                                                                     #";
	this->coordCur.Y = 13;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "#######################################################################################";
	SetConsoleTextAttribute(this->hConsole, this->TITLE);
	this->coordCur.X = 17;
	this->coordCur.Y = 3;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "   ______                             __        __      __  _                  __";
	this->coordCur.Y = 4;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "  / ____/___  ____  ____ __________ _/ /___  __/ /___ _/ /_(_)___  ____  _____/ /";
	this->coordCur.Y = 5;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << " / /   / __ \\/ __ \\/ __ `/ ___/ __ `/ __/ / / / / __ `/ __/ / __ \\/ __ \\/ ___/ / ";
	this->coordCur.Y = 6;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "/ /___/ /_/ / / / / /_/ / /  / /_/ / /_/ /_/ / / /_/ / /_/ / /_/ / / / (__  )_/  ";
	this->coordCur.Y = 7;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "\\____/\\____/_/ /_/\\__, /_/   \\__,_/\\__/\\__,_/_/\\__,_/\\__/_/\\____/_/ /_/____(_)   ";
	this->coordCur.Y = 8;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "                 /____/                                                          ";
	this->coordCur.X = 47;
	this->coordCur.Y = 10;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	std::cout << "You have completed the game.";
	this->coordCur.X = 41;
	this->coordCur.Y = 11;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	std::cout << "Press ENTER to return to restart the game.";
	while (notDone) {
		Sleep(100);
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			notDone = false;
		}
	}
	this->ShowTitlePage();
}
void TreasureMap::ShowFinalStoryPage() {
	system("cls");
	this->coordCur.X = 0;
	this->coordCur.Y = 0;
	SetConsoleCursorPosition(this->hConsole, this->coordCur);
	SetConsoleTextAttribute(this->hConsole, this->INSTRUCTIONS);
	std::cout << "You dig and find the treasure hidden exactly in this spot. The treasure contains several gold coins and, of" << std::endl;
	std::cout << "course, the Holy Grail. " << std::endl << std::endl;

	std::cout << "On your way back to the south shore, you find a stream and use the Holy Grail to drink from it. You felt your body" << std::endl;
	std::cout << "as good as new, and you feel strong again. This has been a major discovery for human kind." << std::endl << std::endl;

	std::cout << "Press ENTER to continue." << std::endl;
	bool notDone = true;
	while (notDone) {
		Sleep(100);
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			notDone = false;
		}
	}
	this->ShowWinningScreen();
}
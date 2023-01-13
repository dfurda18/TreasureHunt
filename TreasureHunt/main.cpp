/*
* This project was greated for an internal Game Jam for the
* first year students at NBCC.
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef UNICODE
#define UNICODE
#endif 

#define WIN32_LEAN_AND_MEAN 
#define VC_EXTRALEAN

#include <windows.h>
#include<iostream>
#include <string>
#include "InfiniteRun.h"
#include "TreasureMap.h"

/**
* Main method that creater the game object and shows the first screen.
* 
* @author Dario Urdapilleta
* @version 1.0
* @since 01-06-2022
*/
int main()
{
	InfiniteRun infiniteRunnerStage;
	TreasureMap game;
	game.ShowTitlePage();
	system("cls");
	system("pause");
	return 0;
}
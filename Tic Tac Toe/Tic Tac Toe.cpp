// Tic Tac Toe.cpp : Defines the entry point for the console application.
//
//This program uses 2D array instead of a simple 1-9 array so extra complications are around, like pairs being used for coordinates

#include "stdafx.h"
#include <array>
#include <iostream>
#include <random>

using std::cout;
using std::cin;
using std::endl;

using  Board3x3 = std::array < std::array<char, 3>, 3>;

int currentPlayer = 1;
int lastPlayer = 2;

//used to translate choice into a pair for use in functions
std::array<std::pair<int, int>, 9> squares = { std::make_pair(0,0), std::make_pair(0,1), std::make_pair(0,2), std::make_pair(1,0), std::make_pair(1,1),
									std::make_pair(1,2), std::make_pair(2,0), std::make_pair(2,1), std::make_pair(2,2) };

//used to check validity of player choice
std::array< bool, 9> isSquareFull = {false, false, false, false, false, false, false, false, false };

std::random_device ranDev;

void displayBoard(Board3x3 & theBoard);
void makePlay(Board3x3 & theBoard, std::pair<int, int> position);
bool checkIfWon(Board3x3 & theBoard);
std::pair<bool, std::pair<int, int>> isPlayerWinning(Board3x3 & theBoard);

//pvp
/*
int main()
{
	bool gameWon = false;
	int squaresFilled = 0;
	int choice;

	std::array<std::array<char, 3>, 3> ticBoard{ '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	while (gameWon == false)
	{
		displayBoard(ticBoard);
		if (checkIfWon(ticBoard)) 
		{ 
			gameWon = true;
			break; 
		}
		if (squaresFilled == 9)
		{
			cout << "draw." << endl;
			break;
		}
		cout << "Player " << currentPlayer << ", select your square: ";
		cin >> choice;
		while ( isSquareFull[choice-1] == true)
		{
			cout << "Choose an available spot: ";
			cin >> choice;
		}
		makePlay(ticBoard, squares[choice-1]);
		++squaresFilled;
		isSquareFull[choice-1] = true;
		
	} 

	//Variable resets
	gameWon = false;
	isSquareFull.fill(false);



	char pause;
	cout << endl << endl << "enter anything to end" << endl;
	cin >> pause;

    return 0;
}
*/

//pve
int main()
{
	bool gameWon = false;
	int squaresFilled = 0;
	int choice;
	std::uniform_int_distribution<int> intDis(1, 9);

	std::array<std::array<char, 3>, 3> ticBoard{ '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	while (gameWon == false)
	{
		displayBoard(ticBoard);
		if (checkIfWon(ticBoard))
		{
			gameWon = true;
			break;
		}
		if (squaresFilled == 9)
		{
			cout << "draw." << endl;
			break;
		}
		
		if (currentPlayer == 1)
		{
			cout << "Player " << currentPlayer << ", select your square: ";
			cin >> choice;
			while (isSquareFull[choice - 1] == true)
			{
				cout << "Choose an available spot: ";
				cin >> choice;
			}
			makePlay(ticBoard, squares[choice - 1]);
			++squaresFilled;
			isSquareFull[choice - 1] = true;
		}

		if (checkIfWon(ticBoard))
		{
			gameWon = true;
			break;
		}
		if (squaresFilled == 9)
		{
			cout << "draw." << endl;
			break;
		}

		if (currentPlayer == 2)
		{
			std::pair<bool, std::pair<int, int>> winStatus = isPlayerWinning(ticBoard);
			bool breakCondition = false;
			bool notWinningPlay = true;

			if (winStatus.first)
			{
				choice = intDis(ranDev);
				while (squares[choice - 1] != winStatus.second)		//keep rolling random until the required coordinate is chosen because program structure is bothersome
				{
					choice = intDis(ranDev);
				}

				if (isSquareFull[choice - 1] == true)	//Make sure input is valid
				{
					breakCondition = true;
				}
				else
				{
					makePlay(ticBoard, squares[choice - 1]);
					++squaresFilled;
					isSquareFull[choice - 1] = true;
					notWinningPlay = false;
				}
			}

			
			if (notWinningPlay == true)
			{
				choice = intDis(ranDev);
				while (isSquareFull[choice - 1] == true)
				{
					choice = intDis(ranDev);
				}
				makePlay(ticBoard, squares[choice - 1]);
				++squaresFilled;
				isSquareFull[choice - 1] = true;
			}
		}
		

	}

	//Variable resets
	gameWon = false;
	isSquareFull.fill(false);



	char pause;
	cout << endl << endl << "enter anything to end" << endl;
	cin >> pause;

	return 0;
}


void displayBoard(Board3x3 & theBoard)
{
	system("cls");	//clears screen

	cout << endl;
	cout << "Player 1: X     -     Player 2: O" << endl << endl;
	cout << endl;
	cout << "           |           |           " << endl;
	cout << "     " << theBoard[0][0] << "     |     " << theBoard[0][1] << "     |     " << theBoard[0][2] << endl;
	cout << "           |           |           " << endl;
	cout << "------------------------------------" << endl;
	cout << "           |           |           " << endl;
	cout << "     " << theBoard[1][0] << "     |     " << theBoard[1][1] << "     |     " << theBoard[1][2] << endl;
	cout << "           |           |           " << endl;
	cout << "------------------------------------" << endl;
	cout << "           |           |           " << endl;
	cout << "     " << theBoard[2][0] << "     |     " << theBoard[2][1] << "     |     " << theBoard[2][2] << endl;
	cout << "           |           |           " << endl;
	cout << endl;
}

void makePlay(Board3x3 & theBoard, std::pair<int, int> position)	
{
	if(currentPlayer == 1)
	{
		theBoard[position.first][position.second] = 'X';
		currentPlayer = 2;
		lastPlayer = 1;
	}
	else
	{
		theBoard[position.first][position.second] = 'O';
		currentPlayer = 1;
		lastPlayer = 2;
	}
	
}

bool checkIfWon(Board3x3 & theBoard)
{
	if ((theBoard[0][0] == theBoard[0][1] && theBoard[0][0] == theBoard[0][2])
		|| (theBoard[1][0] == theBoard[1][1] && theBoard[1][0] == theBoard[1][2])
		|| (theBoard[2][0] == theBoard[2][1] && theBoard[2][0] == theBoard[2][2])
		|| (theBoard[0][0] == theBoard[1][0] && theBoard[0][0] == theBoard[2][0])
		|| (theBoard[0][1] == theBoard[1][1] && theBoard[0][1] == theBoard[2][1])
		|| (theBoard[0][2] == theBoard[1][2] && theBoard[0][2] == theBoard[2][2])
		|| (theBoard[0][0] == theBoard[1][1] && theBoard[0][0] == theBoard[2][2])
		|| (theBoard[0][2] == theBoard[1][1] && theBoard[0][2] == theBoard[2][0]))
	{
		cout << "Player " << lastPlayer << " has won!" << endl;
		return true;
	}
	else
		return false;
}


std::pair<bool, std::pair<int, int>> isPlayerWinning(Board3x3 & theBoard)	//checks all potential 3 matches, if they exist return a pair(true, coordinate of win spot)
{
	std::pair<int, int> coordinates(0, 0);
	std::pair<bool, std::pair<int, int>> result(false, coordinates);

	if (theBoard[0][0] == theBoard[0][1])
	{
		coordinates.first = 0;
		coordinates.second = 2;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][1] == theBoard[0][2])
	{
		coordinates.first = 0;
		coordinates.second = 0;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[1][0] == theBoard[1][1])
	{
		coordinates.first = 1;
		coordinates.second = 2;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[1][1] == theBoard[1][2])
	{
		coordinates.first = 1;
		coordinates.second = 0;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[2][0] == theBoard[2][1])
	{
		coordinates.first = 2;
		coordinates.second = 2;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[2][1] == theBoard[2][2])
	{
		coordinates.first = 2;
		coordinates.second = 0;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][0] == theBoard[1][0])
	{
		coordinates.first = 2;
		coordinates.second = 0;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[1][0] == theBoard[2][0])
	{
		coordinates.first = 0;
		coordinates.second = 0;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][1] == theBoard[1][1])
	{
		coordinates.first = 2;
		coordinates.second = 1;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[1][1] == theBoard[2][1])
	{
		coordinates.first = 0;
		coordinates.second = 1;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][2] == theBoard[1][2])
	{
		coordinates.first = 2;
		coordinates.second = 2;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[1][2] == theBoard[2][2])
	{
		coordinates.first = 0;
		coordinates.second = 2;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][0] == theBoard[1][1])
	{
		coordinates.first = 2;
		coordinates.second = 2;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[1][1] == theBoard[2][2])
	{
		coordinates.first = 0;
		coordinates.second = 0;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][2] == theBoard[1][1])
	{
		coordinates.first = 2;
		coordinates.second = 0;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[1][1] == theBoard[2][0])
	{
		coordinates.first = 0;
		coordinates.second = 2;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][0] == theBoard[0][2])
	{
		coordinates.first = 0;
		coordinates.second = 1;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[2][0] == theBoard[2][2])
	{
		coordinates.first = 2;
		coordinates.second = 1;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][0] == theBoard[2][0])
	{
		coordinates.first = 1;
		coordinates.second = 0;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][2] == theBoard[2][2])
	{
		coordinates.first = 1;
		coordinates.second = 2;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][0] == theBoard[2][2])
	{
		coordinates.first = 1;
		coordinates.second = 1;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	if (theBoard[0][2] == theBoard[2][0])
	{
		coordinates.first = 1;
		coordinates.second = 1;
		result.first = true;
		result.second = coordinates;
		return result;
	}
	else
	{
		return result;
	}
}


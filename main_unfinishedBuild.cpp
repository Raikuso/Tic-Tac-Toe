#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

void cou(char matrix[3][3]);
void gotoxy(int, int);

int main()
{
	char matrix[3][3];
	int m,n;
	char ch='y';
	while(ch=='Y'||ch=='y') {
		for (m=0; m<3; m++)for (n=0; n<3; n++)matrix[m][n]= '\0';
		int i,j,sum=0;
		while (7 == 7) {
			system("cls");
			cou(matrix);
			if(!(sum%2))
				ch = 'X';
			else ch = 'O';
			cout<<"Player " << sum%2+1 << " is '"<< ch <<
			    "': choose the row and column"<<endl;
			cout<<"Row : ";
			do {
				i = _getch();
				i -= 48;
			} while(i > 3 || i < 1);
			cout << i << endl;
			cout<<"Column : ";
			do {
				j = _getch();
				j -= 48;
			} while(j > 3 || j < 0);
			cout << j << endl;
			for (; ('X'==matrix[i-1][j-1]||'O'==matrix[i-1][j-1]);) {
				cout<<"Sorry boy, but you gotta choose another place.\n";
				Sleep(50);
				gotoxy(6,12);
				cout << " ";
				gotoxy(9,13);
				cout << " ";
				gotoxy(0,12);
				cout<<"Row : ";
				do {
					i = _getch();
					i -= 48;
				} while(i > 3 || i < 1);
				cout << i << endl;
				cout<<"Column : ";
				do {
					j = _getch();
					j -= 48;
				} while(j > 3 || j < 0);
				cout << j << endl;
			}
			matrix[i-1][j-1]= ch;

			cou(matrix);
			sum++;
//check if wins
			if ((matrix[0][0]== ch && matrix[0][0]==matrix[1][1]
			     && matrix[1][1]==matrix[2][2])
			    ||  (matrix[2][0]== ch && matrix[2][0]==matrix[1][1]
			         && matrix[1][1]==matrix[0][2])
			    ||  (matrix[0][0]== ch && matrix[0][0]==matrix[1][0]
			         && matrix[1][0]==matrix[2][0])
			    ||  (matrix[0][1]== ch && matrix[0][1]==matrix[1][1]
			         && matrix[1][1]==matrix[2][1])
			    ||  (matrix[0][2]== ch && matrix[0][2]==matrix[1][2]
			         && matrix[1][2]==matrix[2][2])
			    ||  (matrix[0][0]== ch && matrix[0][0]==matrix[0][1]
			         && matrix[0][1]==matrix[0][2])
			    ||  (matrix[1][0]== ch && matrix[1][0]==matrix[1][1]
			         && matrix[1][1]==matrix[1][2])
			    ||  (matrix[2][0]== ch && matrix[2][0]==matrix[2][1]
			         && matrix[2][1]==matrix[2][2])) {
				cout<< endl << endl << endl << "Player " << sum%2+1 << " wins"<< endl;
				break;
			}
			if (sum == 9) {
				cout << "The game is over and no one wins" <<
				     endl;    //sum=9 because there are only 9 boxes in the game
				break;
			}
		}
		cout<<"\nWould you like to play again??? (Y - N)\n";
		do {
			ch = _getch();
		} while(ch != 'y' && ch != 'n' && ch != 'Y' && ch != 'N');
		cout << ch;
	}
	system("PAUSE");
	return 0;
}

void cou(char matrix[3][3])
{
	gotoxy(1,1);
//the play box
	cout<<"\n\t\t                1   2   3\n" << endl;
	cout<<"\t\t             1  " << matrix[0][0] << " | " << matrix[0][1] << " | "
	    << matrix[0][2] << endl;
	cout<<"\t\t               ---|---|---\n";
	cout<<"\t\t             2  " << matrix[1][0] << " | " << matrix[1][1] << " | "
	    << matrix[1][2] << endl;
	cout<<"\t\t               ---|---|---\n";
	cout<<"\t\t             3  " << matrix[2][0] << " | " << matrix[2][1] << " | "
	    << matrix[2][2] << "\n\n\n";
}

void gotoxy(int x, int y)
{
	HANDLE hConsole;
	COORD cursorLoc;
	cursorLoc.X = x;
	cursorLoc.Y = y;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, cursorLoc);
}

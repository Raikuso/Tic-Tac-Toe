#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

void rahmen();
void textcolor(int color);
void field(char matrix[3][3]);
void gotoxy(int, int);
int winning_con(char matrix[3][3], char ch, int);
void leereSpielfeld(char matrix[3][3]);
char Spielzug(int sum, char ch, char matrix[3][3]);
void Spielrunde(char matrix[3][3], char ch);
void Spielstandzaehlerinkrementer(char ch, int sum, int spielstand[2]);
void Spielstandzaehlerausgabe(int spielstand[2]);

int main()
{
	char matrix[3][3];
	char ch='y';
	Spielrunde(matrix, ch);
	return 0;
}

void Spielrunde(char matrix[3][3], char ch)
{
	int spielstand[2] = {};
	while(ch=='Y'||ch=='y'||ch=='d'||ch=='D') {
		leereSpielfeld(matrix);
		int sum=0;
		while (sum < 9) {
			rahmen();
			Spielstandzaehlerausgabe(spielstand);
			field(matrix);
			ch = Spielzug(sum, ch, matrix);
			field(matrix);
			sum++;
			if(winning_con(matrix, ch, sum))
				break;
		}
		Spielstandzaehlerinkrementer(ch, sum, spielstand);
		gotoxy(7,21);
		cout << "Would you like to play again or delete your score? (Y - N - D): ";
		do {
			ch = _getch();
		} while(ch != 'y' && ch != 'n' && ch != 'Y' && ch != 'N' && ch != 'D'
		        && ch != 'd');
		if(ch == 'D' || ch == 'd') {
			spielstand[0] = 0;
			spielstand[1] = 0;
		}
		cout << ch;
		Sleep(74);
	}
}

void leereSpielfeld(char matrix[3][3])
{
	for (int m=0; m<3; m++)
		for (int n=0; n<3; n++)
			matrix[m][n]= '\0';
}

void field(char matrix[3][3])
{
	gotoxy(32,3);
	cout<<"1   2   3";
	gotoxy(29,5);
	cout<<"1  " << matrix[0][0] << " | " << matrix[0][1] << " | "
	    << matrix[0][2]; 
	gotoxy(31,6);
	cout<<"---|---|---";
	gotoxy(29,7);
	cout<<"2  " << matrix[1][0] << " | " << matrix[1][1] << " | "
	    << matrix[1][2];
	gotoxy(31,8);
	cout<<"---|---|---";
	gotoxy(29,9);
	cout<<"3  " << matrix[2][0] << " | " << matrix[2][1] << " | "
	    << matrix[2][2];
}

char Spielzug(int sum, char ch, char matrix[3][3])
{
	int i = 0, j = 0;
	if(!(sum%2))
		ch = 'X';
	else ch = 'O';
	do {
		gotoxy(15,12);
		cout<<"Player " << sum%2+1 << " is '"<< ch <<
		    "': choose the row and column";
		gotoxy(15,14);
		cout << "Use the keys: Q\tW  E";
		gotoxy(29,16);
		cout << "A\tS  D";
		gotoxy(29,18);
		cout << "Y\tX  C";
		gotoxy(38,14);
		cout << " or   7  8  9";
		gotoxy(42,16);
		cout << "  4  5  6";
		gotoxy(42,18);
		cout << "  1  2  3";
		gotoxy(39,16);
		do {
			i = _getch();
			if(i > 47 && i < 58)
				i -= 48;
		} while((i > 9 || i < 1) && (i != 'Q' && i != 'q' && i != 'W' && i != 'w' && i != 'E'
		                             && i != 'e' && i != 'a' && i != 'A' && i != 'S' && i != 's' && i != 'D' && i != 'd' && i != 'y'
		                             && i != 'Y' && i != 'X' && i != 'x' && i != 'C' && i != 'c' && i != 'Z' && i != 'z'));
		switch(i) {
			case 7:case 'Q':case 'q': i = 0;j = 0;continue;
			case 8:case 'W':case 'w': i = 0;j = 1;continue;
			case 9:case 'E':case 'e': i = 0;j = 2;continue;
			case 4:case 'A':case 'a': i = 1;j = 0;continue;
			case 5:case 'S':case 's': i = 1;j = 1;continue;
			case 6:case 'D':case 'd': i = 1;j = 2;continue;
			case 1:case 'Y':case 'y':case 'z':case 'Z': i = 2;j = 0;continue;
			case 2:case 'X':case 'x': i = 2;j = 1;continue;
			case 3:case 'C':case 'c': i = 2;j = 2;continue;
		};
	} while(matrix[i][j] == 'X' || matrix[i][j] == 'O');
	matrix[i][j] = ch;
	return ch;
}

int winning_con(char matrix[3][3], char ch, int sum)
{
	gotoxy(45,6);
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
		textcolor(10);
		cout <<  "Player " << --sum%2+1 << " wins";
		textcolor(7);
		return 1;
	} else if(sum == 9) {
		cout << "The game is over and no one wins"; //sum=9 because there are only 9 boxes in the game
		return 0;
	} else	return 0;
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

void Spielstandzaehlerinkrementer(char ch, int sum, int spielstand[2])
{
	if (!(sum%2) && sum != 0) {
		spielstand[0]++;
	} else if(sum != 0)spielstand[1]++;
	Spielstandzaehlerausgabe(spielstand);
}

void Spielstandzaehlerausgabe(int spielstand[2])
{
	gotoxy(10,5);
	cout << spielstand[1] << " : " << spielstand[0];
}

void rahmen()
{
	gotoxy(1, 1);
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
	     <<
	     "\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X"
	     <<
	     "\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X"
	     <<
	     "\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X"
	     <<
	     "\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X"
	     <<
	     "\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X"
	     <<
	     "\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X"
	     <<
	     "\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X\n X\t\t\t\t\t\t\t\t\t      X"
	     <<
	     "\n XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
}

void textcolor(int color)
{
	SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), color);
}


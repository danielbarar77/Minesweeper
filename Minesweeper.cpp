#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <WinBase.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <wincon.h>
#include <string.h>
 
 // definirea culoriilor folosite
#define BLACK   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
#define RED     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
#define GREEN   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
#define YELLOW  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 246);
#define BLUE    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241);
#define PURPLE  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 245);
#define CYAN    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 251);
#define ORANGE  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
#define GRAY    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248);
#define FLAG    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);
#define RESET   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

#define for_i for(int i = 0; i < DIM_Y; i++)
#define for_j for(int j = 0; j < DIM_X; j++)

int mine_number, mines_set;
char scena[50][100];						// matrice pentru afisarea scenei principale
char scena_mine[50][100];					// matrice pentru afisarea scenei ce contine minele                                                            
char score_name[4][5][100];					// matrice pentru salvarea numelui
float score_points[3][4][2] = { 0 };	    // matrice pentru salvarea punctajului si timpului
char name[100];								// string pentru introducerea numelui
int DIM_X, DIM_Y;							// dimensiunile scenei
int x, y;									// coordonatele ce se introduc
int set_the_mine;					
char s[4];									// string folost pentru introducerea pozitiei
int ok = 0;
int ok1;

void hidecursor();							// functie folosita pentru ascunderea cursorului    
void gotoXY(int x, int y);					// functie folosita pentru mutarea cursorului
void change_color(int x1, int y1);			// functie folosita pentru schimbarea culorii
void meniu(int option);						// functie folosita pentru alegerea optiunii din meniul principal
void main_scene();							// functie folosita pentru initializarea scenei principale	
void print_main_scene();					// functie folosita pentru afisarea scenei principale	
void mines_scene();							// functie folosita pentru initializare scenei ce contine minele 
void print_mines_scene();					// functie folosita pentri afisarea scenei ce contine minele (optional) 
void print_scene_after_game();              // afiseaza scena dupa incheiera jocului
void reset_map(int x, int y, int mine_number1);									// in caz ca pe prima pozitie aleasa se afla mina se genereaza o scena noua
void position_input(int option, int DIM_X, int DIM_Y, int mine_number1);		// functie folosita pentru introducerea pozitiei
int game_end(int x, int y);					// verifica daca jocul a fost pierdut
void values_print();						// functie folosita pentru schimbarea valorilor din scena cu mine in scena principala
void print_score(int mine_number1);			// afiseaza numarul de mine setate si cate au ramas
void score_input(int option, float time);   // se genereaza scorul in functie de numarul de mine setate si timp
void leaderboard();					// afiseaza scorul jcatorilor
void print_message(int option);				// afiseaza mesajul dupa incheierea jocului
void how_to_play();							// afiseaza instructiunile
bool verification(int x, int y);			// verifica daca coordonatele se afla in interiorul scenei
void reveal_free_space();					// afiseaza spatiile goale
void print_menu();							// afiseaza meniul principal
void main();								// functia principala


void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoXY(int x, int y)
{
	COORD coord = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void change_color(int x1, int y1)
{

	switch (scena_mine[y1][x1]) // in functie ce schima culoarea caracterlui si a casutei
	{
	case '*':
		BLACK
		break;
	case ' ':
		BLACK
		break;
	case '0':
		BLACK
		break;
	case '1':
		BLUE
		break;
	case '2':
		GREEN
		break;
	case '3':
		RED
		break;
	case '4':
		PURPLE
		break;
	case '5':
		ORANGE
		break;
	case '6':
		CYAN
		break;
	case '7':
		BLACK
		break;
	case '8':
		GRAY
		break;
	default:
		break;
	}
}

void meniu(int option)
{
	switch (option)			 // in functie de optiunea aleasa variaza numarul de casute si mine
	{
	case 1:
		DIM_X = 23;
		DIM_Y = 14;
		mine_number = 9;
		break;
	case 2:
		DIM_X = 41;
		DIM_Y = 14;
		mine_number = 18;
		break;
	case 3:
		DIM_X = 57;
		DIM_Y = 14;
		mine_number = 27;
		break;
	case 4:						// se genereaza o scena in functie de preferinta
		int ox, oy;
		system("cls");
		printf("\nEnter the scene size:\n");
		printf("\nDIM_X = ");
		scanf("%d", &ox);
		while (ox < 2 || ox>26)
		{
			printf("DIM_X must be in the range of [2;26]\nDIM_X = ");  
			scanf("%d", &ox);
		}
		DIM_X = ox * 2 + 5;
		printf("\nDIM_Y = ");
		scanf("%d", &oy);
		while (oy < 2 || oy>9)
		{
			printf("DIM_Y must be in the range of [2;9]\nDIM_Y = ");
			scanf("%d", &oy);
		}
		DIM_Y = oy + 5;
		printf("\nEnter the mines number: ");
		scanf("%d", &mine_number);
		while (mine_number > (((((DIM_X - 5) / 2) * (DIM_Y - 5)) / 3) * 2) || mine_number < 1)   // optiune pentru a limita numarul de mine la 3/4 din numarul de casute pentru a nu aparea erori
		{
			printf("The number of mines does not match the size of the map\n");
			printf("Enter a value in the range of [1;%d]: ", (((((DIM_X - 5) / 2) * (DIM_Y - 5)) / 3) * 2));
			scanf("%d", &mine_number);
		}
		break;
	case 5:
		leaderboard();			// afiseaza scorul 
		main();					// revine la meniul principal
		break;
	case 6:
		how_to_play();			// afiseaza instructiunile
		main();					// revine la meniul principal
		break;
	case 0:
		exit(0);				// se opreste programul
		break;
	}
}

void main_scene()
{
	int c = 97;

	for_i
		for_j
		scena[i][j] = ' ';							// se initializeaza scena cu spatiu

	for (int j = 3; j < DIM_X - 3; j++)
	{
		scena[2][j] = scena[DIM_Y - 2][j] = '-';	// se initializeaza marginile de sus si de jos ale chenarului
		if (j % 2 != 0)								// se genereaza din doua in doua pozitii pentru a avea un aspect mai placut
		{
			scena[1][j] = scena[DIM_Y - 1][j] = c;  //  se initializeaza literele de la marginea scenei
			c++;
		}
	}

	for (int i = 3; i < DIM_Y - 2; i++)
	{
		scena[i][0] = scena[i][DIM_X-1] = i + 46;	// se initializeaza cifrele de la marginea scenei
		scena[i][1] = scena[i][DIM_X-2] = '|';		//se initializeaza marginile laterale ale chenarului
	}

	for (int i = 3; i < DIM_Y - 2; i++)
		for (int j = 3; j < DIM_X - 3; j++)
			if (j % 2 != 0)
			{
				scena[i][j] = '+';					// se initializeaza casutele ascunse
			}
}

void print_main_scene()
{
	// se afiseaza scena principala
	system("cls");
	BLACK                           // se coloreaza scena
	for_i
	{
		for_j
		printf("%c",scena[i][j]);
	printf("\n");
	}
	RESET
}

void mines_scene()
{
	int c = 97;
	for_i
		for_j
		scena_mine[i][j] = ' ';
	for (int j = 3; j < DIM_X - 3; j++)
	{
		scena_mine[2][j] = scena_mine[DIM_Y - 2][j] = '-';		// se initializeaza marginile de sus si de jos ale chenarului
		if (j % 2 != 0)
		{
			scena_mine[1][j] = scena_mine[DIM_Y - 1][j] = c;	//  se initializeaza literele de la marginea scenei
			c++;
		}
	}

	for (int i = 3; i < DIM_Y - 2; i++)
	{
		scena_mine[i][0] = scena_mine[i][DIM_X - 1] = i + 46;	// se initializeaza cifrele de la marginea scenei
		scena_mine[i][1] = scena_mine[i][DIM_X - 2] = '|';		//se initializeaza marginile laterale ale chenarului
	}

	srand(time(NULL));											// genereaza valori aleatorii pentr mine

	int mine_number2 = mine_number;
	while (mine_number2)
	{
		// se genereaza pe pozitii aleatorii din interiorul scenei minele 
		int i = 0, j = 0;
		i = rand() % (DIM_Y - 5) + 3;
		j = rand() % (DIM_X/2 - 2) * 2 + 3;
		if(scena_mine[i][j] != '*' && scena[i][j] != 'F')       // minele se genereaza pe pozitii care nu contin mine si pe care nu sunt FLAG 
		{														// a doua conditie este utila pentru a nu aparea probleme la generarea unei noi scene cu mine (cand pe prima pozitie introdusa se afla mina)
			scena_mine[i][j] = '*';
			mine_number2--;
		}
	}

	int contor = 0;

	for (int i = 3; i < DIM_Y -2; i++)
		for (int j = 3; j < DIM_X -3; j+=2)
		{
			// se numara minele din jurul casutei
			contor = 0;
			if (scena_mine[i - 1][j - 2] == '*')contor++;
			if (scena_mine[i - 1][j] == '*')contor++;
			if (scena_mine[i - 1][j + 2] == '*')contor++;
			if (scena_mine[i][j - 2] == '*')contor++;
			if (scena_mine[i][j + 2] == '*')contor++;
			if (scena_mine[i + 1][j - 2] == '*')contor++;
			if (scena_mine[i + 1][j] == '*')contor++;
			if (scena_mine[i + 1][j + 2] == '*')contor++;
			if (scena_mine[i][j] != '*')
			scena_mine[i][j] = contor + 48;
		}


}

void print_mines_scene()
{
	// afiseaza scena cu mine (optional - se poate pune in comentarii in main)
	gotoXY(0, 15);
	for_i
	{
		for_j
		{
			printf("%c",scena_mine[i][j]);
		}
	printf("\n");
	}
}

void print_scene_after_game(int option)
{
	int ox;
	switch (option)  // alege coordonatele pentru a pune scena in centrul consolei
	{
	case 1:
		ox = 45;
		break;
	case 2:
		ox = 37;
		break;
	case 3:
		ox = 31;
		break;
	default:
		ox = 51 - DIM_X/3;
		break;
	}
	system("cls");
	for_i
	{
		for_j
		{
			gotoXY(j + ox, i + 5);
			if (scena[i][j] == 'F' && scena_mine[i][j] == '*')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
				printf("%c", scena[i][j]);
				RESET
			}
			else if (scena[i][j] == 'F')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64);
				printf("%c", scena[i][j]);
				RESET
			}
			else if (i > 2 && i < DIM_Y - 2 && j > 2 && j < DIM_X - 2)
			{
				change_color(j, i);
				if (scena_mine[i][j] == '0')
				{
					printf(" ");
				}
				else
				{
					printf("%c", scena_mine[i][j]);
				}
				RESET
			}
			else 
			{
				BLACK
					printf("%c",scena_mine[i][j]);
				RESET
			}
		}
		printf("\n");
	}
	gotoXY(45, 21);
	BLACK
	printf("*");
	RESET
	gotoXY(46, 21);
	printf(" - mine");
	
	gotoXY(45, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
	printf("F");
	RESET
	gotoXY(46, 23);
	printf(" - mine set correctly");

	gotoXY(45, 25);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64);
	printf("F");
	RESET
	gotoXY(46, 25);
	printf(" - mine set incorrectly");

	gotoXY(45, 28);
	printf("Press space to continue");
	while (_getch() != ' ') {}
}

void reset_map(int x, int y, int mine_number1)
{
	if (ok1 == 1 && s[0] != 'F' )							// se intra in acest IF in momentul cand se introduce prima pozitie care nu e FLAG
	{
		if (scena_mine[y][x] == '*' && scena[y][x] != 'F')  // in cazul in care pe prima pozitie introdusa se afla mina se intra in IF
		{
			do												// se genereaza noi scene pana cand pe pozitia introdusa nu se afla mina
			{
				mines_scene();   
			} while (scena_mine[y][x] == '*');
			print_mines_scene();							// se afiseaza noua scena cu mine (optional - se poate pune in comentarii in main)
			mine_number = mine_number1;
		}
	
	ok1 = 0;
	}
}

void position_input(int option, int DIM_X, int DIM_Y, int mine_number1)
{
	int ox_max, oy_max = '9';
	switch (option)  
	{
	case 1:
		ox_max = 'i';
		break;
	case 2:
		ox_max = 'r';
		break;
	case 3:
		ox_max = 'z';
		break;
	case 4:
		ox_max = DIM_X / 2 - 3;
		ox_max += 97;
		oy_max = DIM_Y - 5;
		oy_max += 48;
		break;
	}
	set_the_mine = 0;						// variabila folosita pentru a seta mina
	gotoXY(DIM_X + 3 , 5);
	printf("                                                         ");
	gotoXY(DIM_X + 3, 5);
	printf("Enter the coordinates: ");
	scanf("%s", s);							// se introduce pozitia printr-un sir de caractere
	if (s[0] == 'F')						// se verifica daca primul caracter al sirului este 'M' pentru a seta mina
	{
		set_the_mine = 1;					// in cazul in care dorim sa punem sau sa luam steagul variabila ia valoarea 1
		while (s[1] < 'a' || s[1] > ox_max || s[2] < '1' || s[2] > oy_max)	// conditie pentru ca valorile sa corespunda scenei
		{
			gotoXY(DIM_X + 3, 5);
			printf("                                                          ");
			gotoXY(DIM_X + 3, 5); 
			printf("Enter viable coordinates for the FLAG:");
			scanf("%s", s);
		}
		x = (s[1] - 97) * 2 + 3;			// se adapteaza coordonatele conform scenei
		y = s[2] - 46; 
		reset_map(x, y, mine_number1);		// functie folosita pentru a genera o scena noua in cazul in care pe prima pozitie introdusa se afla o mina
	}
	else
	{
		while (s[0] < 'a' || s[0] > ox_max || s[1] < '1' || s[1] > oy_max) // conditie pentru ca valorile sa corespunda scenei
		{
			gotoXY(DIM_X + 3, 5);
			printf("                                                          ");
			gotoXY(DIM_X + 3, 5);
			printf("Enter viable coordinates: ");
			scanf("%s", s);
		}
		x = (s[0] - 97) * 2 + 3;			// se adapteaza coordonatele conform scenei
		y = s[1] - 46;
		if (scena[y][x] == 'F')set_the_mine = 1; // in cazul in care casuta are deja steag se seteaza variabila cu 1 pentru a nu se modifica 
		reset_map(x, y, mine_number1);		// functie folosita pentru a genera o scena noua in cazul in care pe prima pozitie introdusa se afla o mina
	}
}

int game_end(int x, int y)
{
	if (set_the_mine == 1)return 0;			// in cazul in care dorim sa punem steag pe o casuta cu mina sau sau are deja steag jocul nu se termina 
	if (scena_mine[y][x] == '*')return 1;	// in cazul in care se afla o mina jocul se termina
	return 0;								// altfel jocul continua
}

void values_print()
{
	change_color(x, y);
	if (set_the_mine == 1)							// in cazul in care dorim sa punem sau sa luam stagul sau deja este steag intr-o casuta 
	{
		if (scena[y][x] == 'F' && s[0] == 'F')		// in cazul in care casuta are deja steag casuta ia valoarea '+' si minele setate scad
		{
			mines_set--;
			scena[y][x] = '+';
		}
		else if (scena[y][x] == '+' && s[0] == 'F') // in cazul in care casuta nu are steag casuta ia valoarea 'F' si minele setate cresc
		{
			mines_set++;
			scena[y][x] = 'F';
		}
		if (scena_mine[y][x] == '*' && scena[y][x] == 'F' && s[0] == 'F')		// in cazul in care casuta are o mina si casuta are deja steag casuta ia valoarea 'F' si minele ramase scad
		{
			mine_number--;
			scena[y][x] = 'F';
		}
		else if (scena_mine[y][x] == '*' && scena[y][x] == '+' && s[0] == 'F')  // in cazul in care casuta are o mina si casuta nu are steag casuta ia valoarea '+' si minele ramase scacresc
		{
			mine_number++;
			scena[y][x] = '+';
		}
		BLACK
		printf("%c", scena[y][x]);	// se afiseaza caracterul
		RESET
	}
	else
	{
		if (scena[y][x] == '+' && scena_mine[y][x] == '0')
		{
			BLACK
			reveal_free_space();	 // in cazul in care scena principala nu este afisata si in scena din spate se afla 0 se afiseaza spatiul gol
			RESET
		}
		else if (scena[y][x] == '+') // altfel se afiseaza casuta ce afiseaza numarul de mine din jurul acesteia
		{
			scena[y][x] = scena_mine[y][x];
			printf("%c", scena[y][x]);
		}
	}
}
 
void print_score(int mine_number1)
{
	RESET
	gotoXY(DIM_X + 17, 2);
	printf("     ");
	gotoXY(DIM_X + 3, 2);
	printf("Mines set: %d", mines_set);						// se afiseaza numarul de mine setate
	gotoXY(DIM_X + 3, 3);
	printf("Mines left: %d/%d", mine_number, mine_number1); // se afiseaza numarul de mine ramase din totalul minelor initiale
}

void score_input(int option, float time)  
{
	time = time / CLOCKS_PER_SEC;                                   // calculeaza timpul in secunde
	int map_mines_number;
	switch (option)													// in functie de harta , scorul se salveaza pe diferiti versori
	{
	case 1:
		map_mines_number = 9;
		strcpy(score_name[0][3], name);								// se introduce numele jucatorului in matrice
		score_points[0][3][1] = time;								// timpul si scorul se salveaza pe ultima pozitie a matricii iar apoi se ordoneaza descrescator 
		score_points[0][3][0] = map_mines_number - mine_number;		// in functie de punctaj si timp daca punctajul e egal
		for (int i = 0; i < 3; i++)
		{
			for (int j = i; j < 4; j++)
			{
				if (score_points[0][i][0] < score_points[0][j][0])  // se ordoneaza valorile
				{
					float aux = score_points[0][i][0];
					score_points[0][i][0] = score_points[0][j][0];
					score_points[0][j][0] = aux;
					aux = score_points[0][i][1];
					score_points[0][i][1] = score_points[0][j][1];
					score_points[0][j][1] = aux;
					char saux[100];
					strcpy(saux, score_name[0][i]);
					strcpy(score_name[0][i], score_name[0][j]);
					strcpy(score_name[0][j], saux);
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = i; j < 4; j++)
			{
				if (score_points[0][i][0] == score_points[0][j][0])  // in cazul in care scorul e egal se ordoneaza in fnctie de timp
				{
					if (score_points[0][i][1] > score_points[0][j][1])
					{
						float aux = score_points[0][i][0];
						score_points[0][i][0] = score_points[0][j][0];
						score_points[0][j][0] = aux;
						aux = score_points[0][i][1];
						score_points[0][i][1] = score_points[0][j][1];
						score_points[0][j][1] = aux;
						char saux[100];
						strcpy(saux, score_name[0][i]);
						strcpy(score_name[0][i], score_name[0][j]);
						strcpy(score_name[0][j], saux);
					}
				}
			}
		}
		break;
	case 2:
		map_mines_number = 18;
		strcpy(score_name[1][3], name);
		score_points[1][3][1] = time;
		score_points[1][3][0] = map_mines_number - mine_number;
		for (int i = 0; i < 3; i++)
		{
			for (int j = i; j < 4; j++)
			{
				if (score_points[1][i][0] < score_points[1][j][0])
				{
					float aux = score_points[1][i][0];
					score_points[1][i][0] = score_points[1][j][0];
					score_points[1][j][0] = aux;
					aux = score_points[1][i][1];
					score_points[1][i][1] = score_points[1][j][1];
					score_points[1][j][1] = aux;
					char saux[100];
					strcpy(saux, score_name[1][i]);
					strcpy(score_name[1][i], score_name[1][j]);
					strcpy(score_name[1][j], saux);
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = i; j < 4; j++)
			{
				if (score_points[1][i][0] == score_points[1][j][0])
				{
					if (score_points[1][i][1] > score_points[1][j][1])
					{
						float aux = score_points[1][i][0];
						score_points[1][i][0] = score_points[1][j][0];
						score_points[1][j][0] = aux;
						aux = score_points[1][i][1];
						score_points[1][i][1] = score_points[1][j][1];
						score_points[1][j][1] = aux;
						char saux[100];
						strcpy(saux, score_name[1][i]);
						strcpy(score_name[1][i], score_name[1][j]);
						strcpy(score_name[1][j], saux);
					}
				}
			}
		}
		break;
	case 3:
		map_mines_number = 27;
		strcpy(score_name[2][3], name);
		score_points[2][3][1] = time;
		score_points[2][3][0] = map_mines_number - mine_number;
		for (int i = 0; i < 3; i++)
		{
			for (int j = i; j < 4; j++)
			{
				if (score_points[2][i][0] < score_points[2][j][0])
				{
					float aux = score_points[2][i][0];
					score_points[2][i][0] = score_points[2][j][0];
					score_points[2][j][0] = aux;
					aux = score_points[2][i][1];
					score_points[2][i][1] = score_points[2][j][1];
					score_points[2][j][1] = aux;
					char saux[100];
					strcpy(saux, score_name[2][i]);
					strcpy(score_name[2][i], score_name[2][j]);
					strcpy(score_name[2][j], saux);
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = i; j < 4; j++)
			{
				if (score_points[3][i][0] == score_points[3][j][0])
				{
					if (score_points[3][i][1] > score_points[3][j][1])
					{
						float aux = score_points[3][i][0];
						score_points[3][i][0] = score_points[3][j][0];
						score_points[3][j][0] = aux;
						aux = score_points[3][i][1];
						score_points[3][i][1] = score_points[3][j][1];
						score_points[3][j][1] = aux;
						char saux[100];
						strcpy(saux, score_name[3][i]);
						strcpy(score_name[3][i], score_name[3][j]);
						strcpy(score_name[3][j], saux);
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

void leaderboard()
{
	// se afiseaza clasamentul in functie de harta jucata
	system("cls");
	gotoXY(5, 2);
	printf("\x1B[32mEasy\033[0m");
	for (int j = 0; j < 3; j++)
	{
		gotoXY(2, j + 4);
		printf("%d. %s", j+1, score_name[0][j]);
		gotoXY(40, j + 4);
		printf("%.0f points", score_points[0][j][0]);
		gotoXY(55, j + 4);
		printf("%.3f seconds", score_points[0][j][1]);
	}

	gotoXY(5, 10);
	printf("\x1B[33mMedium\033[0m");
	for (int j = 0; j < 3; j++)
	{
		gotoXY(2, j + 12);
		printf("%d. %s", j + 1, score_name[1][j]);
		gotoXY(40, j + 12);
		printf("%.0f points", score_points[1][j][0]);
		gotoXY(55, j + 12);
		printf("%.3f seconds", score_points[1][j][1]);
	}
	gotoXY(5, 18);
	printf("\x1B[31mHard\033[0m");
	for (int j = 0; j < 3; j++)
	{
		gotoXY(2, j + 20);
		printf("%d. %s", j + 1, score_name[2][j]);
		gotoXY(40, j + 20);
		printf("%.0f points", score_points[2][j][0]);
		gotoXY(55, j + 20);
		printf("%.3f seconds", score_points[2][j][1]);
	}
	gotoXY(28, 25);
	printf("You have to make at least one point to be in the leaderboard");
	gotoXY(38, 28);
	printf("Press space to return to the main menu");
	while (_getch() != ' ')
	{

	}
}

void print_message(int option)
{
	system("cls");				// se curata consola
	gotoXY(50, 10);
	if (mine_number == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);		// se coloreaza caracterele
		printf("YOU WON");		//  in cazul in care toate minele au fost setate jocul este castigat
		RESET
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("GAME OVER");	// altfel jocul este pierdut
		RESET
	}
	if (option > 0 && option < 4)
	{
		gotoXY(37, 20);
		printf("Please enter your name: ");
		scanf(" %[^\n]s", name);  //  se salveaza numele intr un sir de caractere pana la apasarea tastei ENTER
	}
	gotoXY(43, 25);
	printf("Press space to continue");
	while (_getch() != ' ') {}

}

void how_to_play()
{
	// afiseaza instructiunile jocului
	system("cls");
	gotoXY(50, 5);
	printf("Instructions");
	gotoXY(15, 8);
	printf("1. Enter the column and line then press ENTER to choose the coordinates.");
	gotoXY(15, 9);
	printf("2. To place or take the flag you must enter the character 'F' before the coordinates.");
	gotoXY(15, 10);
	printf("3. The numbers show how many mines are adjacent to the block.");
	gotoXY(15, 11);
	printf("4. You have to put a flag on all the mines in order to win, but the number of mines");
	gotoXY(15, 12);
	printf("set must be equal to the number of mines in the scene.");
	gotoXY(15, 13);
	printf("5. In order to be on the leaderboard you must set at least one mine correctly.");
	
	gotoXY(38, 25);
	printf("Press space to return to the main menu");
	while (_getch() != ' ')
	{

	}
}

bool verification(int x, int y)
{
	if (x > 3 && x < DIM_X - 3 && y>3 && y < DIM_Y - 3) // conditie ca coordonatele sa se afle in interiorul scenei
		return TRUE;
}

void reveal_free_space()
{
	// se foloseste o coada pentru a afisa spatiile libere
	int inceput = 0;
	int sfarsit = 0;
	int coord_x[9999] = { 0 };  // se salveaza coorodnata pe x a casutei
	int coord_y[9999] = { 0 };	// se salveaza coordonata pe y a casutei
	coord_x[0] = x;
	coord_y[0] = y;
	gotoXY(x, y);
	printf(" ");
	while (inceput <= sfarsit)
	{
		x = coord_x[inceput];	// coada ia ca prim element pozitia introdusa unde se afla 0
		y = coord_y[inceput];
		if (scena_mine[y][x] == '0')
		{
			// se verifica pe rand casutele din jurul casutei de coordonate introduse
			if (scena[y][x - 2] == '+' && verification(x - 2, y))
			{
				gotoXY(x - 2, y);
				if (scena_mine[y][x - 2] == '0') // in cazul in care pe casuta din scena din spate se afla valoarea 0 ( nu sunt mine in apropiere) se afiseaza spatiu 
				{
					BLACK
					sfarsit++;					 // creste numarul de elemente din coada
					coord_x[sfarsit] = x - 2;	 // se introduc coordonatele in coada
					coord_y[sfarsit] = y;
					printf(" ");
					scena[y][x - 2] = ' ';
					RESET
				}
				else							 // altfel se afiseaza casuta din scena din spate cu numarul de mine din apropierea acestuia
				{
					change_color(x - 2, y);      // schimba culoarea caracterului
					printf("%c", scena_mine[y][x - 2]);
					scena[y][x - 2] = scena_mine[y][x - 2];
					RESET						 
				}
			}
			if (scena[y + 1][x - 2] == '+' && verification(x - 2, y + 1))
			{
				gotoXY(x - 2, y + 1);
				if (scena_mine[y + 1][x - 2] == '0')
				{
					BLACK
					sfarsit++;
					coord_x[sfarsit] = x - 2;
					coord_y[sfarsit] = y + 1;
					printf(" ");
					scena[y + 1][x - 2] = ' ';
					RESET
				}
				else
				{
					change_color(x - 2, y + 1);
					printf("%c", scena_mine[y + 1][x - 2]);
					scena[y + 1][x - 2] = scena_mine[y + 1][x - 2];
					RESET
				}
			}
			if (scena[y + 1][x] == '+' && verification(x, y + 1))
			{
				gotoXY(x, y + 1);
				if (scena_mine[y + 1][x] == '0')
				{
					BLACK
					sfarsit++;
					coord_x[sfarsit] = x;
					coord_y[sfarsit] = y + 1;
					printf(" ");
					scena[y + 1][x] = ' ';
					RESET
				}
				else
				{
					change_color(x, y + 1);
					printf("%c", scena_mine[y + 1][x]);
					scena[y + 1][x] = scena_mine[y + 1][x];
					RESET
				}
			}
			if (scena[y + 1][x + 2] == '+' && verification(x + 2, y + 1))
			{
				gotoXY(x + 2, y + 1);
				if (scena_mine[y + 1][x + 2] == '0')
				{
					BLACK
					sfarsit++;
					coord_x[sfarsit] = x + 2;
					coord_y[sfarsit] = y + 1;
					printf(" ");
					scena[y + 1][x + 2] = ' ';
					RESET
				}
				else
				{
					change_color(x + 2, y + 1);
					printf("%c", scena_mine[y + 1][x + 2]);
					scena[y + 1][x + 2] = scena_mine[y + 1][x + 2];
					RESET

				}
			}
			if (scena[y][x + 2] == '+' && verification(x + 2, y))
			{
				gotoXY(x + 2, y);
				if (scena_mine[y][x + 2] == '0')
				{
					BLACK
					sfarsit++;
					coord_x[sfarsit] = x + 2;
					coord_y[sfarsit] = y;
					printf(" ");
					scena[y][x + 2] = ' ';
					RESET
				}
				else
				{
					change_color(x + 2, y);
					printf("%c", scena_mine[y][x + 2]);
					scena[y][x + 2] = scena_mine[y][x + 2];
					RESET
				}
			}
			if (scena[y - 1][x + 2] == '+' && verification(x + 2, y - 1))
			{				
				gotoXY(x + 2, y - 1);
				if (scena_mine[y - 1][x + 2] == '0')
				{
					BLACK
					sfarsit++;
					coord_x[sfarsit] = x + 2;
					coord_y[sfarsit] = y - 1;
					printf(" ");
					scena[y - 1][x + 2] = ' ';
					RESET
				}
				else
				{
					change_color(x + 2, y - 1);
					printf("%c", scena_mine[y - 1][x + 2]);
					scena[y - 1][x + 2] = scena_mine[y - 1][x + 2];
					RESET
				}
			}
			if (scena[y - 1][x] == '+' && verification(x, y - 1))
			{				
				gotoXY(x, y - 1);
				if (scena_mine[y - 1][x] == '0')
				{
					BLACK
					sfarsit++;
					coord_x[sfarsit] = x;
					coord_y[sfarsit] = y - 1;
					printf(" ");
					scena[y - 1][x] = ' ';
					RESET
				}
				else
				{
					change_color(x, y - 1);
					printf("%c", scena_mine[y - 1][x]);
					scena[y - 1][x] = scena_mine[y - 1][x];
					RESET
				}
			}
			if (scena[y - 1][x - 2] == '+' && verification(x - 2, y - 1))
			{				
				gotoXY(x - 2, y - 1);
				if (scena_mine[y - 1][x - 2] == '0')
				{
					BLACK
					sfarsit++;
					coord_x[sfarsit] = x - 2;
					coord_y[sfarsit] = y - 1;
					printf(" ");
					scena[y - 1][x - 2] = ' ';
					RESET
				}
				else
				{
					change_color(x -2 , y - 1);
					printf("%c", scena_mine[y - 1][x - 2]);
					scena[y - 1][x - 2] = scena_mine[y - 1][x - 2];
					RESET
				}
			}
		}

		inceput++; // se trece la pozitia urmatoare din coada
	}
}

void print_menu()
{ 
	// afiseaza meniul principal
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	gotoXY(3, 1); printf("*|      *|  *|                        *|*|*|                                                                      \n");
	gotoXY(3, 2); printf("*|*|  *|*|      *|*|*|      *|*|    *|        *|      *|      *|    *|*|      _|_|    *|*|*|      *|*|    *|  *|*|\n");
	gotoXY(3, 3); printf("*|  *|  *|  *|  *|    *|  *|    *|    *|      *|      *|      *|  *|    *|  *|    *|  *|    *|  *|    *|  *|*|    \n");
	gotoXY(3, 4); printf("*|      *|  *|  *|    *|  *|*|*|*|      *|    *|      *|      *|  *|*|*|*|  *|*|*|*|  *|    *|  *|*|*|*|  *|      \n");
	gotoXY(3, 5); printf("*|      *|  *|  *|    *|  *|              *|    *|  *|  *|  *|    *|        *|        *|*|*|    *|        *|      \n");
	gotoXY(3, 6); printf("*|      *|  *|  *|    *|    *|*|*|  *|*|*|        *|      *|        *|*|*|    *|*|*|  *|          *|*|*|  *|      \n");
	gotoXY(3, 7); printf("                                                                                      *|                          \n");
	gotoXY(3, 8); printf("                                                                                      *|                          \n");
	
	gotoXY(45, 10);
	printf("\x1B[94mSelect game difficulty\033[0m");
	gotoXY(50, 13);
	printf("\x1B[32m1. Easy\033[0m");
	gotoXY(50, 14);
	printf("\x1B[93m2. Normal\033[0m");
	gotoXY(50, 15);
	printf("\x1B[31m3. Hard\033[0m");
	gotoXY(50, 16); 
	printf("\x1B[35m4. Custom\033[0m");
	gotoXY(50, 18);
	printf("\x1B[33m5. Leaderboard\033[0m");
	gotoXY(50, 19);
	printf("\x1b[34m6. How to play\033[0m");
	gotoXY(50, 22);
	printf("0. Exit");
}

void main()
{
	hidecursor();							 // se ascunde cursorul
	int option, mine_number1;
	float time;
	do
	{
		ok1 = 1;							// pentru generarea unei noi scene in caz ca pe prima pozitie aleasa se afla mina
		mines_set = 0;			
		print_menu();						// afiseaza meniul
		option = _getch();
		while (option < 48 || option > 54)  // se asigura ca optiunea se afla in meniu
		{
			option = _getch();
		}
		option -= 48;
		meniu(option);						// in functie de optiune se intra in subprogramul dorit
		mine_number1 = mine_number;
		main_scene();						// se intializeaza scena principala
		mines_scene();						//  se intializeaza scena din spate cu caseute ce contin valori generate aleatoriu
		print_main_scene();					// se afiseaza scena principala
		print_mines_scene();				// se afiseaza scena cu minele  (optional)
		print_score(mine_number1);			// afiseaza numarul de mine setate si numarul de mine ramase
		x = NULL; y = NULL;					// coordonatele iau valoarea nula pentru a nu aparea erori
		clock_t time;						// functie folosita pentru masurarea timpului
		time = clock();
		while ((!game_end(x, y) && mine_number) || (mines_set > mine_number1))	// cat timp jucatorul nu alege o mina si are numarul de mine setate mai mare decat ar trebui jocul ruleaza
		{
			position_input(option, DIM_X, DIM_Y, mine_number1);					// se introduc pozitiile
			gotoXY(x, y);
			values_print();					// se schimba valorile din scena principala si se afiseaza
			print_score(mine_number1);
		}
		time = clock() - time;
		print_scene_after_game(option);		// afiseaza minele , stagurile puse corect si cele puse incorect
		print_message(option);				// dupa terminarea jocului se afiseaza mesajul corespunzator si se introduce numele jucatorului
		score_input(option, time);			// se salveaza scorul
	} while (true);
}
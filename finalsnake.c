#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
enum eDirecton dir;

struct user
{
	char username[30];
	int score;
};

void Print()
{
    printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
    getch();
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n-> Use W A S D keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat.\n\n-> Everytime you eat a food the length of the snake will be increased by 1 element and the score increases by 10.\n\n-> The game ends as you hit the wall or snake's body.\n\n-> If you want to exit press X. \n");
    printf("\n\nPress any key to play game...");
    if(getch()==27)
        exit(0);
}

void End()
{
	printf("\n\n\t\t\t\t\tGAME OVER!!");

	struct user temp1, temp2;
	struct user U;
	FILE * leader;
	leader = fopen("Leaders3.bin", "rb+");

	if (leader == NULL)
		printf("ERROR 2!");

	printf("\nTo save your score press Y, else press N: ");
	char choice = _getch();
	if (choice == 'y')
	{
		printf("\n\nEnter username: ");
		scanf("%s", U.username);
		U.score = score;
		//fseek(leader, 0, SEEK_SET);
		//while (leader != EOF)
		//{
			fread(&temp1,sizeof(struct user), 1, leader);
			if (temp1.score < U.score)
			{
				//printf("Have to write %s", U.username);
				fseek(leader, -(sizeof(struct user)), SEEK_CUR);
				//fseek(leader, 0, SEEK_SET);
				fwrite(&U, sizeof(struct user), 1, leader);
			}
		//}
	}

	system("cls");
	fseek(leader, 0, SEEK_SET);
	fread(&temp2, sizeof(struct user), 1, leader);
	printf("\tLEADERBOARD\n\tNAME\t\tSCORE\n");
	printf("\t%s\t\t%i\n", temp2.username, temp2.score);
	fclose(leader);
}

void Setup()
{
	FILE * fptr;
	fptr = fopen("Leaders3.bin", "a");
	if (fptr == NULL)
		printf("ERROR 1!");
	time_t t;
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	srand((unsigned)time(&t));
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	fclose(fptr);
}

void Draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < width+2; i++)
		printf("#");
	printf("\n");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				printf("#");
			if (i == y && j == x)
				printf(">");
			else if (i == fruitY && j == fruitX)
				printf("F");
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						printf("o");
						print = true;
					}
				}
				if (!print)
					printf(" ");
			}
			
			if (j == width - 1)
				printf("#");
		}
		printf("\n");
	}

	for (int i = 0; i < width+2; i++)
		printf("#");
	printf("\n");
	printf("Score: %i\n" , score);
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0)
	//	gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}

int main()
{
	Print();
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	End();
	
	return 0;
}


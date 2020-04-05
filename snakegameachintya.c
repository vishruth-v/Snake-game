#include<stdio.h>
#include<stdbool.h>
bool gameOver;
const int width = 10;
const int height = 10;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;
void setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < width ; i++)
		printf("#");
	printf("\n");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				printf("#");
			printf(" ");
			if (j == width - 1)
				printf("#");
		}
		printf("\n");
	}
	for (int i = 0; i < width; i++)
		printf("#");
	printf("\n");
}
void input()
{

}
void logic()
{
	
}
int main()
{
	setup();
		while (!gameOver)
		{
			draw();
			input();
			logic();
		}
	return 0;
}

#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <Windows.h>
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
	system("cls");
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	
	printf("\
 ::::::::  ::::    :::     :::     :::    ::: ::::::::::   ::::::::      :::     ::::    ::::  ::::::::::\n\
:+:    :+: :+:+:   :+:   :+: :+:   :+:   :+:  :+:         :+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:\n\
+:+        :+:+:+  +:+  +:+   +:+  +:+  +:+   +:+         +:+         +:+   +:+  +:+ +:+:+ +:+ +:+\n\
+#++:++#++ +#+ +:+ +#+ +#++:++#++: +#++:++    +#++:++#    :#:        +#++:++#++: +#+  +:+  +#+ +#++:++#\n\
       +#+ +#+  +#+#+# +#+     +#+ +#+  +#+   +#+         +#+   +#+# +#+     +#+ +#+       +#+ +#+\n\
#+#    #+# #+#   #+#+# #+#     #+# #+#   #+#  #+#         #+#    #+# #+#     #+# #+#       #+# #+#\n\
 ########  ###    #### ###     ### ###    ### ##########   ########  ###     ### ###       ### ##########\n "
	);

	printf("\n-------------------------------------------------------------------------------------------------------------\n");

    printf("\n\t\t\tWELCOME TO THE SNAKE GAME.(press any key to continue)\n");
	PlaySound("gamestart.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);
    getch();
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\tGAME INSTRUCTIONS:\n");
    printf("\n-> Use W A S D keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat.\n\n-> Everytime you eat a food the length of the snake will be increased by 1 element and the score increases by 10.\n\n-> The game ends as you hit the wall or snake's body.\n\n-> If you want to exit press X. \n");
    printf("\n-------------------------------------------------------------------------------------------------------------\n");
	printf("\n\nPress any key to play game...");
	PlaySound("beep.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);
    if(getch()==27)
        exit(0);
	PlaySound("beep.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);
}

void End()
{
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	//printf("\n\t\t\t\t\tGAME OVER!!");
	printf("\
 ::::::::      :::     ::::    ::::  ::::::::::   ::::::::  :::     ::: :::::::::: :::::::::\n\  
:+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:         :+:    :+: :+:     :+: :+:        :+:    :+:\n\ 
+:+         +:+   +:+  +:+ +:+:+ +:+ +:+         +:+    +:+ +:+     +:+ +:+        +:+    +:+\n\
:#:        +#++:++#++: +#+  +:+  +#+ +#++:++#    +#+    +:+ +#+     +:+ +#++:++#   +#++:++#:\n\  
+#+   +#+# +#+     +#+ +#+       +#+ +#+         +#+    +#+  +#+   +#+  +#+        +#+    +#+\n\ 
#+#    #+# #+#     #+# #+#       #+# #+#         #+#    #+#   #+#+#+#   #+#        #+#    #+#\n\ 
 ########  ###     ### ###       ### ##########   ########      ###     ########## ###    ###"
 );
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	PlaySound("gameover.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);

	struct user temp1, temp2;
	struct user U;
	FILE * read, * write;
	read = fopen("Leadersfinal2.bin", "rb");
    write = fopen("temp.bin", "wb");
	bool addflag = false;

	if (read == NULL)
		printf("ERROR 2!");

	printf("\nTo save your score press Y, else press N: ");
	char choice = _getch();

	if (choice == 'y')
	{
		PlaySound("beep.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);
		printf("\n\nEnter username: ");
		scanf("%s", U.username);
		PlaySound("beep.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);
		U.score = score;
		while(fread(&temp1,sizeof(struct user), 1, read))
		{
			if (temp1.score < U.score && addflag == false)
			{
                fwrite(&U, sizeof(struct user), 1, write);
                fwrite(&temp1, sizeof(struct user), 1, write);
                addflag = true;
			}
            else
            {
                fwrite(&temp1, sizeof(struct user), 1, write);
            }
		}

		if (addflag == false)
		{
			fwrite(&U, sizeof(struct user), 1, write);
		}
	}
	else
	{
		while(fread(&temp1, sizeof(struct user), 1, read))
		{
			fwrite(&temp1, sizeof(struct user), 1, write);
		}
	}

	fclose(read);
	fclose(write);

    remove("Leadersfinal2.bin");
    rename("temp.bin", "Leadersfinal2.bin");

    FILE * disp;
    disp = fopen("Leadersfinal2.bin", "rb");
	system("cls");
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	printf("\n\t\t\t\t  LEADERBOARD\n");
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\tNAME\t\t\t\tSCORE\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");

	while(fread(&temp2, sizeof(struct user), 1, disp))
	{
		printf("\t\t\t%s\t\t\t\t%i\n", temp2.username, temp2.score);
	}

	fclose(disp);
}

void Setup()
{
	FILE * fptr;
	fptr = fopen("Leadersfinal2.bin", "a");
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
				printf("O");
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
	printf("\nPress X to quit game\n");
	//printf("\n-------------------------------------------------------------------------------------------------------------\n");
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
		PlaySound("beep2.wav", NULL, SND_ASYNC);
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


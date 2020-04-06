//SIMPLE TEXT BASED SNAKE GAME IMPLEMENTED USING C
//By: VISHRUTH, ADVAIT, ACHINTYA 
//2nd SEM, Q SECTION (Group No. 17)
//PES UNIVERSITY

//For queries contact: vishruth2002@gmail.com, advaitkaluve@gmail.com, acharya.achintya@gmail.com

//NOTE: TO COMPILE USE
//      gcc <filename>.c  -lwinmm
//      -lwinmm is to link mmsystem.h which is needed for audio

#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <Windows.h>
#include <time.h>

const int width = 20;
const int height = 20;

//Structure to hold Coordinates of snake and fruit
struct COORD
{
    int X, Y;
};

//Structure for user details to store in leaderboard
struct user
{
	char username[30];
	int score;
};

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN}; //Enum to indicate direction of snake

enum eDirecton dir;
struct COORD snake, fruit;
struct COORD tail[100]; //Array to strore positions of indicidual tail elements

bool gameOver;
int score;
int nTail; //Length of Tail

//Function to print welcome screen/sound and instructions of game
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
	PlaySound("gamestart.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME); //Gamestart sound
    getch();
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\tGAME INSTRUCTIONS:\n");
    printf("\n-> Use W A S D keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat.\n\n-> Everytime you eat a food the length of the snake will be increased by 1 element and the score increases by 10.\n\n-> The game ends as you hit the wall or snake's body.\n\n-> If you want to exit press X. \n");
    printf("\n-------------------------------------------------------------------------------------------------------------\n");
	printf("\n\nPress any key to play game...");
	PlaySound("beep.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME); //Playsound function for playing beep sound
    if(getch()==27)
        exit(0);
	PlaySound("beep.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);
}

//Fucntion to get player details after game and store them on binary file
void End()
{
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
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
	PlaySound("gameover.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME); //Gameover sound

	struct user temp1;
	struct user U;
	FILE * read, * write;
	read = fopen("LeaderBoard.bin", "rb");
    write = fopen("temp.bin", "wb");
	bool addflag = false; //check to see if the present player is added to record

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

		while(fread(&temp1,sizeof(struct user), 1, read)) //Read laderboard
		{
			if (temp1.score < U.score && addflag == false)
			{
                fwrite(&U, sizeof(struct user), 1, write); //Write new leaderboard in order on a different file
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

    remove("LeaderBoard.bin"); 
    rename("temp.bin", "LeaderBoard.bin"); //Revert the new leadeerbord's filename to the old one
}

//Function to display the leaderboard
void Leaderboard()
{
    struct user temp2;
    FILE * disp;
    disp = fopen("LeaderBoard.bin", "rb");
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

//Setup and initialize the game varibales and parameters
void Setup()
{
	FILE * fptr;
	fptr = fopen("LeaderBoard.bin", "a");
	if (fptr == NULL)
		printf("ERROR 1!");
	time_t t;
	gameOver = false;
	dir = STOP;
	snake.X = width / 2;
	snake.Y = height / 2;
	srand((unsigned)time(&t));
	fruit.X = rand() % width;
	fruit.Y = rand() % height;
	score = 0;
	fclose(fptr);
}

//Fucntion to draw board at every instant
void Draw()
{
	system("cls"); //system("clear");
    //Print border
	for (int i = 0; i < width+2; i++)
		printf("#");
	printf("\n");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0) //Print border
 				printf("#");
			if (i == snake.Y && j == snake.X) //Print Head of snake
				printf("O");
			else if (i == fruit.Y && j == fruit.X) //Print fruit
				printf("F");
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tail[k].X == j && tail[k].Y == i) //Print tail segments
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

//Function to get keyboard input to make moves
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

//The game logic function that makes the moves got from input
void Logic()
{
	int prevX = tail[0].X;
	int prevY = tail[0].Y;
	int prev2X, prev2Y;
	tail[0].X = snake.X;
	tail[0].Y = snake.Y;

    //Updating the tail segment's positions based on the previous segment's position
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tail[i].X;
		prev2Y = tail[i].Y;
		tail[i].X = prevX;
		tail[i].Y = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

    //Segment to change position of snake based on movement given
	switch (dir)
	{
	case LEFT:
		snake.X--;
		break;
	case RIGHT:
		snake.X++;
		break;
	case UP:
		snake.Y--;
		break;
	case DOWN:
		snake.Y++;
		break;
	default:
		break;
	}

	//if (snake.X > width || snake.X < 0 || snake.Y > height || snake.Y < 0)
	//	gameOver = true;
	if (snake.X >= width) snake.X = 0; else if (snake.X < 0) snake.X = width - 1;
	if (snake.Y >= height) snake.Y = 0; else if (snake.Y < 0) snake.Y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tail[i].X == snake.X && tail[i].Y == snake.Y) //Checking if the snake has bit itself i.e Head position = one of the tail positions
			gameOver = true;

	if (snake.X == fruit.X && snake.Y == fruit.Y)
	{
		score += 10;
		fruit.X = rand() % width; //Randomising new fruit location
		fruit.Y = rand() % height;
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
    Leaderboard();
	
	return 0;
}


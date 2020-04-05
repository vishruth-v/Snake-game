#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

const int width = 20;
const int height = 20;
int x,y,fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
enum eDirection dir;
int gameOver; // 0 is False, 1 is true


void Draw()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (j == 0)
                printf("%c", '#');
            if (i == y && j == x)
                printf("%c", 'O');
            else if (i == fruitY && j == fruitX)
                printf("%c", 'F');
            else
            {
                int print = 0; //BOOLEAN
                for (int k = 0; k < nTail; ++k)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("%c", 'o');
                        print = 1;
                    }
                }
                if (!print)
                    printf("%c", ' ');
            }
            
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
    for (int i = 1; i < nTail; ++i)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }




    //This segment if we want game to be over after hitting the wall
    if (x > width || x < 0 || y > height || y < 0)
        gameOver = 1;

    //These 2 if-elseifs segments if we want the snake to come out of the other side
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;


    
    
    for(int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % width;
        nTail++;
    } 
}

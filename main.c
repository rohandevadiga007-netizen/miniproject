#include <stdio.h>
#include <math.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

void initializeCanvas();
void displayCanvas();

void drawRectangle(int x, int y, int width, int height);
void drawLine(int x1, int y1, int x2, int y2);
void drawTriangle(int x, int y, int height);
void drawCircle(int cx, int cy, int radius);

void deleteArea(int x, int y, int width, int height);

int main()
{
    int choice;

    initializeCanvas();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Line\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Delete Area\n");
        printf("6. Display Picture\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int x, y, width, height;

                printf("Enter x y width height: ");
                scanf("%d%d%d%d", &x, &y, &width, &height);

                drawRectangle(x, y, width, height);
                break;
            }

            case 2:
            {
                int x1, y1, x2, y2;

                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

                drawLine(x1, y1, x2, y2);
                break;
            }

            case 3:
            {
                int x, y, height;

                printf("Enter center x, y and height: ");
                scanf("%d%d%d", &x, &y, &height);

                drawTriangle(x, y, height);
                break;
            }

            case 4:
            {
                int cx, cy, radius;

                printf("Enter center x y radius: ");
                scanf("%d%d%d", &cx, &cy, &radius);

                drawCircle(cx, cy, radius);
                break;
            }

            case 5:
            {
                int x, y, width, height;

                printf("Enter x y width height to delete: ");
                scanf("%d%d%d%d", &x, &y, &width, &height);

                deleteArea(x, y, width, height);
                break;
            }

            case 6:
                displayCanvas();
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 7);

    return 0;
}

void initializeCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    int i, j;

    printf("\n");

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void drawRectangle(int x, int y, int width, int height)
{
    int i, j;

    for(i = y; i < y + height && i < ROWS; i++)
    {
        for(j = x; j < x + width && j < COLS; j++)
        {
            if(i == y || i == y + height - 1 ||
               j == x || j == x + width - 1)
            {
                canvas[i][j] = '*';
            }
        }
    }
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int i;

    if(y1 == y2)
    {
        if(x1 > x2)
        {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }

        for(i = x1; i <= x2 && i < COLS; i++)
        {
            canvas[y1][i] = '*';
        }
    }
    else if(x1 == x2)
    {
        if(y1 > y2)
        {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }

        for(i = y1; i <= y2 && i < ROWS; i++)
        {
            canvas[i][x1] = '*';
        }
    }
    else
    {
        printf("Only horizontal and vertical lines supported.\n");
    }
}

void drawTriangle(int x, int y, int height)
{
    int i, j;

    for(i = 0; i < height; i++)
    {
        if(y + i < ROWS)
        {
            if(x - i >= 0)
                canvas[y + i][x - i] = '*';

            if(x + i < COLS)
                canvas[y + i][x + i] = '*';
        }
    }

    for(j = x - height + 1; j <= x + height - 1; j++)
    {
        if(j >= 0 && j < COLS &&
           y + height - 1 < ROWS)
        {
            canvas[y + height - 1][j] = '*';
        }
    }
}

void drawCircle(int cx, int cy, int radius)
{
    int x, y;

    for(y = 0; y < ROWS; y++)
    {
        for(x = 0; x < COLS; x++)
        {
            int dx = x - cx;
            int dy = y - cy;

            if(abs(dx * dx + dy * dy - radius * radius) <= radius)
            {
                canvas[y][x] = '*';
            }
        }
    }
}

void deleteArea(int x, int y, int width, int height)
{
    int i, j;

    for(i = y; i < y + height && i < ROWS; i++)
    {
        for(j = x; j < x + width && j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}
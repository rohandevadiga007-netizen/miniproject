#include <stdio.h>
#include <math.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

/* Initialize canvas */
void initCanvas() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            canvas[i][j] = ' ';
}

/* Display canvas */
void displayCanvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

/* Plot a point */
void plot(int x, int y, char ch) {
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS)
        canvas[y][x] = ch;
}

/* Draw line using Bresenham's algorithm */
void drawLine(int x1, int y1, int x2, int y2, char ch) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (1) {
        plot(x1, y1, ch);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

/* Draw rectangle */
void drawRectangle(int x, int y, int width, int height, char ch) {
    for (int i = x; i < x + width; i++) {
        plot(i, y, ch);
        plot(i, y + height - 1, ch);
    }

    for (int i = y; i < y + height; i++) {
        plot(x, i, ch);
        plot(x + width - 1, i, ch);
    }
}

/* Draw triangle */
void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3,
                  char ch) {
    drawLine(x1, y1, x2, y2, ch);
    drawLine(x2, y2, x3, y3, ch);
    drawLine(x3, y3, x1, y1, ch);
}

/* Draw circle */
void drawCircle(int xc, int yc, int r, char ch) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        plot(xc + x, yc + y, ch);
        plot(xc - x, yc + y, ch);
        plot(xc + x, yc - y, ch);
        plot(xc - x, yc - y, ch);

        plot(xc + y, yc + x, ch);
        plot(xc - y, yc + x, ch);
        plot(xc + y, yc - x, ch);
        plot(xc - y, yc - x, ch);

        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

/* Delete object by drawing spaces */
void eraseLine(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y2, ' ');
}

void eraseRectangle(int x, int y, int w, int h) {
    drawRectangle(x, y, w, h, ' ');
}

void eraseTriangle(int x1, int y1,
                   int x2, int y2,
                   int x3, int y3) {
    drawTriangle(x1, y1, x2, y2, x3, y3, ' ');
}

void eraseCircle(int xc, int yc, int r) {
    drawCircle(xc, yc, r, ' ');
}

int main() {

    initCanvas();

    /* Add objects */
    //drawRectangle(2, 2, 15, 8, '#');
    drawLine(0, 20, 30, 10, '*');
    //drawTriangle(40, 5, 55, 15, 35, 15, '+');
   // drawCircle(20, 20, 6, 'O');

    printf("Original Picture:\n\n");
    displayCanvas();

    /* Delete rectangle */
    eraseRectangle(2, 2, 15, 8);

    /* Modify circle (move it) */
    eraseCircle(20, 20, 6);
    drawCircle(45, 22, 4, 'O');

    printf("\n\nModified Picture:\n\n");
    displayCanvas();

    return 0;
}
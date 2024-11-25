#include <stdio.h>            //标准头文件
#include <stdlib.h>             //随机生成食物
#include <conio.h>             //控制蛇的方向
#include <windows.h>            //处理图形界面

#define WIDTH 82            // 游戏区域大小
#define HEIGHT 30

#define GRID_SIZE 20                // 小方格大小

typedef enum {                 // 定义方向
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct {                  // 蛇结构体
    int x;
    int y;
} Position;

Position snake_pos = {5, 5};                                                // 初始化蛇的位置和长度
Position snake_body[WIDTH * HEIGHT] = {{5, 5}, {4, 5}, {3, 5}};
int snake_length = 1;

Position food_pos;               // 食物的位置

int game_over = 0;              // 游戏结束标志

Direction direction = RIGHT;              // 初始方向

void draw() {                                         // 绘制游戏界面
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printf("|");
        for (int j = 0; j < WIDTH; j++) {
            int is_snake = 0;
            int is_food = 0;
            for (int k = 0; k < snake_length; k++) {
                if (snake_body[k].x == j && snake_body[k].y == i) {
                    printf("o");
                    is_snake = 1;
                    break;
                }
            }
            if (food_pos.x == j && food_pos.y == i) {
                printf("@");
                is_food = 1;
            }
            if (!is_snake &&!is_food) {
                printf(" ");
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) {
        printf("-");
    }
    printf("\n");
}

void generate_food() {                              // 生成食物的位置
    food_pos.x = rand() % WIDTH;
    food_pos.y = rand() % HEIGHT;
}

void move_snake() {                                                                                                         // 移动蛇
    Position next_pos = {snake_pos.x + (direction == RIGHT? 1 : direction == LEFT? -1 : 0),
                        snake_pos.y + (direction == DOWN? 1 : direction == UP? -1 : 0)};

        if (next_pos.x == food_pos.x && next_pos.y == food_pos.y) {                                    // 判断是否吃到食物
        snake_body[snake_length++] = next_pos;
        generate_food();
    } else {
        for (int i = 0; i < snake_length; i++) {                                                     // 判断是否撞到自己或边界
            if (next_pos.x == snake_body[i].x && next_pos.y == snake_body[i].y) {
                game_over = 1;
                return;
            }
        }
        if (next_pos.x < 0 || next_pos.x >= WIDTH || next_pos.y < 0 || next_pos.y >= HEIGHT) {
            game_over = 1;
            return;
        }
   
        for (int i = snake_length - 1; i > 0; i--) {                                 // 移动蛇身
            snake_body[i] = snake_body[i - 1];
        }
        snake_body[0] = next_pos;
    }
    snake_pos = next_pos;
}

int main() {
    generate_food();

    while (!game_over) {
        draw();
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 'w':
                    if (direction!= DOWN) {
                        direction = UP;
                    }
                    break;
                case 's':
                    if (direction!= UP) {
                        direction = DOWN;
                    }
                    break;
                case 'a':
                    if (direction!= RIGHT) {
                        direction = LEFT;
                    }
                    break;
                case 'd':
                    if (direction!= LEFT) {
                        direction = RIGHT;
                    }
                    break;
            }
        }
        move_snake();
        Sleep(200);
    }

    printf("Game Over!\n");

    return 0;
}
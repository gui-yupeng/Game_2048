#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "curses.h"
using namespace std;
// 格子数
#define N 4
// 每个格子的字符长度
#define WIDTH 5
class Game2048 {
public:
    Game2048() {
        setTestData();
    }
    // 绘制游戏界面
    void draw() {
        // 清理屏幕
        clear();
        // 居中偏移
        const int offset = 12;
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N; ++j) {
                // 相交点
                drawItem(i * 2, 1 + j * WIDTH + offset, '+');
                // 竖线
                if (i != N) {
                    drawItem(i * 2 + 1, 1 + j * WIDTH + offset, '|');
                }
                // 横线
                for (int k = 1; j != N && k < WIDTH; ++k) {
                    drawItem(i * 2, 1 + j * WIDTH + k + offset, '-');
                }
                // 每个格子里的数
                if (i != N && j != N) {
                    drawNum(i * 2 + 1, (j + 1) * WIDTH + offset, data[i][j]);
                }
            }
        }
        // 提示文字
        mvprintw(2 * N + 2, (5 * (N - 4) - 1) / 2, "W(UP),S(DOWN),A(LEFT),D(RIGHT),R(RESTART),Q(QUIT)");
        mvprintw(2 * N + 3, 12 + 5 * (N - 4) / 2, "https://www.nowcoder.com");
    }
    // 方便调试, 随时设置数据
    void setTestData() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                data[i][j] = 16 << i << j;
                /*
                data[i][0] = 2;
                data[i][1] = 4;
                data[i][2] = 8;
                data[i][3] = 16;*/
            }
        }
    }
private:
    // 左上角为（0，0），在指定的位置画一个字符
    void drawItem(int row, int col, char c) {
        move(row, col);
        addch(c);
    }
    // 游戏里的数字是右对齐，row, col是数字最后一位所在的位置
    void drawNum(int row, int col, int num) {
        while (num > 0) {
            drawItem(row, col, num % 10 + '0');
            num /= 10;
            --col;
        }
    }
private:
    int data[N][N];
};
void initialize() {
    // ncurses初始化
    initscr();
    // 按键不需要输入回车直接交互
    cbreak();
    // 按键不显示
    noecho();
    // 隐藏光标
    curs_set(0);
    // 随机数
    srand(time(NULL));
}
void shutdown() {
    // ncurses清理
    endwin();
}
int main() {
    initialize();
    Game2048 game;
    char ch = 'n';
    do {
        game.draw();
        ch = getch();
    } while (ch != 'Q' && ch != 'q');
    shutdown();
    return 0;
}
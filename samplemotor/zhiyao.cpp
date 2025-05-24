
// #include <stdio.h>
// #include <iostream>
// #include <glob.h>
// #include <SDL2/SDL.h>
// using namespace std;

// int main() {
//     SDL_Init(SDL_INIT_VIDEO);
//     SDL_Window *win = SDL_CreateWindow("Hello SDL", 100, 100, 640, 480, 0);
//     SDL_Delay(10000);
//     SDL_DestroyWindow(win);
//     SDL_Quit();
//     return 0;
// }

/*
g++ -o zhiyao zhiyao.cpp -lSDL2
*/

#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("HMI Window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (!win) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Rect button = { 250, 200, 140, 60 };
    bool running = true;
    SDL_Event e;
    bool isRed = true;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;
                if (x >= button.x && x <= button.x + button.w &&
                    y >= button.y && y <= button.y + button.h) {
                    isRed = !isRed;  // 点击切换颜色
                }
            }
        }

        // 清屏
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        // 画按钮
        if (isRed)
            SDL_SetRenderDrawColor(ren, 255, 225, 0, 255);  // 红色
        else
            SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);  // 绿色

        SDL_RenderFillRect(ren, &button);
        SDL_RenderPresent(ren);  // 显示
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

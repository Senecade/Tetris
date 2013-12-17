#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(300, 600, 0, &window, &renderer);
    SDL_Rect test;
    test.x = 50;
    test.y = 0;
    test.w = 100;
    test.h = 200;
    SDL_SetRenderDrawColor(renderer,255,0,0,100);
    SDL_RenderFillRect(renderer,&test);
    int running = 1;
    while (running) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
	    if (e.type == SDL_QUIT) running = 0;
	}
	SDL_Delay(10);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}

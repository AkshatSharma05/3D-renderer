#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480
#define FPS			  60

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event ev;

bool running = true;

float z = 1;

void initSDL2();
struct point createPoint(float x, float y, float size);
void updatePoint(struct point *p);

struct point{
	float x,y;
	float s;
	float px,py;
	SDL_Rect r;
};

int main(){
	initSDL2();
	
	struct point points[] = {
		createPoint(0.5, 0.5 , 5),
		createPoint(-0.5, 0.5, 5),
		createPoint(0.5, -0.5 , 5),
		createPoint(-0.5, -0.5, 5),
	};

	while(running){
		while(SDL_PollEvent(&ev) != 0){
			switch(ev.type){
				case SDL_QUIT:
				running = false;
				break;
			}
		}
		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_RenderClear( renderer );
		
		SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
		
		for(int i = 0; i < (int) (sizeof(points)/sizeof(struct point)); i++){
			updatePoint(&points[i]);
			SDL_RenderFillRect(renderer, &points[i].r);

		}
		
		z += 0.001*(1000/FPS);
		
		
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/FPS);
	}
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}


void initSDL2(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("SDL2 init failed! \n");
	}
	if(!(window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS))){
		printf("Window creation failed!\n");
	}
	
	if(!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))){
		printf("Renderer creation failed! \n");
	}
}

struct point createPoint(float x, float y, float size){
	struct point p =  {.x = x, .y = y, .s = size};

	p.r = (SDL_Rect) { WINDOW_WIDTH*(p.x+1)/2 - p.s/2, WINDOW_HEIGHT* (1 - (p.y+1)/2) - p.s/2, p.s, p.s }; //xpos and ypos range : -1,1
	SDL_RenderFillRect(renderer, &p.r);
	
	return p;
}

void updatePoint(struct point *p){
	p->px = p->x/z;
	p->py = p->y/z;
	p->r = (SDL_Rect) { WINDOW_WIDTH*(p->px+1)/2 - p->s/2, WINDOW_HEIGHT* (1 - (p->py+1)/2) - p->s/2, p->s, p->s }; //xpos and ypos range : -1,1
}
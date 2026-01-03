#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#define WINDOW_WIDTH  	640
#define WINDOW_HEIGHT 	480
#define FPS			  	60.0

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event ev;

bool running = true;

float dz = 1.0;
float angle = 0.0;

void initSDL2();
void deInitSDL2();

struct point createPoint(float x, float y, float z, float size);
void updatePoint(struct point *p);
struct point *rotatePoint(struct point *p, float angle);

struct point{
	float x, y, z;
	float ox, oy, oz; 
	float s;
	float px, py, pz;
	SDL_Rect r;
};

int main(){
	initSDL2();
	
	struct point points[] = {
		createPoint(0.5,  0.5 ,  2.0, 5),
		createPoint(-0.5, 0.5 ,  2.0, 5),
		createPoint(0.5,  -0.5,  2.0, 5),
		createPoint(-0.5, -0.5,  2.0, 5),

		createPoint(0.5,  0.5 ,  3.0, 5),
		createPoint(-0.5, 0.5 ,  3.0, 5),
		createPoint(0.5,  -0.5,  3.0, 5),
		createPoint(-0.5, -0.5,  3.0, 5),
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
		
		// dz = 0;
		dz += 0.0001*(1000/FPS);

		for(int i = 0; i < (int) (sizeof(points)/sizeof(struct point)); i++){
			updatePoint(rotatePoint(&points[i], angle));
			SDL_RenderFillRect(renderer, &points[i].r);
		}

		angle+=2.0*3.14*(1000.0/FPS)*0.0001;
		printf("%f\n", dz);
		
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/FPS);
	}

	deInitSDL2();
	
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

void deInitSDL2(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

struct point createPoint(float x, float y, float z, float size){
	struct point p = {
		.x = x, .y = y, .z = z,
		.ox = x, .oy = y, .oz = z, 
		.pz = z, .s = size
	};

	p.r = (SDL_Rect) { WINDOW_WIDTH*(p.x+1)/2 - p.s/2, WINDOW_HEIGHT* (1 - (p.y+1)/2) - p.s/2, p.s, p.s };
	SDL_RenderFillRect(renderer, &p.r);
	
	return p;
}

void updatePoint(struct point *p){
	// p->z += dz;
	p->pz = p->z + dz;
	p->px = p->x/p->pz;
	p->py = p->y/p->pz;
	p->r = (SDL_Rect) { WINDOW_WIDTH*(p->px+1)/2 - p->s/2, WINDOW_HEIGHT* (1 - (p->py+1)/2) - p->s/2, p->s, p->s };
}

struct point *rotatePoint(struct point *p, float angle){
    float x = p->ox;
    float z = p->oz-2.5;  
    
    // float center_z = 1.0 + dz;
    
    // z = z - center_z;
    
    p->x = x * cos(angle) - z * sin(angle);
    p->z = x * sin(angle) + z * cos(angle);
    
    // p->z += center_z;
    
    return p;
}
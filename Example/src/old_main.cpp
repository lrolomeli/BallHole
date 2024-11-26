#if 0
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int argc, char* argv[]) {


    RenderWindow window("HB v1.0", 400, 400);

    SDL_Texture* boardTexture = window.loadTexture("res/gfx/1010board.png");
    SDL_Texture* ballTexture = window.loadTexture("res/gfx/ball.png");
    
    // Entity entities[3] = {Entity(0, 0, ballTexture),Entity(100, 100, ballTexture),Entity(200, 200, ballTexture)};
    Vector2f vs[3] = {{0,0},{100,100},{200,200}};
    std::vector<Entity> balls  = {Entity(vs[0], ballTexture),Entity(vs[1], ballTexture),Entity(vs[2], ballTexture)};
    
    {
        Vector2f vpos = {400,400};
        Entity wilson(vpos, ballTexture);
        balls.push_back(wilson);
    }

    bool gameRunning = true;
    SDL_Event event;
    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::stime_s();

    while(gameRunning) {
        float newTime = utils::stime_s();
        float frameTime = newTime - currentTime;
        
        currentTime = newTime;
        accumulator += frameTime;

        while(accumulator >= timeStep){
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    gameRunning = false;
                }
            }
            accumulator -= timeStep;
        }

        const float alpha = accumulator / timeStep; // 50%?

        (void) alpha;

        window.clear();

        window.brender(boardTexture);
        
        for(Entity& b : balls) {
            window.derender(b);
        }
        
        // for(int i = 0; i < 3; i++) {
        //     window.derender(balls[i]);
        // }

        std::cout << utils::stime_s() << std::endl;

        window.display();
    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}
#endif
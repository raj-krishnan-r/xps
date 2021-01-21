#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Framework{
public:
    // Contructor which initialize the parameters.
    Framework(int height_, int width_): height(height_), width(width_){
        SDL_Init(SDL_INIT_VIDEO);       // Initializing SDL as Video
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);      // setting draw color
        SDL_RenderClear(renderer);      // Clear the newly created window
        SDL_RenderPresent(renderer);    // Reflects the changes done in the
                                        //  window.
    }

    // Destructor
    ~Framework(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
std::vector<std::string> explode(const std::string& str, const char& ch) {
    std::string next;
    std::vector<std::string> result;

    // For each character in the string
    for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (!next.empty())
         result.push_back(next);
    return result;
}

    void drawer(){
        std::string line;
        std::string loadedFile;
        std::ifstream fileHandle ("source.txt");
        if(fileHandle.is_open()){
            while(getline(fileHandle,line)){
            loadedFile+=line;
            }
            std::vector<std::string> pixels = explode(loadedFile,',');
            for (int x=0;x<width;x++)
            {
                for(int y=0;y<height;y++)
                {
                    int redIS = y*(width*4)+(x*4);
                    std::stringstream red(pixels.at(redIS));
                    std::stringstream green(pixels.at(redIS+1));
                    std::stringstream blue(pixels.at(redIS+2));
                    std::stringstream alpha(pixels.at(redIS+3));
                    
          

                    int r = 0;
                    red >> r;
                    int g = 0;
                    red >> g;
                    int b = 0;
                    blue >> b;
                    int a = 0;
                    alpha >> a;

                    SDL_SetRenderDrawColor(renderer, r,g,b,a);
                    SDL_RenderDrawPoint(renderer, x, y);

                }
            }
                    SDL_RenderPresent(renderer);

            /*
            for(int i=0;i<pixels.size();i=i+4)
            {
                std::cout<<pixels.at(i);
                //SDL_SetRenderDrawColor(renderer, pixels.at(i), pixels.at(i+1), pixels.at(i+2), pixels.at(i+3));
                SDL_RenderDrawPoint(renderer, x, y);
                

                

            }
            */
            fileHandle.close();
        }
        else{
            std::cout<<"File closed";
        }

        /*
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, x, y);
        SDL_RenderPresent(renderer);
        */
    }

private:
    int height;     // Height of the window
    int width;      // Width of the window
    SDL_Renderer *renderer = NULL;      // Pointer for the renderer
    SDL_Window *window = NULL;      // Pointer for the window
};

int main(int argc, char * argv[]){

    // Creating the object by passing Height and Width value.
    Framework fw(667, 1000);

    // Calling the function that draws circle.
    fw.drawer();

    SDL_Event event;    // Event variable

    // Below while loop checks if the window has terminated using close in the
    //  corner.
    while(!(event.type == SDL_QUIT)){
        SDL_Delay(10);  // setting some Delay
        SDL_PollEvent(&event);  // Catching the poll event.
    }
}
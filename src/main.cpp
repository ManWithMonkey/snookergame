#include "NCursesHelper.hpp"
#include "DrawFunctions.hpp"
#include "Canvas.hpp"
#include <unistd.h>

#include "demos.hpp"

int main(){
    Init();

    while(!ShouldQuit()){
        UpdateNCurses();
        DefaultScreen();

        BouncingBallTest();
        CanvasTest();

        Refresh();
        usleep(1000);
    }

    Quit();

    return 0;
}

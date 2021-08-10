#include "NCursesHelper.hpp"
#include "DrawFunctions.hpp"
#include <unistd.h>

int main(){
    Init();

    while(!ShouldQuit()){
        UpdateNCurses();

        DefaultScreenTest();
        // BouncingBallTest();
        CanvasTest();
        Refresh();

        usleep(1000);
    }

    Quit();

    return 0;
}

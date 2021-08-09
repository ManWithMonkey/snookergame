#include "NCursesHelper.h"
#include <unistd.h>

int main(){
    Init();

    while(!ShouldQuit()){
        UpdateNCurses();

        DefaultScreenTest();
        Refresh();

        usleep(1000);
    }

    Quit();

    return 0;
}

#include "NCursesHelper.h"
#include <unistd.h>

int main(){
    Init();

    while(true){
        UpdateScreenVariables();
        DefaultScreenTest();
        Refresh();

        usleep(100000);
    }

    Quit();

    return 0;
}

#include "rem.h"
#include "controller.h"
#include <iostream>
#include <getopt.h>
#include <unistd.h>

bool G_FLAG_VERBOSE = false;
bool G_INTERACTIVE_MODE = false;



int main(int argc, char *argv[])
{
    if (argc == 1) {
        G_INTERACTIVE_MODE = true;
    }

    int opt;

    Controller *pController = new Controller();

    if (G_INTERACTIVE_MODE) {
        while (1) {
            std::cout << ">>";
            if (pController->poll() == -1) break;
        }
    }
    else // Non-interactive
    {
        // Check verbose flag first.
        while((opt = getopt(argc, argv, "i:lvha:r:")) != -1)  
        {
            if (opt == 'v') {
                G_FLAG_VERBOSE = true;
            }
        }
        optind = 1;

        while((opt = getopt(argc, argv, "i:lvha:r:")) != -1) {
            pController->processCmd(opt, argc, argv);
        }
    }
    

    return 0;
}

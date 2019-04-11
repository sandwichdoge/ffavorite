#include "controller.h"
#include <iostream>
#include <getopt.h>
#include <unistd.h>
#include <string.h>


bool G_FLAG_VERBOSE = false;
bool G_INTERACTIVE_MODE = false;


int main(int argc, char *argv[])
{
    if (argc == 1) {
        G_INTERACTIVE_MODE = true;
    }


    char **raw = (char**)malloc(sizeof(char*) * argc);

    for (int i = 0; i < argc; i++) {
        raw[i] = (char*)malloc(strlen(argv[i]));
        strcpy(raw[i], argv[i]);
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
        while((opt = getopt(argc, argv, "ci:lvha:r:")) != -1)  
        {
            if (opt == 'v') {
                G_FLAG_VERBOSE = true;
            }
        }

        optind = 1;

        while((opt = getopt(argc, argv, "ci:lvha:r:")) != -1) {
            if (pController->processCmd(opt, argc, raw) < 0) break;
        }
    }

    for (int i = 0; i < argc; i++) {
        free(raw[i]);
    }
    free(raw);
    
    delete pController;    

    return 0;
}

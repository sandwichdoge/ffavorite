#include "rememberd.h"
#include <signal.h>

rememberd *p = NULL;

void sighandler(int signo)
{
    switch (signo)
    {
        case SIGINT:
        case SIGTERM:
            p->uinit();
            delete p;
    }

    exit(0);
}


int main()
{
    p = new rememberd;
    
    p->init();

    signal(SIGINT, sighandler);
    signal(SIGTERM, sighandler);

    while (1) {
        sleep(60);
    }


    return 0;
}
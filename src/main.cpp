#include "rememberd.h"

int main()
{
    rememberd *p = new rememberd;
    
    p->init();

    while (1) {
        sleep(60);
    }
    
    return 0;
}
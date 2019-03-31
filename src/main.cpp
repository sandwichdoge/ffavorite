#include "rememberd.h"

int main()
{
    rememberd *p = new rememberd;
    
    p->init();
    sleep(50);
    
    return 0;
}
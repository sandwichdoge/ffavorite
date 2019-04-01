#include "tfmanctl.h"
#include <iostream>


int main()
{
    std::string files;
    client *p = new client;

    p->init();

    files = p->getFormattedFileList();
    std::cout << files;

    p->getFileList();

    p->uinit();
    return 0;
}
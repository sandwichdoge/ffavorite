#include "tfmanctl.h"
#include <iostream>


int main()
{
    std::string files;
    client *p = new client;

    p->init();

    files = p->getFileList();
    std::cout << files;

    p->addFile("/home/z/Test.txt");

    p->uinit();
    return 0;
}
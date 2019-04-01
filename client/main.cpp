#include "tfmanctl.h"
#include <iostream>



int main(int argc, char *argv[])
{
    client *p = new client;
    p->init();
    int status = 0;

    int opt; 
    while((opt = getopt(argc, argv, "ilar:")) != -1)  
    {  
        switch(opt)  
        {
            case 'i':
            {
                /*Access Index*/
                unsigned int i = 0;
                printf("%d\n", optarg);
                std::string filename = p->accessIndex(i);
                if (filename == "") std::cout << "ERROR\n";
                else std::cout << filename << "\n";
            }
                break;
            case 'l':
            {
                std::string files = p->getFormattedFileList();
                std::cout << files;
            }
                break;
            case 'a':
            {
                std::cout << "request a";
                printf("%s\n", optarg);
                //std::string target(optarg);
                //status = p->addFile(target);
                //std::cout << "Add file status:" << status << ".\n";
            }
                break;
            case 'r':
            {
                std::string target = std::string(optarg);
                status = p->removeFile(target);
                std::cout << "Remove file status:" << status << ".\n";
            }
                break;
        }  
    }  

    p->uinit();

    return 0;
}
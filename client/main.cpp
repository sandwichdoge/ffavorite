#include "tfmanctl.h"
#include <iostream>
#include <getopt.h>


int main(int argc, char *argv[])
{
    client *p = new client;
    p->init();

    int status = 0; // operation status
    unsigned int i = 0; // -l access index

    int opt;
    while((opt = getopt(argc, argv, "i:la:r:")) != -1)  
    {  
        switch(opt)  
        {
            case 'i':
            {
                /*Access Index*/
                sscanf(optarg, "%u", &i);
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
                std::string target = "";

                int index = optind - 1; // optarg, 1 in this case
                while (index < argc) {
                    if (argv[index][0] == '-') {
                        break;
                    }

                    target = std::string(argv[index]);

                    /*Handle relative file path here*/

                    status = p->addFile(target);
                    std::cout << "File added " << (status == 0 ? "successfully.\n" : "unsuccessfully.\n");
                    index++;
                }
                optind = index - 1;

                std::cout << optind << "\n";
            }
                break;
            case 'r':
            {
                sscanf(optarg, "%d", &i);

                std::string removedFile = "";
                status = p->removeFile(i, removedFile);
                std::cout << "Removed " << removedFile << (status == 0 ? " successfully.\n" : "unsuccessfully.\n") << ".\n";
            }
                break;
        }  
    }  

    p->uinit();

    return 0;
}
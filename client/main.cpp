#include "rem.h"
#include <iostream>
#include <getopt.h>
#include <unistd.h>

int G_FLAG_VERBOSE = 0;

int expandFilePath(std::string &path)
{
    char tmp[1024];
    if (getcwd(tmp, sizeof(tmp)) == NULL) {
        return -1;
    }

    if (path[0] != '/' && path.substr(0,2) != "./" && path.substr(0,3) != "../") {
        path = "./" + path;
    }

    std::string cwd(tmp);

    if (path == "..") { // Previous dir
        if (cwd == "/") {
            path = "/";
        }
        else
        {
            size_t pos = cwd.rfind("/");
            cwd.resize(pos);
            path = cwd;
        }
    }
    else if (path.substr(0, 3) == "../") {
        if (cwd == "/") {
            path = "/";
        }
        else
        {
            size_t pos = cwd.rfind("/");
            cwd.resize(pos);
            path.replace(0, 3, cwd + "/");
        }
    }
    else if (path == ".") { // Current dir
        path = cwd;
    }
    else if (path.substr(0, 2) == "./") {
        path.replace(0, 2, cwd + "/");
    }

    // Traverse path, handle meaningless .. and . symbols within path
    size_t start = 0;
    size_t slash = 0; // Position of current slash symbol.
    size_t len = 0;

    do {
        slash = path.find("/", start);
        if (slash == std::string::npos) break;
        
        start = path.find("/", slash + 1);

        if (path.substr(slash, start - slash) == "/..") {
            slash = path.rfind("/", slash - 1);
            path.erase(slash, start - slash);
            start = slash;
        }
        else if (path.substr(slash, start - slash) == "/.") {
            path.erase(slash, start - slash);
            start = slash;
        }

    } while (slash != std::string::npos);


    return 0;
}


void showHelp()
{
    std::cout << "\n\
    Commandline file manager.\n\
    Author: sandwichdoge\n\
    Parameters:\n\n\
    -a <filepath>\t: Add a file to storage.\n\
    -r <index>\t\t: Remove file at index in storage.\n\
    -l\t\t\t: List files in storage.\n\
    -i <index>\t\t: Print out name of file at index.\n\
    -v\t\t\t: Verbose.\n\
    -h\t\t\t: Show this help.\n";
}


int main(int argc, char *argv[])
{
    client *p = new client;
    p->init();

    int status = 0; // operation status
    unsigned int i = 0; // -l access index

    int opt;
    while((opt = getopt(argc, argv, "i:lhva:r:")) != -1)  
    {  
        switch(opt)  
        {
            case 'h':
            {
                showHelp();
            }
                break;
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
                std::string files = "";
                if (G_FLAG_VERBOSE == 0) {
                    files = p->getFileListSimple();
                }
                else
                {
                    files = p->getFileListVerbose();
                }
                
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

                    /*Handle relative file path + expand '.' here*/
                    expandFilePath(target);

                    status = p->addFile(target);
                    std::cout << target << " added " << (status == 0 ? "successfully.\n" : "unsuccessfully.\n");
                    index++;

                }
                optind = index - 1;
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
            case 'v': // Verbose
            {
                G_FLAG_VERBOSE = 1; 
            }
        }  
    }  

    p->uinit();

    return 0;
}

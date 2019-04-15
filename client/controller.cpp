#include <iostream>
#include <string>
#include <unistd.h>
#include "controller.h"
#include "../CommonCPP/StringUtils/StringUtils.h"


Controller::Controller() 
{
    _isVerbose = false;

    // Import saved data from previous session.
    p = new client;
    p->init();
    p->importList("saved_data.txt");
    p->uinit();
    delete p;
    p = NULL;
}

Controller::~Controller()
{
    // Export saved data to disk.
    p = new client;
    p->init();
    p->exportList("saved_data.txt");
    p->uinit();
    delete p;
    p = NULL;
}


int Controller::poll()
{
    /*Get user input from stdin*/
    std::string input = "";
    std::cin >> input;

    p = new client;
    p->init();

    /* Process input here.*/
    int ret = processInput(p, input);

    p->uinit();
    delete p;
    p = NULL;

    return ret;
}


int Controller::processInput(client *p, const std::string input)
{
    std::string arg = "";
    int i = 0   ;
    int status = 0;
    std::string line = "";


    if (input == "help" || input == "-h" || input == "?") {
        showHelp();
    }
    else if (input == "list" || input == "l" || input == "-l") {
        std::string files = "";
        if (_isVerbose) {
            files = p->getFileListVerbose();
        }
        else {
            files = p->getFileListSimple();
        }
        
        std::cout << files;
    }
    else if (input == "index" || input == "i" || input == "-i") {
        std::cin >> arg;
        if (!isValidIndex(arg, i)) return -1;

        std::string filename = p->accessIndex(i);

        if (filename == "") {
            std::cout << "DBUS_ERROR\n";
        }
        else {
            std::cout << filename << "\n";
        }
    }
    else if (input == "add" || input == "a" || input == "-a") {
        std::cin >> arg;
        
        expandFilePath(arg);

        status = p->addFile(arg);
        std::cout << arg << " added " << (status == 0 ? "successfully.\n" : "unsuccessfully.\n");
    }
    else if (input == "remove" || input == "r" || input == "-r") {
        std::cin >> arg;
        if (!isValidIndex(arg, i)) return -1;

        std::string removedFile = "";
        status = p->removeFile(i, removedFile);
        std::cout << "Removed " << removedFile << (status == 0 ? " successfully.\n" : "unsuccessfully.\n");
    }
    else if (input == "verbose" || input == "v" || input == "-v") {
        _isVerbose ^= 1;
        std::cout << "Verbose is " << _isVerbose << "\n";
    }
    else if (input == "command" || input == "c" || input == "-c") {
        std::getline(std::cin, line);
        execCmd(line);

    }
    else if (std::cin.eof()) {
        return -1;
    }

    return 0;
}


int Controller::execCmd(std::string line)
{
    if (line[0] == ' ') StringUtils::stringTrimLeft(line, 1);

    size_t tmp = 0;
    std::string filename;
    bool err = false;
    unsigned int total = p->getItemCount();
    
    // Replace $0 in line with storage[0]
    for (int i = 0; i < total; i++) {
        std::string next = "$" + std::to_string(i);
        tmp = line.find(next);
        if (tmp == std::string::npos) {
            continue;
        }

        filename = p->accessIndex(i);
        if (filename.empty()) {
            std::cout << "empty\n";
            err = true;
            break;
        }

        StringUtils::stringReplace(line, next, filename);
    }

    std::cout << line << "\n";

    if (line.substr(0, 3) == "cd ") {
        std::cout << "cd is a built-in shell cmd. Aborted.\n";
    }
    // Execute commandline
    system(line.c_str());

    return 0;
}


bool Controller::isValidIndex(const std::string s, int &out)
{
    if (!isNumber(s)) return false;

    sscanf(s.c_str(), "%d", &out);

    if (out < 0) {
        return false;
    }

    return true;
}


bool Controller::isNumber(const std::string s)
{
    int start = 0;
    if (s[0] == '-') {
        if (s.length() == 1) return false; // String is only "-"
        start = 1;
    }

    for (int i = start; i < s.length(); i++) {
        if (s[i] < 48 || s[i] > 48 + 9) return false;
    }

    return true;
}


int Controller::processCmd(char opt, int argc, char **argv)
{
    p = new client;
    p->init();

    int status = 0; // operation status
    unsigned int i = 0; // -l access index


    switch(opt)  
    {
        case 'c':
        {
            std::string line = "";

            int index = optind; // optarg, 1 in this case
            while (index < argc) {
                line += " " + std::string(argv[index]);
                index++;
            }
            execCmd(line);

            return -1; // -c treats all following arguments as its eval params
        }
        case 'h':
        {
            showHelp();
            break;
        }
        case 'i':
        {
            /*Access Index*/
            sscanf(optarg, "%u", &i);
            std::string filename = p->accessIndex(i);
            if (filename == "") std::cout << "ERROR\n";
            else std::cout << filename << "\n";
            break;
        }
        case 'l':
        {
            std::string files = "";
            if (_isVerbose) {
                files = p->getFileListVerbose();
            }
            else
            {
                files = p->getFileListSimple();
            }
            
            std::cout << files;
            break;
        }
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
            break;
        }
        case 'r':
        {
            sscanf(optarg, "%d", &i);

            std::string removedFile = "";
            status = p->removeFile(i, removedFile);
            std::cout << "Removed " << removedFile << (status == 0 ? " successfully.\n" : "unsuccessfully.\n") << ".\n";
            break;
        }
        case 'v':
            break;
    }


    p->uinit();
    delete p;

    return 0;
}



int Controller::expandFilePath(std::string &path)
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


void Controller::showHelp()
{
    std::cout << "\
[Commandline file manager]\n\
Author\t\t: sandwichdoge\n\
Parameters\t:\n\
    -a <filepath>\t: Add a file to storage.\n\
    -r <index>\t\t: Remove file at index in storage.\n\
    -l\t\t\t: List files in storage.\n\
    -i <index>\t\t: Print out name of file at index.\n\
    -c <cmd>\t\t: Command to execute, $0 will be replaced with file #0 in storage.\n\
    -v\t\t\t: Verbose.\n\
    -h\t\t\t: Show this help.\n";
}

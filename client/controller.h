#include <string>
#include "dbus_interface.h"


class Controller
{
    public:
        Controller();
        virtual ~Controller();

        int poll();
        int processCmd(char opt, int argc, char *argv[]);

    private:
        client *p;
        bool _isVerbose;

        void showHelp();
        int processInput(client *p, const std::string input);
        int expandFilePath(std::string &path);
        int execCmd(std::string line);
        bool isNumber(const std::string s);
        bool isValidIndex(const std::string s, int &out);
};
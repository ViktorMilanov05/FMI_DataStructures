#include "BrowserHandler.h"

void BrowserHandler::openBrowser()
{
	std::string command;

    while (true) {
        std::getline(std::cin, command);

        if (command.rfind("$ GO ", 0) == 0) {
            std::string url = command.substr(5);
            browser.go(url);
        }
        else if (command.rfind("$ INSERT ", 0) == 0) {
            std::string url = command.substr(9);
            browser.insert(url);
        }
        else if (command == "$ BACK") {
            browser.back();
        }
        else if (command == "$ FORWARD") {
            browser.forward();
        }
        else if (command == "$ REMOVE") {
            browser.remove();
        }
        else if (command == "$ PRINT") {
            browser.print();
        }
        else if (command.rfind("$ SORT ", 0) == 0) {
            std::string url = command.substr(7);
            browser.sortBy(url);
        }
        else {
            break;
        }
    }
}

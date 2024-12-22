#include "BrowserLinkedList.h"

class Browser {
    BrowserLinkedList::DllIterator current;
    Tab defaultTab;
    BrowserLinkedList list;

public:
    Browser() : defaultTab("about:blank") ,current(list.begin()){};

    void go(const std::string& url);

    void insert(const std::string& url);

    void back();
    void forward();
    void remove();
    void print();
    void sortBy(const std::string& by);
};
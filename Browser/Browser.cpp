#include "Browser.h"

void Browser::go(const std::string& url) {
    if (!list.isEmpty()) {
        Tab curr = *current;
        curr.setUrl(url);
        curr.refreshTimestamp();
        *current = curr;
    }
    else {
        Tab toAdd(url);
        current = list.insert(toAdd, current.toConst());
    }
}

void Browser::insert(const std::string& url) {
    Tab toAdd(url);
    current = list.insert(toAdd, current.toConst());
}

void Browser::back() {
    if (current != list.begin())
        current--;
}

void Browser::forward() {
    if (&(*current) != &(list.back()))
        current++;
}

void Browser::remove() {
    if (list.getSize() == 1) {
        list.popBack();
    }
    else if (list.getSize() > 1) {
        current = list.remove(current);
    }
}

void Browser::print() {
    if (list.isEmpty()) {
        std::cout << defaultTab.getUrl() << ' ' << defaultTab.getTimestamp() << std::endl;
    }
    else {
        list.print(current.toConst());
    }
}

void Browser::sortBy(const std::string& by)
{
    if (!list.isEmpty()) {
        current = list.mergeSort(by);
    }
}

#include "Tab.h"

Tab::Tab(const std::string& url) : url(url) {
    timestamp = std::time(nullptr);
}

std::string Tab::getUrl() const {
    return url;
}

time_t Tab::getTimestamp() const {
    return timestamp;
}

void Tab::refreshTimestamp() {
    timestamp = std::time(nullptr);
}

void Tab::setUrl(const std::string& url) {
    this->url = url;
}

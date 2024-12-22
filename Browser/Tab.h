#include <string>
#include <ctime>

class Tab {
private:
    std::string url;
    time_t timestamp;

public:
    Tab(const std::string& url);

    std::string getUrl() const;

    time_t getTimestamp() const;

    void refreshTimestamp();

    void setUrl(const std::string& url);
};
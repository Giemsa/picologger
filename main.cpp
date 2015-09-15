#include <iostream>
#include "picologger.h"

static const char *TAG = "picologger";

// custom formatter
struct CustomFormatter : public picologger::formatters::DefaultFormatter
{
    void format(std::ostream &os, const picologger::LogLevel::Type level, const std::string &str)
    {
        os << TAG << " | ";
        picologger::formatters::DefaultFormatter::format(os, level, str);
    }
};


// Logger wrapper
struct Logger : public picologger::Logger
{
private:
    Logger()
    : picologger::Logger(
        new CustomFormatter(), // use custom formatter
        new picologger::writers::DefaultWriter(std::cout)
    )
    { }
public:
    static Logger &getInstance()
    {
        static Logger logger;
        return logger;
    }
};

int main(int argc, const char * argv[]) {
    Logger::getInstance().info("info level log");
    Logger::getInstance().warn("warning level log");

    // default log level is "LogLevel::Info", so following message is not logged.
    Logger::getInstance().debug("debug level log 1");

    // switch log level
    Logger::getInstance().setLogLevel(picologger::LogLevel::Debug);
    Logger::getInstance().debug("debug level log 2");

    return 0;
}

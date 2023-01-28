#include "include/Logger.h"

int main() {
    const std::string& msg = "Here is some test info to be logged";
    GF::Utils::Logger::log(GF::Utils::Logger::LogType::INFO, msg);
    return 0;
}
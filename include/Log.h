#ifndef LOG_H
#define LOG_H

#include <sstream>

class Log
{
    public:
        static std::stringstream& GetStreamLog();
        static void PrintLog();
        static void ClearLog();
    private:
        static std::stringstream ss;
};

#endif // LOG_H

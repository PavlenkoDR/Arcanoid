#include "Log.h"
#include <iostream>

std::stringstream Log::ss;

std::stringstream& Log::GetStreamLog()
{
    return ss;
}

void Log::PrintLog()
{
    std::cout << ss.str() << std::endl;
}

void Log::ClearLog()
{
    ss.str( "" );
}

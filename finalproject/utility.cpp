#include "utility.h"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <direct.h>
    #include <windows.h>
#elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
    #include <unistd.h>
    #include <term.h>
#endif // defined


std::string tt::capitalize(const std::string& str)
{
    std::string s = str;
    for (int i = 0, lim = s.size(); i < lim; ++i)
        s[i] = toupper(s[i]);
    return s;
}

int tt::makeFolder(const std::string& s)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        return _mkdir(s.c_str());
    #elif __APPLE__
        #include <TargetConditionals.h>
        #if TARGET_IPHONE_SIMULATOR
            return 65;
        #elif TARGET_OS_IPHONE
            return 66;
        #elif TARGET_OS_MAC
            return mkdir(s.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
        #else
            #error "Unknown Apple platform"
        #endif
    #elif __linux__
        return mkdir(s.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
    #elif __unix__
        return 31;
    #elif defined(_POSIX_VERSION)
        return 32;
    #else
    #   error "Unknown compiler"
    #endif

    return 0;
}

bool tt::makeDir(const std::string& dir)
{
    size_t pos;
    if (dir[0] == '.') pos = dir.find('/', dir.find('/') + 1);
    else pos = dir.find('/') + 1;
    while (pos < std::string::npos) {
        if (makeFolder(dir.substr(0, pos)) == 0);
        pos = dir.find('/', pos + 1);
    }
    if (makeFolder(dir) == 0) return true;
    return false;
}

void tt::clearConsole()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        COORD topLeft  = { 0, 0 };
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        SetConsoleCursorPosition(console, topLeft);
    #elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
        if (!cur_term) {
            int result;
            setupterm(NULL, STDOUT_FILENO, &result);
            if (result <= 0) return;
        }
        putp(tigetstr( "clear" ));
    #endif // defined
}

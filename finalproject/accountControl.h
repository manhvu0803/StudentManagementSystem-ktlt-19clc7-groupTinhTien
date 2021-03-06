#ifndef ACCOUNTCONTROL_H_INCLUDED
#define ACCOUNTCONTROL_H_INCLUDED

#include <string>
#include "dataStructure.h"
#include "utility.h"

namespace acc
{
    using namespace std;

    struct account
    {
        string username;
        string password;
        string id;
        int type; // 1 is student, 2 is lecturer, 3 is academic staff
    };

    void saveToFile();

    string createUsername(string name);

    bool createAccount(const tt::lecturer& user);
    bool createAccount(const tt::student& user);

    bool removeAccount(string id);

    account* login();

    void changePassword(account* user);

    void showProfile(account user);
}

void schedule(tt::date t, int y, int id);

#endif // ACCOUNTCONTROL_H_INCLUDED

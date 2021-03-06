#include <iostream>
#include <limits>
#include <chrono>
#include <ctime>
#include "accountControl.h"
#include "class.h"
#include "academicYear.h"
#include "scoreboard.h"
#include "lecturer.h"

using namespace std;

int main()
{
    acc::account* user = acc::login();

    int choice;
    while (user) {
        tt::clearConsole();
        cout << "Welcome to Tinh Tien's Student Management System\n";
        cout << "Please log out before closing the program\n\n";
        cout << "Please choose an option:\n";
        cout << "Enter 1: View profile\n";
        cout << "Enter 2: Change password\n";
        if (user->type == 1) {
            cout << "Enter 3: Check in and view scoreboard\n";
            cout << "Enter 4: View schedule\n";
        }
        else if (user->type > 1) {
            cout << "Enter 3: Course menu\n";
            cout << "Enter 4: Attendance and score menu\n";
            if (user->type > 2) cout << "Enter 5: Class menu\n";
        }
        cout << "Enter 0: Log out\n\n";

        cout << "Your choice: ";
        if (!tt::cinIg(cin, choice)) choice = -1;

        tt::clearConsole();
        switch (choice) {
            case 0:
                acc::saveToFile();
                tt::clearConsole();
                user = acc::login();
                break;
            case 1:
                acc::showProfile(*user);
                cout << "\nPress Enter to continue...";
                getchar();
                break;
            case 2:
                acc::changePassword(user);
                break;
            case 3:
                if (user->type == 1) MainForScoreboardandAttendance(user->id, 1);
                else academicYearMenu(user->type);
                break;
            case 4:
                if (user->type == 1) {
                    tt::date now = tt::currentDate();
                    cout << "Your schedule:\n";
                    schedule(now, now.y - 1, stoi(user->id));
                    schedule(now, now.y, stoi(user->id));
                    getchar();
                }
                else {
                    ltr lec;
                    string name = lec.get(user->id).fullName;
                    MainForScoreboardandAttendance(name, user->type);
                }
                break;
            case 5:
                if (user->type == 1);
                else if (user->type > 2) {
                    clss cl;
                    cl.menu();
                }
                break;
            case 6:
            default:
                cout << "\nInvalid choice\n";
        }
        cout << "\n";
    }

    delete user;

    return 0;
}


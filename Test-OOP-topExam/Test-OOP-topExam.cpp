
#include <iostream>
#include <list>
#include <conio.h>
#include"Test.h"

int Menu(std::list<std::string>& punkts)
{
    int num = -1;
    if (!punkts.empty())
    {
        int active = 1;
        int key = 0;
        while (key != 13)
        {
            num = 1;
            system("cls");
            std::cout << "\n\t\tMenu";
            for (auto p = punkts.begin(); p != punkts.end(); p++)
            {
                if (active == num)
                    std::cout << "\x1b[30;47m";
                std::cout << "\n\t#" << num << ". " << *p;
                if (active == num)
                    std::cout << "\x1b[0m";
                num++;
            }
            key = _getch();
            if (key == 224)
                key = _getch();
            switch (key)
            {
            case 72:
                active--;
                if (active < 1)
                    active = punkts.size();
                break;
            case 80:
                active++;
                if (active > punkts.size())
                    active = 1;
                break;
            case 13:
                return active;
            }
        }
    }
}

int main()
{
    std::list<std::string> menuPunkts{
        "Load test",
        "Add question",
        "Pass test",
        "Show results",
        "Teacher mode",
        "Exit"
    };
    switch (Menu(menuPunkts))
    {
    case 1:
        break;
    }
    Test tst;
    tst.ReadFromFile("questions.tst");
    tst.WriteToFile("writetest.txt");
    //tst.PassTst();
    //tst.ResultDisplay();
    //tst.Show();
}


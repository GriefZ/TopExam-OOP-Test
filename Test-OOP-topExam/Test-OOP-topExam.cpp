
#include <iostream>
#include <list>
#include <conio.h>
#include"Test.h"

int Menu(std::string ttl, std::list<std::string>& punkts)
{
	int num = -1;
	if (!punkts.empty())
	{
		size_t active = 1;
		int key = 0;
		while (key != 13)
		{
			num = 1;
			system("cls");
			std::cout << "\n\t\t" << ttl;
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
				break;
			}
		}
		return active;
	}
}

int main()
{
	bool teacherMode = false;
	bool quit = false;
	Test tst;
	std::string fileName = "questions.tst";
	do
	{
		std::list<std::string> menuPunkts{
		"Load test",
		"Pass test",
		"Show results",
		"Teacher mode",
		"Exit"
		};
		switch (Menu("Test", menuPunkts))
		{
		case 1:
			if (tst.Empty())
				tst.ReadFromFile(fileName);
			else
				std::cout << "\nTest is already loaded!";
			system("pause");
			break;

		case 2:
			tst.PassTst();
			system("pause");
			break;
		case 3:
			if (tst.Passed())
				tst.ResultDisplay();
			else
				std::cout << "\nThere is nothing to show!\nPass the test first.";
			system("pause"); 
			break;
		case 4:
		{
			std::cout << "\nPassword: ";
			std::string pswrd;
			std::getline(std::cin, pswrd);
			if (pswrd == "pswrd")
			{
				teacherMode = true;
				std::list<std::string> teacherMenu{
				"Load new test",
				"Add question",
				"Show test",
				"Save Test",
				"Exit from teacher mode"
				};
				do
				{
					switch (Menu("Teacher Mode", teacherMenu))
					{
					case 1:
					{
						std::string fn;
						std::cout << "Enter filename -> ";
						std::getline(std::cin, fn);
						tst.ReadFromFile(fn);
						system("pause");
						break;

					}
					case 2:
						tst.InputQstn();
						break;
					case 3:
						tst.Show(teacherMode);
						break;
					case 4:
					{
						std::string fn;
						std::cout << "Enter filename -> ";
						std::getline(std::cin, fn);
						tst.ReadFromFile(fn);
						system("pause");
						tst.WriteToFile(fn);
						break;
					}
					case 5:
						teacherMode = false;
					}

				} while (teacherMode);
			}
			else
			{
				std::cout << "\nInvalid!";
				system("pause");
			}
			break;
		}
		case 5:
			quit = true;
			break;
		}
	} while (!quit);


	tst.WriteToFile("writetest.txt");

}


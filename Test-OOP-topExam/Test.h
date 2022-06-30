#pragma once
#include <fstream>
#include <algorithm>
#include "TestQuestion.h"

class Test
{
	std::vector<TestQuestion> m_questions;
	int m_maxPoints;
	bool m_adminMode = true;//Убрать потом
	bool m_passed = false;
	std::string m_student;

public:

	class Cir1251to866
	{
	public:
		void operator()(char& inp1251)
		{
			if ((unsigned char)inp1251 > 191 && (unsigned char)inp1251 < 240)
				inp1251 -= 64;
			else if ((unsigned char)inp1251 > 239)
				inp1251 -= 16;
			else if ((unsigned char)inp1251 == 168)
				inp1251 += 72;
			else if ((unsigned char)inp1251 == 184)
				inp1251 += 57;
		}
	};

	class Cir866to1251
	{
	public:
		void operator()(char& inp866)
		{
			if ((unsigned char)inp866 > 127 && (unsigned char)inp866 < 176)
				inp866 += 64;
			else if ((unsigned char)inp866 > 223 && (unsigned char)inp866 < 240)
				inp866 += 16;
			else if ((unsigned char)inp866 == 240)
				inp866 -= 72;
			else if ((unsigned char)inp866 == 241)
				inp866 -= 57;
		}
	};

	Test() :
		m_questions{ std::vector<TestQuestion>() },
		m_maxPoints{ 0 },
		m_passed{false},
		m_student{"none"}
	{}

	Test& InputQstn()
	{
		std::string tempStr;
		TestQuestion tempQstn;
		bool answIsCorr = false;
		rsize_t answSize = 0;
		std::cout << "Input question -> ";
		std::getline(std::cin, tempStr);
		tempQstn.EditQstn(tempStr);
		do
		{
			do
			{
				bool invalidInput = false;
				std::cout << "\nInput answers(if answer is correct last character must be \"+\" , if not \"-\" after input last answer input \"#\"" <<
					"\nExample:\n Q: Who say \"Woof\"?.\n Cat.-\n Dog.+ \n Bulldog.+\n Bobtail.- \n # \n -> ";
				do
				{
					invalidInput = false;
					std::getline(std::cin, tempStr);
					answSize = tempStr.size() - 1;
					if (tempStr.size() > 1 && tempStr[answSize] == '+')
						answIsCorr = true;
					else if (tempStr.size() > 1 && tempStr[answSize] == '-')
						answIsCorr = false;
					else
					{
						std::cout << "\nIncorrect! Try again.\n";
						invalidInput = true;
					}
				} while (invalidInput);
				if (tempStr != "#")
				{
					tempStr.resize(answSize);
					tempQstn.AddAnswr(tempStr, answIsCorr);
				}
			} while (tempStr != "#");
			std::cout << "\nInput points for this question -> ";
			std::getline(std::cin, tempStr);
			tempQstn.SetPoints(std::stoi(tempStr));
			tempQstn.Show(true);
			std::cout << "\nEverything is ok?(y/n) -> ";
			std::getline(std::cin, tempStr);
		} while (tempStr != "y");
		m_questions.push_back(tempQstn);
		m_maxPoints += tempQstn.GetPoints();
	}

	Test& ReadFromFile(std::string fileName)
	{
		std::ifstream f;
		f.open(fileName);
		if (f.is_open())
		{
			m_questions.clear();
			std::string tempStr;
			TestQuestion tempQstn; 
			int nextStr = 0;
			while (!f.eof())
			{
				std::getline(f, tempStr);
				if (tempStr == "<QUESTION>")
					nextStr = 1;
				else if (tempStr == "<ANSWERS>")
					nextStr = 2;
				else if (tempStr == "<POINTS>")
					nextStr = 3;
				else
				{
					std::for_each(tempStr.begin(), tempStr.end(), Cir1251to866());
					switch (nextStr)
					{
					case 1:
						tempQstn.EditQstn(tempStr);
						break;
					case 2:
					{
						size_t answSize = tempStr.size() - 1;
						bool answIsCorr = false;
						if (tempStr.size() > 1 && tempStr[answSize] == '+')
							answIsCorr = true;
						else if (tempStr.size() > 1 && tempStr[answSize] == '-')
							answIsCorr = false;
						tempStr.resize(answSize);
						tempQstn.AddAnswr(tempStr, answIsCorr);
						break;
					}
					case 3:
						tempQstn.SetPoints(std::stoi(tempStr));
						m_questions.push_back(tempQstn);
						tempQstn.Clear();
						break;
					}
				}
			}
			f.close();
			size_t qstCount = m_questions.size();
			for (size_t i = 0; i < qstCount; i++)
			{
				m_maxPoints += m_questions[i].GetPoints();
			}
		}
		else
			std::cout << "\nCan't load file!";
		return *this;
	}

	Test& WriteToFile(std::string fileName)
	{
		std::ofstream f;
		f.open(fileName);
		if (f.is_open())
		{
			size_t qstCount = m_questions.size();
			std::string tmp;
			for (size_t i = 0; i < qstCount; i++)
			{
				std::vector<std::string> qst = m_questions[i].GetQst();
				int qCount = qst.size();
				std::vector<int> crAnsws = m_questions[i].GetCrctAnsw();
				int crCount = crAnsws.size();
				f << "<QUESTION>" << std::endl;
				tmp = qst[0];
				std::for_each(tmp.begin(), tmp.end(), Cir866to1251());
				f << tmp << std::endl;

				f << "<ANSWERS>" << std::endl;
				for (size_t i = 1; i < qCount; i++)
				{
					tmp = qst[i];
					std::for_each(tmp.begin(), tmp.end(), Cir866to1251());
					f << tmp;
					bool crct = false;
					for (size_t k = 0; k < crCount; k++)
					{
						if (crAnsws[k] == i)
							crct = true;
					}
					if (crct)
						f << "+";
					else
						f << "-";
					f << std::endl;
				}
				f << "<POINTS>" << std::endl;
				f << m_questions[i].GetPoints() << std::endl;
			}
		}
		else
		{
			std::cout << "\n\tError! Can't write to file!";
		}
		return *this;
	}

	Test& PassTst()
	{
		if (!m_passed)
		{
			std::string tmp;
			std::cout << "\tWelcome to  test!\n";
			std::cout << "\tInput your name: ";
			std::getline(std::cin, m_student);
			size_t qstCount = m_questions.size();
			for (size_t i = 0; i < qstCount; i++)
			{
				std::cout << "\nQuestion " << i + 1 << "/" << qstCount << " : ";
				m_questions[i].PassQst();
			}
		}
		else
		{
			std::cout << "\nTest is already passed!.";
		}
		return *this;
	}

	Test& ResultDisplay()
	{
		double res = 0;
		size_t qstCount = m_questions.size();
		for (size_t i = 0; i < qstCount; i++)
		{
			res += m_questions[i].Check();
		}
		std::cout.precision(4);
		std::cout << "\nYour score is " << res << "/" << m_maxPoints << "(" << res / (m_maxPoints / 100.0) << "%)." << std::endl;
		return *this;
	}

	void Show()
	{
		if (m_passed)
		{
			size_t qstCount = m_questions.size();
			for (size_t i = 0; i < qstCount; i++)
			{
				std::cout << "\nQuestion " << i + 1 << "/" << qstCount << ": ";
				m_questions[i].Show(m_adminMode);
			}
		}
		else
		{
			std::cout << "\nTest is not passed yet!";
		}
		
	}
};


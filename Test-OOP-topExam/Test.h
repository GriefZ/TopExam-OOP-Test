#pragma once
#include <algorithm>
#include "TestQuestion.h"

class Test
{
	std::vector<TestQuestion> m_questions;
	int m_maxPoints;
	bool m_adminMode = true;//Убрать потом

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
		m_maxPoints{ 0 }
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
		}
		else
			std::cout << "\nCan't load file!";
		return *this;
	}

	void Show()
	{
		for (size_t i = 0; i < m_questions.size(); i++)
		{
			m_questions[i].Show(m_adminMode);
		}
	}
};


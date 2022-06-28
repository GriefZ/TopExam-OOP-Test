#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
class TestQuestion
{
	std::vector<std::string> m_text; // [0] - question, [>0] - answers
	std::vector<int> m_usrAnsw; // indexes of user answers
	std::vector<int> m_crctAnsw; // indexes of correct answers
	int m_points;
public:

	TestQuestion(std::vector<std::string> t, std::vector<int> ua, std::vector<int> ca, int p) :
		m_text{ t },
		m_usrAnsw{ ua },
		m_crctAnsw{ ca },
		m_points{ p }
	{}

	TestQuestion() :
		TestQuestion(std::vector<std::string>({ "Empty" }), std::vector<int>(0), std::vector<int>(0), 0)
	{}

	TestQuestion& EditQstn(std::string q)
	{
		m_text[0] = q;
		return *this;
	}

	TestQuestion& AddAnswr(std::string a, bool crct)
	{
		if (m_text[0] != "Empty")
			m_text.push_back(a);
		if (crct)
			m_crctAnsw.push_back(m_text.size() - 1);
		return *this;
	}

	TestQuestion& SetPoints(int p)
	{
		m_points = p;
		return *this;
	}

	int GetPoints()
	{
		return m_points;
	}

	TestQuestion& Show(bool teacherMode = false)
	{
		std::cout << "\nQuestion: " << m_text[0];
		size_t ci = 0;
		for (size_t i = 1; i < m_text.size(); i++)
		{
			std::cout << "\n" << i << ".";
			if (teacherMode)
			{

				if (ci < m_crctAnsw.size() && i == m_crctAnsw[ci])//Error!!!
				{
					std::cout << "Correct";
					ci++;
				}
				else
					std::cout << "Incorrect";
				std::cout << " answer: ";
			}
			std::cout << m_text[i];
		}
		if (teacherMode)
			std::cout << "\nPoints: " << m_points;
		return *this;
	}

	TestQuestion& Clear()
	{
		TestQuestion t;
		*this = t;
		return *this;
	}
	double Check()
	{
		int caCount = 0;
		for (size_t i = 0; i < m_crctAnsw.size(); i++)
			for (size_t k = 0; k < m_usrAnsw.size(); k)
				if (m_usrAnsw[k] == m_crctAnsw[i])
					caCount++;

		return (double)m_points / caCount;
	}

};


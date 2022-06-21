#pragma once
#include "TestQuestion.h"

class Test
{
	std::vector<TestQuestion> m_questions;
	int m_maxPoints;

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

	Test& ReadFromFile(std::string fileName)
	{

	}
};


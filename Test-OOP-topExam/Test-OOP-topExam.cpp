
#include <iostream>
#include"Test.h"

int main()
{
    Test tst;
    tst.ReadFromFile("questions.tst");
    tst.WriteToFile("writetest.txt");
    //tst.PassTst();
    //tst.ResultDisplay();
    //tst.Show();
}


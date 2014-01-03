//**************************************************************************************************************
// FILE: Main.cpp
//
// DESCRIPTION
// The K1 assembler.
//
// AUTHOR INFORMATION
// Kevin R. Burger [KRB]
//
// Mailing Address:
// Computer Science & Engineering
// School of Computing, Informatics, and Decision Systems Engineering
// Arizona State University
// Tempe, AZ 85287-8809
//
// Email: burgerk@asu
// Web:	  http://kevin.floorsoup.com
//**************************************************************************************************************
#include <iostream>
using std::cout;
using std::endl;

#include "K1as.hpp"

//--------------------------------------------------------------------------------------------------------------
// main()
//--------------------------------------------------------------------------------------------------------------
int main(int pArgc, char *pArgv[])
{
	try {
		cK1as k1as(static_cast<unsigned>(pArgc), pArgv);
	} catch (int e) {
		if (e == cArg::constMissingSrcFname) {
			cout << "usage: k1as srcfile.s" << endl;
		}
	}
	return 0;
}

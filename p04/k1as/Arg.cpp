//**************************************************************************************************************
// CLASS: cArg
//
// DESCRIPTION
// See comments in Arg.hpp.
//
// AUTHOR INFORMATION
// Kevin R. Burger
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
#include "Arg.hpp"

//--------------------------------------------------------------------------------------------------------------
// Ctor.
//--------------------------------------------------------------------------------------------------------------
cArg::cArg(unsigned const pArgc, char **pArgv) :
	mArgc(pArgc),
	mArgv(pArgv),
	mBinFname(""),
	mSrcFname("")
{
	if (pArgc != 2) throw constMissingSrcFname;
	mBinFname = mSrcFname = pArgv[1];
	mBinFname.erase(mBinFname.find_last_of('.'));
}

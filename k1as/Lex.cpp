//**************************************************************************************************************
// CLASS: cLex
//
// DESCRIPTION
// See comments in Lex.hpp.
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
using std::streamsize;

#include <limits>
using std::numeric_limits;

#include "Lex.hpp"

//--------------------------------------------------------------------------------------------------------------
// Ctor.
//
// DESCRIPTION
// Opens pSrcFile for reading.
//--------------------------------------------------------------------------------------------------------------
cLex::cLex(string const& pSrcFile) :
	mSrcIn(pSrcFile.c_str())
{
}

//--------------------------------------------------------------------------------------------------------------
// Dtor.
//
// DESCRIPTION
// Close the input file stream.
//--------------------------------------------------------------------------------------------------------------
cLex::~cLex() {
	mSrcIn.close();
}

//--------------------------------------------------------------------------------------------------------------
// DiscardLine()
//
// DESCRIPTION
// Discards all characters in the input stream until '\n' is reached.
//--------------------------------------------------------------------------------------------------------------
void cLex::DiscardLine()
{
	mSrcIn.ignore(numeric_limits<streamsize>::max(), '\n');
}

//--------------------------------------------------------------------------------------------------------------
// Reset()
//
// DESCRIPTION:
// Resets the stream to the beginning of the file.
//--------------------------------------------------------------------------------------------------------------
void cLex::Reset()
{
	mSrcIn.clear();
	mSrcIn.seekg(0);
}

//--------------------------------------------------------------------------------------------------------------
// Token()
//
// DESCRIPTION
// Returns the next token (i.e., string) from the source file. Comments are discarded.
//
// PSEUDOCODE
// Read from mSrcIn into mToken
// While mSrcIn is in the good state and the first char of mToken is a semicolon Do
//	   Call DiscardLine() to discard the remaining chars on the line
//	   Read from mSrcIn into mToken
// End While
// If mSrcIn is at the eof then return "" else return mToken
//--------------------------------------------------------------------------------------------------------------
string cLex::Token() {
	bool comment;
	do{
		comment = false;
		mToken = "";
		mSrcIn >> mToken;
		if (mToken == "") return "";
		if (mToken[0] == ';') {
			DiscardLine();
			comment = true;
		}
	} while (comment);
	return mToken;
}

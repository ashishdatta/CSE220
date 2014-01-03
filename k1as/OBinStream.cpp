//**************************************************************************************************************
// CLASS: cOBinStream
//
// DESCRIPTION
// See comments in OBinStream.hpp.
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
#include <ios>
using std::ios_base;
using std::streamsize;

#include "OBinStream.hpp"

//==============================================================================================================
// FUNCTION MEMBER DEFINITIONS
//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------
// Ctor.
//
// DESCRIPTION
// Saves the file name, pFname, in mFname. Opens the stream mOut for binary output. Initializes mSize to 0.
//--------------------------------------------------------------------------------------------------------------
cOBinStream::cOBinStream(string const& pFname) :
	mFname(pFname),
	mOut(pFname.c_str(), ios_base::binary),
	mSize(0)
{
}

//--------------------------------------------------------------------------------------------------------------
// Dtor.
//
// PSEUDOCODE
// Ensure the output stream mOut gets closed before this object dies.
//--------------------------------------------------------------------------------------------------------------
cOBinStream::~cOBinStream()
{
	Close();
}

//--------------------------------------------------------------------------------------------------------------
// Close()
//
// PSEUDOCODE
// Close the output stream.
//--------------------------------------------------------------------------------------------------------------
void cOBinStream::Close()
{
	mOut.close();
}

//==============================================================================================================
// NONMEMBER FUNCTION DEFINITIONS
//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------
// operator<<(cOBinStream&, char const)
//
// Write a signed char to the output stream pStream.
//--------------------------------------------------------------------------------------------------------------
cOBinStream& operator<<(cOBinStream& pStream, char const pValue)
{
	pStream.mOut.write(reinterpret_cast<char const *>(&pValue), sizeof(char));
	return pStream;
}

//--------------------------------------------------------------------------------------------------------------
// operator<<(cOBinStream&, char const *)
//
// Write a block of bytes to the output stream pStream.
//
// REMARK
// The cManipSize() manipulator must be sent to pStream before sending the block of bytes.
//--------------------------------------------------------------------------------------------------------------
cOBinStream& operator<<(cOBinStream& pStream, char const *pBlock)
{
	pStream.mOut.write(pBlock, pStream.mSize);
	return pStream;
}

//--------------------------------------------------------------------------------------------------------------
// operator<<(cOBinStream&, int const)
//
// Write a signed int to the output stream.
//--------------------------------------------------------------------------------------------------------------
cOBinStream& operator<<(cOBinStream& pStream, int const pValue)
{
	pStream.mOut.write(reinterpret_cast<char const *>(&pValue), sizeof(int));
	return pStream;
}

//--------------------------------------------------------------------------------------------------------------
// operator<<(cOBinStream&, string const&)
//
// Write a C++ string to the output stream pStream.
//--------------------------------------------------------------------------------------------------------------
cOBinStream& operator<<(cOBinStream& pStream, string const& pValue)
{
	pStream.mOut.write(pValue.c_str(), pValue.length());
	return pStream;
}

//--------------------------------------------------------------------------------------------------------------
// operator<<(cOBinStream&, unsigned char const)
//
// Write an unsigned char to the output stream pStream.
//--------------------------------------------------------------------------------------------------------------
cOBinStream& operator<<(cOBinStream& pStream, unsigned char const pValue)
{
	pStream.mOut.write(reinterpret_cast<char const *>(&pValue), sizeof(unsigned char));
	return pStream;
}

//--------------------------------------------------------------------------------------------------------------
// operator<<(cOBinStream&, unsigned int const)
//
// Write an unsigned int to the output stream pStream.
//--------------------------------------------------------------------------------------------------------------
cOBinStream& operator<<(cOBinStream& pStream, unsigned int const pValue)
{
	pStream.mOut.write(reinterpret_cast<char const *>(&pValue), sizeof(unsigned int));
	return pStream;
}

//--------------------------------------------------------------------------------------------------------------
// operator<<(cOBinStream&, cManipSize)
//
// Sends a cManipSize() manipulator to pStream.
//--------------------------------------------------------------------------------------------------------------
cOBinStream& operator<<(cOBinStream& pStream, cManipSize pSize)
{
	return pSize(pStream);
}

//**************************************************************************************************************
// CLASS: cOBinStream
//
// DESCRIPTION
// cOBinStream is a class that permits writing to binary files using the normal stream insertion operator >>. It
// is essentially a wrapper class around an ofstream object and writes the binary data using the ofstream::write
// function.
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
#ifndef OBINSTREAM_HPP
#define OBINSTREAM_HPP

#include <cstdlib>

#include <fstream>
using std::ofstream;

#include <ios>
using std::streamsize;

#include <stdint.h>

#include <string>
using std::string;

//==============================================================================================================
// FORWARD DECLARATIONS
//==============================================================================================================
class cSize;

//==============================================================================================================
// CLASS: cOBinStream
//==============================================================================================================
class cOBinStream {

friend class cManipSize;
friend cOBinStream& operator<<(cOBinStream& pStream, char const);
friend cOBinStream& operator<<(cOBinStream& pStream, char const *);
friend cOBinStream& operator<<(cOBinStream& pStream, int const);
friend cOBinStream& operator<<(cOBinStream& pStream, string const&);
friend cOBinStream& operator<<(cOBinStream& pStream, unsigned char const);
friend cOBinStream& operator<<(cOBinStream& pStream, unsigned int const);

public:
	//==========================================================================================================
	// PUBLIC FUNCTION MEMBERS
	//==========================================================================================================

	//----------------------------------------------------------------------------------------------------------
	// Ctor.
	//----------------------------------------------------------------------------------------------------------
	cOBinStream(string const& pFname);

	//----------------------------------------------------------------------------------------------------------
	// Dtor.
	//----------------------------------------------------------------------------------------------------------
	~cOBinStream();

	//----------------------------------------------------------------------------------------------------------
	// Close().
	//----------------------------------------------------------------------------------------------------------
	void Close();

private:
	//==========================================================================================================
	// PRIVATE FUNCTION MEMBERS
	//==========================================================================================================

	//----------------------------------------------------------------------------------------------------------
	// Private copy ctor disallows copying of cOBinStream objects.
	//----------------------------------------------------------------------------------------------------------
	cOBinStream(cOBinStream const& pBinStream);

	//----------------------------------------------------------------------------------------------------------
	// Private operator=() disallows assignment of cObinStream objects.
	//----------------------------------------------------------------------------------------------------------
	cOBinStream& operator=(cOBinStream const& pBinary);

	//==========================================================================================================
	// PRIVATE DATA MEMBERS
	//==========================================================================================================

	string	 mFname;
	ofstream mOut;
	streamsize mSize;
};

//==============================================================================================================
// CLASS: cManipSize
//
// This class implements a cOBinStream manipulator that can be used to specify the number of bytes to write
// when writing a block of bytes. Typical usage,
//
// cOBinStream fout("foo.bin");
// char someBytes[] = { 0x00, 0x01, 0x02, 0x03 };
// fout << cManipSize(4) << someBytes;
// fout.close();
//==============================================================================================================
class cManipSize {
public:
	//----------------------------------------------------------------------------------------------------------
	// Ctor. pSize is the number of bytes to be written.
	//----------------------------------------------------------------------------------------------------------
	cManipSize(int pSize) :
		mSize(pSize)
	{
	}

	//----------------------------------------------------------------------------------------------------------
	// Copy ctor.
	//----------------------------------------------------------------------------------------------------------
	cManipSize(cManipSize const& pManip) :
		mSize(pManip.mSize)
	{
	}

	//----------------------------------------------------------------------------------------------------------
	// Dtor.
	//----------------------------------------------------------------------------------------------------------
	~cManipSize()
	{
	}

	//----------------------------------------------------------------------------------------------------------
	// Overloads operator() which sets the mSize data member of pStream to the mSize data member of this
	// manipulator object.
	//----------------------------------------------------------------------------------------------------------
	cOBinStream& operator()(cOBinStream& pStream) const
	{
		pStream.mSize = static_cast<streamsize>(mSize);
		return pStream;
	}
private:
	//----------------------------------------------------------------------------------------------------------
	// operator=()
	//----------------------------------------------------------------------------------------------------------
	cManipSize& operator=(cManipSize const&);

	//----------------------------------------------------------------------------------------------------------
	// mSize is the number of bytes to be written.
	//----------------------------------------------------------------------------------------------------------
	streamsize mSize;
};

//==============================================================================================================
// NONMEMBER FUNCTIONS
//
// Overloaded operator<< prototypes.
//==============================================================================================================

cOBinStream& operator<<(cOBinStream& pStream, char const);
cOBinStream& operator<<(cOBinStream& pStream, char const *);
cOBinStream& operator<<(cOBinStream& pStream, int const);
cOBinStream& operator<<(cOBinStream& pStream, string const&);
cOBinStream& operator<<(cOBinStream& pStream, unsigned char const);
cOBinStream& operator<<(cOBinStream& pStream, unsigned int const);
cOBinStream& operator<<(cOBinStream& pStream, cManipSize pSize);

#endif

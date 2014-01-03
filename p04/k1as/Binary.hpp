//**************************************************************************************************************
// CLASS: cBinary
//
// DESCRIPTION
// Provides a class that writes the binary.
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
#ifndef BINARY_HPP
#define BINARY_HPP

#include "DataSegment.hpp"
#include "OBinStream.hpp"

class cBinary
{
public:
	cBinary(string const& pBinFrame);
	~cBinary(); //deconstructor
	void write(cTextSegment const& pTextSeg, cDataSegment const& pDataSeg); //TODO fix errors here.

private:
	cOBinStream mBinOut; 
	cBinary(cBinary const& pBinary);
	cBinary& operator = (cBinary const& pBinary);

};



#endif
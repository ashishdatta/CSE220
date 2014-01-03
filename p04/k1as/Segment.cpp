//**************************************************************************************************************
// CLASS: cSegment
//
// DESCRIPTION
// See comments in Segment.hpp.
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
#include "Segment.hpp"

//==============================================================================================================
// PUBLIC FUNCTION MEMBERS
//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------
// Default ctor.
//
// IMPORTANT:
// Study the constructors in the cDataSegment and cTextSegment derived classes to see how this ctor gets called.
// Very, very important.
//--------------------------------------------------------------------------------------------------------------
cSegment::cSegment(tAddress const pAddress) :
	mAddress(pAddress)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//--------------------------------------------------------------------------------------------------------------
cSegment::cSegment(cSegment const& pSegment) :
	mAddress(pSegment.mAddress)
{
}

//--------------------------------------------------------------------------------------------------------------
// Dtor.
//--------------------------------------------------------------------------------------------------------------
cSegment::~cSegment()
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy()
//
// DESCRIPTION:
// Makes this cSegment a copy of pSegment.
//--------------------------------------------------------------------------------------------------------------
void cSegment::Copy(cSegment const& pSegment)
{
	mAddress = pSegment.mAddress;
}

//--------------------------------------------------------------------------------------------------------------
// operator=()
//--------------------------------------------------------------------------------------------------------------
cSegment& cSegment::operator=(cSegment const& pSegment)
{
	if (this != &pSegment) Copy(pSegment);
	return *this;
}

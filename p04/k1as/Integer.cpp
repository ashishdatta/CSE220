//**************************************************************************************************************
// CLASS: cInteger
//
// DESCRIPTION
// See comments in Integer.hpp.
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
#include <cstdlib>      // For strol() function.
#include "Integer.hpp"

//--------------------------------------------------------------------------------------------------------------
// Default ctor.
//
// DESCRIPTION:
// Calls the base class Operand::Operand(string const&) ctor. Then converts pValue into an actual int and stores
// the converted int into the mInt data member.
//--------------------------------------------------------------------------------------------------------------
cInteger::cInteger(string const& pValue) :
	cOperand(pValue)
{
	char *end;
	mInt = static_cast<tInt32>(strtol(pValue.c_str(), &end, 10));
}

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//--------------------------------------------------------------------------------------------------------------
cInteger::cInteger(cInteger const& pInteger) :
	cOperand(pInteger),
	mInt(pInteger.mInt)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy()
//--------------------------------------------------------------------------------------------------------------
void cInteger::Copy(cInteger const& pInteger)
{
	cOperand::Copy(pInteger);  // Copy the base class (Operand) data members to this object.
	mInt = pInteger.mInt;	   // Copy the derived class (Integer) data members to this object.
}

//--------------------------------------------------------------------------------------------------------------
// operator=()
//--------------------------------------------------------------------------------------------------------------
cInteger& cInteger::operator=(cInteger const& pInteger)
{
	if (this != &pInteger) Copy(pInteger);
	return *this;
}

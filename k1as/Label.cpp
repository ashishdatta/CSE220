//**************************************************************************************************************
// CLASS: cLabel
//
// DESCRIPTION
// See comments in Label.hpp.
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
#include "Label.hpp"

//==============================================================================================================
// PUBLIC FUNCTION MEMBERS
//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------
// Ctor.
//
// PSEUDOCODE
// Calls the base class cOperand::cOperand(string const&) ctor. Then stores pAddress into mAddress.
//--------------------------------------------------------------------------------------------------------------
cLabel::cLabel(string const& pName, tAddress const pAddress) :
	cOperand(pName),
	mAddress(pAddress)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//--------------------------------------------------------------------------------------------------------------
cLabel::cLabel(cLabel const& pLabel) :
	cOperand(pLabel),
	mAddress(pLabel.Address())
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy()
//
// DESCRIPTION
// Makes this cLabel a copy of pLabel.
//
// PSEUDOCODE
// Copy the base class (cOperand) data members to this cLabel..
// Copy the derived class (cLabel) data members to this cLabel.
//--------------------------------------------------------------------------------------------------------------
void cLabel::Copy(cLabel const& pLabel) {
	cOperand::Copy(pLabel);
	mAddress = pLabel.mAddress;
}

//--------------------------------------------------------------------------------------------------------------
// operator=()
//--------------------------------------------------------------------------------------------------------------
cLabel& cLabel::operator=(cLabel const& pLabel) {
	if (this != &pLabel) Copy(pLabel);
	return *this;
}

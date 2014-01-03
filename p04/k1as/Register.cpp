//**************************************************************************************************************
// CLASS: cRegister
//
// DESCRIPTION
// See comments in Register.hpp.
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
#include "Register.hpp"

//--------------------------------------------------------------------------------------------------------------
// Ctor.
//
// DESCRIPTION:
// Call the base class cOperand::cOperand(string const&) ctor to store the name of the register in the mString
// data member inherited from cOperand.
//--------------------------------------------------------------------------------------------------------------
cRegister::cRegister(string const pName) :
	cOperand(pName)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//--------------------------------------------------------------------------------------------------------------
cRegister::cRegister(cRegister const& pRegister) :
	cOperand(pRegister)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy()
//
// DESCRIPTION
// Makes this Register a copy of pRegister. Since Register has no data members, we simply call cOperand::Copy()
//--------------------------------------------------------------------------------------------------------------
void cRegister::Copy(cRegister const& pRegister)
{
	cOperand::Copy(pRegister);
}

//--------------------------------------------------------------------------------------------------------------
// Encoding()
//
// DESCRIPTION:
// If the name of this register is "%A" we return 0, otherwise we return 1.
//--------------------------------------------------------------------------------------------------------------
tByte cRegister::Encoding() const
{
	return (Name() == "%A") ? 0 : 1;
}

//--------------------------------------------------------------------------------------------------------------
// operator=()
//--------------------------------------------------------------------------------------------------------------
cRegister& cRegister::operator=(cRegister const& pRegister)
{
	if (this != &pRegister) Copy(pRegister);
	return *this;
}

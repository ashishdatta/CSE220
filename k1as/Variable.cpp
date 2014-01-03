//**************************************************************************************************************
// CLASS: cVariable
//
// DESCRIPTION
// See comments in Variable.hpp.
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
#include "Variable.hpp"

//--------------------------------------------------------------------------------------------------------------
// Ctor.
//
// PSEUDOCODE
// Write a member initialization list to call the cOperand class constructor and pass pName as the parameter, to
// initialize mAddress to pAddress, and to initialize mInitValue to pInitValue. The body of the constructor is
// empty.
//--------------------------------------------------------------------------------------------------------------
cVariable::cVariable(string const& pName, tAddress const pAddress, tWord const pInitValue) :
	cOperand(pName),
	mAddress(pAddress),
	mInitValue(pInitValue)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//--------------------------------------------------------------------------------------------------------------
cVariable::cVariable(cVariable const& pVariable) :
	cOperand(pVariable),
	mAddress(pVariable.Address()),
	mInitValue(pVariable.InitValue())
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy()
//
// DESCRIPTION
// Makes this cVariable a copy of pVariable.
//
// PSEUDOCODE
// Copy the base class (Operand) data members to this Variable.
// Copy the derived class (Variable) data members to this Variable.
//--------------------------------------------------------------------------------------------------------------
void cVariable::Copy(cVariable const& pVariable) {
	cOperand::Copy(pVariable);
	mInitValue = pVariable.InitValue();
	mAddress = pVariable.Address();
}

//--------------------------------------------------------------------------------------------------------------
// operator=()
//--------------------------------------------------------------------------------------------------------------
cVariable& cVariable::operator=(cVariable const& pVariable) {
	if (this != &pVariable) Copy(pVariable);
	return *this;
}

//**************************************************************************************************************
// CLASS: cOperand (abstract)
//
// DESCRIPTION
// cOperand represents an operand in an assembly language instruction. It is the base class of the cInteger,
// cLabel, cRegister, and cVariable classes.
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
#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string>
using std::string;

#include "Types.hpp"

//==============================================================================================================
// CLASS: cOperand
//==============================================================================================================
class cOperand {

public:
	//==========================================================================================================
	// PUBLIC FUNCTION MEMBERS
	//==========================================================================================================

	//---------------------------------------------------------------------------------------------------------
	// Ctor.
	//---------------------------------------------------------------------------------------------------------
	cOperand(string const& pString);

	//---------------------------------------------------------------------------------------------------------
	// Copy ctor.
	//---------------------------------------------------------------------------------------------------------
	cOperand(cOperand const& pOperand);

	//---------------------------------------------------------------------------------------------------------
	// Dtor.
	//
	// REMARK
	// Note that this dtor is pure virtual: it is a virtual function and the "= 0" part makes it a pure virtu-
	// al function. A class with at least one pure virtual function is an abstract class. Note also that pure
	// virtual functions cannot be defined in the class declaration (I don't know if that is a C++ rule or a
	// GNU g++ hangup).
	//---------------------------------------------------------------------------------------------------------
	virtual ~cOperand() = 0;

	//---------------------------------------------------------------------------------------------------------
	// operator=()
	//---------------------------------------------------------------------------------------------------------
	cOperand& operator=(cOperand const& pOperand);

	//---------------------------------------------------------------------------------------------------------
	// String()
	//
	// DESCRIPTION
	// Accessor function for mString.
	//---------------------------------------------------------------------------------------------------------
	string String() const
	{
		return mString;
	}

	//---------------------------------------------------------------------------------------------------------
	// String(string const&)
	//
	// DESCRIPTION
	// Mutator function for mString.
	//---------------------------------------------------------------------------------------------------------
	void String(string const& pString)
	{
		mString = pString;
	}

protected:
	//==========================================================================================================
	// PROTECTED FUNCTION MEMBERS:
	//==========================================================================================================

	//---------------------------------------------------------------------------------------------------------
	// Copy()
	//---------------------------------------------------------------------------------------------------------
	void Copy(cOperand const& pOperand);

private:
	//==========================================================================================================
	// PRIVATE DATA MEMBERS:
	//==========================================================================================================

	// All operands are stored as a string. For an Integer operand, the string will be a string representation
	// of the integer, e.g., something like "-231". For a Label operand, the string will be the name of the
	// label. For a Register operand, the string will be the register, either "%A" or "%B". For a Variable
	// operand, the string will be the name of the variable.

	string mString;
};

#endif

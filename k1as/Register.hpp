//**************************************************************************************************************
// CLASS: cRegister (derived from cOperand)
//
// DESCRIPTION
// Decalres a class that represents a register operand in an instruction. cRegister is derived from cOperand,
// i.e., a cRegister is a type of cOperand.
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
#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <string>
using std::string;

#include "Operand.hpp"

//==============================================================================================================
// CLASS: Register
//==============================================================================================================
class cRegister : public cOperand {

public:
	//==========================================================================================================
	// PUBLIC FUNCTION MEMBERS
	//==========================================================================================================

	//---------------------------------------------------------------------------------------------------------
	// Default ctor.
	//---------------------------------------------------------------------------------------------------------
	cRegister(string const pName = "");

	//---------------------------------------------------------------------------------------------------------
	// Copy ctor.
	//---------------------------------------------------------------------------------------------------------
	cRegister(cRegister const& pRegister);

	//---------------------------------------------------------------------------------------------------------
	// Dtor.
	//---------------------------------------------------------------------------------------------------------
	~cRegister()
	{
	}

	//---------------------------------------------------------------------------------------------------------
	// Encoding()
	//---------------------------------------------------------------------------------------------------------
	tByte Encoding() const;

	//---------------------------------------------------------------------------------------------------------
	// Name()
	//
	// DESCRIPTION
	// Returns the name of the register, i.e., either "%A" or "%B".
	//---------------------------------------------------------------------------------------------------------
	string Name() const
	{
		return String();
	}

	//---------------------------------------------------------------------------------------------------------
	// Name(string const&)
	//
	// DESCRIPTION
	// Sets the name of the register.
	//---------------------------------------------------------------------------------------------------------
	void Name(string const& pName)
	{
		String(pName);
	}

	//---------------------------------------------------------------------------------------------------------
	// operator=()
	//---------------------------------------------------------------------------------------------------------
	cRegister& operator=(cRegister const& pRegister);

protected:
	//==========================================================================================================
	// PROTECTED FUNCTION MEMBERS
	//==========================================================================================================

	//---------------------------------------------------------------------------------------------------------
	// Copy()
	//---------------------------------------------------------------------------------------------------------
	void Copy(cRegister const& pRegister);
};

#endif

//**************************************************************************************************************
// CLASS: cInteger (derived from Operand)
//
// DESCRIPTION
// Declares a class that represents Integer operands in assembly language instructions. This class is derived
// from Operand.
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
#ifndef INTEGER_HPP
#define INTEGER_HPP

#include <string>
using std::string;

#include "Operand.hpp"

//==============================================================================================================
// CLASS: cInteger
//==============================================================================================================
class cInteger : public cOperand {

public:
	//==========================================================================================================
	// PUBLIC FUNCTION MEMBERS
	//==========================================================================================================

	//---------------------------------------------------------------------------------------------------------
	// Default ctor.
	//---------------------------------------------------------------------------------------------------------
	cInteger(string const& pValue = "");

	//---------------------------------------------------------------------------------------------------------
	// Copy ctor.
	//---------------------------------------------------------------------------------------------------------
	cInteger(cInteger const& pInteger);

	//---------------------------------------------------------------------------------------------------------
	// Dtor.
	//---------------------------------------------------------------------------------------------------------
	~cInteger()
	{
	}

	//---------------------------------------------------------------------------------------------------------
	// Int()
	//
	// DESCRIPTION
	// Accessof function for mInt.
	//---------------------------------------------------------------------------------------------------------
	tInt32 Int() const
	{
		return mInt;
	}

	//---------------------------------------------------------------------------------------------------------
	// Int(tInt32 const)
	//
	// DESCRIPTION
	// Mutator function for mInt.
	//---------------------------------------------------------------------------------------------------------
	void Int(tInt32 const pInt)
	{
		mInt = pInt;
	}

	//---------------------------------------------------------------------------------------------------------
	// operator=()
	//---------------------------------------------------------------------------------------------------------
	cInteger& operator=(cInteger const& pInteger);

protected:
	//==========================================================================================================
	// PROTECTED FUNCTION MEMBERS
	//==========================================================================================================

	//---------------------------------------------------------------------------------------------------------
	// Copy()
	//---------------------------------------------------------------------------------------------------------
	void Copy(cInteger const& pInteger);

private:
	//==========================================================================================================
	// PRIVATE DATA MEMBERS
	//==========================================================================================================

	tInt32 mInt;
};

#endif

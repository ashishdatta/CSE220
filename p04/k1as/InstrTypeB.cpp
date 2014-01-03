//**************************************************************************************************************
// CLASS: cInstrTypeB
//
// DESCRIPTION
// See comments in InstrTypeB.hpp.
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
#include "InstrTypeB.hpp"

//--------------------------------------------------------------------------------------------------------------
// Default ctor.
//--------------------------------------------------------------------------------------------------------------
cInstrTypeB::cInstrTypeB() :
	mLabel("")
{
}

//--------------------------------------------------------------------------------------------------------------
// Another ctor.
//
// REMARK
// Notice how the base class constructor is called in the member init list.
//--------------------------------------------------------------------------------------------------------------
cInstrTypeB::cInstrTypeB(string const& pMnemonic, cLabel const& pLabel) :
	cInstr(pMnemonic),  // Calls cInstr::cInstr(string const&)
	mLabel(pLabel)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//--------------------------------------------------------------------------------------------------------------
cInstrTypeB::cInstrTypeB(cInstrTypeB const& pInstr) :
	cInstr(pInstr),
	mLabel(pInstr.mLabel)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy()
//
// DESCRIPTION
// Makes this InstrTypeB object a copy of pInstr.
//--------------------------------------------------------------------------------------------------------------
void cInstrTypeB::Copy(cInstrTypeB const& pInstr)
{
	cInstr::Copy(pInstr);	 // Copy the base class (Instr) data members to this object.
	mLabel = pInstr.mLabel;	 // Copy the derived class (InstrTypeB) data members to this object.
	Encode();                // Encode to put address of new label into mEncoding.
}

//--------------------------------------------------------------------------------------------------------------
// Encode()
//
// DESCRIPTION:
// When a type B instruction is encoded, we first call the base class Encode() function to encode the opcode
// bits. Then we encode the branch target label's address.
//
// IMPORTANT:
// To call a base class overridden function, write baseclassname::functioname(params), e.g.,
//
// class Base {
// public:
//	   ...
//	   Function(int pX) { ... }
//	   ...
// };
//
// class Derived : public Base {
// public:
//	   ...
//	   Function(int pX)
//	   {
//		   Base::Function(pX);  -- Call the Base class Function()
//		   ... do the rest of your thing here
//	   }
//	   ...
// };
//--------------------------------------------------------------------------------------------------------------
void cInstrTypeB::Encode()
{
	cInstr::Encode();
	Encoding(Encoding() | mLabel.Address());
}

//--------------------------------------------------------------------------------------------------------------
// operator=()
//--------------------------------------------------------------------------------------------------------------
cInstrTypeB& cInstrTypeB::operator=(cInstrTypeB const& pInstr)
{
	if (this != &pInstr) Copy(pInstr);
	return *this;
}

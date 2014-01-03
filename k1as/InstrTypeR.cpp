//**************************************************************************************************************
// CLASS: cInstrTypeR
//
// DESCRIPTION
// See comments in InstrTyprR.hpp.
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
#include "InstrTypeR.hpp"
#include "Register.hpp"

//==============================================================================================================
// PUBLIC FUNCTION MEMBERS
//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------
// Default ctor.
//--------------------------------------------------------------------------------------------------------------
cInstrTypeR::cInstrTypeR() :
	mRegister("")
{
}

//--------------------------------------------------------------------------------------------------------------
// Another ctor.
//
// DESCRIPTION
// Since cInstrTypeR is derived from cInstr, then we call the base class ctor cInstr::cInstr(string const&) in
// the member init list to let it initialize the mMnemonic data member. Then we initialize mRegister to
// pRegister (either in the ctor body or in the member init list).
//--------------------------------------------------------------------------------------------------------------
cInstrTypeR::cInstrTypeR(string const& pMnemonic, cRegister const& pRegister) :
	cInstr(pMnemonic),
	mRegister(pRegister)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//--------------------------------------------------------------------------------------------------------------
cInstrTypeR::cInstrTypeR(cInstrTypeR const& pInstr) :
	cInstr(pInstr),
	mRegister(pInstr.mRegister)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy()
//
// DESCRIPTION
// Makes this cInstrTypeR object a copy of pInstr.
//--------------------------------------------------------------------------------------------------------------
void cInstrTypeR::Copy(cInstrTypeR const& pInstr)
{
	cInstr::Copy(pInstr);          // Copy the base class (cInstr) data members to this object.
	mRegister = pInstr.mRegister;  // Copy the derived class (cInstrTypeR) data members to this object.
	Encode();                      // Encode because the register may have changed.
}

//--------------------------------------------------------------------------------------------------------------
// Encode()
//
// DESCRIPTION:
// When a cInstrTypeR is encoded, we first call the base class cInstr::Encode() function to allow it to place
// the opcode bits in the most significant five bits of mEncoding. Then we place the register number in bit
// position 26 of the encoding.
//--------------------------------------------------------------------------------------------------------------
void cInstrTypeR::Encode()
{
	cInstr::Encode();
	Encoding(Encoding() | (mRegister.Encoding() << 26));
}

//--------------------------------------------------------------------------------------------------------------
// operator=()
//--------------------------------------------------------------------------------------------------------------
cInstrTypeR& cInstrTypeR::operator=(cInstrTypeR const& pInstr)
{
	if (this != &pInstr) Copy(pInstr);
	return *this;
}

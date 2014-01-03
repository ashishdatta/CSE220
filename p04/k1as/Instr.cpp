//**************************************************************************************************************
// CLASS: cInstr
//
// DESCRIPTION
// See comments in Instr.hpp.
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
#include "Instr.hpp"

//--------------------------------------------------------------------------------------------------------------
// Ctor.
//
// DESCRIPTION
// Initializes mEncoding to 0 and mMnemonic to pMnemonic.
//--------------------------------------------------------------------------------------------------------------
cInstr::cInstr(string const& pMnemonic) :
	mEncoding(0),
	mMnemonic(pMnemonic)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//--------------------------------------------------------------------------------------------------------------
cInstr::cInstr(cInstr const& pInstr) :
	mEncoding(pInstr.mEncoding),
	mMnemonic(pInstr.mMnemonic)
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy()
//
// DESCRIPTION
// Makes this cInstr a copy of pInstr.
//--------------------------------------------------------------------------------------------------------------
void cInstr::Copy(cInstr const& pInstr)
{
	mEncoding = pInstr.mEncoding;
	mMnemonic = pInstr.mMnemonic;
}

//--------------------------------------------------------------------------------------------------------------
// Encode()
//
// DESCRIPTION:
// When a cInstr is encoded, we place the opcode bits in the most significant five bits of mEncoding.
//
// IMPORTANT:
// Note that this function is called by the Encode() function of derived classes. See cInstrTypeB::Encode()
// for example.
//--------------------------------------------------------------------------------------------------------------
void cInstr::Encode()
{
	mEncoding = Opcode() << 27;
}

//--------------------------------------------------------------------------------------------------------------
// Opcode()
//
// DESCRIPTION
// Returns the opcode bits corresponding to the mnemonic.
//--------------------------------------------------------------------------------------------------------------
tByte cInstr::Opcode() const
{
	     if (mMnemonic == "ADD")  return OPCODE_ADD;
	else if (mMnemonic == "BEQ")  return OPCODE_BEQ;
	else if (mMnemonic == "BLT")  return OPCODE_BLT;
	else if (mMnemonic == "BR")   return OPCODE_BR;
	else if (mMnemonic == "BSUB") return OPCODE_BSUB;
	else if (mMnemonic == "HALT") return OPCODE_HALT;
	else if (mMnemonic == "IN")   return OPCODE_IN;
	else if (mMnemonic == "LD")   return OPCODE_LD;
	else if (mMnemonic == "LDA")  return OPCODE_LDA;
	else if (mMnemonic == "LDI")  return OPCODE_LDI;
	else if (mMnemonic == "NEG")  return OPCODE_NEG;
	else if (mMnemonic == "NOR")  return OPCODE_NOR;
	else if (mMnemonic == "OUT")  return OPCODE_OUT;
	else if (mMnemonic == "POP")  return OPCODE_POP;
	else if (mMnemonic == "PUSH") return OPCODE_PUSH;
	else if (mMnemonic == "RET")  return OPCODE_RET;
	else if (mMnemonic == "ROL")  return OPCODE_ROL;
	else if (mMnemonic == "ST")   return OPCODE_ST;
	else return 0xFF;
}

//--------------------------------------------------------------------------------------------------------------
// operator=()
//--------------------------------------------------------------------------------------------------------------
cInstr& cInstr::operator=(cInstr const& pInstr)
{
	if (this != &pInstr) Copy(pInstr);
	return *this;
}

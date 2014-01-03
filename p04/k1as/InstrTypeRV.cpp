//**************************************************************************************************************
// CLASS: cInstrTypeRV
//
// DESCRIPTION
// See comments in InstrTypeRV.hpp.
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
#include "InstrTypeRV.hpp"

cInstrTypeRV::cInstrTypeRV(string const& pMnemonic, cRegister const& pReg, cVariable const& pVar) :
	cInstrTypeR(pMnemonic, pReg),
	mVar(pVar)
{
}

cInstrTypeRV::cInstrTypeRV(cInstrTypeRV const& pInstr) :
	cInstrTypeR(pInstr),
	mVariable(pInstr.mVariable),
{
}

cInstrTypeRV::~cInstrTypeRV()
{
}

cInstrTypeRV::Encode()
{
	cInstrTypeR::Encode();
	Encoding(Encoding | mVariable.Address());
}

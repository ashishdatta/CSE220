#include "InstrTypeRV.hpp"

cInstrTypeRV::cInstrTypeRV() :
	mVariable("")
{
}

cInstrTypeRV::cInstrTypeRV(string const& pMnemonic, cRegister const& pRegister, cVariable const& pVariable) :
	cInstrTypeR(pMnemonic, pRegister),
	mVariable(pVariable)
{
}

cInstrTypeRV::cInstrTypeRV(cInstrTypeRV const& pInstr) :
	cInstrTypeR(pInstr),
	mVariable(pInstr.mVariable)
{
}

void cInstrTypeRV::Encode() {
	cInstrTypeR::Encode();
	Encoding(Encoding() | mVariable.Address());
}

cInstrTypeRV& cInstrTypeRV::operator=(cInstrTypeRV const& pInstr) {
	if (this != &pInstr){
		 Copy(pInstr);
	}
	return *this;
}

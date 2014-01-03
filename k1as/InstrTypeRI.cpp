#include "InstrTypeRI.hpp"

cInstrTypeRI::cInstrTypeRI() :
	mInteger("")
{
}

cInstrTypeRI::cInstrTypeRI(string const& pMnemonic, cRegister const& pRegister, cInteger const& pInteger) :
	cInstrTypeR(pMnemonic, pRegister),
	mInteger(pInteger)
{
}

cInstrTypeRI::cInstrTypeRI(cInstrTypeRI const& pInstr) :
	cInstrTypeR(pInstr),
	mInteger(pInstr.mInteger)
{
}

void cInstrTypeRI::Copy(cInstrTypeRI const& pInstr) {
	cInstrTypeR::Copy(pInstr);
	mInteger = pInstr.mInteger;
	Encode();
}

void cInstrTypeRI::Encode() {
	cInstrTypeR::Encode();
	Encoding(Encoding() | (mInteger.Int() & 0x03ffffff));
}

cInstrTypeRI& cInstrTypeRI::operator=(cInstrTypeRI const& pInstr) {
	if (this != &pInstr) Copy(pInstr);
	return *this;
}

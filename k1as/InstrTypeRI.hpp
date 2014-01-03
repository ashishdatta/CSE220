//**************************************************************************************************************
// CLASS: cInstrTypeRI (derived from cInstrTypeR)
//
// DESCRIPTION
// A type RI instruction is one that encodes a register and an integer. All such instructions are instances of
// this class. cInstrTypeRI is derived from cInstrTypeR.
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
#ifndef INSTRTYPERI_HPP
#define INSTRTYPERI_HPP

#include <string>
using std::string;

#include "Integer.hpp"
#include "Register.hpp"
#include "InstrTypeR.hpp"

class cInstrTypeRI : public cInstrTypeR {

public:
//default ctor
	cInstrTypeRI();
//another ctor
	cInstrTypeRI(string const& pMnemonic, cRegister const& pReg, cInteger const& pInt);
//copy ctor
	cInstrTypeRI(cInstrTypeRI const& pInstr);
//dtor
	virtual ~cInstrTypeRI(){}

	virtual void Encode();
//accessor
	cInteger Integer() const {
		return mInteger;
	}
//overload operator=
	cInstrTypeRI& operator=(cInstrTypeRI const& pInstr);

protected:

	void Copy(cInstrTypeRI const& pInstr);
//mutator
	void Integer(cInteger const& pInteger) {
		mInteger = pInteger;
	}

private:

	cInteger mInteger;

};

#endif

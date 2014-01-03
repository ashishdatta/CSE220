//**************************************************************************************************************
// CLASS: cInstrTypeRV (derived from InstrTypeR)
//
// DESCRIPTION
// An instruction with two operands: a register and a variable.
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
#ifndef INSTRTYPERV_HPP
#define INSTRTYPERV_HPP

#include <string>
using std::string;

#include "InstrTypeR.hpp"
#include "Register.hpp"
#include "Variable.hpp"

class cInstrTypeRV: public cInstrTypeR {

public:
//default ctor
	cInstrTypeRV();
//another ctor
	cInstrTypeRV(string const& pMnemonic, cRegister const& pReg, cVariable const& pVar);
//copy ctor
	cInstrTypeRV(cInstrTypeRV const& pInstr);
//dtor
	virtual ~cInstrTypeRV(){}

	virtual void Encode();
//accessor
	cVariable Variable() const {
		return mVariable;
	}
//overload operator=
	cInstrTypeRV& operator=(cInstrTypeRV const& pInstr);

protected:

	void Copy(cInstrTypeRV const& pInstr){}
//mutator
	void Variable(cVariable const& pVariable) {
		mVariable = pVariable;
	}

private:

	cVariable mVariable;

};

#endif

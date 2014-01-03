//**************************************************************************************************************
// CLASS: cVariable
//
// DESCRIPTION
// Declares a class that represents variable operands in assembly language instructions. This class is derived
// from cOperand. The cOperand class stores the name of the cVariable as a string, and this class adds a tInt32
// data member which is the 2's complement initial value of the cVariable and a tAddress data member which is
// the address of the cVariable within the data segment.
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
#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string>
using std::string;

#include "Types.hpp"
#include "Operand.hpp"

class cVariable: public cOperand {

public:
//ctor
	cVariable(string const& pName = "", tAddress const pAddress = 0, tWord const pInitValue = 0);
//copy ctor
	cVariable(cVariable const& pVariable);
//dtor
	~cVariable(){}
//accessor
	tAddress Address() const {
		return mAddress;
	}
//mutator
	void Address(tAddress const pAddress) {
		mAddress = pAddress;
	}
//accessor
	tInt32 InitValue() const {
		return mInitValue;
	}
//mutator
	void InitValue(tInt32 const pInitValue) {
		mInitValue = pInitValue;
	}
//accessor
	string Name() const {
		return String();
	}
//mutator
	void Name(string const& pName) {
		String(pName);
	}
//overload operator=
	cVariable& operator=(cVariable const& pVariable);
	

protected:

	void Copy(cVariable const& pVariable);

private:

	tAddress mAddress;
	tInt32 mInitValue;
};

#endif	

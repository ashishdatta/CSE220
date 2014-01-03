//**************************************************************************************************************
// CLASS: cLabel
//
// DESCRIPTION
// Declares a class that represents a Label on an assembly language instruction. This class is derived from
// cOperand. The cOperand class stores a string which is the name of the label, and this class adds a tAddress
// data member which is the address in memory of the Label.
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
#ifndef LABEL_HPP
#define LABEL_HPP

#include <string>
using std::string;

#include "Operand.hpp"
#include "Types.hpp"

class cLabel: public cOperand {

public:
//ctor
	cLabel(string const& pName = "", tAddress const pAddress = 0);
//copy ctor
	cLabel(cLabel const& pLabel);
//dtor
	~cLabel(){}
	
//accessor
	tAddress Address() const {
		return mAddress;
	}
//mutator
	void Address(tAddress const pAddress) {
		mAddress = pAddress;
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
	cLabel& operator=(cLabel const& pLabel); 
	

protected:

	void Copy(cLabel const& pLabel);

private:

	tAddress mAddress;
};

#endif

//**************************************************************************************************************
// CLASS: cTextSegment
//
// DESCRIPTION
// Maintains the text segment. The text segment has two data members: a Dictionary (or map) of the labels, and
// a Vector of the instructions. cTextSegment is derived from cSegment.
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
#ifndef TEXTSEGMENT_HPP
#define TEXTSEGMENT_HPP

#include <vector>
using std::vector;

#include <map>
using std::map;

#include "Types.hpp"
#include "Label.hpp"
#include "Instr.hpp"
#include "Segment.hpp"

class cTextSegment: public cSegment {

public:
//ctor
	cTextSegment(tAddress const pAddress = 0);
//copy ctor
	cTextSegment(cTextSegment const& pTextSegment);
//dtor
	~cTextSegment(){}

	void AddInstr(cInstr& pInstr);

	void AddLabel(cLabel const& pLabel);

	tByte const *Contents() const;

	cLabel Label(string const& pName);

	tUint32 Size() const;
//overload operator=
	cTextSegment& operator=(cTextSegment const& pTextSegment);

protected:

	void Copy(cTextSegment const& pTextSegment);

private:

	vector<cInstr>		mInstrs;
	map<string, cLabel>	mLabels;
};

#endif

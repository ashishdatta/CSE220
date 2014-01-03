//**************************************************************************************************************
// CLASS: cDataSegment
//
// DESCRIPTION
// See comments in DataSegment.hpp.
//
// AUTHOR INFORMATION
// Kevin R. Burger
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
#include <algorithm>
using std::find_if;

#include "DataSegment.hpp"

//==============================================================================================================
// PRIVATE PROTOTYPES
//==============================================================================================================

static bool Match(cVariable const& pVariable);

string cDataSegment::mMatchName;

//--------------------------------------------------------------------------------------------------------------
// Default ctor.
//
// IMPORTANT:
// Study this code to see how the base class ctor gets called in the member initialization list. In C++, the
// base class default ctor will be called automatically from the member initialization list, e.g., if you write
// this,
//
// cDataSegment::cDataSegment(tAddress const pAddress)
// {
// }
//
// The compiler generates this,
//
// cDataSegment::cDataSegment(tAddress const pAddress)
//	   : cSegment()	 -- Calls the base class default ctor automatically.
// {
// }
//
// If you wish to call a different ctor, you can, but you have to call it explicitly, AND, it has to be called
// from the member initialization list (i.e., not in the function body).
//--------------------------------------------------------------------------------------------------------------
cDataSegment::cDataSegment(tAddress const pAddress) :
	cSegment(pAddress),  // Calls cSegment::cSegment(tAddress const) rather than cSegment::cSegment()
	mVars()
{
}

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//
// IMPORTANT:
// Make sure you study this code to see how the copy constructor works for a derived class.
//--------------------------------------------------------------------------------------------------------------
cDataSegment::cDataSegment(cDataSegment const& pDataSegment) :
	cSegment(pDataSegment),	   // Call the base class ctor to allow it to copy its data members of pDataSegment
	mVars(pDataSegment.mVars)  // Copy the derived class data members of pDataSegment to this object
{
}

//--------------------------------------------------------------------------------------------------------------
// Add()
//
// <RANT>
// std::vector::push_back() adds the item to the end of the vector. Normal people might call this an append
// operation, but no, apparently push_back is a more descriptive term than append.
// </RANT>
//--------------------------------------------------------------------------------------------------------------
void cDataSegment::Add(cVariable const& pVariable)
{
	mVars.push_back(pVariable);
}

//--------------------------------------------------------------------------------------------------------------
// Contents()
//
// DESCRIPTION
// Returns the contents of the data segment in the binary format to which it will be written to the binary file.
// See the lab project document for a discussion of the binary format of the data segment.
//--------------------------------------------------------------------------------------------------------------
tByte const *cDataSegment::Contents() const
{
	// Dynamically allocate a 1D array of tWords large enough to store the initial values of all of the
	// Variables. The size() function on a map object returns the number of elements in the map.
	tWord *contents = new tWord[mVars.size()];

	// Create a constant iterator over the map mVars. The iterator is const because we are not going to
	// be modifying the Variable objects as we iterate over them. If you want to create a non-const
	// iterator then you would write: std::map<string, cVariable>::iterator it = mVars.begin();
	std::vector<cVariable>::const_iterator it = mVars.begin();

	// Iterate over each element of the map.
	for (unsigned varNum = 0; it != mVars.end(); ++it, ++varNum) {

		// 'it' is a pointer to a vector element, i.e., 'it' points to a cVariable object. Therefore, *it is
		// the cVariable object itself. To get the initial value of the variable, we call InitValue() on the
		// cVariable object. Note: the initial value is stored in 2's complement notation (to handle negative
		// initial values) so the data type returned is tInt32 rather than tWord (tWord is an unsigned data
		// type).
		tInt32 initValue = it->InitValue();

		// Put the initial value of the variable into the contents array at the proper index.
		contents[varNum] = initValue;
	}

	// Return the dynamically allocated array type casted as an array of constant tBytes. Note that the
	// Binary::Write() function deallocates this array.
	return reinterpret_cast<tByte const *>(contents);
}

//--------------------------------------------------------------------------------------------------------------
// Copy()
//
// DESCRIPTION:
// Makes this cDataSegment object a copy of pDataSegment.
//--------------------------------------------------------------------------------------------------------------
void cDataSegment::Copy(cDataSegment const& pDataSegment)
{
	// Call the base class (cSegment) Copy() function to copy the data members inherited from cSegment.
	cSegment::Copy(pDataSegment);

	// Copy the derived class (cDataSegment) data members. This assignment invokes std::vector:::operator=()
	// on mVars and passes pDataSegment.mVars as the parameter.
	mVars = pDataSegment.mVars;
}

//--------------------------------------------------------------------------------------------------------------
// operator=()
//--------------------------------------------------------------------------------------------------------------
cDataSegment& cDataSegment::operator=(cDataSegment const& pDataSegment)
{
	if (this != &pDataSegment) Copy(pDataSegment);
	return *this;
}

//--------------------------------------------------------------------------------------------------------------
// Size()
//
// DESCRIPTION:
// Reads the number of bytes the data segment will consume when written to the binary file. Each variable is
// 4 bytes in the binary and the data segment header takes 9 bytes. Therefore the size of the data segment is
// 9 + 4 * (number of variables).
//--------------------------------------------------------------------------------------------------------------
tUint32 cDataSegment::Size() const
{
	return 9 + 4 * mVars.size();
}

//--------------------------------------------------------------------------------------------------------------
// Variable()
//
// REMARK
// std::find_if (declared in <algorithm>) is a function that we can use to search the vector mVars for a vari-
// able named pName, see: http://cplusplus.com/reference/algorithm/find_if/
//--------------------------------------------------------------------------------------------------------------
cVariable cDataSegment::Variable(string const& pName)
{
	cDataSegment::mMatchName = pName;
	vector<cVariable>::iterator it = find_if(mVars.begin(), mVars.end(), Match);
	return *it;
}

//--------------------------------------------------------------------------------------------------------------
// Match()
//--------------------------------------------------------------------------------------------------------------
static bool Match(cVariable const& pVariable)
{
	return pVariable.Name() == cDataSegment::MatchName();
}

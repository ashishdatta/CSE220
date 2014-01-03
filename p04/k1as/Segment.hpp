//**************************************************************************************************************
// CLASS: cSegment
//
// DESCRIPTION
// Base class for the cDataSegment and cTextSegment derived classes. This is an abstract class, and objects of
// this class cannot be instantiated.
//
// In C++ a class is made abstract by declaring at least one "pure virtual" function, e.g.,
//
// class AbstractClass {
// public:
//	   AbstractClass();				   -- The default ctor. Not virtual (ctors cannot be virtual).
//	   virtual ~AbstractClass() = 0;   -- A pure virtual function. Makes this an abstract class.
//	   virtual SomeFunction();		   -- A virtual function. Must be overridden in a derived class.
//	   ...
// };
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
#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "Types.hpp"

//==============================================================================================================
// CLASS: cSegment
//==============================================================================================================
class cSegment {

public:
	//==========================================================================================================
	// PUBLIC FUNCTION MEMBERS
	//==========================================================================================================

	//---------------------------------------------------------------------------------------------------------
	// Default ctor.
	//---------------------------------------------------------------------------------------------------------
	cSegment(tAddress const pAddress = 0);

	//---------------------------------------------------------------------------------------------------------
	// Copy ctor.
	//---------------------------------------------------------------------------------------------------------
	cSegment(cSegment const& pSegment);

	//----------------------------------------------------------------------------------------------------------
	// Dtor.
	//
	// REMARK
	// See the comments in the source file header comment block concerning virtual and pure virtual functions.
	// Read about abstract classes and pure virtual functions in your textbook.
	//
	// REMARK
	// Even though this function does nothing (see the definition in the Segment.cpp file), when I tried to in-
	// line it here by writing the function definition, the GNU C++ compiler barfed. I don't know if that is
	// because pure virtual functions cannot be defined in a class declaration, per the C++ Standard, or if
	// it cannot be inlined because of the GNU C++ compiler.
	//----------------------------------------------------------------------------------------------------------
	virtual ~cSegment() = 0;

	//----------------------------------------------------------------------------------------------------------
	// Address()
	//
	// DESCRIPTION
	// Accessor function for mAddress.
	//----------------------------------------------------------------------------------------------------------
	tAddress Address() const
	{
		return mAddress;
	}

	//----------------------------------------------------------------------------------------------------------
	// Address(tAddress const)
	//
	// DESCRIPTION
	// Mutator function for mAddress.
	//----------------------------------------------------------------------------------------------------------
	void Address(tAddress const pAddress)
	{
		mAddress = pAddress;
	}

	//----------------------------------------------------------------------------------------------------------
	// Contents()
	//
	// REMARK
	// Another virtual function. Must be overridden (implemented) in a derived class or that derived class will
	// also be abstract. This function does not need to be pure (one pure virtual function is sufficient to make
	// a class abstract, and the destructor has already been declared pure virtual, but I go all out).
	//----------------------------------------------------------------------------------------------------------
	virtual tByte const *Contents() const = 0;

	//----------------------------------------------------------------------------------------------------------
	// Size()
	//
	// REMARK
	// Another virtual function. Must be overridden (implemented) in a derived class or that derived class will
	// also be abstract. This function does not need to be pure (one pure virtual function is sufficient to make
	// a class abstract, and the destructor has already been declared pure virtual, but I go all out).
	//----------------------------------------------------------------------------------------------------------
	virtual tUint32 Size() const = 0;

	//----------------------------------------------------------------------------------------------------------
	// operator=()
	//----------------------------------------------------------------------------------------------------------
	cSegment& operator=(cSegment const& pSegment);

protected:
	//==========================================================================================================
	// PROTECTED FUNCTION MEMBERS
	//==========================================================================================================

	//----------------------------------------------------------------------------------------------------------
	// Copy()
	//----------------------------------------------------------------------------------------------------------
	void Copy(cSegment const& pSegment);

private:
	//==========================================================================================================
	// PRIVATE DATA MEMBERS
	//==========================================================================================================

	// A segment is stored at an address. This data member is inherited by the cDataSegment and cTextSegment
	// classes. Therefore, each cDataSegment and cTextSegment is stored at an address.
	tAddress mAddress;
};

#endif

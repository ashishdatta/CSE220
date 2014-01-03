//**************************************************************************************************************
// CLASS: cTextSegment
//
// DESCRIPTION
// See comments in TextSegment.hpp.
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
#include "TextSegment.hpp"

//--------------------------------------------------------------------------------------------------------------
// Default ctor.
//
// PSEUDOCODE
// In the member init list, call the base class cSegment::cSegment(tAddress const) ctor to initialize the
// mAddress data member. Init mInstrs and mLabels by calling the default ctors of each of those classes.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//
// PSEUDOCODE
// In the member init list, call the base class copy ctor to initiliaze the data members inherited from the base
// class. Then initialize mInstrs and mLabels to the corresponding data members of pSeg.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Add()
//
// DESCRIPTION:
// Encodes the cInstr parameter pInstr and then appends the encoded cInstr to the mInstrs vector.
//
// PSEUDOCODE
// Call Encode() on pInstr to encode the instruction.  -- Note: this is a polymorphic function call. Why?
// Add pInstr to the mInstrs vector (hint: the function is push_back).
//
// NOTES:
// The input parameter pInstr is a reference to a cInstr, but remember that cInstr has several derived classes,
// in particular cInstrTypeB, cInstrTypeR, cInstrTypeRI, and cInstrTypeRV. Since a base class reference can
// actually be a reference to derived class object (the same is true of base and derived class pointers) the
// compiler has no way of knowing in this function if pInstr is really a reference to a cInstr object or a ref-
// erence to, perhaps, a cInstrTypeRV object. Therefore, when we call pInstr.Encode() we need to make a polymor-
// phic call because if pInstr is a reference to a cInstr object then we need to call cInstr::Encode() but if
// pInstr is really a reference to a cInstrTypeRV object then we need to call cInstrTypeRV::Encode(). Therefore,
// if you look in the cInstr class hierarchy, Encode() is declared as a "virtual" function in each class declara-
// tion.
//
// If Encode() were not virtual and pInstr was really a reference to a cInstrTypeRV object and we call
// pInstr.Encode() then the compiler would generate code to call cInstr::Encode() which IS NOT THE FUNCTION
// THAT SHOULD BE CALLED.
//
// C++ is different from Java in this context. In Java, all function calls are dynamically-bound, i.e., the
// compiler generates code to determine which function to call at runtime. In C++, function calls are, by
// default, statically-bound, i.e., the compiler always generates code to call the function in the class
// of which the object is a member of. To tell the compiler that a function should be dynamically-bound, the
// function is declared in the base class as virtual. If the polymoprhism should "go down" in the hierarchy
// tree, then derived classes of the base class should also declared the function as virtual.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Add()
//
// DESCRIPTION
// Adds a new label pLabel to the mLabels dictionary. The key is pLabel.GetName() and the value is pLabel.
// Hint: look at DataSegment::AddVariable().
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Contents()
//
// DESCRIPTION
// Dynamically allocates a tByte array large enough to store all of the instructions. mInstrs.size() is the
// number of instructions in the mInstrs vector, and since each instruction is encoded using four bytes, the
// size of the array is mInstrs.size() * 4. Hint: see the Contents() function in the DataSegment class.
//
// PSEUDOCODE
// Dynamically allocate a 1D array (named 'contents') of tWord of size mInstrs.size().
// Create a constant iterator (named 'it') over the mInstrs vector.
// For (offset = 0; while 'it' has not reached the end of the vector; ++it, ++offset) Do
//	   tWord encoding <- it->Encoding()
//	   memcpy(&contents[offset], &encoding, sizeof(tWord))
// End For
// Return contents typecasted to "tByte const *".
//
// HINT: Look at DataSegment::Contents(). This function is very, very similar.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Copy()
//
// DESCRIPTION
// Makes this cTextSegment object a copy of cpTextSegment.
//
// PSEUDOCODE
// Call the base class (cSegment) Copy() function and pass pTextSegment as the param.
// Assign pTextSegment.mInstrs to mInstrs.  -- Will invoke std::vector::operator=() on mInstrs
// Assign pTextSegment.mLabels to mLabels.  -- Will invoke std::map::operator=() on mLabels.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Label()
//
// DESCRIPTION
// Retrieves the cLabel object with name pName from the mLabels map.
//
// REMARK
// Since mLabels is a map, to access the value of the mpa with key pName, write:
//
// mLabels[pName]
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Size()
//
// DESCRIPTION:
// Returns the size of the cTextSegment. The size is calculated as:
//
//   1 byte                     Type of segment
// + 4 bytes                    Text segment size
// + 4 bytes                    Address of text segment
// + mInstrs.size() * 4 bytes   Encodings of each instruction
//
// PSEUDOCODE:
// See cDataSegment::Size().
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Overload operator=
//--------------------------------------------------------------------------------------------------------------
???

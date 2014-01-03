//**************************************************************************************************************
// CLASS: cInstrTypeRI
//
// DESCRIPTION
// See comments in InstrTypeRI.hpp.
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
#include "InstrTypeRI.hpp"

//--------------------------------------------------------------------------------------------------------------
// Default ctor.
//
// PSEUDOCODE
// In the member init list call the cInteger::cInteger() default ctor to initialize mInteger.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Another ctor.
//
// PSEUDOCODE
// In the member init list, call the base class cInstrTypeR::cInstrTypeR(string const&, cRegister const&) ctor
// to let it initialize the mMnemonic and mRegister data members that were inherited from cInstr and cInstrTypeR
// Then init mInteger to pInteger.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Copy ctor.
//
// PSEUDOCODE
// In the member init list call the cInstrTypeR copy ctor passing pInstr to permit it to copy the data members
// inherited from pInstr. Then initialize mInteger.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Copy()
//
// DESCRIPTION
// Makes this cInstrTypeRI a copy of pInstr.
//
// PSEUDOCODE
// Copy the base class (cInstrTypeR) data members to this object.
// Copy the derived class (cInstrTypeRI) data members to this object.
// Encode since the mInteger data member has been changed.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Encode()
//
// DESCRIPTION:
// When a cInstrTypeRI is encoded, we first call the base class cInstrTypeR::Encode() function to allow it to
// place the register bit in position 26 (note that cInstrTypeR::Encode() calls cInstr::Encode() to allow that
// function to encode the opcode bits). Then we place the integer bits into the encoding.
//
// PSEUDOCODE
// Call the base class Encode() function to let it encode it's part of the instruction.
// Encode the value of the integer.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// operator=()
//--------------------------------------------------------------------------------------------------------------
???

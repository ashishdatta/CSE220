//**************************************************************************************************************
// CLASS: cBinary
//
// DESCRIPTION
// See comments in Binary.hpp.
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
#include "Binary.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------------------------------------------------------------------
// Ctor.
//
// PSEUDOCODE
// In the member init list, initialize mBinOut with pBinFname. This will open the binary file for writing.
//--------------------------------------------------------------------------------------------------------------
cBinary::cBinary(string const& pBinFrame):
	mBinOut(pBinFrame)
{
	//todo
}
//--------------------------------------------------------------------------------------------------------------
// Dtor.
//
// PSEUDOCODE
// Close the binary file.
//--------------------------------------------------------------------------------------------------------------
cBinary::~cBinary()
{
	mBinOut.Close();
}

//--------------------------------------------------------------------------------------------------------------
// FUNCTION: Binary::Write
//
// DESCRIPTION
// Writes the binary to the file name passed to the ctor. The contents of the data segment pDataSeg is written
// first followed by the contents of the text segment pTextSeg.
//
// PSEUDOCODE
// Note: on input, mBinOut is ready to begin writing data to the file.
// Send the signature bytes "K1BIN" to mBinOut (hint: use cManipSize(5) to specify the number of bytes to write).
// initPC <- address of the text segment.
// Send initPC to mBinOut.
// Send the reserved 0 bytes to mBinOut.
// Send 0 for the type of the segment (data segment) to mBinOut.
// size <- size of the data segment.
// Send size to mBinOut.
// address <- address of the data segment.
// Send address to mBinOut.
// contents <- contents of the data segment.
// Send contents to mBinOut (hint: use cManipSize(size - 9) to specify the number of bytes to write.
// free the contents array.
// Send 1 for the type of the segment (text segment) to mBinOut.
// size <- size of the text segment.
// Send size to mBinOut.
// address <- address of the text segment.
// Send address to mBinOut.
// contents <- contents of the text segment.
// Send contents to mBinOut (hint: use cManipSize(size - 9) to specify the number of bytes to write.
// free the contents array.
//--------------------------------------------------------------------------------------------------------------
void cBinary::write(cDataSegment const& pDataSeg, cTextSegment const& pTextSeg)
{
	
	mBinOut << ("K1BIN"); //Sends signature to mBinOut
	tAddress initPC = pTextSeg.getAddress(); //initPC <- address
	mBinOut << initPC; //Sends address to mBinOut
	mBinOut << 0x00;//Send reserved 0 bytes to mBinOut
	// Send 0 for the type of the segment (data segment) to mBinOut.
	mBinOut << pDataSeg.Size(); // size <- size of the data segment.
	tAddress dataSegAddress = pDataSeg.Address(); // address <- address of the data segment.
	mBinOut << dataSegAddress; // Send address to mBinOut.
	tByte *dataSegContents = pDataSeg.Contents(); // contents <- contents of the data segment.
	mBinOut << cManipSize(pDataSeg.Size() - 9) << reinterpret_cast <char *>(dataSegContents);// Send contents to mBinOut (hint: use cManipSize(size - 9) to specify the number of bytes to write.
	delete dataSegContents; // free the contents array.
	mBinOut << 0x01; // Send 1 for the type of the segment (text segment) to mBinOut.
	mBinOut << pTextSeg.Size(); // size <- size of the text segment.
	tAddress textSegAddress =  pTextSeg.Address(); // address <- address of the text segment.
	mBinOut << textSegAddress; // Send address to mBinOut.
	tByte *textSegContents =  pTextSeg.Contents(); // contents <- contents of the text segment.
	mBinOut << cManipSize(pTextSeg.Size() -9) << reinterpret_cast <char *>(textSegContents); // Send contents to mBinOut (hint: use cManipSize(size - 9) to specify the number of bytes to write.
	delete textSegContents;// free the contents array.


}


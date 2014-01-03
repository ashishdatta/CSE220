//**************************************************************************************************************
// CLASS: cK1as
//
// DESCRIPTION
// Assembler for the K1.
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
#include <string>
using std::string;

#include "Binary.hpp"
#include "InstrTypeB.hpp"
#include "InstrTypeR.hpp"
#include "InstrTypeRI.hpp"
#include "InstrTypeRV.hpp"
#include "Integer.hpp"
#include "K1as.hpp"
#include "Register.hpp"
#include "Variable.hpp"

//--------------------------------------------------------------------------------------------------------------
// Ctor.
//
// REMARK
// cArg(unsigned, char **) may throw an exception if pArgc is not 2 (indicating that the source file name is
// missing on the command line). We don't catch the exception here, so it will be thrown again and will land
// back in main()'s lap, where main() will display an error message and end the program.
//--------------------------------------------------------------------------------------------------------------
cK1as::cK1as(unsigned pArgc, char **pArgv) :
	mArg(pArgc, pArgv),
	mLex(mArg.SrcFname())
{
	Run();
}

//--------------------------------------------------------------------------------------------------------------
// Assemble()
//
// DESCRIPTION
// Assembles the source code file in two passes. During the first pass, directives, variables, and labels are
// parsed and handled; instructions are skipped. During the second pass, directives, variables, and labels are
// skipped and instructions are parsed and encoded.
//
// PSEUDOCODE
// mCurrAddr <- 0
// token <- mLex.Token()
// While token does not equal the empty string Do
//	   If first char of token is '.' Then                       -- We are assembling a directive
//		   If pPass is 1 Then Call AssembleDirective(token) -- We assemble directives during the first pass
//		   Else mLex.DiscardLine()                          -- On the second pass, we ignore directives
//	   Elseif first char of token is '$' Then                   -- We are assembling a variable
//		   If pPass is 1 Then                               -- We assemble variables during the first pass
//			   Call AssemblerVariable(token)            -- Assemble the variable
//			   Increment mCurrAddr                      --
//		   Else	                                            --
//			   mLex.DiscardLine()                       -- On the second pass, we ignore variables
//		   End If                                           --
//	   Elseif first char of token is '@' Then                   -- We are assembling a label
//		   If pPass is 1 Then                               -- We assemble labels during the first pass
//			   AssembleLabel(token)                     -- Assemble the label
//			   mLex.DiscardLine()                       -- Ignore the rest of the line
//		   Else	                                            --
//			   mnemonic <- mLex.Token()                 -- Following the label is the mnemonic
//			   instr <- AssembleInstruction(mnemonic)   -- During the 2nd pass we assemble instructions
//			   mTextSeg.AddInstr(*instr)                -- Add the instruction to the text segment
//			   delete instr                             -- Deallocate the mem alloc'd for the instr
//		   End If                                           --
//		   mCurrAddr++                                      --
//	   Else	                                                    -- We are assembling an instruction
//		   If pPass is 1 Then                               -- We ignore instructions during the first pass
//			   mLex.DiscardLine()                       -- Ignore the rest of the line
//		   Else                                             --
//			   instr <- AssembleInstruction(token)      -- During 2nd pass, assemble an instruction
//			   mTextSeg.AddInstr(*instr)                -- Add the instruction to the text segment
//			   delete instr	                            -- Dealloc the mem alloc'd for the instr
//		   End If                                           --
//		   mCurrAddr++                                      --
//	   End If                                                   --
//	   token <- mLex.Token()                                    -- Get the next token from the lex analyzer
// End While                                                        --
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// AssembleDirective()
//
// DESCRIPTION
// Parses and handles a .DATA or .TEXT directive.
//
// PSEUDOCODE
// strAddr <- mLex.Token()                  -- the address following the directive
// address <- convert strAddr to tAddress   -- hint: look up strtol()
// If pDirective is ".DATA" Then            -- .DATA directive
//	   mDataSeg.Address(address)        -- Store the data segment address
// Else                                     -- .TEXT directive
//	   mTextSeg.Address(address)        -- Store the text segment address
// End If                                   --
// mCurrAddr <- address                     -- Set mCurrAddr to the new address
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// AssembleInstr()
//
// DESCRIPTION
// Parses and assembles an instruction. On input, pMnemonic is the mnemonic that was parsed.
//
// PSEUDOCODE
// If pMnemonic is "ADD" or "NEG" or "NOR" or "POP" or "PUSH" or "ROL" Then
//	   return AssembleInstrTypeR(pMnemonic)
// Elseif pMnemonic is "BEQ" or "BLT" or "BR" or "BSUB" Then
//	   return AssembleInstrTypeB(pMnemonic)
// Elseif pMnemonic is "HALT" or "RET" Then
//	   return AssembleInstrTypeN(pMnemonic)
// Elseif pMnemonic is "IN" or "OUT" or "LDI" Then
//	   return AssembleInstrTypeRI(pMnemonic)
// Else
//	   return AssembleInstrTypeRV(pMnemonic)
// End If
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// AssembleInstrTypeB()
//
// DESCRIPTION
// Parses and assembles a type B instruction (BEQ, BLT, BR, or BSUB).
//
// PSEUDOCODE
// strLabel <- mLex.Token()                             -- Read the branch target label from the source file
// cLabel branchTargetLabel <- mTextSeg.Label(strLabel) -- Retrieve the label from the text segment
// return cInstrTypeB(pMnemonic, branchTargetLabel)     -- Assemble a type B instruction
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// AssembleInstrTypeN()
//
// DESCRIPTION:
// Parses and assembles a type N instruction (N = no operands; these are HALT and RET). Note: type N instrs
// are instances of the Instr class.
//
// PSEUDOCODE:
// return new cInstr(pMnemonic)
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// AssembleInstrTypeR()
//
// DESCRIPTION:
// Parses and assembles a type R instruction (R = register).
//
// PSEUDOCODE:
// strReg <- mLex.Token()                  -- Read the register string from the source file
// cRegister reg(strReg)                   -- Instantiate a cRegister object
// return new cInstrTypeR(pMnemonic, reg)  -- Assemble a type R instruction
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// AssembleInstrTypeRI()
//
// DESCRIPTION
// Parses and assembles a type RI instruction (R = register, I = integer).
//
// PSEUDOCODE
// strReg <- mLex.Token()
// strInt <- mLex.Token()
// cRegister reg(strReg)                             -- Instantiate a cRegister object
// cInteger integer(strInt)                          -- Instantiate a cInteger object
// return new cInstrTypeRI(pMnemonic, reg, integer)  -- Assemble a type RI instruction
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// AssembleInstrTypeRV()
//
// DESCRIPTION:
// Parses and assembles a type RI instruction (R = register, V = variable).
//
// PSEUDOCODE:
// If pMnemonic is "LD" or "LDA" Then            -- Is this a LD or LDA instruction?
//	   strReg <- mLex.Token()                -- Yes, read the register string from the source file
//	   strVar <- mLex.Token()                -- Read the variable string from the source file
// Else	                                         --
//	   strVar <- mLex.Token()                -- No, read the variable string from the source file
//	   strReg <- mLex.Token()                -- Read the register string from the source file
// End If                                        --
// cVariable var <- mDataSeg.Variable(strVar)	 -- Get the variable from the data segment
// cRegister reg <- cRegister(strReg)            -- Instantiate a Register object
// return new cInstrTypeRV(pMnemonic, reg, var)	 -- Assemble a type RV instruction
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// AssembleLabel()
//
// DESCRIPTION
// Parses a label during the first pass. Gets the string, creates a new cLabel object, and then adds the cLabel
// to the map of labels stored in the mTextSeg object.
//
// PSEUDOCODE
// Instantiate a cLabel object named newLabel passing pName and mCurrAddr to the ctor.
// Add newLabel to the text segment.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// AssembleVariable()
//
// DESCRIPTION
// Parses a variable during the first pass. Gets the string, create a new cVariable object, and then adds the
// cVariable to the map of cVariables stored in the mDataSeg object.
//
// PSEUDOCODE:
// strInitValue <- mLex.Token()
// initValue <- convert to tWord(strInitValue)
// Instantiate a cVariable object named newVar passing pName, mCurrAddr, initValue to the ctor
// Add newVariable to the data segment.
//--------------------------------------------------------------------------------------------------------------
???

//--------------------------------------------------------------------------------------------------------------
// Run()
//
// PSEUDOCODE
// Call Assemble(1) to perform the first pass.
// Call mLex.Reset() to move the stream get pointer back to the beginning of the file.
// Call Assemble(2) to perform the second pass.
// Instantiate a cBinary object named 'bin' passing the binary file name as the parameter (hint: it's in mArg).
// Call the Write() function on bin to write the binary file (hint: the segments are the parameters).
//--------------------------------------------------------------------------------------------------------------
???

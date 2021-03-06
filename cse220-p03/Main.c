//Skye Croke <scroke@asu.edu>, Ashish Datta <adatta4@asu.edu>
//


/***************************************************************************************************************
 * FILE: Main.c
 *
 * DESCRIPTION
 * bimpie - BMP Image Editor
 *
 * AUTHOR INFORMATION
 * Kevin R. Burger
 * (Modified as  per assignment by S. Croke and A. Datta)
 *
 * Mailing Address:
 * Computer Science & Engineering
 * School of Computing, Informatics, and Decision Systems Engineering
 * Arizona State University
 * Tempe, AZ 85287-8809
 *
 * Email: burgerk@asu.edu
 * Web:   http://kevin.floorsoup.com
 **************************************************************************************************************/
#include <stdbool.h>  // For bool data type
#include <stdio.h>    // For printf()
#include <stdlib.h>   // For exit(), strtod()
#include "Arg.h"
#include "Error.h"
#include "String.h"
#include "Bmp.h"
#include "Image.h"

// NEW:  defines to keep track of order of operations
#define FLIPV_ORDER 1
#define FLIPH_ORDER 2
#define ROTR_ORDER 3

//==============================================================================================================
// TYPE DEFINITIONS
//==============================================================================================================

// Stores command line argument info.
typedef struct {
	int		argc;			// argc from main()
	char  **argv;			// argv from main()
	bool	fliph;			// --fliph was specified
	bool	flipv;			// --flipv
	bool	h;				// -h, --help
	char   *inFile;			// The file name of the input BMP image
	bool	o;				// -o file, --output file
	char   *outFile;		// The output file name following -o or --output
	int		rotArg;			// The argument n following --rotr
	bool	rotr;			// --rotr n
	bool	v;				// -v, --version
	int	order[3];		// NEW: array to keep track of order of operations
} tCmdLine;

//==============================================================================================================
// CONSTANT DEFINITIONS
//==============================================================================================================

const char *cAuthor  = "Skye Croke <scroke@asu.edu>, Ashish Datta <adatta4@asu.edu>";
const char *cBinary  = "bimpie";
const char *cVersion = "1.0 (2013.3.16)";

//==============================================================================================================
// FUNCTION DECLARATIONS
//==============================================================================================================

static bool CheckDupOpt(bool pOptFlag, char *pOptStr);
static void Help();
static void Run(tCmdLine *);
static void ScanCmdLine(tCmdLine *);
static int ScanRotArg(char *pOpt, char *pArg);
static void Version();

//==============================================================================================================
// FUNCTION DEFINITIONS
//==============================================================================================================

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: CheckDupOpt()
 *
 * DESCRIPTION
 * Checks to see if pOptFlag is already true, indicating that the option was duplicated on the command line.
 * If so, error out. If not, return true which will set the flag in the tCmdLine structure to true.
 *------------------------------------------------------------------------------------------------------------*/
static bool CheckDupOpt(bool pOptFlag, char *pOptStr)
{
	if (pOptFlag) ErrorExit(cErrorArgDup, "duplicate option %s", pOptStr);
	return true;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: Help()
 *
 * DESCRIPTION
 * Display help and exit.
 *------------------------------------------------------------------------------------------------------------*/
static void Help()
{
	printf("Usage: %s [options] bmpfile\n", cBinary);
	printf("Perform image processing operations on a BMP image.\n\n");
	printf("Options:\n\n");
	printf("    --fliph                  Flips the image horizontally.\n");
	printf("    --flipv                  Flips the image vertically.\n");
	printf("    -h, --help               Display a help message and exit.\n");
	printf("    -o file, --output file   Write the modified image to 'file' in .bmp format.\n");
	printf("    --rotr n                 Rotate the image 90 degs right (clockwise) n mod 4 times.\n");
	printf("    -v, --version            Display version info and exit.\n\n");
	printf("By default, the modified image is written to 'bmpfile'.\n");
	exit(0);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: main()
 *
 * DESCRIPTION
 * Scan the command line for options and arguments and then call Run().
 *
 * REMARKS
 * memset() is a handy function which is declared in string.h. Look it up.
 *------------------------------------------------------------------------------------------------------------*/
int main(int pArgc, char *pArgv[])
{
	tCmdLine cmdLine;
	memset(&cmdLine, 0, sizeof(tCmdLine));
	cmdLine.argc = pArgc;
	cmdLine.argv = pArgv;
	ScanCmdLine(&cmdLine);
	Run(&cmdLine);
	return 0;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: Run()
 *
 * DESCRIPTION
 *------------------------------------------------------------------------------------------------------------*/
static void Run(tCmdLine *pCmdLine)
{
	// varibles for header structures
	tBmpHeader bmpHeader;
	tBmpInfoHeader bmpInfoHeader;

	// 2D array of pixels
	// read in bitmap
	// filename passed in from command line
	// header structures passed in by reference
	tPixel **pixels  = readBitmap(pCmdLine->inFile, &bmpHeader, &bmpInfoHeader);

	// loop through the command line order of operations
	for (int i = 0; i < 3; i++)
	{
		switch (pCmdLine->order[i])
		{
			case FLIPH_ORDER:
				// flip horizontal
				fliph(pixels, bmpInfoHeader.width, bmpInfoHeader.height);
				break;
			case FLIPV_ORDER:
				// flip vertical
				flipv(pixels, bmpInfoHeader.width, bmpInfoHeader.height);
				break;
			case ROTR_ORDER:
				// rotate right
				pixels = rotr(pixels, pCmdLine->rotArg, &bmpInfoHeader);
				break;
			default:
				// do nothing
				break;
		}
	}

	// write out the bitmap file
	// if -o option is specified, write to output file arugment
	// otherwise overwrite the input file
	if(pCmdLine->o)
	{	
		writeBitmap(pCmdLine->outFile, &bmpHeader, &bmpInfoHeader, pixels);
	}
	else
	{
		
		writeBitmap(pCmdLine->inFile, &bmpHeader, &bmpInfoHeader, pixels);
	}

	// free pixel arrays
        for (int row = 0; row < bmpInfoHeader.height; row++) free(pixels[row]);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: ScanCmdLine()
 *
 * DESCRIPTION
 * Scan the command line extracting the options and arguments.
 *------------------------------------------------------------------------------------------------------------*/
static void ScanCmdLine(tCmdLine *pCmdLine)
{
	tArgScan argScan;
	memset(&argScan, 0, sizeof(tArgScan));
	argScan.argc = pCmdLine->argc;
	argScan.argv = pCmdLine->argv;
	argScan.longOpts = "fliph;flipv;help;output:;rotr:;version;";
	argScan.shortOpts = "ho:v";

	// Start scanning the command line at argv[1]. Note: argv[0] is always the name of the binary.
	argScan.index = 1;
	int result = ArgScan(&argScan);

	// Keep calling ArgargScan() to scan the next option until it returns cArgEnd indicating that the entire
	// command line has been scanned.

	// NEW:  index into order[]
	int orderIndex = 0;
	while (result != cArgEnd) {

		// Was a required argument following a short or long option omitted?
		if (result == cArgMissingArg) {
			ErrorExit(cErrorArg, "%s", argScan.error);

		// Was an invalid short or long option specified?
		} else if (result == cArgInvOpt) {
			ErrorExit(cErrorArgInvOpt, "%s", argScan.error);

		// Was an unexpected string encountered?
		} else if (result == cArgUnexpStr) {
			ErrorExit(cErrorArgUnexpStr, "%s", argScan.error);

		// Was an argument encountered? The only argument on the command line should be the BMP image file name.
		} else if (result == cArg) {
			// Check for two arguments.
			if (pCmdLine->inFile) ErrorExit(cErrorArgUnexpStr, "unexpected string %s", argScan.arg);
			pCmdLine->inFile = argScan.arg;

		// We encountered a valid option. Was it --fliph?
		} else if (streq(argScan.opt, "--fliph")) {
			pCmdLine->fliph = CheckDupOpt(pCmdLine->fliph, argScan.opt);
			// Add to order of operations & increment index
			pCmdLine->order[orderIndex] = FLIPH_ORDER;
			orderIndex++;

		// Was it --flipv?
		} else if (streq(argScan.opt, "--flipv")) {
			pCmdLine->flipv = CheckDupOpt(pCmdLine->flipv, argScan.opt);
			// Add to order of operations & increment index
			pCmdLine->order[orderIndex] = FLIPV_ORDER;
			orderIndex++;

		// Was it -h or --help?
		} else if (streq(argScan.opt, "-h") || streq(argScan.opt, "--help")) {
			pCmdLine->h= CheckDupOpt(pCmdLine->h, argScan.opt);

		// Was it -o or --output?
		} else if (streq(argScan.opt, "-o") || streq(argScan.opt, "--output")) {
			pCmdLine->o = CheckDupOpt(pCmdLine->o, argScan.opt);
			pCmdLine->outFile = argScan.arg;

		// Was it --rotr? If so, attempt to convert the argument following --rotr to an integer. ScanRotArg()
		// does not return if the conversion fails.
		} else if (streq(argScan.opt, "--rotr")) {
			pCmdLine->rotr = CheckDupOpt(pCmdLine->rotr, argScan.opt);
			pCmdLine->rotArg = ScanRotArg(argScan.opt, argScan.arg);
			// Add to order of operations & increment index
			pCmdLine->order[orderIndex] = ROTR_ORDER;
			orderIndex++;

		// Was it -v or --version?
		} else if (streq(argScan.opt, "-v") || streq(argScan.opt, "--version")) {
			pCmdLine->v = CheckDupOpt(pCmdLine->v, argScan.opt);
		}

		// Scan next option.
		result = ArgScan(&argScan);
	}

	if (pCmdLine->h) Help();     // Help() does not return.
	if (pCmdLine->v) Version();  // Version does not return.

	// Check that an input file name was specified.
	if (!pCmdLine->inFile) {
		ErrorExit(cErrorArgRot, "expecting input file");
	}
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: ScanRotArg()
 *
 * DESCRIPTION
 * The --rotr option is supposed to be followed by an integer, n, which is the number of times to rotate the
 * image. This function attempts to convert n (pArg is a pointer to the string representation of n on the
 * command line) to an integer. There is a function in the C Std Lib named strtol() that can be used to do this.
 * If the conversion fails, strtol() will return 0, the 'end' parameter will be pointing at the char in the
 * string where the failure was detected (this character will not be a - or a digit char). If the conversion
 * fails, we error out.
 *------------------------------------------------------------------------------------------------------------*/
static int ScanRotArg(char *pOpt, char *pArg)
{
	char *end;
	int n = (int)strtol(pArg, &end, 10);
	if (n == 0 && *end != '\0') {
		ErrorExit(cErrorArgRot, "%s: invalid argument %s", pOpt, pArg);
	}
	return n;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: Version()
 *
 * DESCRIPTION
 * Displays the version string and exits.
 *------------------------------------------------------------------------------------------------------------*/
static void Version()
{
	printf("%s: version %s\n%s\n", cBinary, cVersion, cAuthor);
	exit(0);
}

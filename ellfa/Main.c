#include <stdio.h>    /* For printf() */
#include <stdlib.h>   /* For exit(), strtod() */
#include "Error.h"
#include "String.h"
#include "charFunction.h"
//Ashish Datta and Skye Croke

/*==============================================================================================================
 * TYPE DEFINITIONS
 *============================================================================================================*/

/* This structure type is used to store command line argument info. */
typedef struct {
	int		argc;       /* argc from main() */
	char  **argv;       /* argv from main() */
	int		c;          /* -c tempc  Temperature in Celsius. */
	int		f;          /* -f tempf  Temperature in Fahr. */
	int		h;          /* -h        Display help info and exit. */
	int		v;          /* -v        Display version info and exit. */
	double	temp;       /* The temperature string converted to a double. */
	char    temps[128]; /* Stores the temperature string found on the command line. */
	char *file;
} tArg;

/*==============================================================================================================
 * CONSTANT DEFINITIONS
 *
 * Notes:
 * 1. The static storage specifier tells the compiler not to export these constants to the linker. Consequently
 *    they cannot be accessed in another source code file.
 * 2. I prefix globals constants with gc for Global Constant.
 *
 * Rule: Any "thing" that is only going to be used in one source code file shall be defined in that source code
 * file as static. Things include: global variables, functions, and constants.
 *============================================================================================================*/

static const char *gcAuthor  = "Ashish B. Datta <adatta@asu.edu> and Skye Croke";
static const char *gcBinary  = "ellfa";
static const char *gcVersion = "1.0 (2013.2.22)";

static const int gcInvalidArg  = -1;
static const int gcInvalidOpt  = -2;
static const int gcMissingArg  = -3;
static const int gcMissingOpt  = -4;
static const int gcUnexpStr    = -5;
static FILE *f;
static int numOfLetters;
static char *fileLocation;
/*==============================================================================================================
 * FUNCTION DECLARATIONS
 *
 * Notes:
 * 1. Since Help() and Version() are only called from within this source code file, they are defined as static.
 * 2. These are function declarations. Remember, the declaration consists of just the header part of the func-
 *    tion definition. The definitions for Help() and Version() can be found below. Why are these declarations
 *    here? The rule in C is that a function must be defined or declared above the point in the code where the
 *    function is called. I like to put the functions in my files in alphabetical order, so some of them require
 *    declarations (those that are called before they are defined), whereas others may not (those that are de-
 *    fined before they are called). For the latter functions, no declaration is necessary, but I put declara-
 *    tions for all of the static functions here anyway for completeness.
 *============================================================================================================*/

static void Help();
static void ScanCmdLine(tArg *pArg);
static void Version();
static void PrintFile(char *fileName);

/*==============================================================================================================
 * FUNCTION DEFINITIONS
 *============================================================================================================*/

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: Help()
 *
 * DESCRIPTION
 * Displays help information and exits.
 *------------------------------------------------------------------------------------------------------------*/
static void Help()
{
	printf("Usage: %s [-h] [-v] [-c] {-o file | -f file} ...\n", gcBinary);
	printf("Read English language text and calculate letter frequencies.\n\n");
	printf("Options:\n\n");
	printf("    -c         Output results in csv format.\n");
	printf("    -f file    Read the text from °file°.\n");
	printf("    -h         Display this help message and exit.\n");
	printf("    -v         Display version info and exit.\n\n");
	exit(0);
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: main()
 *------------------------------------------------------------------------------------------------------------*/
int main(int pArgc, char *pArgv[])
{
	
	tArg arg;
	arg.argc = pArgc;
	arg.argv = pArgv;
	printf("%s",fileLocation);
	ScanCmdLine(&arg);
	return 0;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: ScanCmdLine()
 *
 * DESCRIPTION
 * Scans the command line looking for options and arguments.
 *------------------------------------------------------------------------------------------------------------*/
static void ScanCmdLine(tArg *pArg)
{
	
	
	/* If argc is less than 2, then there are no args on the command line. */
	if (pArg->argc < 2) {
		printf("%s: missing required option: -c tempc | -f tempf\n", gcBinary);
		exit(gcMissingOpt);
	}

	int invOptIdx = 0, unexpStrIdx = 0;

	pArg->c = 0;
	pArg->f = 0;
	pArg->h = 0;
	pArg->v = 0;
	pArg->temps[0] = '\0';
	int i;
	/* For each arg on the command line. */
	for ( i = 1; i < pArg->argc; ++i) {
		char *opt = pArg->argv[i];

		/* Check to see if option is -c. If so, copy the string following -c (if it exists) to pArg->temps. */
		if (streq(opt, "-c")) {
			pArg->c++;
			if (++i < pArg->argc) strcpy(pArg->temps, pArg->argv[i]);

		/* Check to see if option is -f. If so, copy the string following -f (if it exists) to pArg->temps. */
		} else if (streq(opt, "-f")) {
			pArg->f++;
			if (++i < pArg->argc) strcpy(pArg->file, pArg->argv[i++]);
				PrintFile(pArg->file); //this works
		/* Check to see if option is -h. */
		} else if (streq(opt, "-h")) {
			pArg->h++;

		/* Check to see if option is -v. */
		} else if (streq(opt, "-v")) {
			pArg->v++;

		/* Check for an invalid option, which is a - followed by some character that is not c, f, h, or v. */
		} else if (opt[0] == '-' && opt[1] != '\0') {
			invOptIdx = i;
			break;

		/* Else, there is some string on the command line that should not be there. */
		} else {
			unexpStrIdx = i;
			break;
		}
	}

	/* Handle error conditions. */
	if (invOptIdx) {
		ErrorExit(gcInvalidOpt, "%s: invalid option: %s", gcBinary, pArg->argv[invOptIdx]);
	} else if (pArg->c > 1) {
		ErrorExit(gcInvalidOpt, "%s: -c specified twice", gcBinary);
	} else if (pArg->f > 1) {
		ErrorExit(gcInvalidOpt, "%s: -f specified twice", gcBinary);
	} else if (pArg->c && pArg->f) {
		ErrorExit(gcInvalidOpt, "%s: -c and -f specified", gcBinary);
	} else if (unexpStrIdx) {
		ErrorExit(gcUnexpStr, "%s: unexpected string: %s", gcBinary, pArg->argv[unexpStrIdx]);
	} else if (pArg->c || pArg->f) {
		if (pArg->temps[0]) {
			/* Convert temperature string pArg->temps to a double. On return, if end is not pointing to the end-of
			 * string character, then the string was not a valid double number. */
			char *end;
			pArg->temp = strtod(pArg->temps, &end);
			if (*end != '\0') ErrorExit(gcInvalidArg, "%s: invalid temperature %s", gcBinary, end);
		} else {
			ErrorExit(gcMissingArg, "%s: missing temperature after %s", gcBinary, pArg->c ? "-c" : "-f");
		}
	}

	/* -h has higher precedence than the other options, so check for it first. Help() does not return. */
	if (pArg->h) Help();

	/* -v has higher precedence than -c and -f, so check for it second. Version() does not return. */
	if (pArg->v) Version();
	/* If we get to here, we have a valid -c or -h option followed by a valid temperature. The temperature
	 * string converted to a double is stored in pArg->temp. */
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: Version()
 *
 * DESCRIPTION
 * Displays version information and exits.
 *------------------------------------------------------------------------------------------------------------*/
static void Version()
{
	printf("%s: version %s\n%s\n", gcBinary, gcVersion, gcAuthor);
	exit(0);
}
static void PrintFile(char *fileName)
{
	FILE *f;
	int character;
	int i,j;

	f = fopen(fileName, "r");
		/*Read file and calculate number of letters and character Occurences*/
	if (f==NULL) { /* error opening file returns NULL */
		//perror("Could not open file!\n"); /* error message */
		exit(1);
	}
	else{
		fseek(f, 0, SEEK_SET); /* Reset cursor  to the beginning of file */
		while((character=fgetc(f))!=EOF)
		{
			putchar(character);
			if(character >=65&&character!=10) //65 is A and 10 is \n
			{
				
				numOfLetters++; //Counts number of letters
			}
			charOccur(tolower(character)); //tolower so no matter the casing the instance of the letter is recorded
		}
		
		printf("\n\%d Letters\n",numOfLetters); //prints file name and num letters
		printCharOccur(numOfLetters);	
	}
	countPairs(fileName);
}

void copyResults(char *fileName)
{	
	
}

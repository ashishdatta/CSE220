/***************************************************************************************************************
 * FILE: Error.c
 *
 * DESCRIPTION
 * See comments in Error.h.
 *
 * AUTHOR INFORMATION
 * Kevin R. Burger [KRB]
 *
 * Mailing Address:
 * Computer Science & Engineering
 * School of Computing, Informatics, and Decision Systems Engineering
 * Arizona State University
 * Tempe, AZ 85287-8809
 *
 * Email: burgerk@asu
 * Web:   http://kevin.floorsoup.com
 **************************************************************************************************************/
#include <stdarg.h>  // For variadic function macros
#include <stdio.h>   // For printf()
#include <stdlib.h>  // For exit()
#include "Error.h"
#include "String.h"

//==============================================================================================================
// FUNCTION DEFINITIONS
//==============================================================================================================

/*--------------------------------------------------------------------------------------------------------------
 * ErrorExit
 *------------------------------------------------------------------------------------------------------------*/
void ErrorExit(int pExitCode, char *pFmt, ...)
{
	char msg[1024] = { '\0' };
	va_list argp; va_start(argp, pFmt);
	char *fp;
	for ( *fp = pFmt; fp && *fp; ++fp) {
		if (*fp != '%') {
			StrCatCh(msg, *fp);
		} else {
			switch (*++fp) {
				case 'c': StrCatCh(msg, (char)va_arg(argp, int)); break;
				case 'd': StrCatInt(msg, va_arg(argp, int)); break;
				case 's': strcat(msg, va_arg(argp, char *)); break;
			}
		}
	}
	va_end(argp);
	printf("%s\n", msg);
	exit(pExitCode);
}

#include "log.h"

/*
 * This log implementation writes log messages to log
 * file. This implementation is not thread safe. 
 *
 * Different log level defined using an integer.
 *
 * Debug       : 1
 * Info        : 2
 * Warning     : 3
 * Error       : 4 
 * Critical    : 5
 *
 *
 * Off         : 0
 *
 */


// global variables defined for log
double __log_stime__;
FILE *__log_file__;       
FILE *__error_file__;
int __log_level__;

#ifndef __PARALLEL__
struct timeval tval;
struct timezone tzval;
#endif  // __PARALLEL__

void log_init (const char *filename, const char *errorfile, int loglevel)
{
#ifndef __PARALLEL__
	gettimeofday(&tval, &tzval);
#endif
	__log_stime__ = STIME;
	__log_level__ = 0;
	if (!(loglevel < 0))
		__log_level__ = loglevel;

/* #ifdef __LOG_ENABLE__ */

	__log_file__ = fopen (filename, "w");
	if (!__log_file__)
	{
		fprintf (stderr, "Unable to open __log_file__ for writing\n");
	}

	if (!errorfile)
	{
		errorfile = filename;
	}

	__error_file__ = fopen (errorfile, "w");
	if (!__error_file__)
	{
		fprintf (stderr, "Unable to open __error_file__ for writing\n");
	}

/* #endif */ /* __LOG_ENABLE__ */
}


void log_close ()
{
/* #ifdef __LOG_ENABLE__ */
	fclose (__log_file__);
	fclose (__error_file__);
/* #endif */ /* __LOG_ENABLE__ */
}

#ifndef __LOG_H__
#define __LOG_H__

#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

extern double __log_stime__;
extern int __log_level__;
// this file will open inside log_init() and should be closed before exit
extern FILE *__log_file__;
extern FILE *__error_file__;



#ifndef __PARALLEL__
extern struct timeval tval;
extern struct timezone tzval;
#define STIME ((double)tval.tv_sec + ((double)tval.tv_usec)/1000000.0)
#define LOGTIME (gettimeofday(&tval, &tzval), (STIME - __log_stime__))
#else
#include <mpi.h>
#define STIME (MPI_Wtime ())
#define LOGTIME (STIME - __log_stime__)
#endif  /* __PARALLEL__ */

#ifdef __LOG_ENABLE__
#define DEBUG(format, ...) ({if(__log_level__ < 2){fprintf(__log_file__, "[%lf]  [debug] "format, (LOGTIME), ## __VA_ARGS__);fflush(__log_file__);}})
#define INFO(format, ...)  ({if(__log_level__ < 3){fprintf(__log_file__, "[%lf]  [info]  "format, (LOGTIME), ## __VA_ARGS__);fflush(__log_file__);}})
#define WARN(format, ...)  ({if(__log_level__ < 4){fprintf(__error_file__, "[%lf]  [warn]  "format, (LOGTIME), ## __VA_ARGS__);fflush(__error_file__);}})
#define ERROR(format, ...) ({if(__log_level__ < 5){fprintf(__error_file__, "[%lf]  [error] "format, (LOGTIME), ## __VA_ARGS__);fflush(__error_file__);}})
#define CRIT(format, ...)  ({if(__log_level__ < 6){fprintf(__log_file__, "[%lf]  [crit]  "format, (LOGTIME), ## __VA_ARGS__);fflush(__log_file__);}})
/* print to logfile without any tags */
#define GEN(format, ...) ({fprintf(__log_file__, format, ## __VA_ARGS__);fflush(__log_file__);})
#else
#define DEBUG(format, ...)
#define INFO(format, ...) 
#define WARN(format, ...) 
#define ERROR(format, ...)
#define CRIT(format, ...)
#define GEN(format, ...)
#endif /* __LOG_ENABLE__ */


#define LOG_INIT(filename, errorfile, loglevel)  log_init(filename, errorfile, loglevel);
#define LOG_CLOSE() log_close()

void 
log_init (const char *filename, const char *errorfile, int loglevel);

void
log_close ();

#endif  /* __LOG_H__ */



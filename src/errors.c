/** errors.c - Error handling routines.

Copyright (c) 2020 Michael Berry

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include "errors.h"

static const int MAXLINE = 128;

/**
 * do_error:
 *      Print an error message and return to caller.
 */
static void do_error(bool errnoflag, int err, const char *fmt, va_list args)
{
    char buf[MAXLINE];
    memset(buf, 0, MAXLINE * sizeof(char));

    vsnprintf(buf, MAXLINE - 1, fmt, args);
    if (errnoflag)
        snprintf(buf + strlen(buf),
                 MAXLINE - strlen(buf) - 1,
                 ": %s",
                 strerror(err));

    strncat(buf, "\n", 2);
    fflush(stdout);             // in case stdout and stdin are the same
    fputs(buf, stderr);
    fflush(NULL);               // flush all stdio output streams
}

/**
 * error_return:
 *      Nonfatal error related to a system call.
 *      Print an error message and return.
 */
void error_return(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_error(true, errno, fmt, args);
    va_end(args);
}

/**
 * error_syscall:
 *      Fatal error related to a system call.
 *      Print an error message and terminate.
 */
void error_syscall(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_error(true, errno, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

/**
 * error_message:
 *      Nonfatal error unrelated to a system call.
 *      Print an error message and return.
 */
void error_message(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_error(false, 0, fmt, args);
    va_end(args);
}

/**
 * error_quit:
 *      Fatal error unrelated to a system call.
 *      Print an error message and return.
 */
void error_quit(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_error(false, 0, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

/**
 * error_abort:
 *      Fatal error related to a system call.
 *      Print an error message, dump core, and terminate.
 */
void error_abort(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    do_error(false, 0, fmt, args);
    va_end(args);
    abort();                    // dump core and terminate
    exit(EXIT_FAILURE);         // should never happen
}

/**
 * sig_int:
 *      Interrupt ^C signal handler, ignore it for now.
 */
void sig_int(int signo)
{
    static int i = 1;

    if (i <= 1) {
        fprintf(stderr, "\nCaught signal %d. Press ^C again to exit.\n", signo);
        fflush(stderr);
    } else {
        fprintf(stderr, "\nCaught signal %d again. Exiting program.\n", signo);
        fflush(stderr);
    }

    if (i == 2)
        exit(EXIT_FAILURE);

    i++;
}

/**
 * NOTE: NECESSARALY FATAL
 * sig_seg:
 *      Segmentation fault handler, insult programmer then abort.
 */
void sig_seg(int signo)
{
    error_abort("Caught signal %d, terminating.\n"
                "\tAnd fix your damn code.\n", signo);
}

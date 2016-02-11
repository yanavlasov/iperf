/* 
 * I can not fiure out what violates and what does not [L]GPL
 * and do not use [L]GPL source code.
 * This interface is taken form the manual page
 * I HOPE that just using the same interface as getopt does not violate
 * LGPL
 *
 * TODO: handle nonarguments
 * TODO: + at the beginning of the optstring (env POSIXLY_CORRECT)
 * TODO: - at the beginning of the optstring
 * TODO: + at the beginning of the optstring
 * TODO: :: optional parameters
 * TODO: combined short parameters (i.e. -abCdeF)
 * TODO: -W
 * TODO: add getopt
 * TODO: add getopt_long_only
 */
#pragma once

extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;

#define	no_argument			0
#define required_argument	1
#define optional_argument	2

struct option
{
	const char* name;
	int has_arg;
	int *flag;
	int val;
};

/* only getopt_long is supported for now */
extern int getopt_long(int argc, char *const *argv, const char *optstring, const struct option *longopts, int *longindex);

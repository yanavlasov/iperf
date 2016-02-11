/*
* I can not fiure out what violates and what does not [L]GPL
* and do not use [L]GPL source code.
* Not a full implementation
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include "getopt.h"

char *optarg = NULL;
int optind = 1;
int opterr = 1;
int optopt = '?';
int errret = '?';

static int error_badarg(const char *opt)
{
    if (errret == '?' && opterr) {
        fprintf(stderr, "Unrecognized option %s\n", opt);
    }
    return errret;
}

static int error_noparam(const char *opt)
{
    if (errret == '?' && opterr) {
        fprintf(stderr, "Required parameter missing for option %s\n", opt);
    }
    return errret;
}

static int error_param(const char *opt)
{
    if (errret == '?' && opterr) {
        fprintf(stderr, "Invalid parameter for option %s\n", opt);
    }
    return errret;
}

static int return_longopt(const struct option *longopts, unsigned opt, int *longindex)
{
    if (NULL != longindex) {
        *longindex = (int)opt;
    }

    if (longopts[opt].flag) {
        *longopts[opt].flag = longopts[opt].val;
        return 0;
    }
    return longopts[opt].val;
}

static int parse_long_option(int argc, char *const *argv, const struct option *longopts, int *longindex)
{
    const char* opt = argv[optind] + 2;
    const char* arg = strchr(opt, '=');
    unsigned i = 0;
    unsigned optlen = arg ? arg - opt : strlen(opt);

    for (; NULL != longopts[i].name; ++i) {
        if (optlen == strlen(longopts[i].name) && !strncmp(opt, longopts[i].name, optlen)) {
            break;
        }
    }

    if (NULL == longopts[i].name) {
        return error_badarg(argv[optind]);
    }

    ++optind;
    switch (longopts[i].has_arg) {
    case no_argument:
        if (arg) {
            return error_param(argv[optind-1]);
        }
        return return_longopt(longopts, i, longindex);

    case required_argument:
        if (arg) {
            optarg = (char*)arg + 1;
        } else if (optind >= argc) {
            return error_noparam(argv[optind-1]);
        } else {
            optarg = argv[optind];
            ++optind;
        }
        return return_longopt(longopts, i, longindex);

    case optional_argument:
        if (arg) {
            optarg = (char*)arg + 1;
        } else if (optind < argc) {
            if (argv[optind][0] != '-') {
                optarg = argv[optind];
                ++optind;
            }
        }
        return return_longopt(longopts, i, longindex);

    default:
        errno = EINVAL;
        break;
    }
    return -1;
}

static int parse_short_option(int argc, char *const *argv, const char *optstring)
{
    const char* opt = argv[optind] + 1;
    unsigned i = 0;
    unsigned len = strlen(optstring);

    for (; i < len; ++i) {
        if (optstring[i] != ':' && optstring[i] == *opt) {
            break;
        }
    }

    if (i == len) {
        optopt = *opt;
        return error_badarg(argv[optind]);
    }

    ++optind;
    if (i + 1 < len && optstring[i + 1] == ':') {
        if (0 != opt[1]) {
            /* no space between option and argument */
            optarg = (char*)opt + 1;
        } else if (optind >= argc) {
            return error_noparam(argv[optind-1]);
        } else {
            optarg = argv[optind];
            ++optind;
        }
        return optstring[i];
    }

    /* TODO handle optional parameters indicated with '::' */

    /* TODO handle combined short options, i.e. -abcDeF */

    return optstring[i];
}

int getopt_long(int argc, char *const *argv, const char *optstring, const struct option *longopts, int *longindex)
{
    errret = '?';
    optarg = NULL;

    if (optind >= argc) {
        return -1;
    }

    if (optstring[0] == '-' || optstring[0] == '+') {
        /* TODO: handle +/- behavior of the optstring */
        ++optstring;
    }

    if (optstring[0] == ':') {
        errret = ':';
        ++optstring;
    } else {
        errret = '?';
    }

    if (!strcmp("--", argv[optind])) {
        return -1;
    }

    if (argv[optind][0] == '-' && argv[optind][1] == '-') {
        return parse_long_option(argc, argv, longopts, longindex);
    } else if (argv[optind][0] == '-') {
        return parse_short_option(argc, argv, optstring);
    }
    /* TODO: handle non options */
    return errret;
}

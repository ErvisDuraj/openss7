/*****************************************************************************

 @(#) File: src/util/rtgconfig.c

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2015  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation, version 3 of the license.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
 details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>, or
 write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA.

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 *****************************************************************************/

static char const ident[] = "src/util/rtgconfig.c (" PACKAGE_ENVR ") " PACKAGE_DATE;

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 600
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#ifdef _GNU_SOURCE
#include <getopt.h>
#endif

static int debug = 0;			/* default no debug */
static int output = 1;			/* default normal output */
static int dryrun = 0;			/* dry run */

struct rtgconfig {
	int ct;
	int rt;
	int notify;
	char esqaddr[15];
	char isqaddr[15];
};

static struct rtgconfig config = {
	.ct = 20,
	.rt = 45,
	.notify = 1,
	.esqaddr = "09002B000004FE",
	.isqaddr = "09002B000005FE"
};

static void
do_config(int argc, char *argv[], int start)
{
}

static void
copying(int argc, char *argv[])
{
	if (!output && !debug)
		return;
	(void) fprintf(stdout, "\
--------------------------------------------------------------------------------\n\
%1$s\n\
--------------------------------------------------------------------------------\n\
Copyright (c) 2008-2015  Monavacon Limited <http://www.monavacon.com/>\n\
Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>\n\
Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>\n\
\n\
All Rights Reserved.\n\
--------------------------------------------------------------------------------\n\
This program is free software: you can  redistribute it  and/or modify  it under\n\
the terms of the  GNU Affero  General  Public  License  as published by the Free\n\
Software Foundation, version 3 of the license.\n\
\n\
This program is distributed in the hope that it will  be useful, but WITHOUT ANY\n\
WARRANTY; without even  the implied warranty of MERCHANTABILITY or FITNESS FOR A\n\
PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.\n\
\n\
You should have received a copy of the  GNU Affero General Public License  along\n\
with this program.   If not, see <http://www.gnu.org/licenses/>, or write to the\n\
Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.\n\
--------------------------------------------------------------------------------\n\
U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on behalf\n\
of the U.S. Government (\"Government\"), the following provisions apply to you. If\n\
the Software is supplied by the Department of Defense (\"DoD\"), it is classified\n\
as \"Commercial  Computer  Software\"  under  paragraph  252.227-7014  of the  DoD\n\
Supplement  to the  Federal Acquisition Regulations  (\"DFARS\") (or any successor\n\
regulations) and the  Government  is acquiring  only the  license rights granted\n\
herein (the license rights customarily provided to non-Government users). If the\n\
Software is supplied to any unit or agency of the Government  other than DoD, it\n\
is  classified as  \"Restricted Computer Software\" and the Government's rights in\n\
the Software  are defined  in  paragraph 52.227-19  of the  Federal  Acquisition\n\
Regulations (\"FAR\")  (or any successor regulations) or, in the cases of NASA, in\n\
paragraph  18.52.227-86 of  the  NASA  Supplement  to the FAR (or any  successor\n\
regulations).\n\
--------------------------------------------------------------------------------\n\
Commercial  licensing  and  support of this  software is  available from OpenSS7\n\
Corporation at a fee.  See http://www.openss7.com/\n\
--------------------------------------------------------------------------------\n\
", ident);
}

static void
version(int argc, char *argv[])
{
	if (!output && !debug)
		return;
	(void) fprintf(stdout, "\
%1$s (OpenSS7 %2$s) %3$s (%4$s)\n\
Written by Brian Bidulock.\n\
\n\
Copyright (c) 2008, 2009, 2010, 2015  Monavacon Limited.\n\
Copyright (c) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008  OpenSS7 Corporation.\n\
Copyright (c) 1997, 1998, 1999, 2000, 2001  Brian F. G. Bidulock.\n\
This is free software; see the source for copying conditions.  There is NO\n\
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\
\n\
Distributed by OpenSS7 under GNU Affero General Public License Version 3,\n\
with conditions, incorporated herein by reference.\n\
\n\
See `%1$s --copying' for copying permissions.\n\
", NAME, PACKAGE, VERSION, PACKAGE_ENVR " " PACKAGE_DATE);
}

static void
usage(int argc, char *argv[])
{
	if (!output && !debug)
		return;
	(void) fprintf(stderr, "\
Usage:\n\
    %1$s [options]\n\
    %1$s {-h|--help}\n\
    %1$s {-V|--version}\n\
    %1$s {-C|--copying}\n\
", argv[0]);
}

static void
help(int argc, char *argv[])
{
	if (!output && !debug)
		return;
	(void) fprintf(stdout, "\
Usage:\n\
    %1$s [options]\n\
    %1$s {-h|--help}\n\
    %1$s {-V|--version}\n\
    %1$s {-C|--copying}\n\
Options:\n\
  Command:\n\
    -h, --help, -?, --?\n\
        print this usage information and exit\n\
    -V, --version\n\
        print version and exit\n\
    -C, --copying\n\
        print copying permission and exit\n\
  Common:\n\
    -c, --ct SECONDS\n\
        ES-IS configuration timer (seconds) [default: %2$d]\n\
    -r, --rt SECONDS\n\
        ES-IS redirect timer (seconds) [default: %3$d]\n\
    -y, --notify [FLAG], --no-notify\n\
        immediate notification [default: %4$d]\n\
    -e, --esqaddr SNPA\n\
        ES multicast SNPA address [default: %5$s]\n\
    -i, --isqaddr SNPA\n\
        IS multicast SNPA address [default: %6$s]\n\
    -n, --dryrun\n\
        check but do not write [default: false]\n\
    -q, --quiet\n\
        suppress normal output (equivalent to --verbose=0)\n\
    -d, --debug [LEVEL]\n\
        increment or set debug LEVEL [default: 0]\n\
    -v, --verbose [LEVEL]\n\
        increment or set output verbosity LEVEL [default: 1]\n\
        this option may be repeated.\n\
", argv[0], config.ct, config.rt, config.notify, config.esqaddr, config.isqaddr);
}

#define COMMAND_DFLT  0
#define COMMAND_CNFG  1
#define COMMAND_HELP  2
#define COMMAND_VERS  3
#define COMMAND_COPY  4

int
main(int argc, char *argv[])
{
	int command = COMMAND_DFLT;
	int c, val, len, bad;
	int start = 0;

	for (;;) {
#if defined _GNU_SOURCE
		int option_index = 0;
                /* *INDENT-OFF* */
                static struct option long_options[] = {
			{"ct",		required_argument,	NULL, 'c'},
			{"rt",		required_argument,	NULL, 'r'},
			{"notify",	optional_argument,	NULL, 'y'},
			{"no-notify",	no_argument,		NULL, 'Y'},
			{"esqaddr",	required_argument,	NULL, 'e'},
			{"isqaddr",	required_argument,	NULL, 'i'},
			{"dryrun",	no_argument,		NULL, 'n'},
			{"quiet",	no_argument,		NULL, 'q'},
			{"debug",	optional_argument,	NULL, 'd'},
			{"verbose",	optional_argument,	NULL, 'v'},
                        {"help",        no_argument,		NULL, 'h'},
			{"version",	no_argument,		NULL, 'V'},
			{"copying",	no_argument,		NULL, 'C'},
			{"?",		no_argument,		NULL, 'H'},
			{ 0, }
                };
                /* *INDENT-ON* */

		c = getopt_long_only(argc, argv, "c:r:y::Ye:i:nd::v::hVC?W:", long_options, &option_index);
#else				/* _GNU_SOURCE */
		c = getopt(argc, argv, "c:r:y:Ye:i:nqd:vhVC?");
#endif				/* _GNU_SOURCE */
		if (c == -1) {
			if (debug)
				fprintf(stderr, "%s: done options processing\n", argv[0]);
			break;
		}
		switch (c) {
		case 0:
			goto bad_usage;
		case 'c':	/* -c, --ct SECONDS */
			command = COMMAND_CNFG;
			config.ct = strtoul(optarg, NULL, 0);
			break;
		case 'r':	/* -r, --rt SECONDS */
			command = COMMAND_CNFG;
			config.rt = strtoul(optarg, NULL, 0);
			break;
		case 'y':	/* -y, --notify [FLAG] */
			command = COMMAND_CNFG;
			if (optarg == NULL)
				config.notify = 1;
			else
				config.notify = strtol(optarg, NULL, 0) ? 1 : 0;
			break;
		case 'Y':	/* --no-notify */
			command = COMMAND_CNFG;
			config.notify = 0;
			break;
		case 'e':	/* -e, --esqaddr SNPA */
			command = COMMAND_CNFG;
			if ((len = strlen(optarg)) != 14) {
				if (output || debug)
					fprintf(stderr, "%s: invalid ES SNPA length %d\n", argv[0], len);
				goto bad_option;
			}
			if ((optarg[12] != 'f' && optarg[12] != 'F')
			    || (optarg[13] != 'e' && optarg[13] != 'E'))
				goto bad_option;
			/* check for hexadecimal digits only */
			if ((bad = strspn(optarg, "0123456789abcdefABCDEF")) < len) {
				if (output || debug)
					fprintf(stderr, "%s: invalid hexadecimal character '%c' in ES SNPA address\n",
						argv[0], optarg[bad]);
				goto bad_option;
			}
			strncpy(config.esqaddr, optarg, sizeof(config.esqaddr));
			break;
		case 'i':	/* -i, --isqaddr SNPA */
			command = COMMAND_CNFG;
			if ((len = strlen(optarg)) != 14) {
				if (output || debug)
					fprintf(stderr, "%s: invalid IS SNPA length %d\n", argv[0], len);
				goto bad_option;
			}
			/* check for hexadecimal digits only */
			if ((bad = strspn(optarg, "0123456789abcdefABCDEF")) < len) {
				if (output || debug)
					fprintf(stderr, "%s: invalid hexadecimal character '%c' in IS SNPA address\n",
						argv[0], optarg[bad]);
				goto bad_option;
			}
			strncpy(config.isqaddr, optarg, sizeof(config.isqaddr));
			break;
		case 'n':	/* -n, --dryrun */
			dryrun = 1;
			break;
		case 'q':	/* -q, --quiet */
			if (debug)
				fprintf(stderr, "%s: suppressing normal output\n", argv[0]);
			debug = 0;
			output = 0;
			break;
		case 'd':	/* -d, --debug [level] */
			if (debug)
				fprintf(stderr, "%s: increasing debug verbosity\n", argv[0]);
			if (optarg == NULL) {
				debug++;
			} else {
				if ((val = strtol(optarg, NULL, 0)) < 0)
					goto bad_option;
				debug = val;
			}
			break;
		case 'v':	/* -v, --verbose [level] */
			if (debug)
				fprintf(stderr, "%s: increasing output verbosity\n", argv[0]);
			if (optarg == NULL) {
				output++;
				break;
			}
			if ((val = strtol(optarg, NULL, 0)) < 0)
				goto bad_option;
			output = val;
			break;
		case 'h':	/* -h, --help */
		case 'H':	/* -H, --? */
			if (debug)
				fprintf(stderr, "%s: printing help message\n", argv[0]);
			command = COMMAND_HELP;
			break;
		case 'V':	/* -V, --version */
			if (debug)
				fprintf(stderr, "%s: printing version message\n", argv[0]);
			command = COMMAND_VERS;
			break;
		case 'C':	/* -C, --copying */
			if (debug)
				fprintf(stderr, "%s: printing copying message\n", argv[0]);
			command = COMMAND_COPY;
			break;
		case '?':
		default:
		      bad_option:
			optind--;
			goto bad_nonopt;
		      bad_nonopt:
			if (output || debug) {
				if (optind < argc) {
					fprintf(stderr, "%s: syntax error near '", argv[0]);
					while (optind < argc)
						fprintf(stderr, "%s ", argv[optind++]);
					fprintf(stderr, "'\n");
				} else {
					fprintf(stderr, "%s: missing option or argument", argv[0]);
					fprintf(stderr, "\n");
				}
				fflush(stderr);
			      bad_usage:
				usage(argc, argv);
			}
			exit(2);
		}
	}
	if (optind < argc) {
		if (debug)
			fprintf(stderr, "%s: excess non-option arguments\n", argv[0]);
		goto bad_nonopt;
	}
	switch (command) {
	case COMMAND_DFLT:
	case COMMAND_CNFG:
		do_config(argc, argv, start);
		break;
	case COMMAND_HELP:
		help(argc, argv);
		break;
	case COMMAND_VERS:
		version(argc, argv);
		break;
	case COMMAND_COPY:
		copying(argc, argv);
		break;
	}
	exit(0);
}
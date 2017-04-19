/**
 *  @file     lgr.c
 *  @brief    lgr.c
 *  @version  v.5
 *  @date     02/15/2017 18:08:02
 *  @author   Anonrate
 *  @copyright
 *    \parblock
 *      GNU General Public License
 *
 *      Copyright (C) 2017 Anonrate
 *
 *      This program is free software: you can redistribute it and/or modify
 *        it under the terms of the GNU General Public License as published by
 *        the Free Software Foundation, either version 3 of the License, or
 *        (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *        but WITHOUT ANY WARRANTY; without even the implied warranty of
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *        GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *        along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *    \endparblock
 */

#include  <stdio.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <errno.h>
#include  <string.h>
#include  <time.h>
#include  <assert.h>

#define LGR_DEV
#undef  LGR_DEV

#include  "../inc/lgr.h"

static const char*
getvlvln(enum verblvls verblvl)
{
    return  ((verblvl ==              FATAL)  ? FATAL_STR
           : (verblvl ==              ERROR)  ? ERROR_STR
           : (verblvl ==            WARNING)  ? WARNING_STR
           : (verblvl ==             NOTICE)  ? NOTICE_STR
           : (verblvl ==               INFO)  ? INFO_STR
           : (verblvl ==              DEBUG)  ? DEBUG_STR
           : (verblvl ==              TRACE)  ? TRACE_STR
           : (verblvl ==     INTERN_WARNING)  ? INTERN_WARNING_STR
           : (verblvl ==        INTERN_INFO)  ? INTERN_INFO_STR
           : (verblvl ==       INTERN_DEBUG)  ? INTERN_DEBUG_STR
           : (verblvl ==       INTERN_TRACE)  ? INTERN_TRACE_STR
#ifdef  LGR_DEV
           : (verblvl == DEV_INTERN_WARNING)  ? DEV_INTERN_WARNING_STR
           : (verblvl ==    DEV_INTERN_INFO)  ? DEV_INTERN_INFO_STR
           : (verblvl ==   DEV_INTERN_DEBUG)  ? DEV_INTERN_DEBUG_STR
           : (verblvl ==   DEV_INTERN_TRACE)  ? DEV_INTERN_TRACE_STR
#endif  /* LGR_DEV                */

           :                                    NVALID_VERB_LVL_STR);
}

#ifdef  LGR_DEV
static char           *vlvln    = DEV_INTERN_TRACE_STR;
static enum verblvls  vlvl      = DEV_INTERN_TRACE;
#else
static char           *vlvln    = WARNING_STR;
static enum verblvls  vlvl      = WARNING;
#endif  /* LGR_DEV */

static int            ltf       = 0;

static enum verblvls  fprio     = ERROR;

static int            errwarn   = 0;

static char           *fnsfxfmt = "%y%m%d%H%M%S";
static char           *fname    = "\0";

static char           *fnout    = "\0";

static FILE           *fout     = 0;

void
lgrf(enum   verblvls        verblvl,
     const            char  *timestr,
     const            char  *filestr,
     const            char  *funcstr,
     const  unsigned  int   line,
     const            char  *strfmt, ...)
{
    if (!(verblvl > 0
                && verblvl <= TRACE
         )  ? verblvl
            : NVALID_VERB_LVL) { return; }

    const unsigned char tmpvlvl =
        ((errwarn && verblvl == WARNING) ? ERROR : verblvl);

    if (tmpvlvl > vlvl) { return; }
    FILE *fpstrm  =
        ((errwarn)
         ? ((verblvl <= WARNING)
             ? stderr
             : stdout)
         : ((verblvl <= ERROR)
             ? stderr
             : stdout));

    int doltf = ltf && fout && tmpvlvl <= fprio;
    if (timestr)
    {
        fprintf(fpstrm,   "[%s]  %-18s:  ", timestr,  getvlvln(verblvl));
        if (doltf) {
            fprintf(fout, "[%s]  %-18s:  ", timestr,  getvlvln(verblvl));
        }
    }

    if (filestr || funcstr || line)
    {
        if (filestr)
        {
            fprintf(fpstrm,   "%s:",  filestr);
            if (doltf) {
                fprintf(fout, "%s:",  filestr);
            }
        }

        if (funcstr)
        {
            fprintf(fpstrm,   "%s:",  funcstr);
            if (doltf) {
                fprintf(fout, "%s:",  funcstr);
            }
        }

        if (line)
        {
            fprintf(fpstrm,   "%u:", line);
            if (doltf) {
                fprintf(fout, "%u:", line);
            }
        }

        fprintf(fpstrm,             "   ");
        if (doltf) { fprintf(fout,  "   "); }
    }

    va_list ap;
    va_start(ap, strfmt);
    vfprintf(fpstrm,            strfmt, ap);
    if (doltf) { vfprintf(fout, strfmt, ap); }
    va_end(ap);
}

//#include  "../inc/lgr.h"

#ifndef NAME_MAX
#define NAME_MAX  0xfe
#endif  /* NAME_MAX */

//#include  "../inc/lgrmsgs.h"

#ifdef  LGR_DEV
int
main(int argc, char **argv)
{
    setverblvl(TRACE);
    setfileprio(TRACE);
    setlogtofile(1);
    setfilename("lgr");
    logltffnlf(INFO, "%s\n", "Doing this shit.");
    return EXIT_SUCCESS;
}
#endif  /* LGR_DEV    */


const char*
getverblvlname(enum verblvls verblvl)
{
    return getvlvln(verblvl);
}

int
isverblvl(unsigned char lvl)
{
    return (strcmp(getverblvlname(lvl), NVALID_VERB_LVL_STR)
            ? (int)lvl
            : NVALID_VERB_LVL);
}

static void
mallstr(const char *stra, char **pstrb)
{
    size_t tmpstrbsz  = strlen(*pstrb);
    size_t tmpstrasz  = strlen(stra);
    if (tmpstrbsz != tmpstrasz) { *pstrb = malloc(tmpstrasz + 1lu); }
}

static char*
setvlvln(enum verblvls verblvl)
{
    const char *tmpvlvln = getverblvlname(verblvl);
    if (!strcmp(vlvln, tmpvlvln)) { return vlvln; }
    if (strcmp(tmpvlvln, NVALID_VERB_LVL_STR))
    {
        mallstr(tmpvlvln, &vlvln);
        strcpy(vlvln, tmpvlvln);
    }

    return vlvln;
}

static unsigned char
setvlvl(unsigned char verblvl)
{
    return (verblvl = vlvl);
}

unsigned char
setverblvl(enum verblvls verblvl)
{
    if (vlvl == verblvl) { return vlvl; }

    if (isverblvl(verblvl))
    {
        setvlvl(verblvl);
        setvlvln(verblvl);
    }

    return vlvl;
}

enum verblvls
getverblvl(void)
{
    return vlvl;
}

enum verblvls
getfileprio(void)
{
    return fprio;
}

int
geterrwarn(void)
{
    return errwarn;
}

enum verblvls
setfileprio(enum verblvls fileprio)
{
    if (!isverblvl(fileprio)) { return (unsigned char)0; }

    return (fprio = fileprio);
}

int
seterrwarn(int treatwarnerr)
{
    return (errwarn = treatwarnerr);
}

static char*
setfout(void)
{
    time_t    t       = time(0);
    struct tm *ti     = localtime(&t);
    char      *tmpfno = malloc(NAME_MAX);

    strftime(tmpfno, NAME_MAX, fnsfxfmt, ti);

    size_t tmpfnosz = sprintf(tmpfno, "%s-%s", tmpfno, fname);

    realloc(tmpfno, tmpfnosz + 1lu);
    mallstr(tmpfno, &fnout);

    fnout = tmpfno;
    fout  = fopen(fnout, "a");

    return fnout;
}

char*
setfilename(char *filename)
{
    if (!filename || !ltf) { return fname; }

    mallstr(filename, &fname);

    fname = filename;

    setfout();

    return fname;
}

int
setlogtofile(int logtofile)
{
    return (ltf = logtofile);
}

int
getlogtofile(void)
{
    return ltf;
}

char*
setfilenamesuffixfmt(const char *suffixfmt)
{
    time_t    t       = time(0);
    struct tm *ti     = localtime(&t);
    char      *tmpfno = malloc(NAME_MAX);

    size_t tmpfnosz = strftime(tmpfno, NAME_MAX, fnsfxfmt, ti);
    if (!tmpfnosz) { return fnsfxfmt; }

    mallstr(suffixfmt, &fnsfxfmt);
    strcpy(fnsfxfmt, suffixfmt);

    return fnsfxfmt;
}

char*
getfilenamesuffixfmt(void)
{
    return fnsfxfmt;
}

char*
getfilenameout(void)
{
    return fnout;
}

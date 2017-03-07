/**
 *  @file     lgr.c
 *  @brief    lgr.c
 *  @version  v.4
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
#include  <stdnoreturn.h>
#include  <errno.h>
#include  <string.h>
#include  <time.h>
#include  <assert.h>

#define LGR_DEV
#ifdef  LGR_DEV
#ifndef ENABLE_INTERN_WARNING
#define ENABLE_INTERN_WARNING
#endif  /* ENABLE_INTERN_WARNING  */

#ifndef ENABLE_INTERN_INFO
#define ENABLE_INTERN_INFO
#endif  /* ENABLE_INTERN_INFO     */

#ifndef ENABLE_INTERN_DEBUG
#define ENABLE_INTERN_DEBUG
#endif  /* ENABLE_INTERN_DEBUG    */

#ifndef ENABLE_INTERN_TRACE
#define ENABLE_INTERN_TRACE
#endif  /* ENABLE_INTERN_TRACE    */
#endif  /* LGR_DEV                */

#include  "../inc/lgrverblvls.h"

static const char*
getvlvln(enum verblvls verblvl)
{
    return  ((verblvl ==          FATAL)  ? FATAL_STR
           : (verblvl ==          ERROR)  ? ERROR_STR
           : (verblvl ==        WARNING)  ? WARNING_STR
           : (verblvl ==         NOTICE)  ? NOTICE_STR
           : (verblvl ==           INFO)  ? INFO_STR
           : (verblvl ==          DEBUG)  ? DEBUG_STR
           : (verblvl ==          TRACE)  ? TRACE_STR
#ifdef  ENABLE_INTERN_WARNING
           : (verblvl == INTERN_WARNING)  ? INTERN_WARNING_STR
#endif  /* ENABLE_INTERN_WARNING  */

#ifdef  ENABLE_INTERN_INFO
           : (verblvl ==    INTERN_INFO)  ? INTERN_INFO_STR
#endif  /* ENABLE_INTERN_INFO     */

#ifdef  ENABLE_INTERN_DEBUG
           : (verblvl ==   INTERN_DEBUG)  ? INTERN_DEBUG_STR
#endif  /* ENABLE_INTERN_DEBUG    */

#ifdef  ENABLE_INTERN_TRACE
           : (verblvl ==   INTERN_TRACE)  ? INTERN_TRACE_STR
#endif  /* ENABLE_INTERN_TRACE    */

           :                                NVALID_VERB_LVL_STR);
}

#ifdef  LGR_DEV
static char           *vlvln    = INTERN_TRACE_STR;
static enum verblvls  vlvl      = INTERN_TRACE;
#else
static char           *vlvln    = WARNING_STR;
static enum verblvls  vlvl      = WARNING;
#endif  /* LGR_DEV */

static int            ltf       = 0;

static enum verblvls  fprio     = ERROR;

static int            errwarn   = 0;

static char           *fnsfxfmt = "%y%m%d%H%M%S";
static char           *fname    = "x";

static char           *fnout    = "g";

static FILE           *fout;

static void
lgrf(enum   verblvls        verblvl,
     const            char  *timestr,
     const            char  *filestr,
     const            char  *funcstr,
     const  unsigned  int   line,
     const            char  *strfmt, ...)
{
    if (!(verblvl > 0
                && verblvl <= INTERN_TRACE)
            ? verblvl
            : NVALID_VERB_LVL) { return; }

    const unsigned char tmpvlvl =
        ((errwarn && verblvl == WARNING) ? ERROR : verblvl);

    if (tmpvlvl > vlvl) { return; }
    FILE *fpstrm  =
        ((errwarn)
         ? ((verblvl == INTERN_WARNING
                 || verblvl <= WARNING)
             ? stderr
             : stdout)
         : ((verblvl <= ERROR)
             ? stderr
             : stdout));


    if (timestr || line)
    {
        fprintf(fpstrm, "[");
        if (timestr)          { fprintf(fpstrm, "%s", timestr); }
        if (timestr && line)  { fprintf(fpstrm, ":%7u]  ", line); }
        else if (line)        { fprintf(fpstrm, "%7u]  ", line); }
        else { fprintf(fpstrm, "%9s  ", "]"); }
    }

    fprintf(fpstrm, "%-14s  ", getvlvln(verblvl));
    va_list ap;
    va_start(ap, strfmt);
    vfprintf(fpstrm, strfmt, ap);
    va_end(ap);
}

#ifndef NAME_MAX
#define NAME_MAX  0xfe
#endif  /* NAME_MAX */

#ifdef  LGR_DEV
#ifndef LOGLTXF_H
#include  "../inc/lgrmsgs.h"
#include  "../inc/logltxf.h"
#endif  /* LOGLTXF_H  */

int
main(int argc, char **argv)
{
    INFUNC_MSGL(INTERN_DEBUG);
    return EXIT_SUCCESS;
}
#endif  /* LGR_DEV    */

#define fatalf(fmt, ...)                      \
    {                                         \
        fprintf(stderr,                       \
                "\n[%s:%s:%s:%u]  FATAL:  ",  \
                __TIME__,                     \
                __FILE__,                     \
                __func__,                     \
                __LINE__);                    \
        fprintf(stderr, (fmt), __VA_ARGS__);  \
        fprintf(stderr, "\n");                \
        exit(EXIT_FAILURE);                   \
    }

#define fatalstr(str)                         \
    {                                         \
        fprintf(stderr,                       \
                "\n[%s:%s:%s:%u]  FATAL:  ",  \
                __TIME__,                     \
                __FILE__,                     \
                __func__,                     \
                __LINE__);                    \
        fprintf(stderr, "%s\n", (str));       \
        exit(EXIT_FAILURE);                   \
    }

#include  "../inc/lgr.h"

char*
getverblvlname(enum verblvls verblvl)
{
    INFUNC_MSGL(INTERN_DEBUG);

    unsigned char tmpvlvl = INTERN_INFO;

    char *tmpvlvln  = verblvl == INTERN_TRACE   ? INTERN_TRACE_STR
                    : verblvl == INTERN_DEBUG   ? INTERN_DEBUG_STR
                    : verblvl == INTERN_INFO    ? INTERN_INFO_STR
                    : verblvl == INTERN_WARNING ? INTERN_WARNING_STR
                    : verblvl == TRACE          ? TRACE_STR
                    : verblvl == DEBUG          ? DEBUG_STR
                    : verblvl == INFO           ? INFO_STR
                    : verblvl == NOTICE         ? NOTICE_STR
                    : verblvl == WARNING        ? WARNING_STR
                    : verblvl == ERROR          ? ERROR_STR
                    : verblvl == FATAL          ? FATAL_STR

                    : (tmpvlvl = WARNING, NVALID_VERB_LVL_STR);

    return tmpvlvln;
}

int
isverblvl(unsigned char lvl)
{

    INFUNC_MSGL(INTERN_DEBUG);
    unsigned char tmpvlvl = INTERN_INFO;

    int tmplvl =
        ((lvl && (lvl <= INTERN_DEBUG))
         ? lvl
         : (tmpvlvl = INTERN_WARNING, NVALID_VERB_LVL));

    return tmplvl;
}

static void
mallstr(char *stra, char **pstrb, char *strbn)
{
    if (!*pstrb) { (*pstrb) = malloc(1); }

    size_t tmpstrbsz   = strlen(*pstrb);

    size_t tmpstrasz  = strlen(stra);
    if (tmpstrbsz != tmpstrasz)
    {
        if (!(*pstrb = malloc(tmpstrasz + 1ul))) {
           // fatalstr(MALLOC_FAIL);
        }

    }
}

static char*
setvlvln(enum verblvls verblvl)
{

    char *tmpvlvln = getverblvlname(verblvl);
    if (!strcmp(vlvln, tmpvlvln))
    {

        return vlvln;
    }

    if (strcmp(tmpvlvln, NVALID_VERB_LVL_STR))
    {

        mallstr(tmpvlvln, &vlvln, "vlvln");

        vlvln = tmpvlvln;

        return vlvln;
    }


    return vlvln;
}

static unsigned char
setvlvl(unsigned char verblvl)
{

    vlvl = verblvl;

    return (verblvl);
}

int
setverblvl(enum verblvls verblvl)
{

    if (vlvl == verblvl)
    {
        return vlvl;
    }

    if (isverblvl(verblvl))
    {
        setvlvl(verblvl);

        setvlvln(verblvl);

        int ti = strcmp(vlvln, getverblvlname(vlvl));
        //if (ti) { fatalf(VALIDATE_FAIL, ti); }


        return vlvl;
    }

    return vlvl;
}

enum verblvls
getverblvl()
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

    unsigned char tmpvlvl = isverblvl(fileprio);
    fprio = fileprio;

    return fprio;
}

int
seterrwarn(int treatwarnerr)
{

    errwarn = treatwarnerr;

    return errwarn;
}

static char*
setfout(void)
{

    if (!fname)
    {
    }

    time_t t        = time(0);

    struct tm *ti   = localtime(&t);
    if (!ti) { fatalstr(strerror(errno)); }

    char *tmpfno    = malloc(NAME_MAX);
    //if (!tmpfno) { fatalstr(MALLOC_FAIL); }

    size_t tmpfnosz = strftime(tmpfno, NAME_MAX, fnsfxfmt, ti);
    //if (!tmpfnosz) { fatalf(STR_NZ, "tmpfno", tmpfnosz); }

    tmpfnosz        = sprintf(tmpfno, "%s-%s", tmpfno, fname);
    //if (!tmpfnosz) { fatalf(STR_NZ, "tmpfno", tmpfnosz) }

    //if (!realloc(tmpfno, tmpfnosz + 1)) { fatalstr(REALLOC_FAIL); }

    mallstr(tmpfno, &fnout, "fnout");
    fnout = tmpfno;
    fout = fopen(fnout, "a");

    return fnout;
}

char*
setfilename(char *filename)
{
    if (!filename)
    {
        return fname;
    }

    mallstr(filename, &fname, "fname");

    fname = filename;
    setfout();

    return fname;
}

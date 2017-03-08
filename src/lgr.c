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
static char           *fname    = "\0";

static char           *fnout    = "\0";

static FILE           *fout     = 0;

static void
lgrf(enum   verblvls        verblvl,
     const            char  *timestr,
     const            char  *filestr,
     const            char  *funcstr,
     const  unsigned  int   line,
     const            char  *strfmt, ...)
{
    if (!(verblvl > 0
                && verblvl <=
#if   defined ENABLE_INTERN_TRACE
                              INTERN_TRACE
#elif defined ENABLE_INTERN_DEBUG   /* !defined ENABLE_INTERN_TRACE   */
                              INTERN_DEBUG
#elif defined ENABLE_INTERN_INFO    /* !defined ENABLE_INTERN_DEBUG   */
                              INTERN_INFO
#elif defined ENABLE_INTERN_WARNING /* !defined ENABLE_INTERN_INFO    */
                              INTERN_WARNING
#else                                 /* !defined ENABLE_INTERN_WARNING */
                              TRACE
#endif                                /*
                                       *    ENABLE_INTERN_TRACE
                                       *  : ENABLE_INTERN_DEBUG
                                       *  : ENABLE_INTERN_INFO
                                       *  : ENABLE_INTERN_WARNING
                                       *  :
                                       */
         )  ? verblvl
            : NVALID_VERB_LVL) { return; }

    const unsigned char tmpvlvl =
        ((errwarn && verblvl == WARNING) ? ERROR : verblvl);

    if (tmpvlvl > vlvl) { return; }
    FILE *fpstrm  =
        ((errwarn)
         ? ((verblvl
#ifdef  ENABLE_INTERN_WARNING
                     == INTERN_WARNING
                 || verblvl
#endif  /* ENABLE_INTERN_WARNING */
                            <= WARNING)
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

#if defined ENABLE_INTERN_WARNING \
 || defined ENABLE_INTERN_INFO    \
 || defined ENABLE_INTERN_DEBUG   \
 || defined ENABLE_INTERN_TRACE
#ifndef LGRMSGS_H
#include  "../inc/lgrmsgs.h"
#endif  /* LGRMSGS_H */

#ifndef LOGLTXF_H
#include  "../inc/logltxf.h"
#endif  /* LOGLTXF_H */
#endif  /*
         *     ENABLE_INTERN_WARNING
         *  || ENABLE_INTERN_INFO
         *  || ENABLE_INTERN_DEBUG
         *  || ENABLE_INTERN_TRACE
         */

#include  "../inc/lgr.h"

#ifdef  LGR_DEV
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


const char*
getverblvlname(enum verblvls verblvl)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

#if defined ENABLE_INTERN_TRACE && defined LGRMSGS_H
    CALLFN_MSGLS(INTERN_TRACE, "getvlvln()");
#endif  /* ENABLE_INTERN_TRACE  && LGRMSGS_H    */
    const     char *tmpvlvln  = getvlvln(verblvl);

    unsigned  char  tmpvlvl;
#ifdef  ENABLE_INTERN_INFO
    tmpvlvl = INTERN_INFO;
#endif  /* ENABLE_INTERN_INFO */
              char  *tmpstr = ((strcmp(tmpvlvln, NVALID_VERB_LVL_STR))
                            ? " "
                            : (tmpvlvl = WARNING, " not "));
    logltffnlf(tmpvlvl, "%hhu is%sa valid verbose level!\n", verblvl, tmpstr);

#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    R_MSGLS(INTERN_DEBUG, tmpvlvln);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return tmpvlvln;
}

int
isverblvl(unsigned char lvl)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    unsigned char tmpvlvl = INTERN_INFO;

    int tmplvl =
        ((lvl && (lvl <= INTERN_DEBUG))
         ? lvl
         : (tmpvlvl = INTERN_WARNING, NVALID_VERB_LVL));

#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    R_MSGLD(INTERN_DEBUG, tmplvl);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return tmplvl;
}

static void
mallstr(const char *stra, char **pstrb, char *strbn)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

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
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

#if defined ENABLE_INTERN_TRACE && defined LGRMSGS_H
    CALLFN_MSGLS(INTERN_TRACE, "getverblvlname()");
#endif  /* ENABLE_INTERN_TRACE  && LGRMSGS_H    */
    const char *tmpvlvln = getverblvlname(verblvl);
    if (!strcmp(vlvln, tmpvlvln))
    {
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
        R_MSGLS(INTERN_DEBUG, vlvln);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
        return vlvln;
    }

    if (strcmp(tmpvlvln, NVALID_VERB_LVL_STR))
    {
#if defined ENABLE_INTERN_TRACE && defined LGRMSGS_H
        CALLFN_MSGLS(INTERN_TRACE, "mallstr()");
#endif  /* ENABLE_INTERN_TRACE  && LGRMSGS_H    */
        mallstr(tmpvlvln, &vlvln, "vlvln");

        strcpy(vlvln, tmpvlvln);
        //vlvln = tmpvlvln;
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
        R_MSGLS(INTERN_DEBUG, vlvln);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
        return vlvln;
    }

#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    R_MSGLS(INTERN_DEBUG, vlvln);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return vlvln;
}

static unsigned char
setvlvl(unsigned char verblvl)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

    vlvl = verblvl;

#if defined ENABLE_INTERN_DEBUG && defined R_MSGLHHU
    R_MSGLS(INTERN_DEBUG, verblvl);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return (verblvl);
}

int
setverblvl(enum verblvls verblvl)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

    if (vlvl == verblvl)
    {
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
        R_MSGLD(INTERN_DEBUG, vlvl);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
        return vlvl;
    }

    if (isverblvl(verblvl))
    {
#if defined ENABLE_INTERN_TRACE && defined LGRMSGS_H
        CALLFN_MSGLS(INTERN_TRACE, "setvlvl()");
#endif  /* ENABLE_INTERN_TRACE  && LGRMSGS_H    */
        setvlvl(verblvl);

#if defined ENABLE_INTERN_TRACE && defined LGRMSGS_H
        CALLFN_MSGLS(INTERN_TRACE, "setvlvln()");
#endif  /* ENABLE_INTERN_TRACE  && LGRMSGS_H    */
        setvlvln(verblvl);

#if defined ENABLE_INTERN_TRACE && defined LGRMSGS_H
        CALLFN_MSGLS(INTERN_TRACE, "getverblvlname()");
#endif  /* ENABLE_INTERN_TRACE  && LGRMSGS_H   */
        int ti = strcmp(vlvln, getverblvlname(vlvl));
        //if (ti) { fatalf(VALIDATE_FAIL, ti); }

#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
        R_MSGLD(INTERN_DEBUG, vlvl);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
        return vlvl;
    }
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    R_MSGLD(INTERN_DEBUG, vlvl);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return vlvl;
}

enum verblvls
getverblvl(void)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

#if defined ENABLE_INTERN_INFO  && defined LGRMSGS_H
    GET_MSGLS(INTERN_INFO, "vlvl");
#endif  /* ENABLE_INTERN_INFO   && LGRMSGS_H    */

#if defined ENABLE_INTERN_DEBUG && defined R_MSGLHHU
    R_MSGLS(INTERN_DEBUG, fprio);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return vlvl;
}

enum verblvls
getfileprio(void)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

#if defined ENABLE_INTERN_INFO  && defined LGRMSGS_H
    GET_MSGLS(INTERN_INFO, "fprio");
#endif  /* ENABLE_INTERN_INFO   && LGRMSGS_H    */

#if defined ENABLE_INTERN_DEBUG && defined R_MSGLHHU
    R_MSGLS(INTERN_DEBUG, fprio);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return fprio;
}

int
geterrwarn(void)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

#if defined ENABLE_INTERN_INFO  && defined LGRMSGS_H
    GET_MSGLS(INTERN_INFO, "ltf");
#endif  /* ENABLE_INTERN_INFO   && LGRMSGS_H    */

#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    R_MSGLD(INTERN_DEBUG, errwarn);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return errwarn;
}

enum verblvls
setfileprio(enum verblvls fileprio)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

#if defined ENABLE_INTERN_TRACE && defined LGRMSGS_H
    CALLFN_MSGLS(INTERN_TRACE, "isverblvl()");
#endif  /* ENABLE_INTERN_TRACE  && LGRMSGS_H    */
    unsigned char tmpvlvl = isverblvl(fileprio);

#if defined ENABLE_INTERN_INFO  && defined LGRMSGS_H
    SET_MSGLSHHU(INTERN_INFO, "fprio", fprio, fileprio);
#endif  /* ENABLE_INTERN_INFO   && LGRMSGS_H    */
    fprio = fileprio;

#if defined ENABLE_INTERN_DEBUG && defined R_MSGLHHU
    R_MSGLS(INTERN_DEBUG, fprio);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return fprio;
}

int
seterrwarn(int treatwarnerr)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

#if defined ENABLE_INTERN_INFO  && defined LGRMSGS_H
    SET_MSGLSD(INTERN_INFO, "errwarn", errwarn, treatwarnerr);
#endif  /* ENABLE_INTERN_INFO   && LGRMSGS_H    */
    errwarn = treatwarnerr;

#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    R_MSGLD(INTERN_DEBUG, errwarn);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return errwarn;
}

static char*
setfout(void)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

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

#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    R_MSGLS(INTERN_DEBUG, fnout);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return fnout;
}

char*
setfilename(char *filename)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

    if (!filename)
    {
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
        R_MSGLS(INTERN_DEBUG, fname);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
        return fname;
    }

    mallstr(filename, &fname, "fname");

    fname = filename;
    setfout();

#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    R_MSGLS(INTERN_DEBUG, fname);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
    return fname;
}

int
getlogtofile(void)
{
#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    INFUNC_MSGL(INTERN_DEBUG);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */

#if defined ENABLE_INTERN_INFO  && defined LGRMSGS_H
    GET_MSGLS(INTERN_INFO, "ltf");
#endif  /* ENABLE_INTERN_INFO   && LGRMSGS_H    */

#if defined ENABLE_INTERN_DEBUG && defined LGRMSGS_H
    R_MSGLD(INTERN_DEBUG, ltf);
#endif  /* ENABLE_INTERN_DEBUG  && LGRMSGS_H    */
}

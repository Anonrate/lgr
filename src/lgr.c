/**
 *  @file     lgr.c
 *  @brief    lgr.c
 *  @version  v.1
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

#include  "../inc/lgrverblvls.h"

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

    char *tvlvln    = verblvl == INTERN_TRACE   ? INTERN_TRACE_STR
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
                    : NVALID_VERB_LVL_STR;
    fprintf(fpstrm, "%-14s  ", tvlvln);
    va_list ap;
    va_start(ap, strfmt);
    vfprintf(fpstrm, strfmt, ap);
    va_end(ap);
}

#include  "../inc/lgr.h"
#include  "../inc/lgrmsgs.h"

#ifndef NAME_MAX
#define NAME_MAX  0xfe
#endif  /* NAME_MAX */

#ifdef  LGR_DEV
int
main(int argc, char **argv)
{
    setfilename("lgr");
    printf("%s\n", fnout);
    fclose(fout);
    return EXIT_SUCCESS;
}
#endif  /* LGR_DEV */


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

char*
getverblvlname(enum verblvls verblvl)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

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

    logltf(tmpvlvl,
           XVALID_VERB_LVL_N,
           verblvl,
           !strcmp(tmpvlvln, NVALID_VERB_LVL_STR) ? " not " : " ",
           tmpvlvln);

    logltlf(INTERN_DEBUG, RMSG_S, tmpvlvln);
    return tmpvlvln;
}

int
isverblvl(unsigned char lvl)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    unsigned char tmpvlvl = INTERN_INFO;

    int tmplvl =
        ((lvl && (lvl <= INTERN_DEBUG))
         ? lvl
         : (tmpvlvl = INTERN_WARNING, NVALID_VERB_LVL));

    logltf(tmpvlvl,
           XVALID_VERB_LVL,
           lvl,
           tmplvl ? " " : " not ");

    logltlf(INTERN_DEBUG, RMSG_D, tmplvl);
    return tmplvl;
}

static void
mallstr(char *stra, char **pstrb, char *strbn)
{
    logltlf(INTERN_DEBUG, "%s:%s\n", __func__, *pstrb);

    logltlf(INTERN_DEBUG, CALC_STR, *pstrb);

    if (!*pstrb) { (*pstrb) = malloc(1); }

    size_t tmpstrbsz   = strlen(*pstrb);

    logltlf(INTERN_DEBUG, CALC_STR, stra);
    size_t tmpstrasz  = strlen(stra);
    if (tmpstrbsz != tmpstrasz)
    {
        logltf(INTERN_DEBUG, STR_LEN_MSG, *pstrb, tmpstrbsz);
        logltf(INTERN_DEBUG, STR_LEN_MSG, stra, tmpstrasz);
        logltf(INTERN_DEBUG, REALLOC_NEEDED, strbn);

        logltlf(INTERN_DEBUG, REALLOC_MSG, strbn, tmpstrasz);

        if (!(*pstrb = malloc(tmpstrasz + 1ul))) {
            fatalstr(MALLOC_FAIL);
        }

        logltstr(INTERN_DEBUG, REALLOC_WIN);
    }
}

static char*
setvlvln(enum verblvls verblvl)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    logltlf(INTERN_TRACE, "%s\n", __func__);
    char *tmpvlvln = getverblvlname(verblvl);
    logltlstr(INTERN_DEBUG, VERB_LVL_N_CH_CHCK);
    if (!strcmp(vlvln, tmpvlvln))
    {
        logltf(INTERN_INFO, VERB_LVL_N_ASET, vlvln, vlvl);
        logltstr(INTERN_INFO, VERB_LVL_N_NOCH);

        logltlf(INTERN_DEBUG, RMSG_S, vlvln);
        return vlvln;
    }

    logltlf(INTERN_DEBUG, VERB_LVL_N_CHCK, tmpvlvln);
    if (strcmp(tmpvlvln, NVALID_VERB_LVL_STR))
    {
        logltf(INTERN_INFO, VALID_VERB_LVL_N, tmpvlvln);

        logltlf(INTERN_TRACE, "%s\n", __func__);
        mallstr(tmpvlvln, &vlvln, "vlvln");

        logltlf(INTERN_INFO, SET_STR, "verbose level name");
        vlvln = tmpvlvln;

        logltlf(INTERN_DEBUG, RMSG_S, vlvln);
        return vlvln;
    }

    logltf(INTERN_WARNING, NVALID_VERB_LVL_N, tmpvlvln);

    logltlf(INTERN_DEBUG, RMSG_S, vlvln);
    return vlvln;
}

static unsigned char
setvlvl(unsigned char verblvl)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    logltlf(INTERN_INFO, SET_STR, "verbose level");
    vlvl = verblvl;

    logltlf(INTERN_DEBUG, RMSG_HHU, vlvl);
    return (verblvl);
}

int
setverblvl(enum verblvls verblvl)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    logltlstr(INTERN_DEBUG, VERB_LVL_CH_CHCK);
    if (vlvl == verblvl)
    {
        logltf(INFO, VERB_LVL_ASET, vlvl, vlvln);
        logltstr(INFO, VERB_LVL_NOCH);

        logltlf(INTERN_DEBUG, RMSG_HHU, vlvl);
        return vlvl;
    }

    logltlf(INTERN_TRACE, "%s\n", __func__);
    if (isverblvl(verblvl))
    {
        logltlf(INTERN_TRACE, "%s\n", __func__);
        setvlvl(verblvl);

        logltlf(INTERN_TRACE, "%s\n", __func__);
        setvlvln(verblvl);

        logltlf(INTERN_TRACE, "%s\n", __func__);
        logltlstr(INTERN_DEBUG, VALIDATING_MSG);
        int ti = strcmp(vlvln, getverblvlname(vlvl));
        if (ti) { fatalf(VALIDATE_FAIL, ti); }

        logltstr(INTERN_DEBUG, VALIDATE_WIN);

        logltlf(INTERN_DEBUG, RMSG_HHU, vlvl);
        return vlvl;
    }

    logltlf(INTERN_TRACE, "%s\n", __func__);
    logltf(WARNING, VERB_SET_FAIL, verblvl, getverblvlname(verblvl));
    logltf(WARNING, VERB_LVLN_NOCH, vlvl, vlvln);

    logltlf(INTERN_DEBUG, RMSG_HHU, vlvl);
    return vlvl;
}

enum verblvls
getverblvl()
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    logltlf(INTERN_DEBUG, RMSG_HHU, vlvl);
    return vlvl;
}

enum verblvls
getfileprio(void)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    logltlf(INTERN_DEBUG, RMSG_HHU, fprio);
    return fprio;
}

int
geterrwarn(void)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    logltlf(INTERN_DEBUG, RMSG_D, errwarn);
    return errwarn;
}

enum verblvls
setfileprio(enum verblvls fileprio)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    logltlf(INTERN_TRACE, "%s\n", __func__);
    unsigned char tmpvlvl = isverblvl(fileprio);
    logltlf(INTERN_TRACE, "%s\n", __func__);
    logltf(tmpvlvl ? INTERN_INFO : WARNING,
           XVALID_VERB_LVL,
           fileprio,
           tmpvlvl ? " " : " not ",
           getverblvlname(fileprio));

    logltlf(INTERN_INFO, SET_STR, "file priority");
    fprio = fileprio;

    logltlf(INTERN_DEBUG, RMSG_HHU, fprio);
    return fprio;
}

int
seterrwarn(int treatwarnerr)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    logltlf(INTERN_INFO,
            SET_ERRWARN,
            treatwarnerr ? "Enabling" : "Disabling");
    errwarn = treatwarnerr;

    logltlf(INTERN_DEBUG, RMSG_D, errwarn);
    return errwarn;
}

static char*
setfout(void)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    if (!fname)
    {
        logltstr(WARNING, FN_Z);
        logltstr(NOTICE, FN_ZMSG);
    }

    logltlstr(INTERN_TRACE, "time(0)\n");
    time_t t        = time(0);

    logltlstr(INTERN_TRACE, "localtime(&t)\n");
    struct tm *ti   = localtime(&t);
    if (!ti) { fatalstr(strerror(errno)); }

    logltlf(INTERN_DEBUG, ALLOC_STR_SZ, "tmpfno", NAME_MAX);
    char *tmpfno    = malloc(NAME_MAX);
    if (!tmpfno) { fatalstr(MALLOC_FAIL); }

    logltlf(INTERN_DEBUG, PARSE_STR, "time");
    size_t tmpfnosz = strftime(tmpfno, NAME_MAX, fnsfxfmt, ti);
    if (!tmpfnosz) { fatalf(STR_NZ, "tmpfno", tmpfnosz); }
    logltf(INTERN_INFO, "%s\n", tmpfno);

    logltlf(INTERN_DEBUG, PARSE_STR, "file");
    tmpfnosz        = sprintf(tmpfno, "%s-%s", tmpfno, fname);
    if (!tmpfnosz) { fatalf(STR_NZ, "tmpfno", tmpfnosz) }

    logltlf(INTERN_DEBUG, REALLOC_MSG, tmpfno, tmpfnosz);
    if (!realloc(tmpfno, tmpfnosz + 1)) { fatalstr(REALLOC_FAIL); }

    logltf(INTERN_INFO, "%s\n", tmpfno);
    mallstr(tmpfno, &fnout, "fnout");
    fnout = tmpfno;
    fout = fopen(fnout, "a");
    assert(fout);

    logltlf(INTERN_DEBUG, RMSG_S, fnout);
    return fnout;
}

char*
setfilename(char *filename)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);
    if (!filename)
    {
        logltstr(WARNING, FN_Z);
        logltstr(NOTICE, FN_ZMSG);

        logltlf(INTERN_DEBUG, RMSG_S, fname);
        return fname;
    }

    logltlf(INTERN_TRACE, "%s\n", __func__);
    mallstr(filename, &fname, "fname");

    logltlf(INTERN_DEBUG, SET_STR, "filename");
    fname = filename;
    setfout();

    return fname;
}

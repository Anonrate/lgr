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
#include  <errno.h>
#include  <string.h>
#include  <time.h>
#include  <assert.h>

#define LGR_DEV

#include  "../inc/lgrverblvls.h"

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
#ifdef  LGR_DEV
                              DEV_INTERN_TRACE
#else /* !defined LGR_DEV */
                              TRACE
#endif  /* LGR_DEV        */
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

#include  "../inc/lgr.h"

#ifndef NAME_MAX
#define NAME_MAX  0xfe
#endif  /* NAME_MAX */

#include  "../inc/lgrmsgs.h"

#ifdef  LGR_DEV
int
main(int argc, char **argv)
{
    setfilename("lgr");
    return EXIT_SUCCESS;
}
#endif  /* LGR_DEV    */


const char*
getverblvlname(enum verblvls verblvl)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "enum verblvls verblvl = %hhu\n", verblvl);
#endif  /* LGR_DEV                */

    CALLFN_MSGLS(INTERN_TRACE, "getvlvln()");
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_TRACE,
               "enum verblvls verblvl = verblvl(%hhu)\n",
               verblvl);
#endif  /* LGR_DEV                */
    const     char *tmpvlvln  = getvlvln(verblvl);

    unsigned  char  tmpvlvl   = INTERN_INFO;
              char  *tmpstr   = ((strcmp(tmpvlvln, NVALID_VERB_LVL_STR))
                              ? " "
                              : (tmpvlvl = WARNING, " not "));
    logltffnlf(tmpvlvl, "%hhu is%sa valid verbose level!\n", verblvl, tmpstr);

    R_MSGLS(INTERN_DEBUG, tmpvlvln);
    return tmpvlvln;
}

int
isverblvl(unsigned char lvl)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "unsigned char lvl = %hhu\n", lvl);
#endif  /* LGR_DEV                */

    CALLFN_MSGLS(INTERN_TRACE, "getverblvlname()");
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_TRACE, "enum verblvls verblvl = lvl(%hhu)\n", lvl);
#endif  /* LGR_DEV                */
    if (strcmp(getverblvlname(lvl), NVALID_VERB_LVL_STR))
    {
        R_MSGLHHU(INTERN_DEBUG, NVALID_VERB_LVL);
        return NVALID_VERB_LVL;
    }

    R_MSGLHHU(INTERN_DEBUG, lvl);
    return (int)lvl;
}

static void
mallstr(const char *stra, char **pstrb, char *strbn)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "const char *stra   = %s\n", stra);
    logltffnlf(DEV_INTERN_DEBUG, "      char **pstrb = %s\n", *pstrb);
    logltffnlf(DEV_INTERN_DEBUG, "      char *strbn  = %s\n", strbn);
#endif  /* LGR_DEV                */

    size_t tmpstrbsz  = strlen(*pstrb);
    size_t tmpstrasz  = strlen(stra);
    if (tmpstrbsz != tmpstrasz) {
        if (!(*pstrb = malloc(tmpstrasz + 1ul))) {
            fatalf("Failed to allocate %lu + 1 for %s!\n",
                   tmpstrasz,
                   "*pstrb");
        }
    }
}

static char*
setvlvln(enum verblvls verblvl)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "enum verblvls verblvl = %hhu\n", verblvl);
#endif  /* LGR_DEV                */

    CALLFN_MSGLS(INTERN_TRACE, "getverblvlname()");
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_TRACE,
               "enum verblvls verblvl = verblvl(%hhu)\n",
               verblvl);
#endif  /* LGR_DEV                */
    const char *tmpvlvln = getverblvlname(verblvl);
    if (!strcmp(vlvln, tmpvlvln))
    {
        R_MSGLS(INTERN_DEBUG, vlvln);
        return vlvln;
    }

    if (strcmp(tmpvlvln, NVALID_VERB_LVL_STR))
    {
        CALLFN_MSGLS(INTERN_TRACE, "mallstr()");
#ifdef  LGR_DEV
        MALLSTR_DEVMSGSS(tmpvlvln, vlvln);
#endif  /* LGR_DEV                */
        mallstr(tmpvlvln, &vlvln, "vlvln");

        SET_MSGLSS(INTERN_INFO, vlvln, tmpvlvln);
        strcpy(vlvln, tmpvlvln);

        R_MSGLS(INTERN_DEBUG, vlvln);
        return vlvln;
    }

    R_MSGLS(INTERN_DEBUG, vlvln);
    return vlvln;
}

static unsigned char
setvlvl(unsigned char verblvl)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "unsigned char verblvl = %hhu\n", verblvl);
#endif  /* LGR_DEV                */

    SET_MSGLHHUHHU(INTERN_INFO, vlvl, verblvl);
    vlvl = verblvl;

    R_MSGLHHU(INTERN_DEBUG, verblvl);
    return (verblvl);
}

unsigned char
setverblvl(enum verblvls verblvl)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "enum verblvls verblvl = %hhu\n", verblvl);
#endif  /* LGR_DEV                */

    if (vlvl == verblvl)
    {
        R_MSGLHHU(INTERN_DEBUG, vlvl);
        return vlvl;
    }

    CALLFN_MSGLS(INTERN_TRACE, "isverblvl()");
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_TRACE,
               "unsigned char verblvl = verblvl(%hhu)\n",
               verblvl);
#endif  /* LGR_DEV                */
    if (isverblvl(verblvl))
    {
        CALLFN_MSGLS(INTERN_TRACE, "setvlvl()");
#ifdef  LGR_DEV
        logltffnlf(DEV_INTERN_TRACE,
                   "unsigned char verblvl = verblvl(%hhu)\n",
                   verblvl);
#endif  /* LGR_DEV                */
        setvlvl(verblvl);

        CALLFN_MSGLS(INTERN_TRACE, "setvlvln()");
#ifdef  LGR_DEV
        logltffnlf(DEV_INTERN_TRACE,
                   "unsigned char verblvl = verblvl(%hhu)\n",
                   verblvl);
#endif  /* LGR_DEV                */
        setvlvln(verblvl);

        CALLFN_MSGLS(INTERN_TRACE, "getverblvlname()");
#ifdef  LGR_DEV
        logltffnlf(DEV_INTERN_TRACE,
                   "enum verblvls verblvl = vlvl(%hhu)\n",
                   vlvl);
#endif  /* LGR_DEV                */
        int ti = strcmp(vlvln, getverblvlname(vlvl));
        if (ti) { fatalf("Validation failed..  strcmp returned %d.", ti); }

        R_MSGLD(INTERN_DEBUG, vlvl);
        return vlvl;
    }
    R_MSGLHHU(INTERN_DEBUG, vlvl);
    return vlvl;
}

enum verblvls
getverblvl(void)
{
    INFUNC_MSGL(INTERN_DEBUG);
    GET_MSGLS(INTERN_INFO, "vlvl");

    R_MSGLS(INTERN_DEBUG, vlvl);
    return vlvl;
}

enum verblvls
getfileprio(void)
{
    INFUNC_MSGL(INTERN_DEBUG);
    GET_MSGLS(INTERN_INFO, "fprio");

    R_MSGLS(INTERN_DEBUG, fprio);
    return fprio;
}

int
geterrwarn(void)
{
    INFUNC_MSGL(INTERN_DEBUG);
    GET_MSGLS(INTERN_INFO, "errwarn");

    R_MSGLD(INTERN_DEBUG, errwarn);
    return errwarn;
}

enum verblvls
setfileprio(enum verblvls fileprio)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "enum verblvls fileprio = %hhu\n", fileprio);
#endif  /* LGR_DEV                */

    if (!ltf) { logltffnlf(WARNING, "%s\n", "Logging to file is not set..."); }

    CALLFN_MSGLS(INTERN_TRACE, "isverblvl()");
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_TRACE,
               "unsigned char lvl = fileprio(%s)\n",
               fileprio);
#endif  /* LGR_DEV                */
    if (!isverblvl(fileprio))
    {
        logltffnlf(ERROR,
                  "Failed to update file priority.  %hhu is not a valid "
                  "verbose level.  Leaving file priority as is.(%hhu)\n",
                  fileprio,
                  fprio);

        R_MSGLHHU(INTERN_DEBUG, (unsigned char)0);
        return (unsigned char)0;

    }

    SET_MSGLHHUHHU(INTERN_INFO, fprio, fileprio);
    fprio = fileprio;

    R_MSGLHHU(INTERN_DEBUG, fprio);
    return fprio;
}

int
seterrwarn(int treatwarnerr)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "int treatwarnerr = %d\n", treatwarnerr);
#endif  /* LGR_DEV                */

    SET_MSGLDD(INTERN_INFO, errwarn, treatwarnerr);
    errwarn = treatwarnerr;

    R_MSGLD(INTERN_DEBUG, errwarn);
    return errwarn;
}

static char*
setfout(void)
{
    INFUNC_MSGL(INTERN_DEBUG);

    if (!ltf) { logltffnlf(WARNING, "%s\n", "Logging to file is not set..."); }
    if (!fname)
    {
        logltffnlf(WARNING, "%s\n", "Filename is not set!");
        logltffnlf(NOTICE,
                   "%s\n",
                   "Filename not being set may result in log files "
                   "conflicting with one another as there is no name to "
                   "differentiate what log file is for what.  Because of so, "
                   "it may be hard to maintain and read the log files as you "
                   "may not know what the log file is for.");
    }

    logltffnlf(INTERN_DEBUG, "%s\n", "time()");
    time_t t        = time(0);

    logltffnlf(INTERN_DEBUG, "%s\n", "localtime()");
    struct tm *ti   = localtime(&t);
    if (!ti) { fatalstr(strerror(errno)); }

    logltffnlf(INTERN_DEBUG, "malloc(%lu)\n", NAME_MAX);
    char *tmpfno    = malloc(NAME_MAX);
    if (!tmpfno) { fatalf("Failed to allocate memory for: %s!\n", "tmpfno"); }

    logltffnlf(INTERN_DEBUG, "%s\n", "strftime()");
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG,
               "              char    *s      = tmpfno(%s)\n",
               tmpfno);
    logltffnlf(DEV_INTERN_DEBUG,
               "              size_t  max     = NAME_MAX(%lu)\n",
               NAME_MAX);
    logltffnlf(DEV_INTERN_DEBUG,
               "const         char    *format = fnsfxfmt(%s)\n",
               fnsfxfmt);
    logltffnlf(DEV_INTERN_DEBUG,
               "const struct  tm      *tm     = %s\n", "ti");
#endif  /* LGR_DEV                */
    size_t tmpfnosz = strftime(tmpfno, NAME_MAX, fnsfxfmt, ti);
    if (!tmpfnosz) { fatalf("%s can not be 0!\n", "tmpfno"); }

    CALLFN_MSGLS(INTERN_TRACE, "sprintf()");
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "      char *str     = tmpfno(%s)\n", tmpfno);
    logltffnlf(DEV_INTERN_DEBUG, "const char *format  = %s\n", "\"%s-%s\"");
    logltffnlf(DEV_INTERN_DEBUG, "      ...           = tmpfno(%s)\n", tmpfno);
    logltffnlf(DEV_INTERN_DEBUG, "      ...           = fname(%s)\n", fname);
#endif  /* LGR_DEV                */
    tmpfnosz        = sprintf(tmpfno, "%s-%s", tmpfno, fname);
    if (!tmpfnosz) { fatalf("%s can not be 0!\n", "tmpfno"); }

    logltffnlf(INTERN_DEBUG, "%s\n", "realloc()");
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG,
               "void    *ptr  = tmpfno(%lu)\n",
               strlen(tmpfno));
    logltffnlf(DEV_INTERN_DEBUG,
               "size_t  size  = tmpfnosz(%lu) + 1",
               tmpfnosz);
#endif  /* LGR_DEV                */
    if (!realloc(tmpfno, tmpfnosz + 1)) {
        fatalf("Failed to reallocate: %s(%lu) to: %lu(%s) + 1!\n",
               "tmpfno",
               strlen(tmpfno),
               tmpfnosz,
               "tmpfnosz");
    }

        CALLFN_MSGLS(INTERN_TRACE, "mallstr()");
#ifdef  LGR_DEV
        MALLSTR_DEVMSGSS(tmpfno, fnout);
#endif  /* LGR_DEV                */
    mallstr(tmpfno, &fnout, "fnout");

    SET_MSGLSS(INTERN_INFO, fnout, tmpfno);
    fnout = tmpfno;

    logltffnlf(INTERN_INFO, "Updating fout(%s)...\n", fnout);

    logltffnlf(INTERN_DEBUG,
               "Opening file fout(%s) in append mode...\n",
               fnout);
    fout = fopen(fnout, "a");
    if (!fout) {
        fatalf("Failed to open %s! %s(%d)\n", fnout, strerror(errno), errno);
    }

    R_MSGLS(INTERN_DEBUG, fnout);
    return fnout;
}

char*
setfilename(char *filename)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "char *filename = %s\n", filename);
#endif  /* LGR_DEV                */

    if (!ltf) { logltffnlf(WARNING, "%s\n", "Logging to file is not set..."); }
    if (!filename)
    {
        logltffnlf(WARNING, "%s\n", "No filename specified...");

        R_MSGLS(INTERN_DEBUG, fname);
        return fname;
    }

    CALLFN_MSGLS(INTERN_TRACE, "mallstr()");
#ifdef  LGR_DEV
    MALLSTR_DEVMSGSS(filename, fname);
#endif  /* LGR_DEV                */
    mallstr(filename, &fname, "fname");

    SET_MSGLSS(INTERN_INFO, fname, filename);
    fname = filename;

    CALLFN_MSGLS(INTERN_TRACE, "setfout()");
    setfout();

    R_MSGLS(INTERN_DEBUG, fname);
    return fname;
}

int
setlogtofile(int logtofile)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "int logtofile = %d\n", logtofile);
#endif  /* LGR_DEV                */

    SET_MSGLDD(INTERN_INFO, ltf, logtofile);
    ltf = logtofile;

    R_MSGLD(INTERN_DEBUG, ltf);
    return ltf;
}

int
getlogtofile(void)
{
    INFUNC_MSGL(INTERN_DEBUG);
    GET_MSGLS(INTERN_INFO, "ltf");

    R_MSGLD(INTERN_DEBUG, ltf);
    return ltf;
}

char*
setfilenamesuffixfmt(const char *suffixfmt)
{
    INFUNC_MSGL(INTERN_DEBUG);
#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG, "const char *suffixfmt = %s\n", suffixfmt);
#endif  /* LGR_DEV                */

    logltffnlf(INTERN_DEBUG, "%s\n", "time()");
    time_t t        = time(0);

    logltffnlf(INTERN_DEBUG, "%s\n", "localtime()");
    struct tm *ti   = localtime(&t);
    if (!ti) { fatalstr(strerror(errno)); }

    logltffnlf(INTERN_DEBUG, "malloc(%lu)\n", NAME_MAX);
    char *tmpfno    = malloc(NAME_MAX);
    if (!tmpfno) { fatalf("Failed to allocate memory for: %s!\n", "tmpfno"); }

#ifdef  LGR_DEV
    logltffnlf(DEV_INTERN_DEBUG,
               "              char    *s      = tmpfno(%s)\n",
               tmpfno);
    logltffnlf(DEV_INTERN_DEBUG,
               "              size_t  max     = NAME_MAX(%lu)\n",
               NAME_MAX);
    logltffnlf(DEV_INTERN_DEBUG,
               "const         char    *format = fnsfxfmt(%s)\n",
               fnsfxfmt);
    logltffnlf(DEV_INTERN_DEBUG,
               "const struct  tm      *tm     = %s\n", "ti");
#endif  /* LGR_DEV                */
    size_t tmpfnosz = strftime(tmpfno, NAME_MAX, fnsfxfmt, ti);
    if (!tmpfnosz)
    {
        logltffnlf(ERROR,
                   "%s is not a valid of a valid format!  Using current set "
                   "fnsfxfmt...\n",
                   suffixfmt);

        R_MSGLS(INTERN_DEBUG, fnsfxfmt);
        return fnsfxfmt;

    }

    CALLFN_MSGLS(INTERN_TRACE, "mallstr()");
#ifdef  LGR_DEV
    MALLSTR_DEVMSGSS(suffixfmt, fnsfxfmt);
#endif  /* LGR_DEV                */
    mallstr(suffixfmt, &fnsfxfmt, "fnsfxfmt");

    SET_MSGLSS(INTERN_INFO, fnsfxfmt, suffixfmt);
    strcpy(fnsfxfmt, suffixfmt);

    R_MSGLS(INTERN_DEBUG, fnsfxfmt);
    return fnsfxfmt;
}

char*
getfilenamesuffixfmt(void)
{
    INFUNC_MSGL(INTERN_DEBUG);
    GET_MSGLS(INTERN_INFO, "fnsfxfmt");

    R_MSGLS(INTERN_DEBUG, fnsfxfmt);
    return fnsfxfmt;
}

char*
getfilenameout(void)
{
    INFUNC_MSGL(INTERN_DEBUG);
    GET_MSGLS(INTERN_INFO, "fnout");

    R_MSGLS(INTERN_DEBUG, fnout);
    return fnout;
}

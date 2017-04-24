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
static int            eim       = 0;

static char           *fnsfxfmt = "%y%m%d%H%M%S";
static char           *fname    = "\0";

static char           *fnout    = "\0";

static FILE           *fout     = 0;

struct fmtfgbgc_s defattrb      = { RS_ALL, FG_DEF, BG_DEF };
struct fmtfgbgc_s fatalattrb    = { RS_ALL, FG_RED, BG_DEF };
struct fmtfgbgc_s errorattrb    = { RS_ALL, FG_LIGHT_RED, BG_DEF };
struct fmtfgbgc_s warrningattrb = { RS_ALL, FG_YELLOW, BG_DEF };
struct fmtfgbgc_s noticeattrb   = { RS_ALL, FG_LIGHT_BLUE, BG_DEF };
struct fmtfgbgc_s infoattrb     = { RS_ALL, FG_LIGHT_YELLOW, BG_DEF };
struct fmtfgbgc_s debugattrb    = { RS_ALL, FG_MAGENTA, BG_DEF };
struct fmtfgbgc_s traceattrb    = { RS_ALL, FG_LIGHT_MAGENTA, BG_DEF };

struct fmtfgbgc_s timestrattrb  = { RS_ALL, FG_LIGHT_GREEN, BG_DEF };
struct fmtfgbgc_s filestrattrb  = { RS_ALL, FG_YELLOW, BG_DEF };
struct fmtfgbgc_s funcstrattrb  = { RS_ALL, FG_GREEN, BG_DEF };
struct fmtfgbgc_s lineattrb     = { RS_ALL, FG_RED, BG_DEF };

void
lgrf(enum   verblvls        verblvl,
     const            char  *timestr,
     const            char  *filestr,
     const            char  *funcstr,
     const  unsigned  int   line,
     const            char  *strfmt, ...)
{
    if (!(verblvl > 0
                && verblvl <= INTERN_TRACE
         )  ? verblvl
            : NVALID_VERB_LVL) { return; }

    const unsigned char tmpvlvl =
        ((errwarn && verblvl == WARNING) ? ERROR : verblvl);

    if (tmpvlvl > vlvl && (eim && tmpvlvl < TRACE)) { return; }

    FILE *fpstrm  =
        ((errwarn)
         ? ((verblvl <= WARNING)
             ? stderr
             : stdout)
         : ((verblvl <= ERROR)
             ? stderr
             : stdout));

    int doltf = ltf && fout && (tmpvlvl <= fprio || eim);

    struct fmtfgbgc_s vattrb = (verblvl ==   FATAL ? fatalattrb
                             : (verblvl ==   ERROR ? errorattrb
                             : (verblvl == WARNING ? warrningattrb
                             : (verblvl ==  NOTICE ? noticeattrb
                             : (verblvl ==    INFO ? infoattrb
                             : (verblvl ==   DEBUG ? debugattrb
                             :  traceattrb))))));
    if (timestr)
    {
        fprintf(fpstrm,
                "\e[%u;%u;%um[\e[%u;%u;%um%s\e[%u;%u;%um]\e[%u;%u;%um "
                    "\e[%u;%u;%um%-18s\e[%u;%u;%um:\e[%u;%u;%um  ",
                debugattrb.fmt, debugattrb.fgc, debugattrb.bgc,
                timestrattrb.fmt, timestrattrb.fgc, timestrattrb.bgc,
                timestr,
                debugattrb.fmt, debugattrb.fgc, debugattrb.bgc,
                defattrb.fmt, defattrb.fgc, defattrb.bgc,
                vattrb.fmt, vattrb.fgc, vattrb.bgc,
                getvlvln(verblvl),
                debugattrb.fmt, debugattrb.fgc, debugattrb.bgc,
                defattrb.fmt, defattrb.fgc, defattrb.bgc);
        if (doltf) {
            fprintf(fout, "[%s]  %-18s:  ", timestr,  getvlvln(verblvl));
        }
    }

    if (filestr || funcstr || line)
    {
        if (filestr)
        {
            fprintf(fpstrm,
                    "\e[%u;%u;%um%s\e[%u;%u;%um:\e[%u;%u;%um",
                    filestrattrb.fmt, filestrattrb.fgc, filestrattrb.bgc,
                    filestr,
                    debugattrb.fmt, debugattrb.fgc, debugattrb.bgc,
                    defattrb.fmt, defattrb.fgc, defattrb.bgc);
            if (doltf) {
                fprintf(fout, "%s:",  filestr);
            }
        }

        if (funcstr)
        {
            fprintf(fpstrm,
                    "\e[%u;%u;%um%s\e[%u;%u;%um:\e[%u;%u;%um",
                    funcstrattrb.fmt, funcstrattrb.fgc, funcstrattrb.bgc,
                    funcstr,
                    debugattrb.fmt, debugattrb.fgc, debugattrb.bgc,
                    defattrb.fmt, defattrb.fgc, defattrb.bgc);
            if (doltf) {
                fprintf(fout, "%s:",  funcstr);
            }
        }

        if (line)
        {
            fprintf(fpstrm,
                    "\e[%u;%u;%um%u\e[%u;%u;%um:\e[%u;%u;%um",
                    lineattrb.fmt, lineattrb.fgc, lineattrb.bgc,
                    line,
                    debugattrb.fmt, debugattrb.fgc, debugattrb.bgc,
                    defattrb.fmt, defattrb.fgc, defattrb.bgc);
            if (doltf) {
                fprintf(fout, "%u:", line);
            }
        }

        fprintf(fpstrm,             "   ");
        if (doltf) { fprintf(fout,  "   "); }
    }

    fprintf(fpstrm, "\e[%u;%u;%um", vattrb.fmt, vattrb.fgc, vattrb.bgc);
    va_list ap;
    va_start(ap, strfmt);
    vfprintf(fpstrm,            strfmt, ap);
    if (doltf) { vfprintf(fout, strfmt, ap); }
    va_end(ap);
    fprintf(fpstrm, "\e[%u;%u;%um", defattrb.fmt, defattrb.fgc, defattrb.bgc);
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
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "isverblvl()"); }
    return (strcmp(getverblvlname(lvl), NVALID_VERB_LVL_STR)
            ? (int)lvl
            : NVALID_VERB_LVL);
}

static void
mallstr(const char *stra, char **pstrb)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "mallstr()"); }
    size_t tmpstrbsz  = strlen(*pstrb);
    size_t tmpstrasz  = strlen(stra);
    if (tmpstrbsz != tmpstrasz) { *pstrb = malloc(tmpstrasz + 1lu); }
}

static char*
setvlvln(enum verblvls verblvl)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "setvlvln()"); }
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
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "setvlvl()"); }
    return (vlvl = verblvl);
}

unsigned char
setverblvl(enum verblvls verblvl)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "setverblvl()"); }
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
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "getverblvl()"); }
    return vlvl;
}

enum verblvls
getfileprio(void)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "getfileprio()"); }
    return fprio;
}

int
geterrwarn(void)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "geterrwarn()"); }
    return errwarn;
}

enum verblvls
setfileprio(enum verblvls fileprio)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "setfileprio()"); }
    if (!isverblvl(fileprio)) { return (unsigned char)0; }

    return (fprio = fileprio);
}

int
seterrwarn(int treatwarnerr)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "seterrwarn()"); }
    return (errwarn = treatwarnerr);
}

static char*
setfout(void)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "setfout()"); }
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
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "setfilename()"); }
    if (!filename || !ltf) { return fname; }

    mallstr(filename, &fname);

    fname = filename;

    setfout();

    return fname;
}

int
setlogtofile(int logtofile)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "setlogtofile()"); }
    return (ltf = logtofile);
}

int
getlogtofile(void)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "getlogtofile()"); }
    return ltf;
}

char*
setfilenamesuffixfmt(const char *suffixfmt)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "setfilenamesuffixfmt()"); }
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
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "getfilenamesuffixfmt()"); }
    return fnsfxfmt;
}

char*
getfilenameout(void)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "getfilenameout()"); }
    return fnout;
}

int
setenableinternmsg(int enableinternmsg)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "setenableinternmsg()"); }
    return (eim = enableinternmsg);
}

int
getenableinternmsg(void)
{
    if (eim) { logltffnlf(INTERN_TRACE, "%s\n", "getenableinternmsg()"); }
    return eim;
}

int
closeout(void)
{
    return !fclose(fout);
}

int
dellog(void)
{
    if (!fout) { return 1; }

    return closeout() ? !remove(fnout) : 0;
}

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

/** \var  static char *vlvln
 *  \internal
 *    @brief  verbose level name
 *
 *    Contains the name representation that of what the current verbose \link
 *      vlvl level\endlink is set to.
 *  \endinternal
 */

/** \var  static enum verblvls vlvl
 *  \internal
 *    @brief  verbose level
 *
 *    Level of which verbosity is currently set at.
 *  \endinternal
 */

#ifdef  LGR_DEV
static char           *vlvln    = INTERN_TRACE_STR;
static enum verblvls  vlvl      = INTERN_TRACE;
#else
static char           *vlvln    = WARNING_STR;
static enum verblvls  vlvl      = WARNING;
#endif  /* LGR_DEV */

/**
 *  \internal
 *    @brief  file priority
 *
 *    Priority for logging to file.
 *  \endinternal
 */
static enum verblvls  fprio     = ERROR;

/**
 *  \internal
 *    @brief  error warning
 *
 *    Treat #WARNING and #INTERN_WARNING as #ERROR.
 *  \endinternal
 */
static int            errwarn   = 0;

/**
 *  \internal
 *    file name suffix format
 *  \endinternal
 */
static char           *fnsfxfmt = "%y%m%d%H%M%S";

/**
 *  \internal
 *    @brief  file name
 *
 *    Preferably the name of what's being executed, but doesn't necessarily
 *      have to be.
 *  \endinternal
 */
static char           *fname;

/**
 *  \internal
 *    @brief  file name out
 *
 *    The filename of which is used by #fout.
 *  \endinternal
 */
static char           *fnout;

/**
 *  \internal
 *    @brief  file out
 *
 *    The filename of which logs are output to.
 *  \endinternal
 */
static FILE           *fout;

/**
 *  \internal
 *    @todo Log to file.
 *    @todo Enabled \e only selected #verblvls.
 *    @todo Logging level.
 *    @todo Enabled logging for \e only selected #verblvls.
 *
 *    @note Still want #ERROR to be logged even if #vlvl is set to #FATAL.
 *    @note Eventually want to add an option to enable color and after being
 *            done so, implement an option for colors to be customized.
 *  \endinternal
 */

/**
 *  \internal
 *    Outputs desired information to respected stream and/or to a log file,
 *      depending on \link verblvls verbosity level\endlink and configuration.
 *
 *    @param[in]  verblvl An enumerator constant declared in enumeration type
 *                          #verblvls representing the verbosity level of
 *                          specified message given in \p strfmt.
 *    @param[in]  timestr The time as a string to be output to the logger.
 *    @param[in]  line    The line of which corresponds to the given to by \p
 *                          strfmt.
 *    @param[in]  strfmt
 *      \parblock
 *        Either a regular string containing information to be output to a
 *          stream and/or log file depending on what \p verblvl is set to and
 *          configurations or a formatted string.  <b>If a regular string is
 *          give, optional arguments, even if given will be ignored and not
 *          used.</b>
 *
 *        If a formatted string is given, optional arguments will no longer be
 *          optional.  They will be required in order to get the desired
 *          output.
 *      \endparblock
 *  \endinternal
 */
static void
lgrf(enum   verblvls        verblvl,
     const            char  *timestr,
     const  unsigned  int   line,
     const            char  *strfmt, ...)
{
    if (!(verblvl > 0
                && verblvl <= INTERN_DEBUG)
            ? verblvl
            : NVALID_VERB_LVL) { return; }

    /* temp verbose level */
    const unsigned char tmpvlvl =
        ((errwarn && verblvl == WARNING) ? ERROR : verblvl);

    if (tmpvlvl > vlvl) { return; }
    FILE *fpstrm  = fout ? fout : stdout;
/*        ((errwarn)
         ? ((verblvl == INTERN_WARNING
                 || verblvl <= WARNING)
             ? stderr
             : stdout)
         : ((verblvl <= ERROR)
             ? stderr
             : stdout));
*/

    if (timestr || line)
    {
        fprintf(fpstrm, "[");
        if (timestr)          { fprintf(fpstrm, "%s", timestr); }
        if (timestr && line)  { fprintf(fpstrm, ":%7u", line); }
        else if (line)        { fprintf(fpstrm, "%7u", line); }
        fprintf(fpstrm, "]  ");
    }
    char *tvlvln    = verblvl == INTERN_DEBUG   ? INTERN_DEBUG_STR
                    : verblvl == INTERN_INFO    ? INTERN_INFO_STR
                    : verblvl == INTERN_WARNING ? INTERN_WARNING_STR
                    : verblvl == DEBUG          ? DEBUG_STR
                    : verblvl == INFO           ? INFO_STR
                    : verblvl == WARNING        ? WARNING_STR
                    : verblvl == ERROR          ? ERROR_STR
                    : verblvl == FATAL          ? FATAL_STR
                    : NVALID_VERB_LVL_STR;
    /* WHY THE FUCK IS THIS SET TO VLVLN?  I NEEDS TO NOT */
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

/**
 *  \internal
 *    @brief  fatal format
 *
 *    Outputs the message specified to by \p str, to the #stderr stream, along
 *      with #error and its meaning, followed by exiting with code
 *      #EXIT_FAILURE.
 *
 *    @param[in]  fmt A formatted string containing information.
 *  \endinternal
 */
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

/**
 *  \internal
 *    @brief  fatal string
 *
 *    @details  \copydetails  fatalf()
 *
 *    @param[in]  str A string containing information.
 *  \endinternal
 */
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

    /* temp verbose level */
    unsigned char tmpvlvl = INTERN_INFO;

    /*
     *  I don't know if I like this style of formatting as it does not use any
     *  parenthesis..
     *
     *  NOTE: We are not using the 'isverblvl()' function as a method to
     *          validate 'verblvl' prior to retrieving its corresponding name,
     *          because that would result in a recursive loop as 'isverblvl()'
     *          uses 'getverblvlname()' for the INFO log part of its
     *          definition.
     *
     * temp verbose level name */
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

                    /*
                     *  If 'verblvl' is not of a valid constant contained in
                     *    the enumeration of 'verblvls', 'tmpvlvl' will be set
                     *    from its current set level (INTERN_INFO) to 'WARNING'
                     *    .  (See remark below, for an explanation as to why I
                     *    have chosen to set the verbose level accordingly.)
                     *
                     *  Yes I know I am going to be frowned upon for that I am
                     *    using an 'expression statement', but that is just my
                     *    coding style.
                     */
                    : (tmpvlvl = WARNING, NVALID_VERB_LVL_STR);

    /*
     *  Not sure if I should out this message with verbose level 'INTERN_INFO'
     *    or 'WARNING'.
     *
     *  I think it's more appropriate to have this message be
     *    out at the 'WARNING' verbose level as the parameter of
     *    'getverblvlname()' is of type 'enum verblvls' and the purpose of
     *    this function is to get the name of which corresponds to that
     *    argument.
     *
     *  NOTE: Please see above note as to why we are not using function
     *          'isverblvl()' as a method of validation.
     */
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

    /* temp verbose level */
    unsigned char tmpvlvl = INTERN_INFO;

    /* temp level */
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

/**
 *  \internal
 *    @brief  malloc string
 *
 *    If the length of \p stra and \p pstrb are not equal, \p pstrb will be
 *      allocated/reallocated to the length of \p stra.
 *
 *    @param[in]  stra  The string to match length of for \p pstrb.
 *    @param[out] pstrb The string that if needed to be allocated/reallocated
 *                        to match the string length of \p stra.
 *    @param[in]  strbn The name of \p pstrb.  (Used for logging)
 *  \endinternal
 */
static void
mallstr(char *stra, char **pstrb, char *strbn)
{
    logltlf(INTERN_DEBUG, "%s:%s\n", __func__, *pstrb);

    logltlf(INTERN_DEBUG, CALC_STR, *pstrb);
    /* temp strb size */
    size_t tmpstrbsz   = strlen(*pstrb);
    assert(tmpstrbsz);
    logltlf(INTERN_DEBUG, CALC_STR, stra);
    /* temp stra size */
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

/**
 *  \internal
 *    @brief  set verbose level name
 *
 *    Changes the current \link vlvln verbose level name\endlink to that of
 *      given to \p verblvl, if it is of a valid \link verblvls verbose
 *      level\endlink.
 *
 *    @param[in]  verblvl An enumerator constant declared in enumeration type
 *                          #verblvls.
 *
 *    @return If \p verblvl is a valid is a valid \link verblvls verbose
 *              level\endlink, the string representation of \p verblvl will be
 *              returned.\n
 *            If \p verblvl is not a valid \link verblvls verbose
 *              level\endlink, #vlvln will be returned.
 *
 *    @remark #vlvln is a \c static global variable, declared near the top of
 *              this source (lgr.c).
 *  \endinternal
 */
static char*
setvlvln(enum verblvls verblvl)
{
    logltlf(INTERN_DEBUG, "%s\n", __func__);

    logltlf(INTERN_TRACE, "%s\n", __func__);
    /* temp verbose level name */
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

/**
 *  \internal
 *    @brief  set verbose level (static method; used internally)
 *
 *    Sets #vlvl to \p verblvl.
 *
 *    @param[in]  verblvl The #verblvls to set #vlvl to.
 *
 *    @return Returns #vlvl.
 *
 *    @remark This is only exists to suppress the warning of #vlvl possibly
 *              being undefined.
 *  \endinternal
 */
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
        /*
         *  I feel like setting this message priority to 'INFO', rather than
         *    anything lower such as 'INTERN_INFO' is more appropriate so that
         *    the end user will know why the verbosity level went unmodified.
         */
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
        /* temp int */
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

/**
 *  \internal
 *    @brief  set file out
 *
 *    Sets the global variable #fout to the corresponding file to be used when
 *      logging to file.
 *
 *    @return If successful, the filename used in #fout will be returned as a
 *              string.\n
 *            If unsuccessful, \c 0 will be returned.
 *  \endinternal
 */
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
    /* time */
    time_t t        = time(0);

    logltlstr(INTERN_TRACE, "localtime(&t)\n");
    /* time info */
    struct tm *ti   = localtime(&t);
    if (!ti) { fatalstr(strerror(errno)); }

    logltlf(INTERN_DEBUG, ALLOC_STR_SZ, "tmpfno", NAME_MAX);
    /* temp file name out */
    char *tmpfno    = malloc(NAME_MAX);
    if (!tmpfno) { fatalstr(MALLOC_FAIL); }

    logltlf(INTERN_DEBUG, PARSE_STR, "time");
    /* temp file name out size */
    size_t tmpfnosz = strftime(tmpfno, NAME_MAX, fnsfxfmt, ti);
    if (!tmpfnosz) { fatalf(STR_NZ, "tmpfno", tmpfnosz); }

    logltlf(INTERN_DEBUG, PARSE_STR, "file");
    tmpfnosz        = snprintf(tmpfno, NAME_MAX, "./%s-%s", tmpfno, fname);
    if (!tmpfnosz) { fatalf(STR_NZ, "tmpfno", tmpfnosz) }

    logltlf(INTERN_DEBUG, REALLOC_MSG, tmpfno, tmpfnosz);
    if (!realloc(tmpfno, tmpfnosz + 1)) { fatalstr(REALLOC_FAIL); }

    logltf(INTERN_INFO, "%s\n", tmpfno);
    mallstr(tmpfno, &fnout, "fnout");

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

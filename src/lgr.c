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

#include  "../inc/lgr.h"

#define LGR_DEV

/**
 *  \internal
 *    return message decimal
 *  \endinternal
 */
#define RMSG_D    "Returning %d...\n"

/**
 *  \internal
 *    return message unsigned char
 *  \endinternal
 */
#define RMSG_HHU  "Returning %hhu...\n"

/**
 *  \internal
 *    return message string
 *  \endinternal
 */
#define RMSG_S    "Returning %s...\n"

/**
 *  \internal
 *    return message unsigned int
 *  \endinternal
 */
#define RMSG_U    "Returning %u...\n"

/**
 *  \internal
 *    verbose level name change check
 *  \endinternal
 */
#define VERB_LVL_N_CH_CHCK \
    "Checking if verbose level name change is redundant...\n"

/**
 *  \internal
 *    verbose level name already set
 *  \endinternal
 */
#define VERB_LVL_N_ASET   "Verbose level name already set to '%s(%hhu)'!\n"

/**
 *  \internal
 *    verbose level name no change
 *  \endinternal
 */
#define VERB_LVL_N_NOCH   "Leaving verbose level name as is...\n"

/**
 *  \internal
 *    verbose level name check
 *  \endinternal
 */
#define VERB_LVL_N_CHCK   "Checking if '%s' is a valid verbose level name...\n"

/**
 *  \internal
 *    verbose level check
 *  \endinternal
 */
#define VERB_LVL_CH_CHCK  \
    "Checking if verbose level change is redundant...\n"

/**
 *  \internal
 *    verbose level already set
 *  \endinternal
 */
#define VERB_LVL_ASET     "Verbose level already set to '%hhu(%s)'!\n"

/**
 *  \internal
 *    verbose level no change
 *  \endinternal
 */
#define VERB_LVL_NOCH     "Leaving verbose level as is...\n"

/**
 *  \internal
 *    verbose level (and) name no change
 *
 *    @remark This is not the same as #VERB_LVL_N_NOCH.  This is used in
 *              function #setverblvl().
 *  \endinternal
 */
#define VERB_LVLN_NOCH    "Verbose level unchanged (%hhu(%s))...\n"

/**
 *  \internal
 *    verbose set fail
 *  \endinternal
 */
#define VERB_SET_FAIL     "Failed to set verbose level to '%hhu(%s)'!\n"

/**
 *  \internal
 *    x valid verbose level name
 *  \endinternal
 */
#define XVALID_VERB_LVL_N "'%s' is%sa valid verbose level name(%hhu)!\n"

/**
 *  \internal
 *    x valid verbose level
 *  \endinternal
 */
#define XVALID_VERB_LVL   "'%hhu' is%sa valid verbose level(%s)!\n"

/**
 *  \internal
 *    not valid verbose level name
 *  \endinternal
 */
#define NVALID_VERB_LVL_N "'%s' is not a valid verbose level name...\n"

/**
 *  \internal
 *    validating message
 *  \endinternal
 */
#define VALIDATING_MSG    "Validating...\n"

/**
 *  \internal
 *    Validation was successful!
 *  \endinternal
 */
#define VALIDATE_WIN      "Validation was successful!\n"

/**
 *  \internal
 *    Validation was unsuccessful!
 *  \endinternal
 */
#define VALIDATE_FAIL     "Validation was unsuccessful!  strcmp returned"

/**
 *  \internal
 *    valid verbose level name
 *  \endinternal
 */
#define VALID_VERB_LVL_N  "'%s' is a valid verbose level name!\n"

/**
 *  \internal
 *    calculate string
 *  \endinternal
 */
#define CALC_STR          "Calculating length of '%s'...\n"

/**
 *  \internal
 *    string length message
 *  \endinternal
 */
#define STR_LEN_MSG       "'%-14s' has a length of %lu\n"

/**
 *  \internal
 *    reallocation needed
 *  \endinternal
 */
#define REALLOC_NEEDED    "'vlvln' needs reallocation...\n"

/**
 *  \internal
 *    reallocation message
 *  \endinternal
 */
#define REALLOC_MSG       "Reallocating 'vlvln' to %lu + 1...\n"

/**
 *  \internal
 *    reallocation win
 *  \endinternal
 */
#define REALLOC_WIN       "Reallocation was successful!\n"

/**
 *  \internal
 *    memory allocation fail
 *  \endinternal
 */
#define MALLOC_FAIL       "malloc returned"

/**
 *  \internal
 *    setting verbose level name
 *  \endinternal
 */
#define SET_VERB_LVL_N    "Updating verbose level name...\n"

/**
 *  \internal
 *    setting verbose level
 *  \endinternal
 */
#define SET_VERB_LVL      "Updating verbose level...\n"

/**
 *  \internal
 *    setting file priority
 *  \endinternal
 */
#define SET_FPRIO         "Updating file priority...\n"

/**
 *  \internal
 *    set error warning
 *  \endinternal
 */
#define SET_ERRWARN       "%s treat WARNING as ERROR...\n"

#ifdef  LGR_DEV
int
main(int argc, char **argv)
{
    logltf(INTERN_DEBUG, __TIME__, "TT");
    return EXIT_SUCCESS;
}
#endif  /* LGR_DEV */

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
static char           *vlvln  = INTERN_DEBUG_STR;
static enum verblvls  vlvl    = INTERN_DEBUG;
#else
static char           *vlvln  = WARNING_STR;
static enum verblvls  vlvl    = WARNING;
#endif  /* LGR_DEV */

/**
 *  \internal
 *    @brief  file priority
 *
 *    Priority for logging to file.
 *  \endinternal
 */
static enum verblvls fprio = ERROR;

/**
 *  \internal
 *    @brief  error warning
 *
 *    Treat #WARNING and #INTERN_WARNING as #ERROR.
 *  \endinternal
 */
static int errwarn  = 0;

/**
 *  \internal
 *    Outputs the message specified to by \p str, to the #stderr stream, along
 *      with #error and its meaning, followed by exiting with code
 *      #EXIT_FAILURE.
 *
 *    @param[in]  str The string message to be output to the #stderr stream.
 *
 *    @remark This function is marked \e noreturn meaning that this function
 *              will terminate the process.  (Correct me if my wording for
 *              'process' and use of it, is incorrect.)  It is also used for
 *              optimization.
 *  \endinternal
 */
static noreturn void
fatal(const           char  *timestr,
      const           char  *filestr,
      const           char  *funcstr,
      const unsigned  int   line,
      const           char  *msg,
      const           int   rcode)
{
    fprintf(stderr,
            "\n[%s:%s:%s:%u]  FATAL:  %s %d\n",
            timestr,
            filestr,
            funcstr,
            line,
            msg,
            rcode);

    exit(EXIT_FAILURE);
}

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
 *      \endparblock'
 *  \endinternal
 */
static void
lgrf(enum   verblvls        verblvl,
     const            char  *timestr,
     const  unsigned  int   line,
     const            char  *strfmt,
            va_list         vargs)
{
    if (!(verblvl > 0
                && verblvl <= INTERN_DEBUG)
            ? verblvl
            : NVALID_VERB_LVL) { return; }

    /* temp verbose level */
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
        if (timestr && line)  { fprintf(fpstrm, ":%7u", line); }
        else if (line)        { fprintf(fpstrm, "%7u", line); }
        fprintf(fpstrm, "]  ");
    }

    fprintf(fpstrm, "%-14s  ", vlvln);
    vfprintf(fpstrm, strfmt, vargs);
}

/**
 *  \internal
 *    @todo Log to file.
 *    @todo Enabled \e only selected #verblvls.
 *    @todo Logging level.
 *    @todo Enabled logging for \e only selected #verblvls.
 *    @todo Implement option for 'timestamps'.
 *
 *    @note Still want #ERROR to be logged even if #vlvl is set to #FATAL.
 *    @note Eventually want to add an option to enable color and after being
 *            done so, implement an option for colors to be customized.
 *  \endinternal
 */
void
loglf(enum verblvls verblvl, const char *strfmt, ...)
{
    /* argument pointer */
    va_list ap;
    va_start(ap, strfmt);
    lgrf(verblvl, 0, 0, strfmt, ap);
    va_end(ap);
}

void
logltf(enum verblvls verblvl, const char *timestr, const char *strfmt, ...)
{
    /* argument pointer */
    va_list ap;
    va_start(ap, strfmt);
    lgrf(verblvl, timestr, 0, strfmt, ap);
    va_end(ap);
}

void
logllf(enum   verblvls        verblvl,
       const  unsigned  int   line,
       const            char  *strfmt, ...)
{
    /* argument pointer */
    va_list ap;
    va_start(ap, strfmt);
    lgrf(verblvl, 0, line, strfmt, ap);
    va_end(ap);
}

void
logltlf(enum   verblvls        verblvl,
        const            char  *timestr,
        const  unsigned  int   line,
        const            char  *strfmt, ...)
{
    /* argument pointer */
    va_list ap;
    va_start(ap, strfmt);
    lgrf(verblvl, timestr, line, strfmt, ap);
    va_end(ap);
}

char*
getverblvlname(enum verblvls verblvl)
{
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 2u, "%s\n", __func__);

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
    char *tmpvlvln  = verblvl == INTERN_DEBUG   ? INTERN_DEBUG_STR
                    : verblvl == INTERN_INFO    ? INTERN_INFO_STR
                    : verblvl == INTERN_WARNING ? INTERN_WARNING_STR
                    : verblvl == DEBUG          ? DEBUG_STR
                    : verblvl == INFO           ? INFO_STR
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
           __TIME__,
           XVALID_VERB_LVL_N,
           verblvl,
           !strcmp(tmpvlvln, NVALID_VERB_LVL_STR) ? " not " : " ",
           tmpvlvln);

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_S, tmpvlvln);
    return tmpvlvln;
}

int
isverblvl(unsigned char lvl)
{
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 2u, "%s\n", __func__);

    /* temp verbose level */
    unsigned char tmpvlvl = INTERN_INFO;

    /* temp level */
    int tmplvl =
        ((lvl && (lvl <= INTERN_DEBUG))
         ? lvl
         : (tmpvlvl = INTERN_WARNING, NVALID_VERB_LVL));

    logltf(tmpvlvl,
           __TIME__,
           XVALID_VERB_LVL,
           lvl,
           tmplvl ? " " : " not ");

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_D, tmplvl);
    return tmplvl;
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
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 2u, "%s\n", __func__);

    /* temp verbose level name */
    char *tmpvlvln = getverblvlname(verblvl);
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, VERB_LVL_N_CH_CHCK);
    if (!strcmp(vlvln, tmpvlvln))
    {
        logltf(INTERN_INFO, __TIME__, VERB_LVL_N_ASET, vlvln, vlvl);
        logltf(INTERN_INFO, __TIME__, VERB_LVL_N_NOCH);

        logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_S, vlvln);
        return vlvln;
    }

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, VERB_LVL_N_CHCK, tmpvlvln);
    if (strcmp(tmpvlvln, NVALID_VERB_LVL_STR))
    {
        logltf(INTERN_INFO, __TIME__, VALID_VERB_LVL_N, tmpvlvln);

        logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 2u, CALC_STR, vlvln);
        /* temp verbose level size */
        size_t tmpvlvlnsz   = strlen(vlvln);

        logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 2u, CALC_STR, tmpvlvln);
        /* temp temp verbose level size (tmpt(mp)vlvln) */
        size_t tmptvlvlnsz  = strlen(tmpvlvln);
        if (tmpvlvlnsz != tmptvlvlnsz)
        {
            logltf(INTERN_DEBUG, __TIME__, STR_LEN_MSG, vlvln, tmpvlvlnsz);
            logltf(INTERN_DEBUG, __TIME__, STR_LEN_MSG, tmpvlvln, tmptvlvlnsz);
            logltf(INTERN_DEBUG, __TIME__, REALLOC_NEEDED);

            logltlf(INTERN_DEBUG,
                    __TIME__,
                    __LINE__ + 3u,
                    REALLOC_MSG,
                    tmptvlvlnsz);

            if (!(vlvln = malloc(tmptvlvlnsz + 1ul))) {
                fatal(__TIME__,
                      __FILE__,
                      __func__,
                      __LINE__ - 4u,
                      MALLOC_FAIL,
                      0);
            }

            logltf(INTERN_DEBUG, __TIME__, REALLOC_WIN);
        }

        logltlf(INTERN_INFO, __TIME__, __LINE__ + 1u, SET_VERB_LVL_N);
        vlvln = tmpvlvln;

        logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_S, vlvln);
        return vlvln;
    }

    logltf(INTERN_WARNING, __TIME__, NVALID_VERB_LVL_N, tmpvlvln);

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_S, vlvln);
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
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 2u, "%s\n", __func__);

    logltlf(INTERN_INFO, __TIME__, __LINE__ + 1u, SET_VERB_LVL);
    vlvl = verblvl;

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_HHU, vlvl);
    return (verblvl);
}

int
setverblvl(enum verblvls verblvl)
{
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 2u, "%s\n", __func__);

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, VERB_LVL_CH_CHCK);
    if (vlvl == verblvl)
    {
        /*
         *  I feel like setting this message priority to 'INFO', rather than
         *    anything lower such as 'INTERN_INFO' is more appropriate so that
         *    the end user will know why the verbosity level went unmodified.
         */
        logltf(INFO, __TIME__, VERB_LVL_ASET, vlvl, vlvln);
        logltf(INFO, __TIME__, VERB_LVL_NOCH);

        logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_HHU, vlvl);
        return vlvl;
    }

    if (isverblvl(verblvl))
    {
        setvlvl(verblvl);
        setvlvln(verblvl);

        logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 2u, VALIDATING_MSG);
        /* temp int */
        int ti = strcmp(vlvln, getverblvlname(vlvl));
        if (ti) {
            fatal(__TIME__,
                  __FILE__,
                  __func__,
                  __LINE__ - 5u,
                  VALIDATE_FAIL, ti);
        }

        logltf(INTERN_DEBUG, __TIME__, VALIDATE_WIN);

        logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_HHU, vlvl);
        return vlvl;
    }

    logltf(WARNING, __TIME__, VERB_SET_FAIL, verblvl, getverblvlname(verblvl));
    logltf(WARNING, __TIME__, VERB_LVLN_NOCH, vlvl, vlvln);

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_HHU, vlvl);
    return vlvl;
}

enum verblvls
getverblvl()
{
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 2u, "%s\n", __func__);

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_HHU, vlvl);
    return vlvl;
}

enum verblvls
getfileprio(void)
{
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 2u, "%s\n", __func__);

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_HHU, fprio);
    return fprio;
}

int
geterrwarn(void)
{
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 2u, "%s\n", __func__);

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_D, errwarn);
    return errwarn;
}

enum verblvls
setfileprio(enum verblvls fileprio)
{
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 2u, "%s\n", __func__);

    unsigned char tmpvlvl = isverblvl(fileprio);
    logltf(tmpvlvl ? INTERN_INFO : WARNING,
           __TIME__,
           XVALID_VERB_LVL,
           fileprio,
           tmpvlvl ? " " : " not ",
           getverblvlname(fileprio));

    logltlf(INTERN_INFO, __TIME__, __LINE__ + 1u, SET_FPRIO);
    fprio = fileprio;

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_HHU, fprio);
    return fprio;
}

int
seterrwarn(int treatwarnerr)
{
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 2u, "%s\n", __func__);

    logltlf(INTERN_INFO,
            __TIME__,
            __LINE__ + 3u,
            SET_ERRWARN,
            treatwarnerr ? "Enabling" : "Disabling");
    errwarn = treatwarnerr;

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_D, errwarn);
    return errwarn;
}

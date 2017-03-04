/**
 *  @file     lgr.h
 *  @brief    lgr.h
 *  @version  v.1
 *  @date     02/15/2017 17:10:55
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

#ifndef LGR_H
#define LGR_H /**< Include guard for 'lgr.h'. */

/**
 *  #NVALID_VERB_LVL string
 */
#define NVALID_VERB_LVL_STR "NVALID_VERB_LVL"

/*
 *  Each same line document in the following definitions, do not have a 'valid'
 *    'tabstop' after the word 'string' because even if to do so, that would
 *    make the comment closer at column 80, and that is greater than 79
 *    (Obviously), and my coding style is to keep everything under or at max 79
 *    characters long for each line as said so in the GNU formatting docs.  Yes
 *    I follow a lot of the conventions there, but not all.
 */
#define FATAL_STR           "FATAL"           /**< #FATAL          string */
#define ERROR_STR           "ERROR"           /**< #ERROR          string */
#define WARNING_STR         "WARNING"         /**< #WARNING        string */
#define INFO_STR            "INFO"            /**< #INFO           string */
#define DEBUG_STR           "DEBUG"           /**< #DEBUG          string */
#define INTERN_WARNING_STR  "INTERN_WARNING"  /**< #INTERN_WARNING string */
#define INTERN_INFO_STR     "INTERN_INFO"     /**< #INTERN_INFO    string */
#define INTERN_DEBUG_STR    "INTERN_DEBUG"    /**< #INTERN_DEBUG   string */

/**
 *  @brief   verbosity levels
 *
 *  Enumerator containing constants specifying each verbosity level.
 */
enum
verblvls
{
    /**
     *  Used when a verbose level is given, and it is not a valid \link
     *    verblvls verbose level\endlink.
     */
    NVALID_VERB_LVL = 0x0,  /**< @brief invalid verbose level */

    FATAL   = 0x1,  /**< Fatal messages.        */
    ERROR   = 0x2,  /**< Error messages.        */
    WARNING = 0x3,  /**< Warning messages.      */
    INFO    = 0x4,  /**< Informative messages.  */
    DEBUG   = 0x5,  /**< Display everything!    */

    /**
     *  Used to enable the #WARNING messages of the logger itself.
     */
    INTERN_WARNING  = 0x6,  /**< @brief internal warning      */

    /**
     *  Used to enable the #INFO messages of the logger itself.
     */
    INTERN_INFO     = 0x7,  /**< @brief internal information  */

    /**
     *  Used to enable the #DEBUG messages of the logger itself.
     */
    INTERN_DEBUG    = 0x8   /**< @brief internal debug        */
};

/**
 *  @brief log level format
 *
 *  Outputs desired information to respected stream and/or to a log file,
 *    depending on \link verblvls verbosity level\endlink and configuration.
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p strfmt.
 *  @param[in]  strfmt
 *    \parblock
 *      Either a regular string containing information to be output to a stream
 *        and/or log file depending on what \p verblvl is set to and
 *        configurations or a formatted string.  <b>If a regular string is
 *        give, optional arguments, even if given will be ignored and not used.
 *        </b>
 *
 *      If a formatted string is given, optional arguments will no longer be
 *        optional.  They will be required in order to get the desired output.
 *    \endparblock
 */
extern void
loglf(enum verblvls verblvl, const char *strfmt, ...);

/**
 *  @brief log level time format
 *
 *  Outputs desired information to respected stream and/or to a log file,
 *    depending on \link verblvls verbosity level\endlink and configuration.
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p strfmt.
 *  @param[in]  timestr The time as a string to be output to the logger.
 *  @param[in]  strfmt
 *    \parblock
 *      Either a regular string containing information to be output to a stream
 *        and/or log file depending on what \p verblvl is set to and
 *        configurations or a formatted string.  <b>If a regular string is
 *        give, optional arguments, even if given will be ignored and not used.
 *        </b>
 *
 *      If a formatted string is given, optional arguments will no longer be
 *        optional.  They will be required in order to get the desired output.
 *    \endparblock
 */
extern void
logltf(enum verblvls verblvl, const char *timestr, const char *strfmt, ...);

/**
 *  @brief log level line format
 *
 *  Outputs desired information to respected stream and/or to a log file,
 *    depending on \link verblvls verbosity level\endlink and configuration.
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p strfmt.
 *  @param[in]  line    The line of which corresponds to the given to by \p
 *                        strfmt.
 *  @param[in]  strfmt
 *    \parblock
 *      Either a regular string containing information to be output to a stream
 *        and/or log file depending on what \p verblvl is set to and
 *        configurations or a formatted string.  <b>If a regular string is
 *        give, optional arguments, even if given will be ignored and not used.
 *        </b>
 *
 *      If a formatted string is given, optional arguments will no longer be
 *        optional.  They will be required in order to get the desired output.
 *    \endparblock
 */
extern void
logllf(enum   verblvls        verblvl,
       const  unsigned  int   line,
       const            char  *strfmt, ...);

/**
 *  @brief log level time line format
 *
 *  Outputs desired information to respected stream and/or to a log file,
 *    depending on \link verblvls verbosity level\endlink and configuration.
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p strfmt.
 *  @param[in]  timestr The time as a string to be output to the logger.
 *  @param[in]  line    The line of which corresponds to the given to by \p
 *                        strfmt.
 *  @param[in]  strfmt
 *    \parblock
 *      Either a regular string containing information to be output to a stream
 *        and/or log file depending on what \p verblvl is set to and
 *        configurations or a formatted string.  <b>If a regular string is
 *        give, optional arguments, even if given will be ignored and not used.
 *        </b>
 *
 *      If a formatted string is given, optional arguments will no longer be
 *        optional.  They will be required in order to get the desired output.
 *    \endparblock
 */
extern void
logltlf(enum   verblvls       verblvl,
       const            char  *timestr,
       const  unsigned  int   line,
       const            char  *strfmt, ...);

/**
 *  @brief get verbose level name
 *
 *  Attempts to get the name representation of the given enumerator specified
 *    to \p verblvl.
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls.
 *
 *  @return If \p verblvl is a valid \link verblvls verbose level\endlink, \p
 *            verblvl will be returned.\n
 *          If \p verblvl is not a valid \link verblvls verbose level\endlink,
 *            #NVALID_VERB_LVL_STR will be returned.
 */
extern char*
getverblvlname(enum verblvls verblvl);

/**
 *  @brief valid verbose level
 *
 *  Checks if \p verblvl is a valid \link verblvls verbose level\endlink.
 *
 *  @param[in]  verblvl The level to verify if is a valid \link verblvls
 *                        verbose level\endlink.
 *
 *  @return If \p verblvl is a valid \link verblvls verbose level\endlink, \p
 *            verblvl will be returned.\n
 *          If \p verblvl is not a valid \link verblvls verbose level\endlink,
 *            #NVALID_VERB_LVL will be returned.
 */
extern int
isverblvl(unsigned char lvl);

/**
 *  @brief set verbose level
 *
 *  Changes the current \link verblvls verbose level\endlink to that of
 *    given to \p verblvl, if it is a valid \link verblvls verbose
 *    level\endlink.
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls.
 *
 *  @return If \p verblvl is a valid \link verblvls verbose level\endlink, \p
 *            verblvl will be returned.\n
 *          If \p verblvl is not a valid \link verblvls verbose level\endlink,
 *            the current \link verblvls verbose level\endlink will be
 *            returned.
 *
 *  \internal
 *    @remark The return value in short, will just return the value of #vlvl,
 *              which is a \c static global variable, declared in 'lgr.c'.
 *  \endinternal
 */
extern int
setverblvl(enum verblvls verblvl);

/**
 *  @brief get verbose level
 *
 *  Gets the current \link verblvls verbose level\endlink.
 *
 *  @return  Returns the current set \link verblvls verbose level\endlink.
 */
extern enum verblvls
getverblvl(void);

/**
 *  @brief get file priority
 *
 *  Gets the priority of which the logger will use to determine if the given
 *    message is applicable to be wrote out to a file.
 *
 *  @return Returns the \link verblvls verbose level\endlink of which the file
 *            priority is set to.
 */
extern enum verblvls
getfileprio(void);

/**
 *  @brief get error warning
 *
 *  Gets a value indicating weather or not #WARNING or #INTERN_WARNING is
 *    treated as an #ERROR or not.
 *
 *  @return If #WARNING and #INTERN_WARNING are to be treated as an #ERROR, \c
 *            nonzero will be returned.\n
 *          If #WARNING and #INTERN_WARNING are not to be treated as an #ERROR,
 *            \c 0 will be returned.
 */
extern int
geterrwarn(void);

/**
 *  @brief set file priority
 *
 *  Sets the file priority of which the logger will use to determine if the
 *    given message is applicable to be wrote out to a file, to by \p fileprio.
 *
 *  @param[in]  fileprio  The \link verblvls verbose level\endlink used to set
 *                          the file priority to.
 *
 *  @return Returns what the current set file priority is set to.
 */
extern enum verblvls
setfileprio(enum verblvls fileprio);

/**
 *  @brief set error warning
 *
 *  Sets weather or not #WARNING and #INTERN_WARNING should be treated as an
 *    #ERROR.
 *
 *  @param[in]  treatwarnerr  Treat #WARNING and #INTERN_WARNING as #ERROR?
 *
 *  @return If #WARNING and #INTERN_WARNING are to be treated as an #ERROR, \c
 *            nonzero will be returned.\n
 *          If #WARNING and #INTERN_WARNING are not to be treated as an #ERROR,
 *            \c 0 will be returned.
 */
extern int
seterrwarn(int treatwarnerr);

/**
 *  Sets the filename used for when out putting the log information to a file.
 *
 *  @param[in]  filename  The filename itself not including the path.  The
 *                          filename name will be prefixed with the current
 *                          date and time.
 *
 *  @return If successful, the name of \p filename will be returned.\n
 *          If not successful, \c 0 will be returned and logging to a file will
 *            be disabled.
 */
extern char*
setfilename(char *filename);

/**
 *  Gets the current filename used when logging to a file.
 *
 *  @return If there is a filename set for when logging to a file, the filename
 *            is returned.\n
 *          If there is no filename set, \c 0 will be returned.
 */
extern char*
getfilename(void);
#endif  /* LGR_H */

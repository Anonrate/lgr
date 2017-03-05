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
 *  @brief log level format
 *
 *  Outputs desired information to respected stream and/or to a log file,
 *    depending on \link verblvls verbosity level\endlink and configuration.
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p fmt.
 *  @param[in]  fmt     A formatted string containing information to be output
 *                        to a stream and/or log file depending on what \p
 *                        verblvl is set to and configurations.
 */
#define loglf(verblvl, fmt, ...)                  \
    (                                             \
        lgrf((verblvl), 0, 0, (fmt), __VA_ARGS__) \
    )

/**
 *  @brief log level string
 *
 *  @details  \copydetails  loglf()
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p fmt.
 *  @param[in]  str     A string containing information to be output to a
 *                        stream and/or log file depending on what \p verblvl
 *                        is set to and configurations.
 */
#define loglstr(verblvl, str)         \
    (                                 \
        lgrf((verblvl), 0, 0, (str))  \
    )

/**
 *  @brief log level time format
 *
 *  Outputs desired information including the current time when this function
 *    was called, to respected stream and/or to a log file, depending on \link
 *    verblvls verbosity level\endlink and configuration.
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p fmt.
 *  @param[in]  timestr The time as a string to be output to the logger.
 *  @param[in]  fmt     A formatted string containing information to be output
 *                        to a stream and/or log file depending on what \p
 *                        verblvl is set to and configurations.
 */
#define logltf(verblvl, fmt, ...)                         \
    (                                                     \
        lgrf((verblvl), __TIME__, 0, (fmt), __VA_ARGS__)  \
    )

/**
 *  @brief log level time string
 *
 *  @details  \copydetails  logltf()
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p fmt.
 *  @param[in]  str     A string containing information to be output to a
 *                        stream and/or log file depending on what \p verblvl
 *                        is set to and configurations.
 */
#define logltstr(verblvl, st)               \
    (                                       \
        lgrf((verblvl), __TIME__, 0, (str)) \
    )

/**
 *  @brief log level line format
 *
 *  Outputs desired information including the line from which called this
 *    function, to respected stream and/or to a log file, depending on \link
 *    verblvls verbosity level\endlink and configuration.
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p fmt.
 *  @param[in]  fmt     A formatted string containing information to be output
 *                        to a stream and/or log file depending on what \p
 *                        verblvl is set to and configurations.
 */
#define logllf(verblvl, fmt, ...)                         \
    (                                                     \
        lgrf((verblvl), 0, __LINE__, (fmt), __VA_ARGS__)  \
    )

/**
 *  @brief log level line string
 *
 *  @details  \copydetails  logllf()
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p fmt.
 *  @param[in]  str     A string containing information to be output to a
 *                        stream and/or log file depending on what \p verblvl
 *                        is set to and configurations.
 */
#define logllstr(verblvl, str)              \
    (                                       \
        lgrf((verblvl), 0, __LINE__, (str)) \
    )
/**
 *  @brief log level time line format
 *
 *  Outputs desired information including the current time when this function
 *    was called and the line from which called this function, to respected
 *    stream and/or to a log file, depending on \link verblvls verbosity
 *    level\endlink and configuration.
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p fmt.
 *  @param[in]  fmt     A formatted string containing information to be output
 *                        to a stream and/or log file depending on what \p
 *                        verblvl is set to and configurations.
 */
#define logltlf(verblvl, fmt, ...)                              \
    (                                                           \
        lgrf((verblvl), __TIME__, __LINE__, (fmt), __VA_ARGS__) \
    )

/**
 *  @brief log level time line string
 *
 *  @details  \copydetails  logltlf()
 *
 *  @param[in]  verblvl An enumerator constant declared in enumeration type
 *                        #verblvls representing the verbosity level of
 *                        specified message given in \p fmt.
 *  @param[in]  str     A string containing information to be output to a
 *                        stream and/or log file depending on what \p verblvl
 *                        is set to and configurations.
 */
#define logltlstr(verblvl, str)                     \
    (                                               \
        lgrf((verblvl), __TIME__, __LINE__, (str))  \
    )

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

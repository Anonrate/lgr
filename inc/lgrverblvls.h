/**
 *  @file     lgrverblvls.h
 *  @brief    lgrverblvls.h
 *  @version  v.1
 *  @date     03/04/2017 22:38:27
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

#ifndef LGRVERBLVLS_H
#define LGRVERBLVLS_H /*< Include guard for 'lgrverblvls.h' */

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
#define NOTICE_STR          "NOTICE"          /**< #NOTICE         string */
#define INFO_STR            "INFO"            /**< #INFO           string */
#define DEBUG_STR           "DEBUG"           /**< #DEBUG          string */
#define TRACE_STR           "TRACE"           /**< #TRACE          string */
#define INTERN_WARNING_STR  "INTERN_WARNING"  /**< #INTERN_WARNING string */
#define INTERN_INFO_STR     "INTERN_INFO"     /**< #INTERN_INFO    string */
#define INTERN_DEBUG_STR    "INTERN_DEBUG"    /**< #INTERN_DEBUG   string */
#define INTERN_TRACE_STR    "INTERN_TRACE"    /**< #INTERN_TRACE   string */

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
    NOTICE  = 0x4,  /**< Notice messages.       */
    INFO    = 0x5,  /**< Informative messages.  */
    DEBUG   = 0x6,  /**< Display everything!    */
    TRACE   = 0x7,  /**< Trace messages.        */

    /**
     *  Used to enable the #WARNING messages of the logger itself.
     */
    INTERN_WARNING  = 0x8,  /**< @brief internal warning      */

    /**
     *  Used to enable the #INFO messages of the logger itself.
     */
    INTERN_INFO     = 0x9,  /**< @brief internal information  */

    /**
     *  Used to enable the #DEBUG messages of the logger itself.
     */
    INTERN_DEBUG    = 0xa,  /**< @brief internal debug        */

    /**
     *  Used to enable the #TRACE messages of the logger itself.
     */
    INTERN_TRACE    = 0xa   /**< @brief internal trace        */
};
#endif  /* LGRVERBLVLS_H */

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
#define LGRVERBLVLS_H

#define NVALID_VERB_LVL_STR "NVALID_VERB_LVL"

#define FATAL_STR           "FATAL"
#define ERROR_STR           "ERROR"
#define WARNING_STR         "WARNING"
#define NOTICE_STR          "NOTICE"
#define INFO_STR            "INFO"
#define DEBUG_STR           "DEBUG"
#define TRACE_STR           "TRACE"
#define INTERN_WARNING_STR  "INTERN_WARNING"
#define INTERN_INFO_STR     "INTERN_INFO"
#define INTERN_DEBUG_STR    "INTERN_DEBUG"
#define INTERN_TRACE_STR    "INTERN_TRACE"

enum
verblvls
{
    NVALID_VERB_LVL = 0x0,

    FATAL   = 0x1,
    ERROR   = 0x2,
    WARNING = 0x3,
    NOTICE  = 0x4,
    INFO    = 0x5,
    DEBUG   = 0x6,
    TRACE   = 0x7,

    INTERN_WARNING  = 0x8,
    INTERN_INFO     = 0x9,
    INTERN_DEBUG    = 0xa,
    INTERN_TRACE    = 0xb
};
#endif  /* LGRVERBLVLS_H */

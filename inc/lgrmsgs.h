/**
 *  @file     lgrmsgs.h
 *  @brief    lgrmsgs.h
 *  @version  v.1
 *  @date     03/05/2017 00:17:07
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

#ifndef LGRMSGS_H
#define LGRMSGS_H /**< Include guard for 'lgrmsgs.h'  */


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
#define VALIDATE_FAIL     "Validation was unsuccessful!  strcmp returned %d"

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
#define REALLOC_NEEDED    "'%s' needs reallocation...\n"

/**
 *  \internal
 *    reallocation message
 *  \endinternal
 */
#define REALLOC_MSG       "Reallocating '%s' to %lu + 1...\n"

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
#define MALLOC_FAIL       "malloc returned %d"

/**
 *  \internal
 *    set error warning
 *  \endinternal
 */
#define SET_ERRWARN       "%s treat WARNING as ERROR...\n"

/**
 *  \internal
 *    string not set
 *  \endinternal
 */
#define STR_NSET          "%s is not set!\n"

/**
 *  \internal
 *    file name zero
 *  \endinternal
 */
#define FN_Z              "Filename is 0!\n"

/**
 *  \internal
 *    file name zero message
 *  \endinternal
 */
#define FN_ZMSG                                                             \
    "Filename being 0 will result in unexpected results causing logs that " \
    "correspond to a different process to be merged as there is no way to " \
    "differentiate them...\n"

/**
 *  \internal
 *    setting string
 *  \endinternal
 */
#define SET_STR           "Updating %s...\n"

/**
 *  \internal
 *    string not zero
 *  \endinternal
 */
#define STR_NZ            "Length of %s string can not be %lu!\n"

/**
 *  \internal
 *    parse string
 *  \endinternal
 */
#define PARSE_STR         "Parsing %s string...\n"

/**
 *  \internal
 *    allocating string size
 *  \endinternal
 */
#define ALLOC_STR_SZ      "Allocating %s to %lu...\n"

#endif  /* LGRMSGS_H */

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
#define LGRMSGS_H

#define RMSG_D    "Returning %d...\n"

#define RMSG_HHU  "Returning %hhu...\n"

#define RMSG_S    "Returning %s...\n"

#define RMSG_U    "Returning %u...\n"

#define VERB_LVL_N_CH_CHCK \
    "Checking if verbose level name change is redundant...\n"

#define VERB_LVL_N_ASET   "Verbose level name already set to '%s(%hhu)'!\n"

#define VERB_LVL_N_NOCH   "Leaving verbose level name as is...\n"

#define VERB_LVL_N_CHCK   "Checking if '%s' is a valid verbose level name...\n"

#define VERB_LVL_CH_CHCK  \
    "Checking if verbose level change is redundant...\n"

#define VERB_LVL_ASET     "Verbose level already set to '%hhu(%s)'!\n"

#define VERB_LVL_NOCH     "Leaving verbose level as is...\n"

#define VERB_LVLN_NOCH    "Verbose level unchanged (%hhu(%s))...\n"

#define VERB_SET_FAIL     "Failed to set verbose level to '%hhu(%s)'!\n"

#define XVALID_VERB_LVL_N "'%s' is%sa valid verbose level name(%hhu)!\n"

#define XVALID_VERB_LVL   "'%hhu' is%sa valid verbose level(%s)!\n"

#define NVALID_VERB_LVL_N "'%s' is not a valid verbose level name...\n"

#define VALIDATING_MSG    "Validating...\n"

#define VALIDATE_WIN      "Validation was successful!\n"

#define VALIDATE_FAIL     "Validation was unsuccessful!  strcmp returned %d\n"

#define VALID_VERB_LVL_N  "'%s' is a valid verbose level name!\n"

#define CALC_STR          "Calculating length of '%s'...\n"

#define STR_LEN_MSG       "'%-14s' has a length of %lu\n"

#define REALLOC_NEEDED    "'%s' needs reallocation...\n"

#define REALLOC_MSG       "Reallocating '%s' to %lu + 1...\n"

#define REALLOC_WIN       "Reallocation was successful!\n"

#define REALLOC_FAIL      "realloc returned 0!\n"

#define MALLOC_FAIL       "malloc returned 0!\n"

#define SET_ERRWARN       "%s treat WARNING as ERROR...\n"

#define STR_NSET          "%s is not set!\n"

#define FN_Z              "Filename is 0!\n"

#define FN_ZMSG                                                             \
    "Filename being 0 will result in unexpected results causing logs that " \
    "correspond to a different process to be merged as there is no way to " \
    "differentiate them...\n"

#define SET_STR           "Updating %s...\n"

#define STR_NZ            "Length of %s string can not be %lu!\n"

#define PARSE_STR         "Parsing %s string...\n"

#define ALLOC_STR_SZ      "Allocating %s to %lu...\n"

#endif  /* LGRMSGS_H */

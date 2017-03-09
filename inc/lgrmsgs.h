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

#define R_MSGLHHU(l, hhu)                                         \
    (                                                             \
        logltffnlf((l), "Returning %s(%hhu)...\n", (#hhu), (hhu)) \
    )

#define R_MSGLD(l, d)                                       \
    (                                                       \
        logltffnlf((l), "Returning %s(%d)...\n", (#d), (d)) \
    )

#define R_MSGLU(l, u)                                       \
    (                                                       \
        logltffnlf((l), "Returning %s(%u)...\n", (#u), (u)) \
    )

#define R_MSGLS(l, s)                                       \
    (                                                       \
        logltffnlf((l), "Returning %s(%s)...\n", (#s), (s)) \
    )

#define INFUNC_MSGL(l)                                  \
    (                                                   \
        logltffnlf((l), "Entering %s()...\n", __func__) \
    )

#define GET_MSGLS(l, s)                         \
    (                                           \
        logltffnlf((l), "Getting %s...\n", (s)) \
    )

#define SET_MSGLHHUHHU(l, hhua, hhub)                       \
    (                                                       \
        logltffnlf((l),                                     \
                   "Updating: %s from: %hhu to: %hhu...\n", \
                   (#hhua),                                 \
                   (hhua),                                  \
                   (hhub))                                  \
    )

#define SET_MSGLDD(l, da, db)                           \
    (                                                   \
        logltffnlf((l),                                 \
                   "Updating: %s from: %d to: %d...\n", \
                   (#da),                               \
                   (da),                                \
                   (db))                                \
    )

#define SET_MSGLSS(l, sa, sb)                           \
    (                                                   \
        logltffnlf((l),                                 \
                   "Updating: %s from: %s to: %s...\n", \
                   (#sa),                               \
                   (sa),                                \
                   (sb))                                \
    )

#define CALLFN_MSGLS(l, s)                                          \
    (                                                               \
        logltffnlf((l), "Calling: %s from %s...\n", (s), __func__)  \
    )

#ifdef  LGR_DEV
#define MALLSTR_DEVMSGSS(sa, sb)                      \
    {                                                 \
        logltffnlf(DEV_INTERN_TRACE,                  \
                   "const char *stra   = %s(%s)\n",   \
                   (#sa),                             \
                   (sa));                             \
        logltffnlf(DEV_INTERN_TRACE,                  \
                   "      char **pstrb = &%s(%s)\n",  \
                   (#sb),                             \
                   (sb));                             \
        logltffnlf(DEV_INTERN_TRACE,                  \
                   "      char *strbn  = \"%s\"\n",   \
                   (#sb));                            \
    }
#endif  /* LGR_DEV    */

#define MALLOC_FAIL_MSGSF "Failed to allocated memory for: %s!\n"

#define REALLOC_FAIL_MSGULUL(ula, ulb)                          \
    (                                                           \
        fatalf("Failed to reallocate: %s(%lu) to: %lu(%s)!\n",  \
               (#ula),                                          \
               sizeof (ula),                                    \
               sizeof (ulb),                                    \
               (#ulb))                                          \
    )

#define STRZ_MSGSF        "%s can not be 0!\n"
#endif  /* LGRMSGS_H  */

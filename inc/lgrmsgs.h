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

#define R_MSGLHHU(l, hhu)                             \
    (                                                 \
        logltffnlf((l), "Returning %hhu...\n", (hhu)) \
    )

#define R_MSGLD(l, d)                             \
    (                                             \
        logltffnlf((l), "Returning %d...\n", (d)) \
    )

#define R_MSGLU(l, u)                             \
    (                                             \
        logltffnlf((l), "Returning %u...\n", (u)) \
    )

#define R_MSGLS(l, s)                             \
    (                                             \
        logltffnlf((l), "Returning %s...\n", (s)) \
    )

#define INFUNC_MSGL(l)                                  \
    (                                                   \
        logltffnlf((l), "Entering %s()...\n", __func__) \
    )

#define GET_MSGLS(l, s)                         \
    (                                           \
        logltffnlf((l), "Getting %s...\n", (s)) \
    )

#define SET_MSGLSHHU(l, s, hhua, hhub)                      \
    (                                                       \
        logltffnlf((l),                                     \
                   "Updating: %s from: %hhu to: %hhu...\n", \
                   (s),                                     \
                   (hhua),                                  \
                   (hhub))                                  \
    )

#define SET_MSGLSD(l, s, da, db)                                              \
    (                                                                         \
        logltffnlf((l), "Updating: %s from: %d to: %d...\n", (s), (da), (db)) \
    )

#define CALLFN_MSGLS(l, s)                                          \
    (                                                               \
        logltffnlf((l), "Calling: %s from %s...\n", (s), __func__)  \
    )
#endif  /* LGRMSGS_H */

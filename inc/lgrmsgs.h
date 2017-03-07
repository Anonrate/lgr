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

#define RMSG_LHHU(l, hhu)           \
    (                               \
        lgr((l),                    \
            __TIME__,               \
            __FILE__,               \
            __func__,               \
            __LINE__,               \
            "Returning %hhu...\n",  \
            (hhu))                  \
    )

#define RMSG_LD(l, d)             \
    (                             \
        lgr((l),                  \
            __TIME__,             \
            __FILE__,             \
            __func__,             \
            __LINE__,             \
            "Returning %d...\n",  \
            (d))                  \
    )

#define RMSG_LU(l, u)             \
    (                             \
        lgr((l),                  \
            __TIME__,             \
            __FILE__,             \
            __func__,             \
            __LINE__,             \
            "Returning %u...\n",  \
            (u))                  \
    )

#define RMSG_LS(l, str)           \
    (                             \
        lgr((l),                  \
            __TIME__,             \
            __FILE__,             \
            __func__,             \
            __LINE__,             \
            "Returning %s...\n",  \
            (str))                \
    )

#define INFUNC_MSGL(l)            \
    (                             \
        lgr((l),                  \
            __TIME__,             \
            __FILE__,             \
            __func__,             \
            __LINE__,             \
            "Entering %s()...\n", \
            __func__)             \
    )
#endif  /* LGRMSGS_H */

/**
 *  @file     loglfxf.h
 *  @brief    loglfxf.h
 *  @version  v.1
 *  @date     03/05/2017 20:27:16
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

#ifndef (LOGLFXF_H)
#define LOGLFXF_H

#define loglff(verblvl, fmt, ...)                               \
    (                                                           \
        lgrf((verblvl), 0, __FILE__, 0, 0, (fmt), __VA_ARGS__)  \
    )

#define loglfstr(verblvl, str)                    \
    (                                             \
        lgrf((verblvl), 0, __FILE__, 0, 0, (str)) \
    )

#define loglffnf(verblvl, fmt, ...)                                     \
    (                                                                   \
        lgrf((verblvl), 0, __FILE__, __func__, 0u, (fmt), __VA_ARGS__)  \
    )

#define loglffnstr(verblvl, str)                          \
    (                                                     \
        lgrf((verblvl), 0, __FILE__, __func__, 0u, (str)) \
    )

#define loglflf(verblvl, fmt, ...)                                    \
    (                                                                 \
        lgrf((verblvl), 0, __FILE__, 0, __LINE__, (fmt), __VA_ARGS__) \
    )

#define loglflstr(verblvl, str)                           \
    (                                                     \
        lgrf((verblvl), 0, __FILE__, 0, __LINE__, (str))  \
    )

#define loglffnlf(verblvl, fmt, ...)                                          \
    (                                                                         \
        lgrf((verblvl), 0, __FILE__, __func__, __LINE__, (fmt), __VA_ARGS__)  \
    )

#define loglffnlstr(verblvl, str)                               \
    (                                                           \
        lgrf((verblvl), 0, __FILE__, __func__, __LINE__, (str)) \
    )
#endif  /* LOGLFXF_H */

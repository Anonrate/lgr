/**
 *  @file     logltxf.h
 *  @brief    logltxf.h
 *  @version  v.1
 *  @date     03/05/2017 19:55:28
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

#ifndef LOGLTXF_H
#define LOGLTFX_H

#define logltf(verblvl, fmt, ...)                               \
    (                                                           \
        lgrf((verblvl), __TIME__, 0, 0, 0, (fmt), __VA_ARGS__)  \
    )

#define logltstr(verblvl, str)                    \
    (                                             \
        lgrf((verblvl), __TIME__, 0, 0, 0, (str)) \
    )

#define logltff(verblvl, fmt, ...)                                    \
    (                                                                 \
        lgrf((verblvl), __TIME__, __FILE__, 0, 0, (fmt), __VA_ARGS__) \
    )

#define logltfstr(verblvl, str)                           \
    (                                                     \
        lgrf((verblvl), __TIME__, __FILE__, 0, 0, (str))  \
    )

#define logltfnf(verblvl, fmt, ...)                                   \
    (                                                                 \
        lgrf((verblvl), __TIME__, 0, __func__, 0, (fmt), __VA_ARGS__) \
    )

#define logltfnstr(verblvl, str)                          \
    (                                                     \
        lgrf((verblvl), __TIME__, 0, __func__, 0, (str))  \
    )

#define logltlf(verblvl, fmt, ...)                                    \
    (                                                                 \
        lgrf((verblvl), __TIME__, 0, 0, __LINE__, (fmt), __VA_ARGS__) \
    )

#define logltlstr(verblvl, str)                                             \
    (                                                                       \
        lgrf((verblvl), __TIME__, 0, 0, __LINE__, (str)) \
    )

#define logltffnf(verblvl, fmt, ...)                                          \
    (                                                                         \
        lgrf((verblvl), __TIME__, __FILE__, __func__, 0, (fmt), __VA_ARGS__)  \
    )

#define logltffnstr(verblvl, str)                               \
    (                                                           \
        lgrf((verblvl), __TIME__, __FILE__, __func__, 0, (str)) \
    )

#define logltflf(verblvl, fmt, ...)                                           \
    (                                                                         \
        lgrf((verblvl), __TIME__, __FILE__, 0, __LINE__, (fmt), __VA_ARGS__)  \
    )

#define logltflstr(verblvl, str)                                \
    (                                                           \
        lgrf((verblvl), __TIME__, __FILE__, 0, __LINE__, (str)) \
    )

#define logltfnlf(verblvl, fmt, ...)                                          \
    (                                                                         \
        lgrf((verblvl), __TIME__, 0, __func__, __LINE__, (fmt), __VA_ARGS__)  \
    )

#define logltfnlstr(verblvl, str)                               \
    (                                                           \
        lgrf((verblvl), __TIME__, 0, __func__, __LINE__, (str)) \
    )

#define logltffnlf(verblvl, fmt, ...) \
    (                                 \
        lgrf((verblvl),               \
             __TIME__,                \
             __FILE__,                \
             __func__,                \
             __LINE__,                \
             (fmt),                   \
             __VA_ARGS__)             \
    )

#define logltffnlstr(verblvl, str)                                      \
    (                                                                   \
        lgrf((verblvl), __TIME__, __FILE__, __func__, __LINE__, (str))  \
    )
#endif  /* LOGLTXF_H */

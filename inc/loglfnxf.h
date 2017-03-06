/**
 *  @file     loglfnxf.h
 *  @brief    loglfnxf.h
 *  @version  v.1
 *  @date     03/06/2017 16:02:48
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

#ifndef LOGLFNXF_H
#define LOGLFNXF_H

#define loglfnlf(verblvl, fmt, ...)                                   \
    (                                                                 \
        lgrf((verblvl), 0, 0, __func__, __LINE__, (fmt), __VA_ARGS__) \
    )

#define loglfnlstr(verblvl, str)                          \
    (                                                     \
        lgrf((verblvl), 0, 0, __func__, __LINE__, (str))  \
    )
#endif  /* LOGLFNXF_H */

/**
 *  @file     lgr.h
 *  @brief    lgr.h
 *  @version  v.3
 *  @date     02/15/2017 17:10:55
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

#ifndef LGR_H
#define LGR_H

#define fatalf(fmt, ...)                      \
    {                                         \
        fprintf(stderr,                       \
                "\n[%s:%s:%s:%u]  FATAL:  ",  \
                __TIME__,                     \
                __FILE__,                     \
                __func__,                     \
                __LINE__);                    \
        fprintf(stderr, (fmt), __VA_ARGS__);  \
        fprintf(stderr, "\n");                \
        exit(EXIT_FAILURE);                   \
    }

#define fatalstr(str)                         \
    {                                         \
        fprintf(stderr,                       \
                "\n[%s:%s:%s:%u]  FATAL:  ",  \
                __TIME__,                     \
                __FILE__,                     \
                __func__,                     \
                __LINE__);                    \
        fprintf(stderr, "%s\n", (str));       \
        exit(EXIT_FAILURE);                   \
    }

#define loglf(verblvl, fmt, ...)                        \
    (                                                   \
        lgrf((verblvl), 0, 0, 0, 0, (fmt), __VA_ARGS__) \
    )

#define loglstr(verblvl, str)               \
    (                                       \
        lgrf((verblvl), 0, 0, 0, 0, (str))  \
    )

#ifndef logltffnlf
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
#endif  /* logltffnlf */

extern const char*
getverblvlname(enum verblvls verblvl);

extern int
isverblvl(unsigned char lvl);

extern unsigned char
setverblvl(enum verblvls verblvl);

extern enum verblvls
getverblvl(void);

extern enum verblvls
getfileprio(void);

extern int
geterrwarn(void);

extern enum verblvls
setfileprio(enum verblvls fileprio);

extern int
seterrwarn(int treatwarnerr);

extern char*
setfilename(char *filename);

extern char*
getfilename(void);

extern int
setlogtofile(int logtofile);

extern int
getlogtofile(void);
#endif  /* LGR_H */

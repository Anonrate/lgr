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

#include  "lgrverblvls.h"
#include  "../../termsole/inc/linux/cntrlseq/enums/formatenum.h"
#include  "../../termsole/inc/linux/cntrlseq/enums/fgcolenum.h"
#include  "../../termsole/inc/linux/cntrlseq/enums/bgcolenum.h"

extern void
lgrf(enum   verblvls        verblvl,
     const            char  *timestr,
     const            char  *filestr,
     const            char  *funcstr,
     const  unsigned  int   line,
     const            char  *strfmt, ...);

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

extern char*
setfilenamesuffixfmt(const char *suffixfmt);

extern char*
getfilenamesuffixfmt(void);

extern char*
getfilenameout(void);

extern int
setenableinternmsg(int enableinternmsg);

extern int
getenableinternmsg(void);

extern int
closeout(void);

extern int
dellog(void);

struct fmtfgbgc_s {
    enum allfmts  fmt;
    enum fgcol    fgc;
    enum bgcol    bgc;
};

/*
extern struct lgropts_s {
    char            *vlvln;
    enum  verblvls  vlvl;
    int             ltf;
    enum  verblvls  fprio;
    int             errwarn;
    int             eim;
    char            *fnsfxfmt;
    char            *fname;
    char            *fout;
    FILE            *fout;
    int             usecolr;
};
*/
extern int usecolr;
extern int enableinternmsgs;
extern int erronwarn;
extern int logtofile;

extern struct fmtfgbgc_s defattrb;
extern struct fmtfgbgc_s fatalattrb;
extern struct fmtfgbgc_s errorattrb;
extern struct fmtfgbgc_s warrningattrb;
extern struct fmtfgbgc_s noticeattrb;
extern struct fmtfgbgc_s infoattrb;
extern struct fmtfgbgc_s debugattrb;
extern struct fmtfgbgc_s traceattrb;

extern struct fmtfgbgc_s timestrattrb;
extern struct fmtfgbgc_s filestrattrb;
extern struct fmtfgbgc_s funcstrattrb;
extern struct fmtfgbgc_s lineattrb;
#endif  /* LGR_H */

/**
 * @file	lgr.c
 * @brief	lgr.c
 * @version	v.1
 * @date	02/15/2017 18:08:02
 * @author	Anonrate
 * @copyright	
 *  \parblock
 *    GNU General Public License
 *
 * 	  Copyright (C) 2017 Anonrate
 *
 * 	  This program is free software: you can redistribute it and/or modify 
 * 	  it under the terms of the GNU General Public License as published by 
 * 	  the Free Software Foundation, either version 3 of the License, or 
 * 	  (at your option) any later version.
 *
 * 	  This program is distributed in the hope that it will be useful, 
 * 	  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * 	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * 	  GNU General Public License for more details.
 *
 * 	  You should have received a copy of the GNU General Public License
 * 	  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  \endparblock
 */

#include  <stdio.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <errno.h>
#include  <string.h>
#include  <time.h>

#include  "../inc/lgr.h"

/**
 * \internal  
 *  @brief  verbose level name
 *
 *  Contains the name representation that of what the current verbose \link 
 *    #vlvl level\endlink is set to.
 * \endinternal
 */
static char           *vlvln  = WARNING_STR;

/**
 * \internal  
 *  @brief  verbose level
 *
 *  Level of which verbosity is currently set at.
 * \endinternal
 */
static enum verblvls  vlvl    = WARNING;
/*
int
main(void)
{
    printf("%s\n", getyear());
    return 0;
}
*/
/**
 * \internal  
 *  @todo Log to file.
 *  @todo Enabled \e only selected #verblvls.
 *  @todo Logging level.
 *  @todo Enabled logging for \e only selected #verblvls.
 *  @todo Implement option for 'timesamps'.
 *
 *  @note Still want \c #ERROR to be logged even if #vlvl is set to \c #FATAL.
 *  @note Eventually want to add an option to enable color and after being done
 *          so, implement an option for colors to be customized.
 * \endinternal
 */
void
loglf(enum verblvls verblvl, char *strfmt, ...)
{
    /*
     * 'verblvl' is not a vald verbose level.
     */
    if (!isverblvl(verblvl)) { return; }

    /*
     * Prioirty is to high for this message to be displayed.
     */
    if (verblvl > vlvl) { return; }
    
    /*
     * NOTE:  Don't really like this approach...  It's faster than 'if'
     *          conditional checks, but maybe there is another way to
     *          accomplish duplicate results when 'Log to file' feature is
     *          implemented.
     *
     * file pointer stream */
    FILE *fpstrm;
    switch (verblvl)
    {
        case FATAL:
        case ERROR:
            fpstrm = stderr;
            break;
        case WARNING:
        case INFO:
        case DEBUG:
        case INTERN_WARNING:
        case INTERN_INFO:
        case INTERN_DEBUG:
            fpstrm = stdout;
            break;
        default:

            /*
             * If somehow the code reaches here...  Something fucked up
             *  emensely..!.
             */
            fprintf(stderr,
                    "%s:%s:%u:\t010001!2!!1 errno(%d)%s\n",
                    __FILE__,
                    __func__,
                    __LINE__,
                    errno,
                    strerror(errno));
            exit(EXIT_FAILURE);
    }
    
    /* argument pointer */
    va_list ap;
    va_start(ap, strfmt);
    vfprintf(fpstrm, strfmt, ap);
    va_end(ap);
}

char*
getverblvlname(enum verblvls verblvl)
{
    loglf(INTERN_DEBUG, "Getting verbose name for level '%hhu'...\n", verblvl);
    
    /* temp verbose level */
    unsigned char tmpvl = INTERN_INFO;

    /* 
     * I don't know if I like this style of formating as it does not use any
     *  parenthesis..
     *
     * NOTE:  We are not using the 'isverblvl()' function as a method to
     *          validate 'verblvl' prior to retreiving its corresponding name, 
     *          because that would result in a recursive loop as 'isverblvl()' 
     *          uses 'getverblvlname()' for the INFO log part of its
     *          definition.
     *
     * temp verbose level name */
    char *tmpvln  = verblvl == INTERN_DEBUG   ? INTERN_DEBUG_STR
                  : verblvl == INTERN_INFO    ? INTERN_INFO_STR
                  : verblvl == INTERN_WARNING ? INTERN_WARNING_STR
                  : verblvl == DEBUG          ? DEBUG_STR
                  : verblvl == INFO           ? INFO_STR
                  : verblvl == WARNING        ? WARNING_STR
                  : verblvl == ERROR          ? ERROR_STR
                  : verblvl == FATAL          ? FATAL_STR
                  
                  /*
                   * If 'verblvl' is not of a valid constant contained in the
                   *  enumeration of 'verblvls', 'tmpvl' will be set from its
                   *  current set level (INTERN_INFO) to 'WARNING'.  (See 
                   *  remark below, for an explination as to why I have chosen 
                   *  to set the verbose level accordingly.)
                   *
                   * Yes I know I am going to be frowned upon for that I am
                   *  using an 'expression statment', but that is just my
                   *  coding style.
                   */
                  : (tmpvl = NVALID_VERB_LVL, NVALID_VERB_LVL_STR);
    
    /*
     * Not sure if I should out this message with verbose level 'INTERN_INFO' 
     *  or 'WARNING'.
     *
     * I think it's more appropriate to have this message be 
     *  out at the 'WARNING' verbose level as the paramater of 
     *  'getverblvlname()' is of type 'enum verblvls' and the the purpose of 
     *  this function is to get the name of which corresponds to that argument.
     *
     * NOTE:  Please see above note as to why we are not using function
     *          'isverblvl()' as a method of validation.
     */
    loglf(tmpvl,
          "'%hhu' is%sa valid verbose level(%s)!\n",
          verblvl,
          !strcmp(tmpvln, NVALID_VERB_LVL_STR) ? " not " : " ",
          tmpvln);

    loglf(INTERN_DEBUG, "Returning '%s'...\n", tmpvln);
    return tmpvln;
}

int
isverblvl(unsigned char lvl)
{
    loglf(INTERN_DEBUG,
          "Checking if '%hhu' is a valid verbose level...\n",
          lvl);
    
    /* temp level */
    int tmplvl = ((lvl && (lvl <= INTERN_DEBUG)) ? lvl : NVALID_VERB_LVL);
    loglf(INTERN_INFO,
          "'%hhu(%s)' is%sa valid verbose level!\n",
          lvl,
          getverblvlname(lvl),
          tmplvl ? " " : " not ");

    loglf(INTERN_DEBUG, "Returning '%d'...\n", tmplvl);
    return tmplvl;
}

/**
 * \internal  
 *  @brief  validate verbose level name
 *
 *  Makes sure that #vlvl corresponds with #vlvln.
 *
 *  @return If #vlvl correpsonds to #vlvln, \c nonzero will be returned.\n
 *          If #vlvl does not correspond to #vlvln, \c 0 will be returned.
 * \endinternal
 */
static int
vldtvlvlname(void)
{
    loglf(INTERN_DEBUG, "Validating verbose level with verbose name...\n");
    /* 
     * Not sure if the '!' will reverse the value or not, and by that I mean if
     *  '0', turn the value into 'nonzero' and visa versa..
     *
     * return code */
    int rcode = !(strcmp(vlvln, getverblvlname(vlvl)));

    loglf(INTERN_DEBUG, "Returning '%d'...\n", rcode);
    return rcode;
}

/**
 * \internal  
 *  @brief  set verbose level name
 *
 *  Changes the current \link #vlvln verbose level name\endlink to that of
 *    given to \p verblvl, if it is of a valid \link #verblvls verbose
 *    level\endlink.
 *
 *  param[in] verblvl An enumerator constant decalred in enumeration type
 *                      #verblvls.
 *
 *  @return If \p verblvl is a valid is a valid \link #verblvls verbose
 *            level\endlink, the string representation of \p verblvl will be
 *            returned.\n
 *          If \p verblvl is not a valid \link #verblvls verbose level\endlink,
 *            #vlvln will be returned.
 *
 *  @remark #vlvln is a \c static global variable, delcared near the top of
 *            this source (lgr.c).
 * \endinternal
 */
static char*
setverblvlname(enum verblvls verblvl)
{
    loglf(INTERN_DEBUG,
          "Checking if verbose level name change is redundant...\n");
    if (!strcmp(vlvln, getverblvlname(verblvl)))
    {
        /*
         * This validation check may be redundant..
         *
         * Unlike the function below and how it uses verbose level 'INFO', this
         *  is an internal function, so a verbose level will be used.
         */
        loglf(INTERN_INFO,
              "Verbose level name already set to '%s(%hhu)'!\n", vlvln, vlvl);

        /* temp verbose level */
        unsigned char tmpvlvl = INTERN_INFO;

        /*
         * I don't really like how I have this formatted because there isn't
         *  any parenthasis.
         *
         * temp string format argument */
        char *tmpstrfmta      =
            /*
             * Ya I know, another one.  Deal with it...
             */
            vldtvlvlname() ? " " : (tmpvlvl = INTERN_WARNING, " un");
        
        loglf(tmpvlvl, "Validation was%ssucessfull!\n", tmpstrfmta);
        loglf(INTERN_INFO, "Leaving verbose level name as is...\n");
        loglf(INTERN_DEBUG, "Returning '%s'...\n", vlvln);
        return vlvln;
    }

    char *tmpvlvln = getverblvlname(verblvl);
    loglf(INTERN_DEBUG, "Setting verbose level name to '%s'...\n", tmpvlvln);
    if (strcmp(tmpvlvln, NVALID_VERB_LVL_STR))
    {
        /*
         * I am aware that function 'isverblvl()' uses a verbose level of
         *  'INTERN_INFO', but if doing so here as well, to much information
         *  will be output to the stream along about the procedure so to speak.
         */
        loglf(INTERN_DEBUG, "'%s' is a valid verbose level name!\n", tmpvlvln);
        loglf(INTERN_INFO,
              "Sucessfull changed verbose level name from '%s', to '%s'!\n",
              vlvln,
              tmpvlvln);

        loglf(INTERN_DEBUG, "Checking if 'vlvln' needs to be reallocated..\n");
        /*
         * I'm drawing blanks here as to weather or not I need to perform a
         *  'strcpy', or if I just need to reallocate (If need be) 'vlvln' 
         *  followed by reassigning the value of 'tmpvlvln'..
         */
        loglf(INTERN_DEBUG, "Calculating 'strlen' of 'vlvln'...\n");
        /* temp verbose level size */
        size_t tmpvlvlnsz   = strlen(vlvln);

        loglf(INTERN_DEBUG, "Calculating 'strlen' of 'tmpvlvln'...\n");
        /* temp temp verbose level size (tmpt(mp)vlvln) */
        size_t tmptvlvlnsz  = strlen(tmpvlvln);
        if (tmpvlvlnsz != tmptvlvlnsz)
        {
            loglf(INTERN_DEBUG, 
                  "sizeof:\t'vlvln'     = %lu\nsizeof:\t'tmpvlvln'  = %lu\n",
                  tmpvlvlnsz,
                  tmptvlvlnsz);
            loglf(INTERN_DEBUG, "'vlvln' needs reallocation!\n");
            loglf(INTERN_DEBUG,
                  "Reallocating 'vlvln' to %lu + 1...\n",
                  tmptvlvlnsz);
            /*
             * Plus '1' for 'null byte'.
             *
             * void pointer */
            void *vp = realloc(vlvln, tmptvlvlnsz + 1);
            loglf(INTERN_DEBUG, "Finished reallocation!\nVerifying...\n");
            if (!vp)
            {
                loglf(ERROR, "'realloc' returned %p!\n", vp);
                loglf(ERROR, "vlvln' did not successfully allocate!\n");
                
                loglf(ERROR, "Returning '%s'...\n", vlvln);
                return vlvln;
            }

            loglf(INTERN_DEBUG, "Reallocation was successfull!\n");
        }
        
        loglf(INTERN_DEBUG, "Assigning 'tmpvlvln' to 'vlvln'...\n");
        vlvln = tmpvlvln;

        loglf(INTERN_INFO, "Returning '%s'...\n", vlvln);
        return vlvln;
    }

    loglf(INTERN_WARNING,
          "'%s' is not a valid verbose level name...\n",
          tmpvlvln);

    loglf(INTERN_INFO, "Returning '%s'...", vlvln);
    return vlvln;
}

int
setverblvl(enum verblvls verblvl)
{
    loglf(INTERN_DEBUG, "Checking if verbsoe level change is redundant...\n");
    if (vlvl == verblvl)
    {
        /*
         * I feel like setting this message priority to 'INFO', rather than
         *  anything lower such as 'INTERN_INFO' is more appropriate so that
         *  the end user will know why the verbosity level went unmodified.
         */
        loglf(INFO, "Verbose level already set to '%hhu(%s)'!\n", vlvl, vlvln);
        loglf(INFO, "Leaving verbose level as is...\n");

        loglf(INTERN_DEBUG, "Returning '%hhu'...\n", vlvl);
        return vlvl;
    }

    /*
     * Can't choose what priority this message should have..  Either
     * 'INTERN_DEBUG' or 'INTERN_INFO'.
     */
    loglf(INTERN_DEBUG, "Setting verbose level to '%hhu'...\n", verblvl);
    if (isverblvl(verblvl))
    {
        /*
         * Using verbose level 'INTERN_INFO' here however, seems apropriate
         *  because setting of the verbose level was successful.
         */
        loglf(INTERN_INFO,
              "Sucessfully %s verbose level from '%hhu(%s)', to '%hhu(%s)'!\n",
              /*
               *  verb    < verblvl
               *  -----------------
               *  INFO(4) < DEBUG(5)
               */
              vlvl < verblvl ? "lowered" : "raised",
              vlvl,
              vlvln,
              vlvl  = verblvl,
              setverblvlname(verblvl));
        
        loglf(INTERN_DEBUG, "Returning '%hhu'...\n", vlvl);
        return vlvl;
    }

    loglf(WARNING, "Failed to set verbose level to '%hhu(%s)'!\n");
    loglf(WARNING, "Verbolse level unchanged (%hhu(%s))...\n", vlvl, vlvln);

    loglf(INTERN_DEBUG, "Returning '%hhu'...\n", vlvl);
    return vlvl;
}

enum verblvls
getverblvl()
{ 
    loglf(INTERN_DEBUG, "Getting set verbose level...\n");
    loglf(INTERN_DEBUG, "Returning '%hhu'...\n", vlvl);
    return vlvl;
}

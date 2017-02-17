/**
 * @file	lgr.c
 * @brief	lgr.c
 * @version	v.1
 * @date	02/15/2017 18:08:02
 * @author	Anonrate
 * @copyright	
 * 	\parblock
 * 		GNU General Public License
 *
 * 		Copyright (C) 2017 Anonrate
 *
 * 		This program is free software: you can redistribute it and/or modify 
 * 		it under the terms of the GNU General Public License as published by 
 * 		the Free Software Foundation, either version 3 of the License, or 
 * 		(at your option) any later version.
 *
 * 		This program is distributed in the hope that it will be useful, 
 * 		but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * 		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * 		GNU General Public License for more details.
 *
 * 		You should have received a copy of the GNU General Public License
 * 		along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 	\endparblock
 */

#include  <stdio.h>
#include  <stdlib.h>
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

int
main(void)
{
    return 0;
}

void
loglf(enum verblvls verblvl, char *strfmt, ...)
{

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
    char *tmpvln  = verblvl == INTERN_DEBUG ? INTERN_DEBUG_STR
                  : verblvl == INTERN_INFO  ? INTERN_INFO_STR
                  : verblvl == DEBUG        ? DEBUG_STR
                  : verblvl == INFO         ? INFO_STR
                  : verblvl == WARNING      ? WARNING_STR
                  : verblvl == ERROR        ? ERROR_STR
                  : verblvl == FATAL        ? FATAL_STR
                  
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
          tmpvln == NVALID_VERB_LVL_STR ? " not " : " ",
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
              vlvln = getverblvlname(vlvl));
        
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

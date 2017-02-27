# lgr
**lgr** is a verbose logger that allows the user to output useful information
to a respected stream and/or file depending on the level given and
configurations.

To everyone logging levels can be used for different situations as compared to
others.  There is really no *official* way to use each level, it's just more of
common sense as to when, where and how to use each level.

## Verbose levels
Below I will explain how I would usually go about and use each level.
* `FATAL`   This level is probably one of the most intuitive levels.  I merely
  use this level if the System fucks something up, or if something detrimental
  happens and the code will not work correctly if chosen to continue on.  When
  I use this level, I typically call a function that is marked with the
  `noreturn` attribute to state to the compiler that something has fucked up
  and there is no point of return if said function is called.
* `ERROR`   The `ERROR` level probably has a lot of discrepancy as to how each
  person utilizes it.  Along with `FATAL`, I do not use this level that often
  as I don't like my code have to be terminated on the end user and them get
  frustrated at me saying *"You should have done this.  You should have done
  that.  You should have made it more efficient so that even if someone types
  something incorrect or does the wrong 'thing' that the code corrects it by
  itself"*.  You see, I don't want to deal with that shit, so unless the end
  user does something real fucked up say like...  To be honest I can't even
  give an example because the way I code I make it utmost impossible for my
  code to actually *fail* or run into an `ERROR` minimal.
  <!--TODO:  Include an example of where `ERROR` can be used.**
  TODO:  Don't know if I mentioned anything alone the lines of termination,
  but I must say something along those lines as well -->

* `WARNING` Now this level is pretty much done and said for it its own name.
  It's a *warning* that something had gone wrong.  An example would be in the
  logger itself, during the configuration of setting the priority of verbose,
  if a level is given that is not valid, a warning will be displayed saying
  that the given level is no valid and is leaving the priority level as is.
  The code can continue on exactly how it's intended to, just not as the user
  intended to because their dumbass didn't specify a level correctly.

  So in short, if a `WARNING` occurs, the code can still continue on as it was
  intended to, but not as the user intends.
* `INFO`    I myself have a very hard time trying to choose where to use this
  level along with `DEBUG`.  I keep telling myself that it's just informative
  which in all seriousness it is..  The question is to what is it informative?
  A function call?  Something being valid?  Something needing to be modified?
  The technical answer is yes.  Yes to all of them.  It's pretty much down to
  personal preference.  A example from the loggers point of view would be
  letting the user know if a given level IS valid.  Not invalid, is valid.
  There really isn't much else to say about that there.
* `DEBUG`   Now lastly but most certainly not least we have `DEBUG`.  In
  retrospect...  If something is being done in your code and that it really
  doesn't matter to the user what the fuck it is because they probably wont
  understand...  Use `DEBUG`.  Use `DEBUG` to you know.. debug your code.
  Calling a function?  Put a message at the top right before it's starts doing
  shit so you know what is happening while you're debugging your code and
  reading a shit load of *useless* information.

### Internal Verbose levels
Now there are also some internal verbose levels that just the logger uses (I
use to see what the fuck is going on and if something fucks up).  But if you're
nosey and want to know what they are, here they are anyways.  I use them as
described above.  Just take out the word "INTERN\_" and that's what ya gotta
read upon above.
* `INTERN_WARNING`
* `INTERN_INFO`
* `INTERN_DEBUG`

## Getting to know the `loglf()` functions
### The basics
There are 4 functions that can be called to log.  Each function is prefixed
`logl` and suffixed with `f`.  The 'l' in `logl` stands for *level*, and the
'f' stands for *format*.

Three of the 4 functions use 2 other letters to differentiate themselves from
the rest.  Use this table as a general reference.

#### Basic literals
| letter | meaning |
|:------:| ------- |
| t      | time    |
| l      | line    |

Taken note of the very simple table above, you may notice that I did say
*three* functions , and I still still stand by what I said.  The last function
combines both the letter 't' and 'l' and what do you get?  You guessed it 'tl'.
If you're not able to guess what the 'tl' stands for...  Leave.  If you do,
then you can stay.  I will now show you another very simple table of the 4
functions.

### Extended literals
| log level | time | line | format | forms     | meaning                    |
|:---------:|:----:|:----:|:------:| --------- | -------------------------- |
| logl      |      |      | f      | `loglf`   | log level           format |
| logl      | t    |      | f      | `logltf`  | log level time      format |
| logl      |      | l    | f      | `logllf`  | log level      line format |
| logl      | t    | l    | f      | `logltlf` | log level time line format |

There, you now understand quantum physics.  If that table didn't help you
understand then leave...  For real..  Get the fuck out.  Read a book or
something.  Actually don't read a book, just read interwebs.

I really hope you were able to notice that 'logl' and the 'f' was mandatory in
each function because that was part of the point..  Anywho, each function have
the same first parameter, and the same last two parameters.

I will first show you the declaration for each function, followed by what each
parameter does, then finally followed by an example of how to use each one.

### Function declarations
#### `loglf()`  log level format
```c
extern void
loglf(enum verblvls verblvl, const char *strfmt, ...);
```

#### `logltf()` log level time format
```c
extern void
logltf(enum verblvls verblvl, const char *timestr, const char *strfmt, ...);
```

#### `logllf()` log level line format
```c
extern void
logllf(enum   verblvls        verblvl,
       const  unsigned  int   line,
       const            char  *strfmt, ...);
```

#### `logltf()` log level time line format
```c
extern void
logltlf(enum   verblvls       verblvl,
        const            char *timestr,
        const  unsigned  int  line,
        const            char *strfmt, ...);
```

So now tat you have seen the declaration for each function, lets tell you what
should have already noticed.

If you remember, previously I had said this:
> Anywho, each function have the same first parameter, and the same last two
> parameters.

If you're looking at the declaration and you're confused as fuck, look at the
end of each where the `...` are.  That is in fact a parameter, BUT it is not
mandatory.  It is in fact optional.

Lets break down each declaration so you can understand it more if you're
confused.

We currently know what each letter means in the function if you actually read
it above, and that the first and last two parameters are the same for each
function.  So really if you know one you know them all.  If you're confused yet
again, let me explain further.

Lets start with the last function `logltlf()` and take a look at it's
parameters.
<!-- Need the two trailing spaces in order for a new paragraph to not be
created -->

### The break down - The parameters

1. #### _verblvl_  
   This parameter can be any of the log levels described above.  An example one
   would be `WARNING`.
2. #### _*timestr_
   If you weren't already wondering, obviously means the time.  Now you don't
   have to specify the time here if you don't want to, you could simply use the
   date or whatever the fuck you wanted to, but for the purpose of this
   demonstration, we will use *time* because that's what in the name.

   There are a few different ways one can get the time, but the most simple way
   to do so is to use the Standard macro `__TIME__`.  All that this macro does
   is expands into the current time.

   Now like I had mentioned before, you could specify the date rather than the
   time, and to do so is the same principle.  Use the Standard macro
   `__DATE__`.  Now if you wanted to use both of them, it's still rather
   simple, but just not as simple as specifying `__TIME__`  `__DATE__`.  That
   wouldn't work.  So here is a quick code snipet that will demonstrate how to
   do so.
      ```c
      /*
       *  So the time and date stay the same during parsing.
       */
      const char *timestr   = __TIME__;
      const char *timedate  = __DATE__;
      int sz = snprintf(0, 0, "%s:%s", timestr, timedate);
      if (sz < 0) { exit(EXIT_FAILURE); }       /* Don't do failure part */

      /* Plus one for null byte */
      char *timedatestr = malloc(sz + 1);
      if (!timedatestr) { exit(EXIT_FAILURE); } /* Don't do failure part */

      sz = sprintf(timedatestr, "%s:%s", timestr, datestr);
      if (sz < 0) { exit(EXIT_FAILURE); }       /* Don't do failure part */
      /*
       *  timedatestr is now a valid string that contains not only the time,
       *    but the date as well.
       */
      ```

3. #### *line*
   Now as you can tell that the naming is pretty simple.  If you're aren't able
   to tell what this means well then you should really go back to school.  Like
   _*timestr_, *line* is also really easy to specify.  It's just a simple macro
   as well.  That macro is `__LINE__`.  What this will expand to is the current
   line of which `__LINE__` is on.  Now this may not give you accurate*is*
   results, and I will show you why.
      ```c
      /* 1 */ char*
      /* 2 */ gettimedatestr(const char *timestr, const char *datestr)
      /* 3 */ {
      /* 4 */     logllf(DEBUG, __LINE__, "%s\n", __func__);
      /* 5 */     /* ... */
      /* 6 */ }
      ```
   The code above is what I do for every single function (other than the
   logging functions because that would lead to being recursive).  What it
   basically does it tells me the function of which is just called.  The macro
   `__func` expands to the function name in this case `gettimedatestr`.  Note
   how the definition starts on line 2, but the macro `__LINE__` is on line 4.
   Being that the macro is on line 4, the output would be be displayed as
   follows.  
      `[       4]  DEBUG           gettimedatestr`  
   This isn't what we want because `gettimedatestr` is not defined on line 4,
   it is defined on line 2.  So the way to get the correct line number is by
   doing simple match.  For this specific situation I would just subtract 2
   like this `__LINE__ -2u`.  The reason why I am using the literal 'u' is
   because `__LINE__` expands into type `unsigned int` which if you did not
   know has a range from 0 to `UINT_MAX`.  No negative numbers.
4. #### _*strfmt_
   Have you ever used `printf()`?  You know you're specifying a string with
   parameters then passing arguments to correspond to those parameters?  This
   is the exact same process.  You do not need to specify a formatted string.
   You could simple specify a regular string if you like, just don't pass any
   arguments afterwards.  Just be sure to use append a new line with `\n`  so
   the output looks like it should, unless you know you don't need a new line.
5. #### *...*
   These are the *optional* arguments that will correspond to the formatted
   string given to the parameter _*strfmt_.  If you aren't using any parameters
   in _*strfmt_, don't give any arguments because that would be pointless.

## Examples
I promised given an example on how to use each one, and I am going to deliver.
So here are an example on how to use each one.
**<sup>NOTE:  These are just mere examples that I have taken out of the function
`isverblvl()` and just added a few extra lines.  Yes I am that lazy.</sup>**

### `loglf()`
```c
int
main(void)
{
    loglf(INTERN_DEBUG, "s\n", "Hello world!");

    return EXIT_SUCESSS;
}
```

### `logltf()`
```c
int
main(void)
{
    loglf(INTERN_DEBUG, "s\n", "Hello world!");
    /* level */
    unsigned int lvl = DEBUG;

    /* temp verbose level */
    unsigned char tmpvlvl = INTERN_INFO;

    /* temp level */
    int tmplvl =
        ((lvl && (lvl <= INTERN_DEBUG))
         ? lvl
         : (tmpvlvl = INTERN_WARNING, NVALID_VERB_LVL));

    logltf(tmpvlvl,
           __TIME__,
           XVALID_VERB_LVL,
           lvl,
           tmplvl ? " " : " not ");

    return EXIT_SUCCESS;
}
```

### `logllf()`
```c
/* 1 */ int
/* 2 */ main(void)
/* 3 */ {
/* 4 */     logllf(DEBUG, __LINE__ - 2u, "main\n");
/* 5 */
/* 6 */     return EXIT_SUCCESS;
/* 7 */ }
```

### `logtlf()`
```c
int
main(void)
{
    loglf(INTERN_DEBUG, "s\n", "Hello world!");
    logltlf(INTERN_DEBUG, __TIME__, __LINE__ - 3u, "%s\n", __func__);

    /* level */
    unsigned int lvl = DEBUG;

    /* temp verbose level */
    unsigned char tmpvlvl = INTERN_INFO;

    /* temp level */
    int tmplvl =
        ((lvl && (lvl <= INTERN_DEBUG))
         ? lvl
         : (tmpvlvl = INTERN_WARNING, NVALID_VERB_LVL));

    logltf(tmpvlvl,
           __TIME__,
           XVALID_VERB_LVL,
           lvl,
           tmplvl ? " " : " not ");

    logltlf(INTERN_DEBUG, __TIME__, __LINE__ + 1u, RMSG_D, tmplvl);
    return tmplvl;
}
```

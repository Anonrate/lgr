# lgr
**lgr** is a verbose logger that allows the user to output useful information
to a respected stream and/or file depending on the level given and
configurations.

To everyone logging levels can be used for different situations as compared to
others.  There is really no *official* way to use each level, it's just more of
common sense as to when, where and how to use each level.

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

Now there are also some internal verbose levels that just the logger uses (I
use to see what the fuck is going on and if something fucks up).  But if you're
nosey and want to know what they are, here they are anyways.  I use them as
described above.  Just take out the word "INTERN\_" and that's what ya gotta
read upon above.
* `INTERN_WARNING`
* `INTERN_INFO`
* `INTERN_DEBUG`

There are 4 functions that can be called to log.  Each function is prefixed
`logl` and suffixed with `f`.  The 'l' in `logl` stands for *level*, and the
'f' stands for *format*.

Three of the 4 functions use 2 other letters to differentiate themselves from
the rest.  Use this table as a general reference.

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

| log level | time | line | format | forms     | meaning                    |
|:---------:|:----:|:----:|:------:|:---------:| -------------------------- |
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

### `loglf()`  log level format
```c
extern void
loglf(enum verblvls verblvl, const char *strfmt, ...);
```

### `logltf()` log level time format
```c
extern void
logltf(enum verblvls verblvl, const char *timestr, const char *strfmt, ...);
```

### `logllf()` log level line format
```c
extern void
logllf(enum   verblvls        verblvl,
       const  unsigned  int   line,
       const            char  *strfmt, ...);
```

### `logltf()` log level time line format
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

Lets start with the last function `logltlf()`.

 The first parameter is *verblvl*.
   This parameter can be any of the log levels described above.  An example one
   would be `WARNING`.

 The second parameter is _*timestr_ and if you weren't wondering, it
   obviously means the time.  Now you don't have to specify the time here if
   you don't want to, you could simply use the date or whatever the fuck you
   wanted to, but for the purpose of this demonstration, we will use *time*
   because that's what in the name.

   There are a few different ways one can get the time, but the most simple way
   to do so is to use the standard macro `__TIME__`.  All that this macro does
   is expands into the current time

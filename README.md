<h1>lgr</h1>
<b>lgr</b> is verbose logger with the ability to log to a respected stream,
<em>stdout</em>, <em>stderr</em> and/or a file depending on the situtation and
configurations.

<h3>This list below contains the valid verbose levels</h3>
  * <a href=inc/lgr.h#L67><code>FATAL</code></a>  This verbose level depicts that whatever just
  occured, can not be recovered from, and therefore the application/lib etc..
  Needs to be terminate.
  * <a href=inc/lgr.h#L68><code>ERROR</code></a>  This verbose level is kind of along the same
  lines as `FATAL`except, the application/lib etc, can still run and work a bit
  , but most not.  If you're one that likes to have whatever your coding not
  terminate whatsoever until the job is completly done...  You could use this
  level.  Another possibly scenario that this level could be used is, if a
  function fails to do what you had wanted it to do, but returning something
  else will still make it work just not ideally..  This is your level.
  * <a href=inc/lgr.h#L69><code>WARNING</code></a>Say the user enters in something stupid that they
  aren't supposed to, but they either have another chance or you the code is
  sufficeint enough to fix the problem, you could use this level.
  * <a href=inc/lgr.h#L70><code>INFO</code></a>    This is pretty much self expalnitory.  It's
  purly for informative reasons.  Want to know input given was valid or not?
  <a href=inc/lgr.h#L70><code>INFO</code></a>is your verbosity of choice.
  * <a href=inc/lgr.h#71><code>DEBUG</code></a>   Finally last but most certainly not lease...
  <a href=inc/lgr.h#L71><code>DEBUG</code></a>.  Just use this on everything pretty much, that way
  when you test your code and it fucks up somehwere you didn't put any other
  log message too..  You still has something.  It information can be very
  little.  For example:  I put it at the starting of every function and when
  something is being returned.

   There are also some internal verbose level as well, but they are just used
   during debugging.  But here they are if you're wondering.
   * <a href=inc/lgr.h#L76><code>INTERN_WARNING</code></a>
   * <a href=inc/lgr.h#L81><code>INTERN_INFO</code></a>
   * <a href=inc/lgr.h#L86><code>INTERN_DEBUG</code></a>
There are a few different functions that log.  The following is their
correspdonding declarations.

<h3><a href=inc/lgr.h#L111><code>loglf()</code></a></h3>
log level format

Outputs desired information to respected stream and/or to a log file, depending
  on <a href=inc/lgr.h#59>verbose level</a> and configuration.

<code>verblvl<sup>[in]</sup></code>An enumerator constant declared in
  enumeration type <a href=inc/lgr.h#L59>verblvls</a> representing the
  verbosity level of specified message given in <code>strfmt</code>

<code>strfmt<sup>[in]</sup></code>Either a regular string containing
  information to be output to a stream and/or log file depending on what
  <code>verblvl</code> is set to and configurations or a formatted string.
  <sup>If a regular string is give, optional arguments, even if given will be
  ignored and not used.</sup>

If a formatted string is given, optional arguments will no longer be optional.
  They will be required in order to get the desired output.
<pre><code class=language-c>
    extern void
    loglf(enum verblvls verblvl, const char *strfmt, ...);
</code></pre>

<h3><a href=inc/lgr.h#L136><code>logltf()</code></a></h3>
log level time format

Outputs desired information to respected stream and/or to a log file, depending
  on <a href=inc/lgr.h#L59>verbose level</a> and configuration.

<code>verblvl<sup>[in]</sup></code>An enumerator constant declared in
  enumeration type <a href=inc/lgr.h#L59>verblvls</a> representing the
  verbosity level of specified message given in <code>strfmt</code>

<code>timestr<sup>[in]</sup></code> The time as a string to be output to the
  logger.

<code>strfmt<sup>in[in]</sup></code>Either a regular string containing
  information to be output to a stream and/or log file depending on what
  <code>verblvl</code> is set to and configurations or a formatted string.
  <sup>If a regular string is give, optional arguments, even if given will be
  ignored and not used.</sup>

If a formatted string is given, optional arguments will no longer beoptional.
  They will be required in order to get the desired output.
<pre>
  <code class=lang-c>
    extern void
    logltf(enum verblvls verblvl, const char *timestr, const char *strfmt, ...);
  </code>
</pre>

<h3><a href=inc/lgr.h#L162><code>logllf()</code></a></h3>
log level line format

Outputs desired information to respected stream and/or to a log file, depending
  on <a href=inc/lgr.h#L59>verbose level</a> and configuration.

<code>verblvl<sup>[in]</sup></code>An enumerator constant declared in
  enumeration type <a href=inc/lgr.h#L59>verblvls</a> representing the
  verbosity level of specified message given in <code>strfmt</code>

<code>line<sup>[in]</sup></code>   The line of which corresponds to the given
to by <code>strfmt</code>.

<code>strfmt<sup>in[in]</sup></code>Either a regular string containing
  information to be output to a stream and/or log file depending on what
  <code>verblvl</code> is set to and configurations or a formatted string.
  <sup>If a regular string is give, optional arguments, even if given will be
  ignored and not used.</sup>

If a formatted string is given, optional arguments will no longer beoptional.
  They will be required in order to get the desired output.
<pre>
  <code class=lang-c>
    extern void
    logllf(enum   verblvls        verblvl,
           const  unsigned  int   line,
           const            char  *strfmt, ...);
  </code>
</pre>

<h3><a href=inc/lgr.h#L191><code>logltlf()</code></a></h3>
log level line format

Outputs desired information to respected stream and/or to a log file, depending
  on <a href=inc/lgr.h#L59>verbose level</a> and configuration.

<code>verblvl<sup>[in]</sup></code>An enumerator constant declared in
  enumeration type <a href=inc/lgr.h#L59>verblvls</a> representing the
  verbosity level of specified message given in <code>strfmt</code>

<code>timestr<sup>[in]</sup></code> The time as a string to be output to the
  logger.

<code>line<sup>[in]</sup></code>   The line of which corresponds to the given
  to by <code>strfmt</code>.

<code>strfmt<sup>in[in]</sup></code>Either a regular string containing
  information to be output to a stream and/or log file depending on what
  <code>verblvl</code> is set to and configurations or a formatted string.
  <sup>If a regular string is give, optional arguments, even if given will be
  ignored and not used.</sup>

If a formatted string is given, optional arguments will no longer beoptional.
  They will be required in order to get the desired output.
<pre>
  <code class=lang-c>
    extern void
    logltlf(enum   verblvls       verblvl,
            const            char  *timestr,
            const  unsigned  int   line,
            const            char  *strfmt, ...);
  </code>
</pre>





THIS IS NOT EVEN CLOSE TO BEING THE FINAL DRAFT!  I JUST WANTED SOMETHING TO BE
DISPLAYED SO I QUICKLY TYPED OUT THIS HUNK OF SHIT!  DON'T GET BUTT HURT AND/OR
CRY BECAUSE I DON'T CARE!  THATS A YOU PROBLEM, NOT ME..

lgr is what I'm hoping to be an advanced logger that is able to log to a
specified stream, and/or file depending on the conditions and/or
configurations.

There are multiple verbose levels.
FATAL:    If you're logging with this...  Ods are something on your application
fucked up.

ERROR:    Almost like FATAL except, the application is able to run atabit.
Still not stable in any way or form but, but usable; shitty but usable.  Very
shitty but kind of not really usable.

WARNING:  If something kind of fucks but say when it does so, you can just
return the current value instead of changing it..  Use this bitch.

INFO:     This is just to inform you on information such as if something was
sucessfully done.

DEBUG:    This bitch is just used for everything...  You calling a function?
Put this bitch and let yourself know when ya calling it.

There are a few other ones, but they are just used internally for when I was
(Still am at current moment of typing this) coding this library.
They are as follows:
INTERN_WARNING
INTERN_INFO
INTERN_DEBUG

They are used for pretty much what I described above.
While typing this out in vim, the undscore doesn't look to happy intbeween the
words.

Also, please take note that this isn't even close to being the final draft and
what is going to be used to be taken seriously as a description for this.

Spelling is fucked, wording is fucked swearing is good however.  I just hope
it's not against Git policy.  I probably should have checked that.

You're able to log to a file (Not implemented yet)
You're able to change what the verbose level is.
You're able to specify what level of verbosity is to be using with the message.
You're able to treat warrning as errors.
You're able to specify if you want to include the time with the message;
You're also able to specify if you want to include the line number with the
message.

Todo so you need to specify both of them yourself.  This is very easy.
For to just use the macro __TIME__ (There is supposed to be 2 underscores
prefixing and suffixing the word TIME, but I doubt that worked).  As for the
line, you do the same thing __LINE__.  (Probably can't see them again.)

You can also choose weather or not if you want to use both at the sametime.
There is a different function for each one but I am kind of two lazy fuck it.

loglf:    Just logs with a level and uses vargs if present.
logltf:   The same as above except you specify the time.
logllf:   The same as the first one expcet you specify the line.
logltlf:  All three of em cunts put togeather.

I will eventually adding support for color..  When that is going to be is
beyhond me.  I still need to do the file log part.

I also want to add an option so you can set your own format for the time and/or
date and/or function, but if you're smart you would know how to implement it
while passing a string to the timestr parameter.

This is all standard (I'm pretty sure, I have tried to make sure it is).  It
uses magic numbers meaning if something null or false, I use 0.  If something
is true I use a nonzero (Usually 1).

This project is far from done and I am high at keeping this project active and
that probably didn't even make sense.

I also may include an option to choose what the filename you want the file log
to be.

You can also choose the file log piororiy fuck spelling.

Also am hoping that I will add a feature to include what levels to be out by
the logger.  So say you want INFO, DEBUG and FATAL, but not WARNING or ERROR
because you're fucking dumb..  You can do that.  I may add that.

THIS IS NOT EVEN CLOSE TO BEING THE FINAL DRAFT!  I JUST WANTED SOMETHING TO BE
DISPLAYED SO I QUICKLY TYPED OUT THIS HUNK OF SHIT!  DON'T GET BUTT HURT AND/OR
CRY BECAUSE I DON'T CARE!  THATS A YOU PROBLEM, NOT ME..

<h1>lgr</h1>
<b>lgr</b> is verbose logger with the ability to log to a respected stream,
<em>stdout</em>, <em>stderr</em> and/or a file depending on the situation and
configurations.

<h3>This list below contains the valid verbose levels</h3>
* <a href=inc/lgr.h#L67><code>FATAL</code></a>  This verbose level depicts that
whatever just occurred, can not be recovered from, and therefore the
application/lib etc.. Needs to be terminate.
* <a href=inc/lgr.h#L68><code>ERROR</code></a>  This verbose level is kind of
along the same lines as `FATAL`except, the application/lib etc, can still run
and work a bit, but most not.  If you're one that likes to have whatever your
coding not terminate whatsoever until the job is completely done...  You could
use this level.  Another possibly scenario that this level could be used is, if
a function fails to do what you had wanted it to do, but returning something
else will still make it work just not ideally..  This is your level.
* <a href=inc/lgr.h#L69><code>WARNING</code></a>Say the user enters in
something stupid that they aren't supposed to, but they either have another
chance or you the code is sufficient enough to fix the problem, you could use
this level.
* <a href=inc/lgr.h#L70><code>INFO</code></a>    This is pretty much self
explanatory.  It's purely for informative reasons.  Want to know input given
was valid or not?  <a href=inc/lgr.h#L70><code>INFO</code></a>is your verbosity
of choice.
* <a href=inc/lgr.h#71><code>DEBUG</code></a>   Finally last but most
certainly not lease...  <a href=inc/lgr.h#L71><code>DEBUG</code></a>.
Just use this on everything pretty much, that way when you test your code and
it fucks up somewhere you didn't put any other log message too..  You still has
something.  It information can be very little.  For example:  I put it at the
starting of every function and when something is being returned.

There are also some internal verbose level as well, but they are just used
  during debugging.  But here they are if you're wondering.
* <a href=inc/lgr.h#L76><code>INTERN_WARNING</code></a>
* <a href=inc/lgr.h#L81><code>INTERN_INFO</code></a>
* <a href=inc/lgr.h#L86><code>INTERN_DEBUG</code></a>

There are a few different functions that log.  The following is their
corresponding declarations.

<h3><a href=inc/lgr.h#L111><code>loglf()</code></a></h3>
log level format

Outputs desired information to respected stream and/or to a log file, depending
  on <a href=inc/lgr.h#59>verbose level</a> and configuration.

<em>verblvl</em><sup>[in]</sup> An enumerator constant declared in
  enumeration type <a href=inc/lgr.h#L59>verblvls</a> representing the
  verbosity level of specified message given in <em>strfmt</em>.

<em>line</em><sup>[in]</sup>    Either a regular string containing
  information to be output to a stream and/or log file depending on what
  <em>verblvl</em> is set to and configurations or a formatted string.
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
Hello world!
<em>verblvl</em><sup>[in]</sup> An enumerator constant declared in
  enumeration type <a href=inc/lgr.h#L59>verblvls</a> representing the
  verbosity level of specified message given in <em>strfmt</em>.

<em>timefmt</em><sup>[in]</sup> The time as a string to be output to the
  logger.

<em>strfmt</em><sup>[in]</sup>  Either a regular string containing
  information to be output to a stream and/or log file depending on what
  <em>verblvl</em> is set to and configurations or a formatted string.
  <sup>If a regular string is give, optional arguments, even if given will be
  ignored and not used.</sup>

If a formatted string is given, optional arguments will no longer be optional.
  They will be required in order to get the desired output.
<pre><code class=language-c>
    extern void
    logltf(enum verblvls  verblvl,
           const char     *timestr,
           const char     *strfmt, ...);
</code></pre>

<h3><a href=inc/lgr.h#L162><code>logllf()</code></a></h3>
log level line format

Outputs desired information to respected stream and/or to a log file, depending
  on <a href=inc/lgr.h#L59>verbose level</a> and configuration.

<em>verblvl</em><sup>[in]</sup> An enumerator constant declared in
  enumeration type <a href=inc/lgr.h#L59>verblvls</a> representing the
  verbosity level of specified message given in <em>strfmt</em>.

<em>line</em><sup>[in]</sup>    The line of which corresponds to the given
to by <em>strfmt</em>.

<em>strfmt</em><sup>[in]</sup>  Either a regular string containing
  information to be output to a stream and/or log file depending on what
  <em>verblvl</em> is set to and configurations or a formatted string.
  <sup>If a regular string is give, optional arguments, even if given will be
  ignored and not used.</sup>

If a formatted string is given, optional arguments will no longer be optional.
  They will be required in order to get the desired output.
<pre><code class=language-c>
    extern void
    logllf(enum   verblvls        verblvl,
           const  unsigned  int   line,
           const            char  *strfmt, ...);
</code></pre>

<h3><a href=inc/lgr.h#L191>logltlf()</a></h3>
log level line format

Outputs desired information to respected stream and/or to a log file, depending
  on <a href=inc/lgr.h#L59>verbose level</a> and configuration.

<em>verblvl</em><sup>[in]</sup> An enumerator constant declared in
  enumeration type <a href=inc/lgr.h#L59>verblvls</a> representing the
  verbosity level of specified message given in <em>strfmt</em>.

<em>timestr</em><sup>[in]</sup> The time as a string to be output to the
  logger.

<em>line</em><sup>[in]</sup>    The line of which corresponds to the given
  to by <code>strfmt</code>.

<code>strfmt<sup>[in]</sup></code>Either a regular string containing
  information to be output to a stream and/or log file depending on what
  <em>verblvl</em> is set to and configurations or a formatted string.
  <sup>If a regular string is give, optional arguments, even if given will be
  ignored and not used.</sup>

If a formatted string is given, optional arguments will no longer be optional.
  They will be required in order to get the desired output.
<pre><code class=language-c>
    extern void
    logltlf(enum   verblvls       verblvl,
            const            char *timestr,
            const  unsigned  int  line,
            const            char *strfmt, ...);
</code></pre>

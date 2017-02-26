# lgr
<b>lgr</b> is verbose logger with the ability to log to a respected stream,
<em>stdout</em>, <em>stderr</em> and/or a file depending on the situtation and
configurations.

#### This list below contains the valid verbose levels
  * `FATAL`
  * `ERROR`
  * `WARNING`
  * `INFO`
  * `DEBUG`

  There are also some internal verbose level as well, but they are just used
  during debugging.  But here they are if you're wondering.
  * `INTERN_WARNING`
  * `INTERN_INFO`
  * `INTERN_DEBUG`

| verbose level   | Description |
| --------------- | ----------- |
| `FATAL`         | `FATAL` depicts that whatever just occured can not be
recovered by, and therefore needs to be terminated.|
| `ERROR`         | test        |
| `WARNING`       | test        |
| `INFO`          | test        |
| `DEBUG`         | test        |

1. Test list 2?
2. Test list 2 and 3 work but not 1?
  * So for this kind of list two spaces are needed
  1. You can do this as well.
   Three spaces...

   Three spaces and blank line
  - You can use this
  + this 
    - this is this a sub point?







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

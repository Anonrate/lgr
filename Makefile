IDIR		= inc
CC			=	gcc
CFLAGS	= -I$(IDIR)

BDIR	= bin
LDIR	= ../timex/lib
LIBS	= -ltimex
ODIR	= obj
SDIR	= src
_DEPS	= lgr.h ../../timex/inc/timex.h
DEPS	= $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ	= lgr.o ../../timex/obj/timex.o
OBJ		= $(patsubst %,$(ODIR)/%,$(_OBJ))

_CDEPS	= lgr.c ../../timex/src/timex.c
CDEPS		= $(patsubst %,$(SDIR)/%,$(_CDEPS))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lgr: $(OBJ)
	gcc -o $(BDIR)/$@ $^ $(CFLAGS) -L$(LDIR)/ $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

IDIR		= inc
CC			=	gcc
CFLAGS	= -I$(IDIR)

LDIR	= lib
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

lgrmake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

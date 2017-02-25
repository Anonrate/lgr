IDIR		= inc
CC			=	gcc

BDIR	= bin
ODIR	= obj
SDIR	= src
_DEPS	= lgr.h
DEPS	= $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ	= lgr.o
OBJ		= $(patsubst %,$(ODIR)/%,$(_OBJ))

_CDEPS	= lgr.c
CDEPS		= $(patsubst %,$(SDIR)/%,$(_CDEPS))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lgr: $(OBJ)
	gcc -o $(BDIR)/$@ $^ $(CFLAGS) -L$(LDIR)/ $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

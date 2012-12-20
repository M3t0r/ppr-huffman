DEBUGFLAGS = 
ifdef DEBUG
DEBUGFLAGS = -g
endif

CCFLAGS = -std=c89 -pedantic-errors -Wall $(DEBUGFLAGS)
LDFLAGS = 
SFLAGS = -weak -booltype BOOL -boolfalse FALSE -booltrue TRUE +predboolint +noret +usedef +infloops +casebreak -initallelements -incompletetype -fixedformalarray
OUTPUT = ppr-huffman
BUILDDIR = build/
SRC = main.c

all: $(OUTPOUT)

splint:
	@splint $(SFLAGS) *.c *.h

# das endprodukt linken
$(OUTPUT): $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(SRC)))
	# alles zusammen linken, $^ sind alle vorraussetzungen, $@ das ziel
	@echo $^
	$(LD) $(LDFLAGS) $^ -o $@

# einzelne quellen compilen
$(BUILDDIR)/%.c.o: %.c
	-@mkdir -p $(BUILDDIR)
	@echo $^
	$(CC) $(CCFLAGS) -c $^ -o $@

clean:
	-rm $(OUTPUT)
	-rm -rf $(BUILDDIR)
	
debug:
	-@make clean
	@make DEBUG=1



.PHONY: clean debug
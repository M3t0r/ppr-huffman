DEBUGFLAGS = 
ifdef DEBUG
DEBUGFLAGS = -g -DDEBUG
endif

CCFLAGS = -std=c89 -pedantic-errors -Wall $(DEBUGFLAGS)
LDFLAGS = 
LD = $(CC)
SFLAGS = -weak -booltype BOOL -boolfalse FALSE -booltrue TRUE +predboolint +noret +usedef +infloops +casebreak -initallelements -incompletetype -fixedformalarray
OUTPUT = ppr-huffman
BUILDDIR = build/
SRC = main.c bit_access.c cmdargs.c

# das endprodukt linken
$(OUTPUT): $(addprefix $(BUILDDIR), $(addsuffix .o, $(SRC)))
# alles zusammen linken, $^ sind alle vorraussetzungen, $@ das ziel
	@echo "  (LD) $^ -> $@"
	@$(LD) $(LDFLAGS) $^ -o $@

all: clean $(OUTPUT)

splint:
	@splint $(SFLAGS) *.c *.h

# einzelne quellen compilen
$(BUILDDIR)%.c.o: %.c
	-@mkdir -p $(BUILDDIR)
	@echo "  (CC) $^"
	@$(CC) $(CCFLAGS) -c $^ -o $@

clean:
	-@rm -rf $(OUTPUT) $(BUILDDIR)
	-@echo "clean!"
	
debug:
	-@make clean
	@make DEBUG=1



.PHONY: clean debug
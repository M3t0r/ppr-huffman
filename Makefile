DEBUGFLAGS 		= 
ifdef DEBUG
DEBUGFLAGS 		= -g -DDEBUG
endif

CCFLAGS 		= -std=c89 -pedantic-errors -Wall $(DEBUGFLAGS)
LD 				= $(CC)
SFLAGS 			= -weak -booltype BOOL -boolfalse FALSE -booltrue TRUE +predboolint +noret +usedef +infloops +casebreak -initallelements -incompletetype -fixedformalarray
SPLINT_LOG		= ./splint.log
OUTPUT 			= ppr-huffman
BUILDDIR 		= build/
SRC 			= bitarray.c bitfile.c cmdargs.c code.c codebuch.c frequency.c heap.c huffmann.c main.c
DOXYGEN_PATH 	= doxygen
DOXYGEN_FILE 	= $(DOXYGEN_PATH)/html/index.html
DOXYGEN_CFG 	= ./doxygen.cfg
PNG				= ./struktur.png

# das endprodukt linken
$(OUTPUT): $(addprefix $(BUILDDIR), $(addsuffix .o, $(SRC)))
# alles zusammen linken, $^ sind alle vorraussetzungen, $@ das ziel
	@echo "  (LD) $^ -> $@"
	@$(LD) $(LDFLAGS) $^ -o $@

bitdump: $(addprefix $(BUILDDIR), $(addsuffix .o, bitdump.c bitfile.c bitarray.c))
	@echo "  (LD) $^ -> $@"
	@$(LD) $(LDFLAGS) $^ -o $@

all: clean splint doxygen $(OUTPUT)

splint:
	@echo "Prüfe Dateien mit splint"
	@splint $(SFLAGS) $(SRC) $(filter-out main.h,$(SRC:.c=.h)) | tee $(SPLINT_LOG)
	
doxygen: $(DOXYGEN_FILE)

$(DOXYGEN_FILE): *.c *.h
	@echo "Erzeuge Doxygen-Dokumentation"
	@doxygen $(DOXYGEN_CFG)
	@cp $(PNG) $(DOXYGEN_PATH)/html/

# einzelne quellen compilen
$(BUILDDIR)%.c.o: %.c
	-@mkdir -p $(BUILDDIR)
	@echo "  (CC) $^"
	@$(CC) $(CCFLAGS) -c $^ -o $@


test: clean tests/bitarray tests/bitfile tests/heap tests/code tests/frequency tests/codebuch
	@tests/test.sh

tests/bitarray: bitarray.c tests/bitarray_test.c tests/testmain.c
	@$(CC) $(CCFLAGS) -g -DDEBUG $^ -o $@

tests/bitfile: bitarray.c bitfile.c tests/bitfile_test.c tests/testmain.c
	@$(CC) $(CCFLAGS) -g -DDEBUG $^ -o $@

tests/heap: heap.c tests/heap_test.c tests/testmain.c
	@$(CC) $(CCFLAGS) -g -DDEBUG $^ -o $@
	
tests/code: bitarray.c code.c tests/code_test.c tests/testmain.c
	@$(CC) $(CCFLAGS) -g -DDEBUG $^ -o $@
	
tests/frequency: frequency.c tests/frequency_test.c tests/testmain.c
	@$(CC) $(CCFLAGS) -g -DDEBUG $^ -o $@
	
tests/codebuch: bitarray.c heap.c code.c frequency.c codebuch.c tests/codebuch_test.c tests/testmain.c
	@$(CC) $(CCFLAGS) -g -DDEBUG $^ -o $@

clean:
	-@rm -rf $(OUTPUT) $(BUILDDIR)
	-@rm -rf tests/codebuch tests/frequency tests/heap tests/test tests/code tests/bitarray tests/bitfile tests/*.dSYM tests/bitfile_write.txt
	-@rm -rf $(DOXYGEN_PATH)
	-@rm -rf $(SPLINT_LOG)
	-@echo "clean!"
	
debug: clean
	@make DEBUG=1


.PHONY: clean debug test

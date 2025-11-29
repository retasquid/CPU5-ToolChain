# Chemins
CCOMP_DIR = Ccomp
ASMCOMP_DIR = ASMcomp
FLASHER_DIR = Flasher3.1/PC_flasher

all: compile_c preprocess compile_asm flash

compile_c:
	cd $(CCOMP_DIR) && \
	bison -d parser.y && \
	flex lexer.l && \
	gcc parser.tab.c lex.yy.c -o CcompilerCPU5

preprocess:
	gcc -E -P ../main.c -o $(CCOMP_DIR)/CompFiles/main.i

compile_asm:
	cd $(CCOMP_DIR) && \
	./CcompilerCPU5 CompFiles/main.i -o CompFiles/main.asm
	python $(ASMCOMP_DIR)/ASMcompilerCPU5.py $(CCOMP_DIR)/CompFiles/main.asm $(ASMCOMP_DIR)/CompFiles/prog.py

flash:
	python $(FLASHER_DIR)/programmer.py $(ASMCOMP_DIR)/CompFiles/prog.py

clean:
	rm -f $(CCOMP_DIR)/CcompilerCPU5
	rm -f $(CCOMP_DIR)/parser.tab.* $(CCOMP_DIR)/lex.yy.c
	rm -f $(CCOMP_DIR)/CompFiles/main.i
	rm -f $(CCOMP_DIR)/CompFiles/main.asm
	rm -f $(ASMCOMP_DIR)/CompFiles/prog.py

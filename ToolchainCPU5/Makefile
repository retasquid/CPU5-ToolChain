all:
	@cd Ccomp
	@bison -d parser.y
	@flex lexer.l
	@gcc parser.tab.c lex.yy.c -o CcompilerCPU5
	@gcc -E -P ../../main.c -o CompFiles/main.i
	@./CcompilerCPU5 CompFiles/main.i -o CompFiles/main.asm
	@cd ../
	@python ASMcomp/ASMcompilerCPU5.py Ccomp/CompFiles/main.asm ASMcomp/CompFiles/prog.py
	@python Flasher3.1/PC_flasher/programmer.py ASMcomp/CompFiles/prog.py

@cd Ccomp
@Win_bison -d parser.y
@Win_flex lexer.l
@gcc parser.tab.c lex.yy.c -o CcompilerCPU5
@gcc -E -P ../../main.c -o CompFiles/main.i
@CcompilerCPU5.exe CompFiles/main.i -o CompFiles/main.asm
@cd ../
@python3 ASMcomp/ASMcompilerCPU5.py Ccomp/CompFiles/main.asm ASMcomp/CompFiles/prog.py
@python3 Flasher3.1/PC_flasher/programmer.py ASMcomp/CompFiles/prog.py
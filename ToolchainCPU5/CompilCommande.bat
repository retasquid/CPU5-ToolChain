@echo off
set FILENAME=%1
set FILEPATH=%2

REM Si pas d'argument, utiliser main par défaut
if "%FILENAME%"=="" set FILENAME=main
if "%FILEPATH%"=="" set FILEPATH=%CD%\main.c

@cd Ccomp
@Win_bison -d parser.y
@Win_flex lexer.l
@gcc parser.tab.c lex.yy.c -o CcompilerCPU5
@gcc -E -P "%FILEPATH%" -o CompFiles/%FILENAME%.i
@CcompilerCPU5.exe CompFiles/%FILENAME%.i -o CompFiles/%FILENAME%.asm
@cd ../
@python3 ASMcomp/ASMcompilerCPU5.py Ccomp/CompFiles/%FILENAME%.asm ASMcomp/CompFiles/prog.py
@python3 Flasher3.1/PC_flasher/programmer.py ASMcomp/CompFiles/prog.py
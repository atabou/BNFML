

INC=./include
SRC=./src
OBJ=./obj
EXE=./bin

COMPILE=${OBJ}/AndExpr.o ${OBJ}/Binding.o ${OBJ}/BindingList.o ${OBJ}/NonTerminal.o ${OBJ}/OrExpr.o ${OBJ}/Symbol.o ${OBJ}/Terminal.o ${OBJ}/bnf.tab.o ${OBJ}/lex.yy.o

${EXE}/bnfml: ${COMPILE}
	gcc -o bin/bnfml ${COMPILE}

${OBJ}/AndExpr.o: ${SRC}/AndExpr.c ${INC}/BNF.h
	gcc -c $< -o $@

${OBJ}/Binding.o: ${SRC}/Binding.c ${INC}/BNF.h
	gcc -c $< -o $@

${OBJ}/BindingList.o: ${SRC}/BindingList.c ${INC}/BNF.h
	gcc -c $< -o $@

${OBJ}/NonTerminal.o: ${SRC}/NonTerminal.c ${INC}/BNF.h
	gcc -c $< -o $@

${OBJ}/OrExpr.o: ${SRC}/OrExpr.c ${INC}/BNF.h
	gcc -c $< -o $@

${OBJ}/Symbol.o: ${SRC}/Symbol.c ${INC}/BNF.h
	gcc -c $< -o $@

${OBJ}/Terminal.o: ${SRC}/Terminal.c ${INC}/BNF.h
	gcc -c $< -o $@

${OBJ}/bnf.tab.o: bnf.tab.c bnf.tab.h
	gcc -c $< -o $@

bnf.tab.c:	bnf.y ${INC}/BNF.h
	bison -d --graph="log/bnfml.dot" -v --report-file="log/bnfml.output" bnf.y

${OBJ}/lex.yy.o: lex.yy.c bnf.tab.h
	gcc -c $< -o $@

lex.yy.c: bnf.flex
	flex bnf.flex

clean:
	rm bnf.tab.h bnf.tab.c lex.yy.c obj/* bin/* log/*
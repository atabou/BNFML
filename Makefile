

INC=./include
SRC=./src
OBJ=./obj
EXE=./bin

COMPILE=${OBJ}/AndExpr.o ${OBJ}/Binding.o ${OBJ}/BindingList.o ${OBJ}/NonTerminal.o ${OBJ}/OrExpr.o ${OBJ}/Terminal.o ${OBJ}/bnfml.tab.o ${OBJ}/lex.yy.o

${EXE}/bnfml: ${COMPILE}
	gcc -Iinclude -o bin/bnfml ${COMPILE}

${OBJ}/AndExpr.o: ${SRC}/AndExpr.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/Binding.o: ${SRC}/Binding.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/BindingList.o: ${SRC}/BindingList.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/NonTerminal.o: ${SRC}/NonTerminal.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/OrExpr.o: ${SRC}/OrExpr.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/Terminal.o: ${SRC}/Terminal.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/bnfml.tab.o: ${SRC}/bnfml.tab.c ${INC}/bnfml.tab.h
	gcc -Iinclude -c $< -o $@

${SRC}/bnfml.tab.c: bnfml.y ${INC}/ParserTree.h
	bison --defines="include/bnfml.tab.h" --output="src/bnfml.tab.c" --graph="log/bnfml.dot" -v --report-file="log/bnfml.output" bnfml.y

${OBJ}/lex.yy.o: ${SRC}/lex.yy.c ${INC}/bnfml.tab.h
	gcc -Iinclude -c $< -o $@

${SRC}/lex.yy.c: bnfml.flex
	flex --outfile="src/lex.yy.c" bnfml.flex

clean:
	rm include/bnfml.tab.h src/bnfml.tab.c src/lex.yy.c obj/* bin/* log/*


INC=./include
PTREE=./src/ParserTree
ETREE=./src/ExecutionTree
GEN=./src/Generated
OBJ=./obj
EXE=./bin

COMPILE=${OBJ}/AndExpr.o ${OBJ}/Binding.o ${OBJ}/BindingList.o ${OBJ}/NonTerminal.o ${OBJ}/OrExpr.o ${OBJ}/Terminal.o ${OBJ}/bnfml.tab.o ${OBJ}/lex.yy.o ${OBJ}/ExecutionNode.o ${OBJ}/ExecutionTree.o




${EXE}/bnfml: ${COMPILE}
	gcc -Iinclude -o bin/bnfml ${COMPILE}

${OBJ}/AndExpr.o: ${PTREE}/AndExpr.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/Binding.o: ${PTREE}/Binding.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/BindingList.o: ${PTREE}/BindingList.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/NonTerminal.o: ${PTREE}/NonTerminal.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/OrExpr.o: ${PTREE}/OrExpr.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/Terminal.o: ${PTREE}/Terminal.c ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@




${OBJ}/ExecutionNode.o: ${ETREE}/ExecutionNode.c ${INC}/ParserTree.h ${INC}/ExecutionTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/ExecutionTree.o: ${ETREE}/ExecutionTree.c ${INC}/ParserTree.h ${INC}/ExecutionTree.h
	gcc -Iinclude -c $< -o $@




${OBJ}/bnfml.tab.o: ${GEN}/bnfml.tab.c ${INC}/bnfml.tab.h
	gcc -Iinclude -c $< -o $@

${GEN}/bnfml.tab.c: bnfml.y ${INC}/ParserTree.h
	bison --defines="include/bnfml.tab.h" --output="${GEN}/bnfml.tab.c" --graph="log/bnfml.dot" -v --report-file="log/bnfml.output" bnfml.y

${OBJ}/lex.yy.o: ${GEN}/lex.yy.c ${INC}/bnfml.tab.h
	gcc -Iinclude -c $< -o $@

${GEN}/lex.yy.c: bnfml.flex
	flex --outfile="${GEN}/lex.yy.c" bnfml.flex

clean:
	rm include/bnfml.tab.h ${GEN}/bnfml.tab.c ${GEN}/lex.yy.c obj/* bin/* log/*
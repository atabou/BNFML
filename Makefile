

INC=./include

PTREE=./src/ParserTree
PTREE_H=${INC}/ParserTree

ETREE=./src/ExecutionGraph
GEN=./src/Generated
OBJ=./obj
EXE=./bin

COMPILE=${OBJ}/AndExpr.o ${OBJ}/Binding.o ${OBJ}/BindingList.o ${OBJ}/NonTerminal.o ${OBJ}/OrExpr.o ${OBJ}/Terminal.o ${OBJ}/Symbol.o ${OBJ}/bnfml.tab.o ${OBJ}/lex.yy.o ${OBJ}/ExecutionNode.o ${OBJ}/ExecutionGraph.o




${EXE}/bnfml: ${COMPILE}
	gcc -Iinclude -o bin/bnfml ${COMPILE}



${OBJ}/NonTerminal.o: ${PTREE}/NonTerminal.c ${PTREE_H}/NonTerminal.h ${INC}/Common.h
	gcc -Iinclude -c $< -o $@

${OBJ}/Terminal.o: ${PTREE}/Terminal.c ${PTREE_H}/Terminal.h ${INC}/Common.h
	gcc -Iinclude -c $< -o $@

${OBJ}/AndExpr.o: ${PTREE}/AndExpr.c ${PTREE_H}/AndExpr.h ${PTREE_H}/NonTerminal.h ${PTREE_H}/Terminal.h ${INC}/Common.h
	gcc -Iinclude -c $< -o $@

${OBJ}/OrExpr.o: ${PTREE}/OrExpr.c ${PTREE_H}/OrExpr.h ${PTREE_H}/AndExpr.h ${INC}/Common.h
	gcc -Iinclude -c $< -o $@

${OBJ}/Binding.o: ${PTREE}/Binding.c ${PTREE_H}/Binding.h ${PTREE_H}/NonTerminal.h ${PTREE_H}/OrExpr.h ${INC}/Common.h
	gcc -Iinclude -c $< -o $@

${OBJ}/BindingList.o: ${PTREE}/BindingList.c ${PTREE_H}/BindingList.h ${PTREE_H}/Binding.h ${INC}/Common.h
	gcc -Iinclude -c $< -o $@

${OBJ}/Symbol.o: ${PTREE}/Symbol.c ${PTREE_H}/Symbol.h ${PTREE_H}/Terminal.h ${PTREE_H}/NonTerminal.h
	gcc -Iinclude -c $< -o $@


${OBJ}/ExecutionNode.o : ${ETREE}/ExecutionNode.c ${INC}/ExecutionGraph.h ${INC}/ParserTree.h
	gcc -Iinclude -c $< -o $@

${OBJ}/ExecutionGraph.o: ${ETREE}/ExecutionGraph.c ${INC}/ExecutionGraph.h ${INC}/ParserTree.h
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
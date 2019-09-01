CXX=clang++
CFLAGS=-Wall -Wextra
CXXFLAGS=$(CFLAGS) -std=c++14 -Wno-deprecated-register
LDFLAGS=-ll

asvm: lex.yy.o operand.o exceptions.o

lex.yy.cc: asvm.lex
	flex++ asvm.lex

clean:
	rm -f lex.yy.o lex.yy.cc
	rm -f operand.o exceptions.o
	rm -f asvm
	rm -rf asvm.dSYM

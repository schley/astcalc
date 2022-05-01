CPP	= g++ 
CPPOPTS	= -g -Wshadow -Wall -Wextra -pedantic -pedantic-errors -std=c++20
CXXOPTS = 


LINK	= g++
LINKOPTS= 
LIBS	= 


OUT	= astcalc 

SOURCE	= numberCalc.cxx \
	Token.cxx \
	Parser.cxx \
	Logger.cxx \
	AstNode.cxx \
	AstTree.cxx \
	CodeGenStack.cxx \
	AstNodeVisitor.cxx

OBJECTS	= $(addsuffix .o, $(basename $(SOURCE)))

%.o	: %.cxx
	$(CPP) $(CPPOPTS) $(CXXOPTS) -c $^ -o $@

$(OUT)	: $(OBJECTS)
	$(LINK) $(LINKOPTS) $(OBJECTS) $(LIBS) -o $@

clean	:
	rm -f $(OBJECTS)
	rm -f $(OUT)
	rm -f core*
	rm -f *debug.log

# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = test/gtest

# Where to find user code.
USER_DIR = src

# The test code.
TEST_DIR = test

# Flags passed to the preprocessor.
CPPFLAGS += -I$(GTEST_DIR) -I$(GTEST_DIR)/include -I$(USER_DIR) -I.

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = OctaveTest GrammarTest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

Octave.o : $(USER_DIR)/Octave.cpp $(USER_DIR)/Octave.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Octave.cpp

OctaveTest.o : $(TEST_DIR)/OctaveTest.cpp \
               $(USER_DIR)/Octave.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TEST_DIR)/OctaveTest.cpp

OctaveTest : Octave.o OctaveTest.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

GrammarTest.o : $(TEST_DIR)/GrammarTest.cpp \
				$(USER_DIR)/Ast.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TEST_DIR)/GrammarTest.cpp

Parser.o : Parser.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^ 

Parser.cpp : $(USER_DIR)/Parser.y $(USER_DIR)/Ast.h
	bison -d -o $@ $(USER_DIR)/Parser.y

Parser.hpp : Parser.cpp

Lexer.o : Lexer.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

Lexer.cpp : $(USER_DIR)/Lexer.l Parser.hpp
	lex -o $@ --header-file=Lexer.h $(USER_DIR)/Lexer.l 

Lexer.h : Lexer.cpp

Ast.o : $(USER_DIR)/Ast.cpp $(USER_DIR)/Ast.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Ast.cpp

Interpreter.o : $(USER_DIR)/Interpreter.cpp $(USER_DIR)/Interpreter.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Interpreter.cpp

GrammarTest : GrammarTest.o Parser.o Lexer.o Ast.o Interpreter.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "Interpreter.h"

TEST(GrammarTest, Integer)
{
    EXPECT_EQ("[[(1)4]]", INTERPRETER.parse("4")->toString());
    EXPECT_EQ("[[(1)52]]", INTERPRETER.parse("52")->toString());
    EXPECT_EQ("[[(1)204]]", INTERPRETER.parse("204")->toString());
    EXPECT_EQ("[[(1)7]]", INTERPRETER.parse("07")->toString());
}

TEST(GrammarTest, Strings)
{
    EXPECT_EQ("[[(')hola]]", INTERPRETER.parse("'hola'")->toString());
    EXPECT_EQ("[[(')1234]]", INTERPRETER.parse("'1234'")->toString());
}

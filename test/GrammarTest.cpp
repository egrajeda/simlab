#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "Interpreter.h"

TEST(GrammarTest, Integer)
{
    Interpreter interpreter;

    EXPECT_EQ("[[(1)4]]", interpreter.parse("4")->toString());
    EXPECT_EQ("[[(1)9]]", interpreter.parse("000009")->toString());
    EXPECT_EQ("[[(1)-2]]", interpreter.parse("-2")->toString());
}

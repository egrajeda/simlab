#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "Interpreter.h"

TEST(GrammarTest, Integer)
{
    EXPECT_EQ("[[(1)4]]", INTERPRETER.parse("4")->toString());
    EXPECT_EQ("[[(1)9]]", INTERPRETER.parse("000009")->toString());
    EXPECT_EQ("[[(1)-2]]", INTERPRETER.parse("-2")->toString());
}

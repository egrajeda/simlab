#include <gtest/gtest.h>

#include "Octave.h"

// Puede no ser recomendado usar variables globales, pero *necesito* que
// Octave solamente se cree una vez, se tarda bastante en crear el proceso.
Octave octave;

TEST(OctaveTest, DefaultConstructor) 
{
    const Octave octave;
}

TEST(OctaveTest, Addition)
{
    EXPECT_EQ("8", octave.send("4+4\n"));
    EXPECT_EQ("12-6i", octave.send("4+3i+8-9i\n"));
}

TEST(OctaveTest, Substraction)
{
    EXPECT_EQ("8", octave.send("10-2\n"));
    EXPECT_EQ("4+3i", octave.send("8+7i-4-4i\n"));
}

TEST(OctaveTest, Multiplication)
{
    EXPECT_EQ("5", octave.send("2.5*2\n"));
    EXPECT_EQ("-16+38i", octave.send("(4+3i)*(2+8i)\n"));
}

TEST(OctaveTest, Division)
{
    EXPECT_EQ("3", octave.send("6/2\n"));
    EXPECT_EQ("-3+2i", octave.send("(-6+4i)/2\n"));
}

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>

template <typename Iterator>
class Grammar : boost::spirit::qi::grammar<Iterator>
{
  public:
    // Default constructor
    Grammar();    
};

#endif

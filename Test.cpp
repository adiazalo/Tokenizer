/*
 * Test.cpp
 *
 *      Author: wcs
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Course Project Part 1
#include <boost/test/unit_test.hpp>

#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> tokenizeCodeStrip(istream& code);

BOOST_AUTO_TEST_CASE( test1 )
{
	istringstream code("sum = a + 10 ;");
	vector<string> tokenList= {"sum","=","a","+","10",";"};
	BOOST_CHECK(tokenizeCodeStrip(code) == tokenList);
}

BOOST_AUTO_TEST_CASE( test1b )
{
	istringstream code("sum=a+10;");
	vector<string> tokenList= {"sum","=","a","+","10",";"};
	BOOST_CHECK(tokenizeCodeStrip(code) == tokenList);
}

BOOST_AUTO_TEST_CASE( test2 )
{
	istringstream code("char* str = \"string test.\";");
	vector<string> tokenList= {"char", "*","str","=","\"string test.\"",";"};
	BOOST_CHECK(tokenizeCodeStrip(code) == tokenList);
}

// below was the original testcase 3, but it had a problem.
// once you deal with the escape characters, the end of the string ends up
// being the following characters delimited by '<' and '>'
//            < str="\""+"'";>
// If I "split apart" the two embedded strings, you get   < str=  "\"  "+" '";>
// but the '" part at the end is a syntax error, and we said that we wouldn't
// give you things to parse that had syntax errors.
/*
BOOST_AUTO_TEST_CASE( test3 )
{
	istringstream code("#define MYDEFINE \r\n str=\"\\\"\"+\"'\";");
	vector<string> tokenList= {"str","=","\"\\\"\"","+","\"'\"",";"}; -- wrong
	BOOST_CHECK(tokenizeCodeStrip(code) == tokenList);
}
*/

// below are two improved test cases.  I worked out the desiredTokenList by hand.  I hope
// I did it correctly.  Let me know if you see a problem.  Craig
BOOST_AUTO_TEST_CASE( test3a )
{
//	istringstream code("#define MYDEFINE \r\n str   =    \"  \\  \"  \"  +  \"  \"  \"   ; ");
//	vector<string> desiredTokenList= {       "str","=", "\"  \\  \"  \"  +  \"  \"  \"",";"};
    istringstream code("#define MYDEFINE \r\n str    =    \"  \\  \"     \"  +  \"     \"  \"    ; ");
    vector<string> desiredTokenList= {       "str", "=", "\"  \\  \"",  "\"  +  \"",  "\"  \"", ";"};
//	BOOST_CHECK_EQUAL(tokenizeCodeStrip(code), tokenList);
	auto vectorToTest = tokenizeCodeStrip(code);
	BOOST_CHECK(vectorToTest == desiredTokenList);
}
BOOST_AUTO_TEST_CASE( test3b )
{
	istringstream code("#define MYDEFINE \r\n str    =    \"\\\"    \"+\"    \"\"    ; ");
	vector<string> desiredTokenList= {       "str", "=", "\"\\\"", "\"+\"", "\"\"", ";"};
//	BOOST_CHECK_EQUAL(tokenizeCodeStrip(code), tokenList);
	auto vectorToTest = tokenizeCodeStrip(code);
	BOOST_CHECK(vectorToTest == desiredTokenList);
}

BOOST_AUTO_TEST_CASE( test4 )
{
	istringstream code("i+++j;");
	vector<string> tokenList= {"i","++","+","j",";"};
	BOOST_CHECK(tokenizeCodeStrip(code) == tokenList);
}

BOOST_AUTO_TEST_CASE( test5 )
{
	istringstream code("if (_sum!=a+ 10) { return 0;}");
	vector<string> tokenList= {"if","(","_sum","!=","a","+","10",")","{","return","0",";","}"};
	BOOST_CHECK(tokenizeCodeStrip(code) == tokenList);
}




// by JJeong

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"
#include <string>
#include <vector>

using namespace std;

// There should be at least one test per FindPalindrome method
//Given test on basic code.
TEST_CASE("Test FindPalindrome add a non-allowable word", "[FindPalindrome]")
{
	INFO("Hint: add a single non-allowable word");
	FindPalindrome b;
	REQUIRE(!b.add("kayak1"));
	REQUIRE(!b.add("ka yak"));
	b.clear();
}

//Testing add(string) w/ allowable word and recursive function.
TEST_CASE("Test FindPalindrome add an allowable word", "[FindPalindrome]")
{
	FindPalindrome b;
	REQUIRE(b.add("kayak"));
	REQUIRE(b.add("car"));
	REQUIRE(!b.add("KAYAK"));
	REQUIRE(b.number() == 0); //KAYAK is not unique and kayakcar forms no palindrome. Thus, number() = 0.
	b.clear();
}

//Testing clear().
TEST_CASE("Test FindPalindrome clear function", "[FindPalindrome]")
{
	FindPalindrome b;
	REQUIRE(b.add("kayak"));
	b.clear();
	REQUIRE(b.add("kayak")); //This should be false if clear() is implemented incorrectly.
	REQUIRE(b.number() == 1);
	REQUIRE(!b.add("!KD"));
	b.clear();
	REQUIRE(b.add("AaaaaAaaa"));
	REQUIRE(b.add("aaaa"));
	REQUIRE(b.add("aaaaaAAAaaAAAaaAAAaaAAAaaaa"));
	REQUIRE(b.number() == 6); //3 factorial, thus 6 combinations.
	b.clear();
}

//Testing add(vector) w/ allowable and non-allowable vector.
TEST_CASE("Testing FindPalindrome add an allowable/non-allowable vector string", "[FindPalindrome]")
{
	FindPalindrome b;
	vector<string> test = { "madam", "i", "madam"};
	REQUIRE(b.add(test));
	REQUIRE(b.number() == 1); //Two possible palindromes "wasitacatisaw" and "sawitacatiwas"
	vector<string> test2 = { "111", "xxx", "!@#" }; //Invalid input.
	REQUIRE(!b.add(test2));
	b.clear();
}

//Testing add(vector) w/ allowable and non-allowable vector.
TEST_CASE("Testing cutTest1 and cutTest2", "[FindPalindrome]")
{
	FindPalindrome b;
	vector <string> testthis = { "was", "it", "a", "cat", "i", "saw" };
	vector <string> testthis2 = { "was", "it", "a", "cat", "i", "saw" };
	vector <string> testthis3 = { "" };
	REQUIRE(b.cutTest1(testthis));
	b.clear();
	REQUIRE(b.cutTest2(testthis2, testthis3));
	b.clear();
	vector <string> testthis4 = { "!!!!@@@@" };
	vector <string> testthis5 = { "" };
	REQUIRE(!b.cutTest2(testthis4, testthis5));
	b.clear();
}

//Testing toVector function.
TEST_CASE("Testing toVector", "[FindPalindrome]")
{
	FindPalindrome b;
	REQUIRE(b.add("mY"));
	REQUIRE(b.add("gym"));
	vector<vector<string>> testthisNOW = { {"mY","gym"} };
	REQUIRE(b.toVector() == testthisNOW);
}
// by JJeong

#include <string>
#include <vector>
#include <iostream>
#include <locale> 
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	locale loc;
	for (int i = 0; i<value.size(); i++) {
		value[i] = tolower(value[i], loc);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

void FindPalindrome::recursiveFindPalindromes(vector<string>
	candidateStringVector, vector<string> currentStringVector)
{
	if (cutTest1(currentStringVector)) //Compiler won't even enter the function if currentStringVector does not pass cutTest1.
	{
		string candidateString = ""; //Create temp string to test if it is a palindrome
		if (currentStringVector.empty() == true) //Base case is where the currentStringVector is empty.
		{
			for (unsigned int i = 0; i < candidateStringVector.size(); i++) //Now we add the vector strings into one temp string.
			{
				candidateString += candidateStringVector[i];
			}
			if (isPalindrome(candidateString)) //Check palindrome. If it is, +1 for # of palindromes and add candidateStringVector to our vector of vectors.
			{
				m_countPalindromeSentences++;
				m_validPalindromes.push_back(candidateStringVector);
			}
			return;
		}
		else
		{
			int length = currentStringVector.size(); //Calculate length of currentStringVector BEFORE for loop
			for (int i = 0; i < length; i++)
			{
				{
					std::string tempWord = currentStringVector[i];
					vector<string> tempVector1 = candidateStringVector; //Use a buffer vector to keep length consistent
					tempVector1.push_back(tempWord); //Add word from currentStringVector starting at index 0
					vector<string> tempVector2 = currentStringVector;
					tempVector2.erase(tempVector2.begin() + i);
					if (cutTest2(candidateStringVector, currentStringVector))
						recursiveFindPalindromes(tempVector1, tempVector2); //Recursively call function. Once currentStringVector is empty, the for loop starts again at index 1 and so on
				}
			}
			return;
		}
	}
}


bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();

	for (int i = 0; i<stringLength / 2; i++)
	{
		if (currentString[i] != currentString[stringLength - i - 1])
		{
			return false;
		}
	}

	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	//Initilizes private vectors and int count.
	m_currentStringVector = {};
	m_candidateStringVector = {};
	m_countPalindromeSentences = 0;
}

FindPalindrome::~FindPalindrome()
{
	m_currentStringVector.clear();
	m_candidateStringVector.clear();
}

int FindPalindrome::number() const
{
	// Returns number of valid palindromes/palindrome sentences.
	return m_countPalindromeSentences;
}

void FindPalindrome::clear()
{
	//Clearing all of my private vectors and int count.
	m_currentStringVector.clear();
	m_candidateStringVector.clear();
	m_validPalindromes.clear();

	m_countPalindromeSentences = 0;
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	//First convert the stringVector into a string data type.
	vector<string> testVector = stringVector;
	string testString = "";
	int v_length = testVector.size();
	for (int i = 0; i < v_length; i++)
		testString += testVector[i];

	//Convert to lower case before testing.
	convertToLowerCase(testString);

	bool numOdd_success = 1;
	bool numOdd_fail = 0;

	//If length is 1, return true.
	if (testString.length() == 1)
		return numOdd_success;

	//Checking if string contains only 1 character.
	bool same_char = testString.empty() || testString.find_first_not_of(testString[0]) == std::string::npos;

	//Return true if same_char is true.
	if (same_char)
		return numOdd_success;

	if (isPalindrome(testString))
	{
		//Compare every letter to string and store how many times each letter has been detected in an array.
		char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		int letters_count[26] = {};
		int s_length = testString.length();

		for (int i = 0; i < 26; i++)
		{
			letters[i];
			letters_count[i];
			for (int j = 0; j < s_length; j++)
				if (letters[i] == testString[j])
					letters_count[i] += 1;
		}

		//Checking if only one character appeared odd number of times.
		int count_odd = 0;
		for (int i = 0; i < 26; i++)
			if ((letters_count[i] > 1 && (letters_count[i] % 2 != 0)) || (letters_count[i] == 1))
			{
				count_odd++;
			}

		if (count_odd > 1) //If more than one character appeared odd number of times return true.
			return numOdd_fail;
		else
			return numOdd_success;
	}
	else
		numOdd_fail;
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1, const vector<string> & stringVector2)
{
	bool matching_success = 1;
	bool matching_fail = 0;

	string s_combined = "";

	//Combine the the two vectors into one string.
	int v1_length = stringVector1.size();
	int v2_length = stringVector2.size();

	for (int i = 0; i < v1_length; i++)
		s_combined += stringVector1[i];

	for (int i = 0; i < v2_length; i++)
		s_combined += stringVector2[i];

	convertToLowerCase(s_combined); //Convert to lower case before testing.

	if (s_combined.length() == 1) //Case where length is 1, which is technically palindrome.
		return matching_success;

	bool only_one_char = s_combined.empty() || s_combined.find_first_not_of(s_combined[0]) == std::string::npos; //Bool value to check if the string contains only one letter.

	if (only_one_char) //Return true if the string contains only 1 kind of character.
		return matching_success;

	if (isPalindrome(s_combined)) //Checking if the string is a palindrome to save time.
	{
		int s_length = s_combined.length();
		int bigindex = (s_length / 2) + (s_length % 2);
		int smallindex = bigindex + 1;

		//Splintting the string into two substrings.
		string s_big = s_combined.substr(0, bigindex);
		string s_small = s_combined.substr(smallindex - 1, s_length);

		// this was written in 2016 ...
		// a better way is to implement the ASCII code... 09/2019
		char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		int count_big[26] = {};
		int count_small[26] = {};

		//Checking if it only contains alphabets.
		int letter_count = 0;
		for (int i = 0; i < s_length; i++)
		{
			s_combined[i];
			for (int j = 0; j < 26; j++)
				if (letters[j] == s_combined[i])
					letter_count++;
		}

		//If the letter count equaled the length of the string,
		//the whole string contains only alphabetical characters.
		if (letter_count == s_length)
		{
			//Counting how many and what letters are included for each sub string.
			for (int i = 0; i < 26; i++)
			{
				letters[i];
				for (int j = 0; j < bigindex; j++)
					if (letters[i] == s_big[j])
						count_big[i]++;
			}

			for (int i = 0; i < 26; i++)
			{
				letters[i];
				for (int j = 0; j < s_small.size(); j++)
					if (letters[i] == s_small[j])
						count_small[i]++;
			}

			//Counting how many times the big substring includes the letters in the small substring.
			int count_include = 0;
			for (int i = 0; i < 26; i++)
				if ((count_big[i] >= count_small[i]) && (count_big[i] != 0))
				{
					int temp = count_big[i];
					count_include += count_big[i];
				}

			//If the counting is bigger or equal to the smaller substring length, this means the bigger substring includes all characters of the smaller string.
			if (count_include >= s_small.length())
				return matching_success;
			else
				return matching_fail;
		}
		else
			return matching_fail;
	}
	else return matching_fail;
}


/** Adds a new string to this FindPalindrome instance and computes the
number of palindrome sentences possible. Note that the new string must
be unique per the definition in the project description.
@post  If successful, the string has been added to the FindPalindrome
and instance, and the sentence palindromes in the instance
have been recomputed.
@param value  The string to add to the instance of FindPalindrome.
@return  True if addition was successful, or false if not. */
bool FindPalindrome::add(const string & value) //Check works.
{
	m_countPalindromeSentences = 0;

	bool addingString_success = 1;
	bool addingString_failed = 0;

	vector<string> testVectorString = m_currentStringVector; //Store m_currentStringVector in a temp vector to test.
	int v_length = testVectorString.size(); //Length of vector.

	string addingString = value; //Store string to temp string to test (so we preserve case of letters).
	int s_length = addingString.length();
	convertToLowerCase(addingString);

	//Checking if the added string or "value" is unique.
	//Lets check if the two strings are the same.
	int unique_count = 0; //This count will be used to determine if the adding string is unique or not.
	for (int i = 0; i < v_length; i++) //Test every string in vector.
	{
		convertToLowerCase(testVectorString[i]); //Convert each string for every loop to lower case to compare.
		string currentString = "";
		currentString = testVectorString[i];
		int cs_length = currentString.length();
		if (cs_length == s_length != 0) //If the length of both strings are the same then we test each character.
		{
			for (int k = 0; k < s_length; k++)
				if (currentString[k] == addingString[k]) //Everytime they have the same character unique_count adds 1.
					unique_count++;
		}
	}

	//If unique_count is exactly equal to the length of the string, this means they all had the same characters.
	if (unique_count == s_length)
		return addingString_failed; //Not unique, thus return false.

									//Checking if the added string contains only letters.
	char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	int letter_count = 0;

	for (int i = 0; i < s_length; i++)
	{
		addingString[i];
		for (int j = 0; j < 26; j++)
			if (letters[j] == addingString[i])
				letter_count++;
	}

	//If the letter count equaled the length of the string,
	//the whole string contains only alphabetical characters.
	if (letter_count == s_length)
	{
		m_currentStringVector.push_back(value);
		recursiveFindPalindromes(m_candidateStringVector, m_currentStringVector);
		return addingString_success;
	}
	else
		return addingString_failed;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	m_countPalindromeSentences = 0; //Set number of palindromes to 0 since we are adding new sets of strings.

	bool addingVectorString_success = 1;
	bool addingVectorString_failed = 0;

		vector<string> tempVectorString = m_currentStringVector; //To preserve case, copy the current vector.
		int cv_length = m_currentStringVector.size();

		vector<string> addingVector = stringVector; //Same here, to preserve case, copy the adding vector.
		int v_length = addingVector.size();

		//Checking if the adding vector string is unique or not.
		for (int i = 0; i < cv_length; i++)
		{
			convertToLowerCase(tempVectorString[i]); //Testing each vector string index after converting them to lower case.
			for (int j = 0; j < v_length; j++)
			{
				convertToLowerCase(addingVector[j]);
				if (tempVectorString[i] == addingVector[j]) //Directly comparing two vectors that are lower case.
					return addingVectorString_failed;
			}
		}

		//Checking if the adding vector string contains only letters or not.
		char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		int letter_count = 0;

		string tempString = "";

		for (int i = 0; i < v_length; i++) //Convert every vector string to lower case and add them to one temp string.
		{
			convertToLowerCase(addingVector[i]);
			tempString += addingVector[i];
		}

		int s_length = tempString.length();
		for (int i = 0; i < s_length; i++) //Count how many letters are inside this set of vector string.
		{
			tempString[i];
			for (int j = 0; j < 26; j++)
				if (letters[j] == tempString[i])
					letter_count++;
		}

		if (letter_count == s_length) //If the count equals the length of the string. Then we can conclude the vector string only contains letters.
		{
			for (int i = 0; i < v_length; i++)
			{
				m_currentStringVector.push_back(stringVector[i]);
			}
			recursiveFindPalindromes(m_candidateStringVector, m_currentStringVector);
			return addingVectorString_success;
		}
		else
			return addingVectorString_failed;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	// Returning the vector of vectors for strings that stored the valid palindromes that went through the recursive function.
	return m_validPalindromes;
}
#define CATCH_CONFIG_RUNNER
#include "Catch2.hpp"

/************************************************************/
// System includes

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Main.cpp"
/************************************************************/
// Local includes

#include "SearchTree.hpp"

/************************************************************/
// Using declarations

using std::abs;
using std::advance;
using std::cerr;
using std::cout;
using std::equal;
using std::fixed;
using std::mt19937;
using std::ostringstream;
using std::pair;
using std::remove;
using std::set;
using std::setprecision;
using std::string;
using std::to_string;
using std::vector;

/************************************************************/
// Function prototypes

template<typename T>
void
REQUIRE_TREE(const SearchTree<T>& t, string treeString);

template<typename T>
void
REQUIRE_TREE(const SearchTree<T>& t, string treeString, int depth);

template<typename T>
void
REQUIRE_HEAD(const SearchTree<T>& tree, T left, T right, T parent);

template<typename T>
void
REQUIRE_HEAD_NULL(const SearchTree<T>& tree);

template<typename T>
void
REQUIRE_LEVEL_ORDER(const SearchTree<T>& tree, string answer);

template<typename T>
void
tree_insert(SearchTree<T>& tree, const vector<T>& values);

template<typename T>
void
tree_erase(SearchTree<T>& tree, const vector<T>& values);

template<typename T>
void
REQUIRE_ALL_EQUAL(const vector<T>& values);

void
CHECK_AND_WARN(bool condition, string message);

ostringstream
CHECK_AND_WARN(bool condition, string message, ostringstream stream);

/************************************************************/
// Global variables

// Messages from failed tests to be outputted at end.
vector<string> FAILED_TESTS;
// Total points lost from all tests.
double LOST_SCORE;
// Total points scored. Separately calculated as checksum.
double GAINED_SCORE;
// Total point value of all tests that actually ran.
double TESTED_SCORE;
// Total points that these tests are worth.
double POINTS;

/************************************************************/
// Catch listeners

struct ScoringListener : Catch::TestEventListenerBase
{
	using TestEventListenerBase::TestEventListenerBase;

	virtual void
		sectionEnded(Catch::SectionStats const& sectionStats) override
	{
		string point_value_string = sectionStats.sectionInfo.description;

		if (point_value_string.front() == '['
			&& point_value_string.back() == ']')
		{
			double point_value_num;
			try
			{
				// Point value is multiplied by total total points for the tests as a precentage.
				point_value_num = (stod(point_value_string.substr(1, 4)) / 100.0) * POINTS;

				if (sectionStats.assertions.total() > 0)
				{
					if (!sectionStats.assertions.allPassed())
					{
						ostringstream stream;
						LOST_SCORE += point_value_num;
						stream << "- " << fixed << setprecision(2)
							<< point_value_num << " points:   "
							<< sectionStats.sectionInfo.name;
						FAILED_TESTS.push_back(stream.str());
					}
					else
					{
						GAINED_SCORE += point_value_num;
					}

					TESTED_SCORE += point_value_num;
				}
			}
			catch (std::invalid_argument& e)
			{
				cerr << e.what();
				GAINED_SCORE = std::numeric_limits<double>::max();
			}
		}
	}
};

CATCH_REGISTER_LISTENER(ScoringListener)

/************************************************************/

int
main(int argc, char* argv[])
{
	// Set this to total point value of these tests.
	POINTS = 90;
	TESTED_SCORE = GAINED_SCORE = LOST_SCORE = 0.0;

	int result = Catch::Session().run(argc, argv);

	cout << fixed << setprecision(2);

	// Print all failed test error messages.
	for (string str : FAILED_TESTS)
	{
		cout << str << "\n";
	}

	double FINAL_SCORE = TESTED_SCORE - LOST_SCORE;

	// Don't print with pretty colors if running on Windows.
#ifdef _WIN32

	cout << "\nSCORE: " << FINAL_SCORE << " / " << POINTS << "   >>>   "
		<< (FINAL_SCORE / POINTS) * 100.0
		<< " %\n\nYour output could have pretty colors if "
		<< "you weren't on Windows.\n\n";

	// Check that calculated score hasn't been compromised.
	if (abs((POINTS - LOST_SCORE) - GAINED_SCORE) > 0.1)
	{
		cout << "Not all tests were run or an error occurred.\n\n";
	}

#else

// Bold
	cout << "\033[1m";
	cout << "\nSCORE: " << FINAL_SCORE << " / " << POINTS << "   >>>   ";
	if (FINAL_SCORE >= 80.0)
	{
		// Green
		cout << "\033[32m";
	}
	else if (FINAL_SCORE >= 60)
	{
		// Yellow
		cout << "\033[33m";
	}
	else
	{
		// Red
		cout << "\033[31m";
	}

	cout << (FINAL_SCORE / POINTS) * 100.0 << " %\n\n";
	// Reset
	cout << "\033[0m";

	// Check that calculated score hasn't been comprimised.
	if (abs((POINTS - LOST_SCORE) - GAINED_SCORE) > 0.1)
	{
		// Red
		cout << "\033[31m";
		cout << "Not all tests were run or an error occurred.\n\n";
		// Reset
		cout << "\033[0m";
	}

#endif

	return result;
}

/************************************************************/
// Tests

// Not currently part of assignment
TEST_CASE("Create a Class", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	holder->CreateNewClass("Car")

	SECTION("default constructor - tree", "0")
	{
		REQUIRE_TREE(tree, "[ ]", -1);
	}

	// Dependencies: size
	SECTION("default constructor - size", "0")
	{
		REQUIRE(tree.size() == 0);
	}

	// Dependencies: end
	SECTION("default constructor - head", "0")
	{
		REQUIRE_HEAD_NULL(tree);
	}
}

/*----------------------------------------------------------*/

// Dependencies: insert
TEST_CASE("copy constructor", "7")
{
	SearchTree<int> tree_a;

	tree_insert(tree_a, { 1, 2, 3, 4 });

	SearchTree<int> tree_b(tree_a);

	SECTION("copy constructor - state of tree after copy construct", "[3.00]")
	{
		REQUIRE_TREE(tree_b, "[ 1 2 3 4 ]", 3);
	}

	// Dependencies: size
	SECTION("copy constructor - size of tree after copy construct", "[0.20]")
	{
		REQUIRE(tree_b.size() == 4);
	}

	// Dependencies: iterator decrement, end
	SECTION("copy constructor - head links after copy construct", "[0.80]")
	{
		REQUIRE_HEAD(tree_b, 1, 4, 1);
	}

	// Dependencies: clear
	SECTION("copy constructor - separate from original", "[3.00]")
	{
		tree_b.clear();
		tree_b.insert(5);

		ostringstream stream_a, stream_b;

		tree_a.printInOrder(stream_a);
		tree_b.printInOrder(stream_b);

		REQUIRE(stream_a.str() != stream_b.str());
	}
}

/*----------------------------------------------------------*/

TEST_CASE("empty", "1")
{
	SearchTree<int> tree;

	SECTION("empty - on empty tree", "[0.25]")
	{
		REQUIRE(tree.empty());
	}

	// Dependencies: insert
	SECTION("empty - on non-empty tree", "[0.75]")
	{
		tree_insert(tree, { 4, 2, 7, 6 });

		REQUIRE_FALSE(tree.empty());
	}
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/

void
CHECK_AND_WARN(bool condition, string message)
{
	CHECK(condition);
	if (!condition)
	{
		cout << message << "\n";
	}
}

/*----------------------------------------------------------*/

ostringstream
CHECK_AND_WARN(bool condition, string message, ostringstream stream)
{
	CHECK(condition);
	if (!condition)
	{
		stream << message << "\n";
	}

	return stream;
}

/*----------------------------------------------------------*/

/************************************************************/

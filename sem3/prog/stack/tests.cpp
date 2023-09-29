#include "googletest/googletest/include/gtest/gtest.h"
#include "stack.cpp"

using namespace std;

TEST(TestGroupName, Subtest_1) {
	cout << "STACK INT ";
	int b = 1;
	Stack<int> a;
	a.push( 1 );
	ASSERT_EQ( a.pop(), b );
}

TEST(TestGroupName, Subtest_2) {
	cout << "STACK DOUBLE ";
	double b = 3.14;
	Stack<double> a;
	a.push( 3.14 );
	ASSERT_EQ( a.pop(), b );
}

struct AB { 
	int a;
	double b;
	string c;
};

TEST(TestGroupName, Subtest_3) {
	cout << "STACK STRUCT";
	AB b { 1, 3.14, "HELLO" };
	Stack<AB> a;
	a.push( { 1, 3.14, "HELLO" } );
	AB c = a.pop();

	ASSERT_EQ( c.a, b.a );
	ASSERT_EQ( c.b, b.b );
	ASSERT_EQ( c.c, b.c );
}

TEST(TestGroupName, Subtest_4) {
	cout << "STACK STRING";
	string b = "HELLO";
	Stack<string> a;
	a.push( "HELLO" );

	ASSERT_EQ( a.pop( ), b );
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}

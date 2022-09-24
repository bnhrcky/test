#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <list>
using namespace std;
#include "../../includes/rational/rational.h"

bool basic_test_rational(bool debug = false){
  Rational r1(4, 6);
  Rational r2(3, 8);
  Rational r3;
  cout << r1 << " + " << r2 << " = " << r1 + r2 << endl;
  cout << r1 << " - " << r2 << " = " << r1 - r2 << endl;
  cout << r1 << " * " << r2 << " = " << r1 * r2 << endl;
  cout << r1 << " / " << r2 << " = " << r1 / r2 << endl;
  r3.set(r1.get_denom(), r2.get_num());
  cout << "r3: " << r3 << endl;
  r3.set_denom(0);
  r3.set_num(77);
  cout << "r3 is now: " << r3 << endl;

  cout << "r3 error state: " << r3.error() << endl;
  cout << "r3 error descr: " << r3.error_description() << endl;
  cout << "r3.reset(): " << endl;
  r3.reset();
  cout << "r3 is now: " << r3 << endl;
  return true;
}
//----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 
//Lord help me! 
bool debug = false;
//----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

TEST(TEST_BASIC_TEST, BasicTest) {
  bool success = basic_test_rational(debug);
  EXPECT_EQ(success, true);
}


int main(int argc, char **argv) {
  if (argc>1){
    debug = argv[1][0]=='t';
  }
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

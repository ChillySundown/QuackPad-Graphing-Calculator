#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/queue/MyQueue.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/rpn/rpn.h"
#include "../../includes/token/token.h"
#include "../../includes/token/function.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/rightparen.h"
#include "../../includes/token/leftparen.h"

using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool test_complex_trig_functions(bool debug = false) {
  if(debug) {
    cout << "testB:: testing_trig_functions() entering test_trig_functions" << endl;
  }

  ShuntingYard s;
  RPN r;
  Queue<Token*> t;

  t.push(new Function("sin"));
  t.push(new Function("x"));

  Queue<Token*> post = s.postfix(t);
  cout << "Post: " << post << endl;
  r.set_input(post);
  double result = r.calculate(3);
  cout << result << endl;
  if(result == sin(3)) {
    return true;
  }

  t = Queue<Token*>();
  t.push(new Function("sin"));
  t.push(new LeftParen());
  t.push(new Integer(1));
  t.push(new Operator("-"));
  t.push(new Function("tan"));
  t.push(new LeftParen());
  t.push(new Function("x"));
  t.push(new RightParen());
  t.push(new RightParen());

  r.set_input(s.postfix(t));
  double result2 = r.calculate(2.2);
  if(result2 == sin(1-tan(2.2))) {
    return true;
  }
  return false;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}

TEST(TEST_RPM_SHUNTING_YARD, TestComplexTrigFunctions) {
  EXPECT_EQ(1, test_complex_trig_functions(false));
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}


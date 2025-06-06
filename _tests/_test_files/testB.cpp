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
#include "../../includes/graph_info.h"

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

  t.push(new Function("cos"));
  t.push(new Function("x"));

  Queue<Token*> post = s.postfix(t);
  r.set_input(post);
  double result = r.calculate(3);
  if(result != cos(3)) {
    return false;
  }

  Queue<Token*> t2;
  t2.push(new Function("sin"));
  t2.push(new LeftParen());
  t2.push(new Integer(1));
  t2.push(new Operator("-"));
  t2.push(new Function("tan"));
  t2.push(new LeftParen());
  t2.push(new Function("x"));
  t2.push(new RightParen());
  t2.push(new RightParen());

  cout << "Complex Trig postfix:" << endl;
  Queue<Token*> post2 = s.postfix(t2);
  r.set_input(post2);
  cout << post2 << endl;
  
  double result2 = r.calculate(2.2);
  cout << result2 << endl;
  if(result2 != sin(1-tan(2.2))) {
    return false;
  }
  return true;
}

bool test_str_spacer(bool debug = false) {
  if(!bothNumbers('6', '8') || !bothNumbers('2', '0') || bothNumbers('(', '1')) {
    return false;
  }
  if(debug) {
    cout << "testB:: test_str_space - entering test_str_spacer" << endl;
  }

  string s1 = "68.62*sin(41.72*x^2)";
  str_spacer(s1);
  cout << s1 << endl;

  if(s1 != "68.62 * sin ( 41.72 * x ^ 2 )") {
    return false;
  }

  string s2 = "x^2";
  str_spacer(s2);
  cout << s2 << endl;
  if(s2 != "x ^ 2") {
    return false;
  }

  string s3 = "(1-tan(5*cos(2*x)))";
  str_spacer(s3);
  cout << s3 << endl;
  if(s3 != "( 1 - tan ( 5 * cos ( 2 * x ) ) )") { 
    return false;
  }
  return true;
}

bool test_str_to_equation(bool debug = false) {
  if(debug) {
    cout << "testB:: test_str_to_equation - entering test_str_to_equation" << endl;
  }
  GraphInfo g;
  g.setEquation("x^2");
  g.setEquation("sin(x)");
  g.setEquation("1-tan(2*x+5/8*cos(6*x))");

  return true;
}

bool test_shunting_yard_rpn(bool debug = false) {
  if(debug) {
    cout << "testB:: test_shunting_yard_rpn - entering test_shunting_yard_rpn" << endl;
  }

  ShuntingYard post;
  Queue<Token*> eq1;

  RPN solver;

  eq1.push(new Integer(1));
  eq1.push(new Operator("-"));
  eq1.push(new Operator("-"));
  eq1.push(new Integer(3));

  Queue<Token*> eq1_post = post.postfix(eq1);
  cout << eq1_post << endl;

 double result1 = solver.calculate(0);
 if(result1 != 4.0) {
    return false;
 }
  return true;
}
 
TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}

TEST(TEST_RPM_SHUNTING_YARD, TestComplexTrigFunctions) {
  EXPECT_EQ(1, test_complex_trig_functions(false));
}

TEST(TEST_GRAPH_INFO, TestStrSpacer) {
  EXPECT_EQ(1, test_str_spacer(false));
}

TEST(TEST_GRAPH_INFO, TestStrToEquation) {
  EXPECT_EQ(1, test_str_to_equation(false));
}

TEST(TEST_RPN_SHUNTING_YARD, TestRpmShuntingYard) {
  EXPECT_EQ(1, test_shunting_yard_rpn(false));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}


// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(Collatz, read) {
    std::istringstream r("1 10\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);
}

//My unit tests
/*TEST(Collatz, read_one_item) {
    std::istringstream r("110 \n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(110, p.first);
    ASSERT_EQ(0, p.second);
}*/

TEST(Collatz, read_no_items) {
    std::istringstream r(""); 
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(0, p.first);
    ASSERT_EQ(0, p.second);   
}

TEST(Collatz, read_newline) {
    std::istringstream r("\n"); 
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(0, p.first);
    ASSERT_EQ(0, p.second);   
}

TEST(Collatz, read_extra_items) {
    std::istringstream r("1 10 20"); 
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(1, p.first);
    ASSERT_EQ(10, p.second);   
}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

//My unit tests
TEST(Collatz, eval_matching_output) {
    const int v = collatz_eval(1, 100);
    const int u = collatz_eval(51, 100);
    ASSERT_EQ(v, u);
}

TEST(Collatz, eval_matching_output2) {
    const int v = collatz_eval(1, 10);
    const int u = collatz_eval(6, 10);
    ASSERT_EQ(20, v);
    ASSERT_EQ(20, u);
    ASSERT_EQ(v, u);
}

TEST(Collatz, eval_reverse_input) {
    const int v = collatz_eval(10, 1);
    ASSERT_EQ(20, v);
}

TEST(Collatz, eval_ones) {
    const int v = collatz_eval(1, 1);
    ASSERT_EQ(1, v);
}

TEST(Collatz, eval_duplicate_input) {
    const int v = collatz_eval(10, 10);
    ASSERT_EQ(7, v); //7 I think?
}

// -----
// cycle_length
// -----

//Tests for my added method
TEST(Collatz, cycle_length_1) {
    const int v = collatz_cycle_length(1);
    ASSERT_EQ(1, v);
}

TEST(Collatz, cycle_length_2) {
    const int v = collatz_cycle_length(5);
    ASSERT_EQ(6, v);
}

TEST(Collatz, cycle_length_3) {
    const int v = collatz_cycle_length(22);
    ASSERT_EQ(16, v);
}

TEST(Collatz, cycle_length_4) {
    const int v = collatz_cycle_length(10);
    ASSERT_EQ(7, v);
}

TEST(Collatz, cycle_length_5) {
    const int v = collatz_cycle_length(11);
    ASSERT_EQ(15, v);
}

TEST(Collatz, cycle_length_6) {
    const int v = collatz_cycle_length(100);
    ASSERT_EQ(26, v);
}

TEST(Collatz, cycle_length_7) {
    const int v = collatz_cycle_length(5000);
    ASSERT_EQ(29, v);
}

TEST(Collatz, cycle_length_8) {
    const int v = collatz_cycle_length(50001);
    ASSERT_EQ(53, v);
}

TEST(Collatz, cycle_length_zero) {
    const int v = collatz_cycle_length(0);
    ASSERT_EQ(0, v);
}

TEST(Collatz, cycle_length_negative) {
    const int v = collatz_cycle_length(-5);
    ASSERT_EQ(0, v);
}


// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());
}

//My unit tests
TEST(Collatz, print_big_parameter) {
    std::ostringstream w;
    collatz_print(w, 1, 2, 500000000);
    ASSERT_EQ("1 2 500000000\n", w.str());
}

TEST(Collatz, print_double_parameter) {
    std::ostringstream w;
    collatz_print(w, 1, 2, 3.0);
    ASSERT_EQ("1 2 3\n", w.str());
}

TEST(Collatz, print_variable_parameter) {
    std::ostringstream w;
    const int k = 100;
    collatz_print(w, 1, 2, k);
    ASSERT_EQ("1 2 100\n", w.str());
}

//Just for creating acceptance test cases in RunCollatz.in
/*TEST(Collatz, collatz_RunCollatz_in_values) {
    std::ostringstream w;
    collatz_RunCollatz_in_values(w);
    ASSERT_EQ("1 2 100\n", w.str());
}*/


// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());
}

//My unit tests
TEST(Collatz, solve_1) {
    std::istringstream r("1 1\n10 20\n201 210\n0 0\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1 1\n10 20 21\n201 210 89\n", w.str());
}

TEST(Collatz, solve_2) {
    std::istringstream r("2 1\n20 10\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("2 1 2\n20 10 21\n", w.str());
}

TEST(Collatz, solve_3) {
    std::istringstream r("10 1\n10 6\n0 10\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("10 1 20\n10 6 20\n0 10 20\n", w.str());
}

// -----
// collatz_overflow_check
// -----

//My personal method
TEST(Collatz, collatz_overflow_check_1) {
    const bool v = collatz_overflow_check(1);
    ASSERT_EQ(true, v);
}

TEST(Collatz, collatz_overflow_check_2) {
    const bool v = collatz_overflow_check(1000000);
    ASSERT_EQ(true, v);
}

TEST(Collatz, collatz_overflow_check_3) {
    const bool v = collatz_overflow_check(999999);
    ASSERT_EQ(true, v);
}

TEST(Collatz, collatz_overflow_check_4) {
    const bool v = collatz_overflow_check(999999999);
    ASSERT_FALSE(v);
}

TEST(Collatz, collatz_overflow_check_5) {
    const bool v = collatz_overflow_check(999999990);
    ASSERT_EQ(true, v);
}

TEST(Collatz, collatz_overflow_check_6) {
    const bool v = collatz_overflow_check(1000000000);
    ASSERT_EQ(true, v);
}

/* To recompile and test TestCollatz.c++ run:

g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread

valgrind TestCollatz        >  TestCollatz.out 2>&1

gcov-4.7 -b Collatz.c++     >> TestCollatz.out

gcov-4.7 -b TestCollatz.c++ >> TestCollatz.out

cat TestCollatz.out
*/


/*
% ls -al /usr/include/gtest/
...
gtest.h
...



% locate libgtest.a
/usr/lib/libgtest.a
...



% locate libpthread.a
...
/usr/lib32/libpthread.a



% locate libgtest_main.a
/usr/lib/libgtest_main.a
...



% g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz        >  TestCollatz.out 2>&1
% gcov-4.7 -b Collatz.c++     >> TestCollatz.out
% gcov-4.7 -b TestCollatz.c++ >> TestCollatz.out



% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
...
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
...



RunCollatz.in
1 10
100 200
201 210
900 1000
40001 40000
980410 983323
703061 588955
624792 772796
308796 52402
601869 248186
832817 795472
315086 287593
762304 897484
638896 226067
117051 51718
333333 33333
600000 6000
1 200000
1 300001
1 900006
900006 900000
900006 900006

RunCollatz.out
1 10 20
100 200 125
201 210 89
900 1000 174
40001 40000 169
980410 983323 427
703061 588955 447
624792 772796 468
308796 52402 443
601869 248186 470
832817 795472 468
315086 287593 389
762304 897484 468
638896 226067 470
117051 51718 354
333333 33333 443
600000 6000 470
1 200000 383
1 300001 443
1 900006 470
900006 900000 189
900006 900006 189
*/




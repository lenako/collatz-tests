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
    ASSERT_EQ(1, p.first);
    ASSERT_EQ(10, p.second);}

TEST(Collatz, readzeros) {
    std::istringstream r("0 0\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(0, p.first);
    ASSERT_EQ(0, p.second);}

TEST(Collatz, readnegative) {
    std::istringstream r("-1 -10\n");
    const std::pair<int,    int> p = collatz_read(r);
    ASSERT_EQ(-1, p.first);
    ASSERT_EQ(-10, p.second);}

TEST(Collatz, readnothing) {
    std::istringstream r("\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(0,p.first);
    ASSERT_EQ(0,p.second);}
// ----
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

TEST(Collatz, eval_backwards_range) {
    const int v = collatz_eval(10, 1);
    ASSERT_EQ(20, v);}

TEST(Collatz, eval_small_range) {
    const int v = collatz_eval(1,1);
    ASSERT_EQ(1, v);}

TEST(Collatz, eval_negative) {
    ASSERT_DEATH({collatz_eval(-1, -10);}, "Assertion");}

TEST(Collatz, eval_one_negative) {
    ASSERT_DEATH({collatz_eval(1, -10);}, "Assertion");}

TEST(Collatz, eval_zero) {
    ASSERT_DEATH({collatz_eval(0, 1);}, "Assertion");}

TEST(Collatz, eval_overflow) {
    ASSERT_DEATH({collatz_eval(2147483646, 2147483647);}, "Assertion");}

TEST(Collatz, eval_not_so_obvious_overflow) {
    ASSERT_DEATH({collatz_eval(2000000000, 2000000001);}, "Assertion");}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

// Although zeros and negatives should never be printed, make sure they would be printed if they occur
TEST(Collatz, print_0) {
    std::ostringstream w;
    collatz_print(w, 0, 0, 0);
    ASSERT_EQ("0 0 0\n", w.str());}

TEST(Collatz, print_negative) {
    std::ostringstream w;
    collatz_print(w, -1, -10, -20);
    ASSERT_EQ("-1 -10 -20\n", w.str());}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

TEST(Collatz, solve_one) {
    std::istringstream r("1 10\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(Collatz, solve_backwards_range) {
    std::istringstream r("10 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("10 1 20\n", w.str());}

TEST(Collatz, solve_nothing) {
    std::istringstream r("\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("", w.str());}

TEST(Collatz, solve_negative) {
    std::istringstream r("-1 -10\n");
    std::ostringstream w;
    ASSERT_DEATH({collatz_solve(r, w);}, "Assertion");}

TEST(Collatz, solve_small_range) {
    std::istringstream r("1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1 1\n", w.str());}

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
*/

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
    ASSERT_EQ(10, p.second);}

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

//Additional tests
TEST(Collatz, eval_5) {
    const int v = collatz_eval(1, 1);
    ASSERT_EQ(1, v);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(10, 1);
    ASSERT_EQ(20, v);}
    
TEST(Collatz, eval_7) {
    const int v = collatz_eval(1, 100);
    ASSERT_EQ(119, v);}

TEST(Collatz, eval_8) {
    const int v = collatz_eval(51, 100);
    ASSERT_EQ(119, v);}

TEST(Collatz, eval_9) {
    const int v = collatz_eval(5, 5);
    ASSERT_EQ(6, v);}

TEST(Collatz, eval_10) {
    const int v = collatz_eval(99, 100);
    ASSERT_EQ(26, v);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

//Additional Tests
TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_EQ("1 1 1\n", w.str());}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 1, 100, 119);
    ASSERT_EQ("1 100 119\n", w.str());}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w, 51, 100, 119);
    ASSERT_EQ("51 100 119\n", w.str());}

TEST(Collatz, print4) {
    std::ostringstream w;
    collatz_print(w, 100, 51, 119);
    ASSERT_EQ("100 51 119\n", w.str());}
// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

//Additional Tests
TEST(Collatz, solve1) {
    std::istringstream r("1 1\n5 5\n10 10\n20 20\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1 1\n5 5 6\n10 10 7\n20 20 8\n", w.str());}
      
TEST(Collatz, solve2) {
    std::istringstream r("15 25\n1 100\n51 100\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("15 25 24\n1 100 119\n51 100 119\n", w.str());}

TEST(Collatz, solve3) {
    std::istringstream r("10 20\n14 20\n15 20\n16 20\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("10 20 21\n14 20 21\n15 20 21\n16 20 21\n", w.str());}

TEST(Collatz, solve4) {
    std::istringstream r("20 10\n20 14\n15 20\n16 20\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("20 10 21\n20 14 21\n15 20 21\n16 20 21\n", w.str());}


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

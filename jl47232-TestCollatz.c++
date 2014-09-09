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
// read: my tests
// ----

TEST(Collatz, read_1) {
    std::istringstream r("1 1\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(1, p.second);}
TEST(Collatz, read_2) {
    std::istringstream r("10 1\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 10, p.first);
    ASSERT_EQ(1, p.second);}
TEST(Collatz, read_3) {
    std::istringstream r("15 25\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 15, p.first);
    ASSERT_EQ(25, p.second);}
TEST(Collatz, read_4) {
    std::istringstream r("99999 99999\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 99999, p.first);
    ASSERT_EQ(99999, p.second);}

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

// ----
// eval: my tests
// ----
TEST(Collatz, eval_5) {
    const int v = collatz_eval(1, 1);
    ASSERT_EQ(1, v);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(31735, 49331);
    ASSERT_EQ(324, v);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(90027, 2362);
    ASSERT_EQ(351, v);}

TEST(Collatz, eval_8) {
    const int v = collatz_eval(86931, 86930);
    ASSERT_EQ(46, v);}


// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

// -----
// print: my tests
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_EQ("1 1 1\n", w.str());}
TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 10, 1, 20);
    ASSERT_EQ("10 1 20\n", w.str());}
TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 86931, 86930, 46);
    ASSERT_EQ("86931 86930 46\n", w.str());}    
TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 99165, 99165, 60);
    ASSERT_EQ("99165 99165 60\n", w.str());}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

// -----
// solve: my tests
// -----
TEST(Collatz, solve_1) {
    std::istringstream r("1 1\n1 1\n1 1\n1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1 1\n1 1 1\n1 1 1\n1 1 1\n", w.str());}
TEST(Collatz, solve_2) {
    std::istringstream r("2 2\n3 3\n4 4\n5 5\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("2 2 2\n3 3 8\n4 4 3\n5 5 6\n", w.str());}
TEST(Collatz, solve_3) {
    std::istringstream r("3815 18965\n438 68254\n91631 43229\n16281 8013\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("3815 18965 279\n438 68254 340\n91631 43229 351\n16281 8013 276\n", w.str());}

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
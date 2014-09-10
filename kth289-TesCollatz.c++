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

// ---------
// put_cache
// ---------

TEST(Collatz, put_0) {
    ASSERT_EQ(put_cache(1000000, 1000), 0);}

TEST(Collatz, put_1) {
    const int v = put_cache(0, 1000);
    ASSERT_EQ(v, 1000);}

TEST(Collatz, put_2) {
    const int v = put_cache(2000000, 1000);
    ASSERT_EQ(v, 0);}

// ---------
// get_cache
// ---------

TEST(Collatz, get_0) {
    put_cache(1,1);
    ASSERT_EQ(get_cache(1), 1);}

TEST(Collatz, get_1) {
    ASSERT_EQ(get_cache(0), 1000);}

TEST(Collatz, get_2) {
    const int v = get_cache(1000000);
    ASSERT_EQ(v, 0);}

// ----
// read
// ----

TEST(Collatz, read) {
    std::istringstream r("1 10\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

TEST(Collatz, read_1) {
    std::istringstream r("\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 0, p.first);
    ASSERT_EQ( 0, p.second);}

TEST(Collatz, read_2) {
    std::istringstream r("1 10\n2 20\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ( 10, p.second);

    const std::pair<int, int> q = collatz_read(r);
    ASSERT_EQ( 2, q.first);
    ASSERT_EQ( 20, q.second);}
    

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

TEST(Collatz, eval_5) {
    const int v = collatz_eval(1, 1);
    ASSERT_EQ(1, v);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(22, 22);
    ASSERT_EQ(16, v);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(100, 101);
    ASSERT_EQ(26, v);}

TEST(Collatz, eval_8) {
    const int v = collatz_eval(2, 1);
    ASSERT_EQ(2, v);}

// ------------
// cycle_length
// ------------

TEST(Collatz, cycle_1) {
    const int v = collatz_cycle_length(1);
    ASSERT_EQ(1, v);}

TEST(Collatz, cycle_2) {
    const int v = collatz_cycle_length(999999);
    ASSERT_EQ(259, v);}

TEST(Collatz, cycle_3) {
    const int v = collatz_cycle_length(5000);
    ASSERT_EQ(29, v);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_EQ("1 1 1\n", w.str());}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 0, 0, 0);
    ASSERT_EQ("0 0 0\n", w.str());}


// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

TEST(Collatz, solve_1) {
    std::istringstream r("1 1\n100 101\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1 1\n100 101 26\n", w.str());}

TEST(Collatz, solve_2) {
    std::istringstream r("481871 482418\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("481871 482418 382\n", w.str());}


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
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

TEST(Collatz, read_1) {
    std::istringstream r("1 10\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

TEST(Collatz, read_2) {
    std::istringstream r("50 200\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 50, p.first);
    ASSERT_EQ(200, p.second);}

TEST(Collatz, read) {
    std::istringstream r("1 999999\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(999999, p.second);}

// -----
// cache
// -----

TEST(Collatz, cache_1) {
    const int v = collatz_cache(2300, 89);
    ASSERT_EQ(89, v);}

TEST(Collatz, cache_2) {
    const int v = collatz_cache(6900, 76);
    ASSERT_EQ(76, v);}

TEST(Collatz, cache_3) {
    const int v = collatz_cache(890300, 467);
    ASSERT_EQ(467, v);}

TEST(Collatz, cache_4) {
    const int v = collatz_cache(999900, 999);
    ASSERT_EQ(999, v);}

// ------
// length
// ------

TEST(Collatz, length_1) {
    const int v = collatz_length(230631);
    ASSERT_EQ(443, v);}

TEST(Collatz, length_2) {
    const int v = collatz_length(999999);
    ASSERT_EQ(259, v);}

TEST(Collatz, length_3) {
    const int v = collatz_length(34675);
    ASSERT_EQ(130, v);}

TEST(Collatz, length_4) {
    const int v = collatz_length(2895);
    ASSERT_EQ(54, v);}

// ----
// loop
// ----

TEST(Collatz, loop_1) {
    const int v = collatz_loop(1, 10);
    ASSERT_EQ(20, v);}

TEST(Collatz, loop_2) {
    const int v = collatz_loop(100, 200);
    ASSERT_EQ(125, v);}

TEST(Collatz, loop_3) {
    const int v = collatz_loop(201, 210);
    ASSERT_EQ(89, v);}

TEST(Collatz, loop_4) {
    const int v = collatz_loop(900, 1000);
    ASSERT_EQ(174, v);}

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

// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 100, 200, 125);
    ASSERT_EQ("100 200 125\n", w.str());}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 201, 210, 89);
    ASSERT_EQ("201 210 89\n", w.str());}

TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 900, 1000, 174);
    ASSERT_EQ("900 1000 174\n", w.str());}

// -----
// solve
// -----

TEST(Collatz, solve_1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

TEST(Collatz, solve_2) {
    std::istringstream r("4 7\n8 16\n4 336\n7 60493\n10 641422\n63 28\n91 60\n64 13927\n41 383427\n173 737\n212 95369\n568 956430\n65783 21531\n22863 65124\n174068 703136\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("4 7 17\n8 16 20\n4 336 144\n7 60493 340\n10 641422 470\n63 28 113\n91 60 116\n64 13927 276\n41 383427 443\n173 737 171\n212 95369 351\n568 956430 476\n65783 21531 340\n22863 65124 340\n174068 703136 470\n", w.str());}

TEST(Collatz, solve_3) {
    std::istringstream r("10 3\n3 59\n10 168\n4 18457\n2 478043\n30 74\n22 920\n85 98538\n99 594325\n316 371\n414 3527\n92 268981\n59957 41874\n6863 99171\n906997 497282\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("10 3 20\n3 59 113\n10 168 122\n4 18457 279\n2 478043 449\n30 74 116\n22 920 179\n85 98538 351\n99 594325 470\n316 371 144\n414 3527 217\n92 268981 443\n59957 41874 340\n6863 99171 351\n906997 497282 470\n", w.str());}

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

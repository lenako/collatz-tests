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
#include <cassert>  // assert

#include "gtest/gtest.h"

#include "Collatz.h"

extern int basic_cache[CACHE_SIZE];

// -----------
// TestCollatz
// -----------

/****************
 *  CACHE TESTS *
 ****************/

// ---------
// cache_put
// ---------
TEST(Collatz, cache_put_1) {
    cache_put(0, 50);
    ASSERT_EQ(50, basic_cache[0]);
}

TEST(Collatz, cache_put_2) {
    cache_put(CACHE_SIZE/2, 100);
    ASSERT_EQ(100, basic_cache[CACHE_SIZE/2]);
}

TEST(Collatz, cache_put_3) {
    assert(CACHE_SIZE > 0);
    cache_put(CACHE_SIZE-1, 3000);
    ASSERT_EQ(3000, basic_cache[CACHE_SIZE-1]);
}

// make sure a segfault isn't triggered if we "put"
// into an array element outside the bounds of the array
TEST(Collatz, cache_put_4) {
    cache_put(CACHE_SIZE+1, 10);
}

// -----------
// cache_check
// -----------
TEST(Collatz, cache_check_1) {
    basic_cache[0] = 50;
    ASSERT_EQ(50, cache_check(0));
}

TEST(Collatz, cache_check_2) {
    basic_cache[CACHE_SIZE/2] = 100;
    ASSERT_EQ(100, cache_check(CACHE_SIZE/2));
}

TEST(Collatz, cache_check_3) {
    assert(CACHE_SIZE > 0);
    basic_cache[CACHE_SIZE-1] = 3000;
    ASSERT_EQ(3000, cache_check(CACHE_SIZE-1));
}

// should be OK to check beyond bounds of cache
TEST(Collatz, cache_check_4) {
    ASSERT_EQ(0, cache_check(CACHE_SIZE+1));
}

/***********************
 * BASIC COLLATZ TESTS *
 ***********************/

// ----
// read
// ----

TEST(Collatz, read_1) {
    std::istringstream r("1 10\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);
}

TEST(Collatz, read_2) {
    std::istringstream r("100000");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(100000, p.first);
    ASSERT_FALSE(r);
}

TEST(Collatz, read_3) {
    std::istringstream r("\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(0, p.first);
    ASSERT_EQ(0, p.second);
}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);
}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);
}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(10000, 10100);
    ASSERT_EQ(224, v);
}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);
}


// case: i > j
TEST(Collatz, eval_5) {
    const int v = collatz_eval(1000, 900);
    ASSERT_EQ(174, v);
}

// ----
// cycle_length
// ----

TEST(Collatz, cycle_length_1) {
    int ans = cycle_length(1);
    ASSERT_EQ(1, ans);
}

TEST(Collatz, cycle_length_2) {
    int ans = cycle_length(9);
    ASSERT_EQ(20, ans);
}

TEST(Collatz, cycle_length_3) {
    int ans = cycle_length(16);
    ASSERT_EQ(5, ans);
}

// test case of cache hit mid-cycle-calculation
TEST(Collatz, cycle_length_4) {
    int a = 9;
    cycle_length(a);

    // this should hit the cache on the second round
    cycle_length(a*2);
}

//
// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());
}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 100, 200, 125);
    ASSERT_EQ("100 200 125\n", w.str());
}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 0, 0, 0);
    ASSERT_EQ("0 0 0\n", w.str());
}

// -----
// solve
// -----

TEST(Collatz, solve_1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());
}

TEST(Collatz, solve_2) {
    std::istringstream r("\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("", w.str());
}

TEST(Collatz, solve_3) {
    std::istringstream r("1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1 1\n", w.str());
}

TEST(Collatz, solve_w_likely_overflow) {
    std::istringstream r("1000000 1500000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1000000 1500000 528\n", w.str());
}

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

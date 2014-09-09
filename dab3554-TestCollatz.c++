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

TEST(Collatz, read_2) {
	std::istringstream r("string val");
	const std::pair<int, int> p = collatz_read(r);
	ASSERT_EQ(0, p.first);
	ASSERT_EQ(0, p.second);
}

TEST(Collatz, read_3) {
    std::istringstream r("");
	const std::pair<int, int> p = collatz_read(r);
	ASSERT_EQ(0, p.first);
	ASSERT_EQ(0, p.second);
}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(55, 56);
    ASSERT_EQ(113, v);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(101, 101);
    ASSERT_EQ(26, v);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(999999, 999168);
    ASSERT_EQ(396, v);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(1, 113382);
    ASSERT_EQ(354, v);}

// ----
// computeNumCycles
// ----

TEST(Collatz, computeNumCycles_1) {
    const int v = computeNumCycles(999999);
    ASSERT_EQ(259, v);
}

TEST(Collatz, computeNumCycles_2) {
    const int v = computeNumCycles(1);
    ASSERT_EQ(1, v);
}

TEST(Collatz, computeNumCycles_3) {
    const int v = computeNumCycles(1001);
    ASSERT_EQ(143, v);
}
 
// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 5000, 6000, 1000);
    ASSERT_EQ("5000 6000 1000\n", w.str());
}
TEST(Collatz, print_3) {
	std::ostringstream w;
    collatz_print(w, 100000, 200000, 10333);
    ASSERT_EQ("100000 200000 10333\n", w.str());
}
// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("999166 997824\n999166 997824\n999166 997824\n999166 997824\n999166 997824\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("999166 997824 396\n999166 997824 396\n999166 997824 396\n999166 997824 396\n999166 997824 396\n", w.str());}

TEST(Collatz, solve_2) {
    std::istringstream r("910272 912166\n912168 917160\n917162 918069\n918072 919450\n1024 128\n612968 620970\n1 10\n7777 3333\n999166 997824\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("910272 912166 383\n912168 917160 401\n917162 918069 352\n918072 919450 339\n1024 128 179\n612968 620970 447\n1 10 20\n7777 3333 262\n999166 997824 396\n", w.str());}

TEST(Collatz, solve_3) {
    std::istringstream r("7777 3333\n999999 999999\n113382 1\nsomething\n201 210");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("7777 3333 262\n999999 999999 259\n113382 1 354\n", w.str());}


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

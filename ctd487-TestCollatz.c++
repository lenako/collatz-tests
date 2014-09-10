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
    ASSERT_EQ(10, p.second);
}

TEST(Collatz, read_2) {
    std::istringstream r("1000000 0\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(1000000, p.first);
    ASSERT_EQ(   0, p.second);
}

TEST(Collatz, read_3) {
    std::istringstream r("-1 -1\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(-1, p.first);
    ASSERT_EQ(-1, p.second);
}

TEST(Collatz, read_4) {
    std::istringstream r("-2147483647 2147483647\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(-2147483647, p.first);
    ASSERT_EQ( 2147483647, p.second);
}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);
}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(1, 113382);
    ASSERT_EQ(354, v);
}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(302356, 306022);
    ASSERT_EQ(340, v);
}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(999168, 1000000);
    ASSERT_EQ(396, v);
}

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
    collatz_print(w, -2147483647, 2147483647, 0x1);
    ASSERT_EQ("-2147483647 2147483647 1\n", w.str());
}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, -1, 1000000, 1000001);
    ASSERT_EQ("-1 1000000 1000001\n", w.str());
}

TEST(Collatz, print_4) {
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
    std::istringstream r("93643 4984\n137833 134380\n1 113382\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("93643 4984 351\n137833 134380 344\n1 113382 354\n", w.str());
}

TEST(Collatz, solve_3) {
    std::istringstream r("957212 957630\n955588 955590\n1000000 999999\n502442 504056\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("957212 957630 352\n955588 955590 78\n1000000 999999 259\n502442 504056 333\n", w.str());
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

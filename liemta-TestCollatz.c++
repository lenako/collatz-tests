// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------------

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestCollatz

To obtain coverage of the test:
    % gcov-4.7 -b Collatz.c++ TestCollatz.c++
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <utility>  // make_pair, pair

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

/*
OWN TESTS
*/
TEST(Collatz, read_2) {
    std::istringstream r("1 5\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(1, p.first);
    ASSERT_EQ(5, p.second);}

TEST(Collatz, read_3) {
    std::istringstream r("1 1\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(1, p.first);
    ASSERT_EQ(1, p.second);}

TEST(Collatz, read_4) {
    std::istringstream r("10 1\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ(10, p.first);
    ASSERT_EQ( 1, p.second);}

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

/*
OWN TESTS
*/

TEST(Collatz, eval_5) {
    const int v = collatz_eval(3, 52);
    ASSERT_EQ(112, v);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(65, 43);
    ASSERT_EQ(113, v);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(82, 43);
    ASSERT_EQ(116, v);}

// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

/*
OWN TESTS
*/

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 3, 52, 112);
    ASSERT_EQ("3 52 112\n", w.str());}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 65, 43, 113);
    ASSERT_EQ("65 43 113\n", w.str());}

TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 82, 43, 116);
    ASSERT_EQ("82 43 116\n", w.str());}

// -----
// solve
// -----

TEST(Collatz, solve_1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

/*
OWN TESTS
*/

TEST(Collatz, solve_2) {
    std::istringstream r("100 80\n59 30\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("100 80 119\n59 30 113\n", w.str());}

TEST(Collatz, solve_3) {
    std::istringstream r("67 95\n3 84\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("67 95 116\n3 84 116\n", w.str());}

TEST(Collatz, solve_4) {
    std::istringstream r("4 53\n72 78\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("4 53 112\n72 78 116\n", w.str());}
/*
// ----------------------
// determine_cycle_length
// ----------------------

TEST(Collatz, determine_1) {
    const int v = determine_cycle_length(1);
    ASSERT_EQ(1, v);}

TEST(Collatz, determine_2) {
    const int v = determine_cycle_length(10);
    ASSERT_EQ(7, v);}

TEST(Collatz, determine_3) {
    const int v = determine_cycle_length(2);
    ASSERT_EQ(2, v);}
*/

/*
% g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz
==24339== Memcheck, a memory error detector
==24339== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==24339== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==24339== Command: TestCollatz
==24339== 
Running main() from gtest_main.cc
[==========] Running 22 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 22 tests from Collatz
[ RUN      ] Collatz.read_1
[       OK ] Collatz.read_1 (18 ms)
[ RUN      ] Collatz.read_2
[       OK ] Collatz.read_2 (3 ms)
[ RUN      ] Collatz.read_3
[       OK ] Collatz.read_3 (3 ms)
[ RUN      ] Collatz.read_4
[       OK ] Collatz.read_4 (3 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (32 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (13 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (2 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (19 ms)
[ RUN      ] Collatz.eval_5
[       OK ] Collatz.eval_5 (8 ms)
[ RUN      ] Collatz.eval_6
[       OK ] Collatz.eval_6 (4 ms)
[ RUN      ] Collatz.eval_7
[       OK ] Collatz.eval_7 (4 ms)
[ RUN      ] Collatz.print_1
[       OK ] Collatz.print_1 (10 ms)
[ RUN      ] Collatz.print_2
[       OK ] Collatz.print_2 (3 ms)
[ RUN      ] Collatz.print_3
[       OK ] Collatz.print_3 (3 ms)
[ RUN      ] Collatz.print_4
[       OK ] Collatz.print_4 (3 ms)
[ RUN      ] Collatz.solve_1
[       OK ] Collatz.solve_1 (28 ms)
[ RUN      ] Collatz.solve_2
[       OK ] Collatz.solve_2 (6 ms)
[ RUN      ] Collatz.solve_3
[       OK ] Collatz.solve_3 (7 ms)
[ RUN      ] Collatz.solve_4
[       OK ] Collatz.solve_4 (5 ms)
[ RUN      ] Collatz.determine_1
[       OK ] Collatz.determine_1 (2 ms)
[ RUN      ] Collatz.determine_2
[       OK ] Collatz.determine_2 (2 ms)
[ RUN      ] Collatz.determine_3
[       OK ] Collatz.determine_3 (2 ms)
[----------] 22 tests from Collatz (193 ms total)

[----------] Global test environment tear-down
[==========] 22 tests from 1 test case ran. (220 ms total)
[  PASSED  ] 22 tests.
==24339== 
==24339== HEAP SUMMARY:
==24339==     in use at exit: 0 bytes in 0 blocks
==24339==   total heap usage: 1,312 allocs, 1,312 frees, 116,468 bytes allocated
==24339== 
==24339== All heap blocks were freed -- no leaks are possible
==24339== 
==24339== For counts of detected and suppressed errors, rerun with: -v
==24339== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)




% gcov-4.7 -b Collatz.c++
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
...



% cat Collatz.c++.gcov
...



% gcov-4.7 -b TestCollatz.c++
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:83.93% of 224
Taken at least once:41.96% of 224
Calls executed:67.65% of 204
Creating 'TestCollatz.c++.gcov'
...



% cat TestCollatz.c++.gcov
...
*/

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

TEST (Collatz, READ_1) {
    std::istringstream r("9999 7777\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 9999, p.first);
    ASSERT_EQ( 7777, p.second);

}

TEST (Collatz, READ_2) {
    std::istringstream r("\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( 0, p.first);
    ASSERT_EQ( 0, p.second);

}

TEST (Collatz, READ_3) {
    std::istringstream r("-7 8\n");
    const std::pair<int, int> p = collatz_read(r);
    ASSERT_EQ( -7, p.first);
    ASSERT_EQ( 8, p.second);

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

TEST(Collatz, EVAL_5) {
    const int v = collatz_eval(10,1);
    ASSERT_EQ(20, v);}

TEST(Collatz, EVAL_6) {
    const int v = collatz_eval(200,100);
    ASSERT_EQ(125, v);}

TEST(Collatz, EVAL_7) {
    const int v = collatz_eval(210, 201);
    ASSERT_EQ(89, v);}

TEST(Collatz, EVAL_8) {
    const int v = collatz_eval(1000, 900);
    ASSERT_EQ(174, v);}

TEST(Collatz, EVAL_9) {
    const int v = collatz_eval(1,1);
    ASSERT_EQ(1, v);
}

TEST (Collatz, EVAL_10 ) {
const int v = collatz_eval( 611, 5475);
ASSERT_EQ( 238, v );
 }

TEST (Collatz, EVAL_11 ) {
const int v = collatz_eval( 8870, 4734);
ASSERT_EQ( 262, v );
 }

TEST (Collatz, EVAL_12 ) {
const int v = collatz_eval( 4817, 3887);
ASSERT_EQ( 215, v );
 }

TEST (Collatz, EVAL_13 ) {
const int v = collatz_eval( 6117, 7952);
ASSERT_EQ( 262, v );
 }

TEST (Collatz, EVAL_14 ) {
const int v = collatz_eval( 1670, 2897);
ASSERT_EQ( 209, v );
 }

TEST (Collatz, EVAL_15 ) {
const int v = collatz_eval( 8589, 3297);
ASSERT_EQ( 262, v );
 }

TEST (Collatz, EVAL_16 ) {
const int v = collatz_eval( 4662, 1600);
ASSERT_EQ( 238, v );
 }

TEST (Collatz, EVAL_17 ) {
const int v = collatz_eval( 2616, 2103);
ASSERT_EQ( 209, v );
 }

TEST (Collatz, EVAL_18 ) {
const int v = collatz_eval( 5574, 1454);
ASSERT_EQ( 238, v );
 }

TEST (Collatz, EVAL_19 ) {
const int v = collatz_eval( 837, 7285);
ASSERT_EQ( 262, v );
}

TEST (Collatz, EVAL_20 ) {
const int v = collatz_eval( 5328, 8699);
ASSERT_EQ( 262, v );

}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(Collatz, PRINT_1) {
    std::ostringstream w;
    collatz_print(w, -4, 600, 2013);
    ASSERT_EQ("-4 600 2013\n", w.str());
}

TEST(Collatz, PRINT_2) {
    std::ostringstream w;
    collatz_print(w, 0, 0, 97);
    ASSERT_EQ("0 0 97\n", w.str());
}

TEST(Collatz, PRINT_3) {
    std::ostringstream w;
    collatz_print(w, 78, 215, 65);
    ASSERT_EQ("78 215 65\n", w.str());
}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

TEST(Collatz, SOLVE_1) {
    std::istringstream r("10 1\n100 200\n210 201\n1000 900\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("10 1 20\n100 200 125\n210 201 89\n1000 900 174\n", w.str());}

TEST(Collatz, SOLVE_2) {
    std::istringstream r("1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 1 1\n", w.str());}

TEST(Collatz, SOLVE_3 ) {
            std::istringstream r ("835609 764159\n194508 386197\n594285 113367\n684886 780530\n632146 179725\n");
            std::ostringstream w;
            collatz_solve(r, w);
            ASSERT_EQ("835609 764159 520\n194508 386197 443\n594285 113367 470\n684886 780530 507\n632146 179725 509\n", w.str() ); }


TEST(Collatz, SOLVE_4 ) {
            std::istringstream r ("441306 344514\n226902 795939\n308308 965629\n503851 697348\n322522 114731\n145044 905256\n");
            std::ostringstream w;
            collatz_solve(r, w);
            ASSERT_EQ("441306 344514 449\n226902 795939 509\n308308 965629 525\n503851 697348 509\n322522 114731 443\n145044 905256 525\n", w.str() ); }


TEST (Collatz, SOLVE_5 ) {
         std::istringstream r("6155 1502\n");
         std::ostringstream w;
         collatz_solve( r, w);
         ASSERT_EQ("6155 1502 238\n", w.str() );
 }

TEST (Collatz, SOLVE_6 ) {
         std::istringstream r("7514 1266\n2141 6762\n295 4422\n945 3092\n1366 9943\n2781 1548\n");
         std::ostringstream w;
         collatz_solve( r, w);
         ASSERT_EQ("7514 1266 262\n2141 6762 262\n295 4422 238\n945 3092 217\n1366 9943 262\n2781 1548 209\n", w.str() );
 }

TEST (Collatz, SOLVE_7 ) {
         std::istringstream r("796 7212\n1193 1275\n690 7710\n2470 3359\n4905 4674\n5970 6793\n7164 9065\n8065 2053\n");
         std::ostringstream w;
         collatz_solve( r, w);
         ASSERT_EQ("796 7212 262\n1193 1275 177\n690 7710 262\n2470 3359 217\n4905 4674 197\n5970 6793 262\n7164 9065 252\n8065 2053 262\n", w.str() );
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

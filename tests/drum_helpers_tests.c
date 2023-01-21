#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // ssize_t

#include "drum_helpers.h"
#include "greatest/greatest.h"
#include "log.h"

TEST test_tresillo_zero() {
    ASSERT(tresillo(0, 0, 0, 8, 0) == 0);
    PASS();
}

// int pattern1, int pattern2, int len, int step

TEST test_tresillo_one_two_eight() {
    ASSERT(tresillo(0, 1, 2, 8, 0) == 0);
    ASSERT(tresillo(0, 1, 2, 8, 1) == 0);
    ASSERT(tresillo(0, 1, 2, 8, 2) == 1);
    ASSERT(tresillo(0, 1, 2, 8, 3) == 0);
    ASSERT(tresillo(0, 1, 2, 8, 4) == 0);
    ASSERT(tresillo(0, 1, 2, 8, 5) == 1);
    ASSERT(tresillo(0, 1, 2, 8, 6) == 0);
    ASSERT(tresillo(0, 1, 2, 8, 7) == 1);
    ASSERT(tresillo(0, 1, 2, 8, 8) == 0);
    ASSERT(tresillo(0, 1, 2, 8, 9) == 0);
    ASSERT(tresillo(0, 1, 2, 8, 10) == 1);
    ASSERT(tresillo(0, 1, 2, 8, 11) == 0);
    PASS();
}


TEST test_tresillo_thirteen_sixteen_eight() {
    ASSERT(tresillo(0, 13, 16, 8, 0) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 1) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 2) == 1);
    ASSERT(tresillo(0, 13, 16, 8, 3) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 4) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 5) == 1);
    ASSERT(tresillo(0, 13, 16, 8, 6) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 7) == 1);
    ASSERT(tresillo(0, 13, 16, 8, 8) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 9) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 10) == 1);
    ASSERT(tresillo(0, 13, 16, 8, 11) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 12) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 13) == 1);
    ASSERT(tresillo(0, 13, 16, 8, 14) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 15) == 1);
    ASSERT(tresillo(0, 13, 16, 8, 16) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 17) == 0);
    ASSERT(tresillo(0, 13, 16, 8, 18) == 1);
    PASS();
}

TEST test_tresillo_eighteen_twentythree_sixteen() {
    ASSERT(tresillo(0, 18, 23, 16, 0) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 1) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 2) == 1);
    ASSERT(tresillo(0, 18, 23, 16, 3) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 4) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 5) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 6) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 7) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 8) == 1);
    ASSERT(tresillo(0, 18, 23, 16, 9) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 10) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 11) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 12) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 13) == 1);
    ASSERT(tresillo(0, 18, 23, 16, 14) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 15) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 16) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 17) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 18) == 1);
    ASSERT(tresillo(0, 18, 23, 16, 19) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 20) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 21) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 22) == 0);
    ASSERT(tresillo(0, 18, 23, 16, 23) == 0);
    PASS();
}

TEST test_tresillo_thirtyone_thirtytwo_sixtyfour() {
    ASSERT(tresillo(0, 31, 32, 64, 0) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 1) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 2) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 3) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 4) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 5) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 6) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 7) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 8) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 9) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 10) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 11) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 12) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 13) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 14) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 15) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 16) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 17) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 18) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 19) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 20) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 21) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 22) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 23) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 24) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 25) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 26) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 27) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 28) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 29) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 30) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 31) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 32) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 33) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 34) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 35) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 36) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 37) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 38) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 39) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 40) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 41) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 42) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 43) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 44) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 45) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 46) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 47) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 48) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 49) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 50) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 51) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 52) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 53) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 54) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 55) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 56) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 57) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 58) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 59) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 60) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 61) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 62) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 63) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 64) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 65) == 0);
    ASSERT(tresillo(0, 31, 32, 64, 66) == 1);
    ASSERT(tresillo(0, 31, 32, 64, 67) == 0);
    PASS();
}

TEST test_tresillo_eighteen_twentythree_sixteen_rounddown() {
    ASSERT(tresillo(0, 18, 23, 17, 8) == 1);
    ASSERT(tresillo(0, 18, 23, 17, 17) == 0);
    PASS();
}

TEST test_tresillo_twentythree_twentyfive_eight_bank_four() {
    ASSERT(tresillo(4, 23, 25, 8, 0) == 0);
    ASSERT(tresillo(4, 23, 25, 8, 1) == 0);
    ASSERT(tresillo(4, 23, 25, 8, 2) == 1);
    ASSERT(tresillo(4, 23, 25, 8, 3) == 0);
    ASSERT(tresillo(4, 23, 25, 8, 4) == 0);
    ASSERT(tresillo(4, 23, 25, 8, 5) == 1);
    ASSERT(tresillo(4, 23, 25, 8, 6) == 0);
    ASSERT(tresillo(4, 23, 25, 8, 7) == 1);
    ASSERT(tresillo(4, 23, 25, 8, 8) == 0);
    ASSERT(tresillo(4, 23, 25, 8, 9) == 0);
    ASSERT(tresillo(4, 23, 25, 8, 10) == 1);
    ASSERT(tresillo(4, 23, 25, 8, 11) == 0);
    PASS();
}

TEST test_tresillo_fifty_fiftyone_fourtyeight_bank_two() {
    ASSERT(tresillo(2, 50, 51, 48, 0) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 1) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 2) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 3) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 4) == 1);
    ASSERT(tresillo(2, 50, 51, 48, 5) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 6) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 7) == 1);
    ASSERT(tresillo(2, 50, 51, 48, 8) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 9) == 1);
    ASSERT(tresillo(2, 50, 51, 48, 10) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 11) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 12) == 1);
    ASSERT(tresillo(2, 50, 51, 48, 13) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 14) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 15) == 1);
    ASSERT(tresillo(2, 50, 51, 48, 16) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 17) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 18) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 19) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 20) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 21) == 0);
    ASSERT(tresillo(2, 50, 51, 48, 22) == 1);
    PASS();
}

TEST test_drum_five_bank_zero() {
    ASSERT(drum(0, 5, 0) == 0);
    ASSERT(drum(0, 5, 18) == 0);
    PASS();
}

TEST test_drum_eighteen_bank_zero() {
    ASSERT(drum(0, 18, 0) == 0);
    ASSERT(drum(0, 18, 15) == 0);
    ASSERT(drum(0, 18, 16) == 0);
    ASSERT(drum(0, 18, 17) == 0);
    ASSERT(drum(0, 18, 18) == 1);
    PASS();
}

TEST test_drum_fifty_bank_two() {
    ASSERT(drum(2, 50, 0) == 0);
    ASSERT(drum(2, 50, 15) == 1);
    ASSERT(drum(2, 50, 16) == 0);
    ASSERT(drum(2, 50, 17) == 0);
    ASSERT(drum(2, 50, 18) == 0);
    ASSERT(drum(2, 50, 19) == 0);
    ASSERT(drum(2, 50, 20) == 1);
    PASS();
}

TEST test_velocity_zero() {
    ASSERT(velocity(0, 0) == 10965);
    ASSERT(velocity(0, 4) == 12255);
    ASSERT(velocity(0, 14) == 11610);
    ASSERT(velocity(0, 15) == 2580);
    PASS();
}

TEST test_velocity_five() {
    ASSERT(velocity(5, 0) == 5160);
    ASSERT(velocity(5, 4) == 5805);
    PASS();
}

TEST test_velocity_out_out_of_bound_pattern() {
    ASSERT(velocity(20, 0) == 0);
    PASS();
}

SUITE(drum_helpers_suite) {
    log_init();
    RUN_TEST(test_tresillo_zero);
    RUN_TEST(test_tresillo_one_two_eight);
    RUN_TEST(test_tresillo_thirteen_sixteen_eight);
    RUN_TEST(test_tresillo_eighteen_twentythree_sixteen);
    RUN_TEST(test_tresillo_thirtyone_thirtytwo_sixtyfour);
    RUN_TEST(test_tresillo_eighteen_twentythree_sixteen_rounddown);
    RUN_TEST(test_tresillo_twentythree_twentyfive_eight_bank_four);
    RUN_TEST(test_tresillo_fifty_fiftyone_fourtyeight_bank_two);
    RUN_TEST(test_drum_five_bank_zero);
    RUN_TEST(test_drum_eighteen_bank_zero);
    RUN_TEST(test_drum_fifty_bank_two);
    RUN_TEST(test_velocity_zero);
    RUN_TEST(test_velocity_five);
    RUN_TEST(test_velocity_out_out_of_bound_pattern);
}

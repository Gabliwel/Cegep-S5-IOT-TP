#pragma once

#include <Arduino.h>
#include <unity.h>
#include <RGBLedManager.h>

RGBLedManager ledManager = RGBLedManager(12, 13, 14);


void test_function_getColorFromPM25_11(void) {
    TEST_ASSERT_EQUAL(Color::green, ledManager.getColorFromPM25(11));
}

void test_function_getColorFromPM25_34(void) {
    TEST_ASSERT_EQUAL(Color::yellow, ledManager.getColorFromPM25(34));
}

void test_function_getColorFromPM25_54(void) {
    TEST_ASSERT_EQUAL(Color::orange, ledManager.getColorFromPM25(54));
}

void test_function_getColorFromPM25_55(void) {
    TEST_ASSERT_EQUAL(Color::red, ledManager.getColorFromPM25(55));
}

void process_test_del(void){
    RUN_TEST(test_function_getColorFromPM25_11);
    RUN_TEST(test_function_getColorFromPM25_34);
    RUN_TEST(test_function_getColorFromPM25_54);
    RUN_TEST(test_function_getColorFromPM25_55);
}
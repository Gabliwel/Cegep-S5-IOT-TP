#pragma once

#include <Arduino.h>
#include <unity.h>
#include <AqiScale.h>

AqiScale scale;

void test_function_scale_getPollutionLvl1(void) {
    TEST_ASSERT_EQUAL(scale.lvl1, scale.getPollutionLvl(11));
}

void test_function_scale_getPollutionLvl2(void) {
    TEST_ASSERT_EQUAL(scale.lvl2, scale.getPollutionLvl(34));
}

void test_function_scale_getPollutionLvl3(void) {
    TEST_ASSERT_EQUAL(scale.lvl3, scale.getPollutionLvl(54));
}

void test_function_scale_getPollutionLvl4(void) {
    TEST_ASSERT_EQUAL(scale.lvl4, scale.getPollutionLvl(55));
}

void process_test_scale() {
    RUN_TEST(test_function_scale_getPollutionLvl1);
    RUN_TEST(test_function_scale_getPollutionLvl2);
    RUN_TEST(test_function_scale_getPollutionLvl3);
    RUN_TEST(test_function_scale_getPollutionLvl4);
}


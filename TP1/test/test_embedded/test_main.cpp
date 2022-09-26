#include <Arduino.h>
#include <unity.h>

#include "test_AqiScale.h"
#include "test_DEL_RGB.h"
#include "test_pass.h"

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    
    process_test_scale();

    process_test_del();
    
    process_test_pass();

    
    UNITY_END();

}

void loop() {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}

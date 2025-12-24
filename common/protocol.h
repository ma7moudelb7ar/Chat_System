#pragma once
#include <cstdint>

const int MAX_TEXT = 256;
const int MAX_NAME = 32;
const int SHM_CAPACITY = 20;

// A simple fixed-size message for both systems
struct Message {
    int32_t sender_id;
    char sender[MAX_NAME];
    char text[MAX_TEXT];
    int64_t timestamp_ms;
};

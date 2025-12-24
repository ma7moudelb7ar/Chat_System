#pragma once
#include <string>
#include <cstdint>
#include "protocol.h"

int64_t now_ms();
std::string format_message(const Message& m);

// Safe copy into fixed char arrays
void copy_cstr(char* dst, size_t cap, const std::string& src);

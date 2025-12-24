#include "utils.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <cstring>

int64_t now_ms(){
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void copy_cstr(char* dst, size_t cap, const std::string& src){
    std::memset(dst, 0, cap);
    std::strncpy(dst, src.c_str(), cap-1);
}

std::string format_message(const Message& m){
    std::ostringstream oss;
    oss << "[" << m.sender << "] " << m.text;
    return oss.str();
}

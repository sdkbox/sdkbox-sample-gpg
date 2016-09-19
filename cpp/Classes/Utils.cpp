#include <sstream>
#include <vector>
#include "Utils.h"

std::vector<uint8_t> str_to_vector( const std::string& str ) {
    return std::vector<uint8_t>( str.begin(), str.end() );
}

std::string vec_to_string( const std::vector<uint8_t>& v ) {
    return std::string(v.begin(), v.end());
}

std::string __printf( const char* format, ... ) {
    char b[256];
    va_list args;
    va_start (args, format);
    vsnprintf (b,256,format, args);
    va_end( args );

    return std::string(b);
}
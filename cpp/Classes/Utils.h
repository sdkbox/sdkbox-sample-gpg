#pragma once

std::vector<uint8_t> str_to_vector( const std::string& str );

std::string vec_to_string( const std::vector<uint8_t>& v );

template <typename T>
std::string to_str ( T Number )
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

std::string __printf( const char* format, ... );

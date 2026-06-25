#pragma once
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <iostream>
#include <map>
#include <vector>

template< typename T >
std::string int_to_hex(T i)
{
    std::stringstream stream;
    stream << std::hex << i;
    return stream.str();
}

std::vector<unsigned char> hex_to_bytes(const std::string& hex);


#endif
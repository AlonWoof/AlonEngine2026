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

template<class T>
T base_name(T const& path, T const& delims = "/\\")
{
    return path.substr(path.find_last_of(delims) + 1);
}

template<class T>
T remove_extension(T const& filename)
{
    typename T::size_type const p(filename.find_last_of('.'));
    return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
}

std::string path_to_filename(std::string in, bool removeExt = true);
std::vector<unsigned char> hex_to_bytes(const std::string& hex);


#endif
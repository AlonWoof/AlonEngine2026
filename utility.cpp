
#include "utility.h"



std::vector<unsigned char> hex_to_bytes(const std::string& hex)
{
    std::vector<unsigned char> bytes;

    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        char byte = (char)strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }

    return bytes;
}

std::string bytes_to_hex(const unsigned char* data, int len)
{
    std::stringstream ss;
    ss << std::hex;

    for (int i(0); i < len; ++i)
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}

std::string path_to_filename(std::string in, bool removeExt)
{
    std::string out = base_name<std::string>(in);

    if (removeExt)
        return remove_extension(out);

    return out;
}

std::string extract_directory(const std::string& path) {
    // Look for the last occurrence of either a forward slash or backslash
    size_t found = path.find_last_of("/\\");

    if (found != std::string::npos) {
        return path.substr(0, found);
    }

    return ""; // No directory separator found
}




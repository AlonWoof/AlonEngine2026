
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

std::string path_to_filename(std::string in, bool removeExt)
{
    std::string out = base_name<std::string>(in);

    if (removeExt)
        return remove_extension(out);

    return out;
}



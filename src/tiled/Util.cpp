#include <algorithm>
#include <functional>

#define MINIZ_HEADER_FILE_ONLY
#include "miniz/miniz.c"

#include "Util.hpp"
#include "base64/base64.h"

namespace tiled
{
static inline std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

static inline std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string& Util::trim(std::string& trim)
{
    return ltrim(rtrim(trim));
}

std::string Util::decodeBase64(const std::string& base64)
{
    return base64_decode(base64);
}

char* Util::decompressGZIP(const char* data, int size_data, int size_expected)
{
    int bufferSize = size_expected;
    int ret;
    z_stream strm;
    char *out = (char*)malloc(bufferSize);

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = (Bytef*)data;
    strm.avail_in = size_data;
    strm.next_out = (Bytef*)out;
    strm.avail_out = bufferSize;

    ret = inflateInit2(&strm, 15 + 32);

    if (ret != Z_OK)
    {
        free(out);
        return NULL;
    }

    do
    {
        ret = inflate(&strm, Z_SYNC_FLUSH);

        switch (ret)
        {
            case Z_NEED_DICT:
            case Z_STREAM_ERROR:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&strm);
                free(out);
            return NULL;
        }

        if (ret != Z_STREAM_END)
        {
            out = (char *) realloc(out, bufferSize * 2);

            if (!out)
            {
                inflateEnd(&strm);
                free(out);
                return NULL;
            }

            strm.next_out = (Bytef *)(out + bufferSize);
            strm.avail_out = bufferSize;
            bufferSize *= 2;
        }
    }
    while (ret != Z_STREAM_END);

    if (strm.avail_in != 0)
    {
        free(out);
        return NULL;
    }

    inflateEnd(&strm);

    return out;
}
}

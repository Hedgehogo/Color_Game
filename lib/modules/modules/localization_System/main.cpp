#include <iostream>

#include "lib/loc/system.hpp"

#ifdef _MSC_VER

std::string to_utf8(std::u32string const & s)
{
    std::wstring_convert<std::codecvt_utf8<int32_t>, int32_t> convert;
    auto const p = reinterpret_cast<int32_t const *>(s.data());
    return convert.to_bytes(p, p + s.size());
}

#else

std::string to_utf8(std::u32string const & s)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    return conv.to_bytes(s);
}

#endif

int main() {
    loc::system.setModules({"../../LocalizationZip/cmake-build-debug/libLocalizationZip.so"});

    loc::system.loadFromDirectory("../test");

    loc::system.setDefaultLanguage("en");
    loc::system.setNowLanguage("ru");

    std::u32string str32Test{loc::system.getText("text")};
    std::cout << to_utf8(str32Test) << std::endl;
}

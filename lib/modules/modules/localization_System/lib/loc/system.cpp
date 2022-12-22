#include "system.hpp"

#include <fstream>
#include <algorithm>
//#include <dlfcn.h>

typedef unsigned uint;

namespace loc {
    bool findNotSpace(const char32_t &a) {
        bool r = a != U' ' && a != U'\n' && a != U'\t';
        return r;
    }

    bool findSpace(const char32_t &a) {
        return a == U' ' || a == U'\n' || a == U'\t';
    }

    bool findQuoteMarks(const char32_t &a){
        return a == U'"';
    }

    std::u32string::iterator searchQuoteMark(std::u32string::iterator first, std::u32string::iterator last){
        std::u32string::iterator result;
        while ((result = std::find_if(first, last, findQuoteMarks)) != last && *(result - 1) == U'\\');
        return result;
    }

    LocalizationNonexistentKeyException::LocalizationNonexistentKeyException(std::string nowLanguage, std::string defaultLanguage, std::string key) :
        nowLanguage(nowLanguage), defaultLanguage(defaultLanguage), key(key),
        str(std::string{"could not find the key '"} + key + std::string{"' in either the specified language '"} + nowLanguage + std::string{"' or the standard '"} + defaultLanguage + std::string{"'"}){}

    const char *LocalizationNonexistentKeyException::what() const noexcept {
        return str.c_str();
    }

    void readLocFile(std::filesystem::path path, std::u32string& files){
        std::u32string str{};
        std::basic_ifstream<char32_t> fin(path);
        std::getline(fin, str, U'\0');
        files += str + U'\n';
    }

    void System::readAllLocInDirectory(std::filesystem::path path, std::u32string& files){
        for (auto &languageFile: std::filesystem::directory_iterator(path)) {
            if(languageFile.path().extension() == ".loc") {
                if (languageFile.is_directory()) {
                    readAllLocInDirectory(languageFile.path(), files);
                }
                else {
                    readLocFile(languageFile.path(), files);
                }
            }
            /*else{
                bool (*read)(std::filesystem::path path, std::u32string& files){nullptr};
                for (auto& module : modules) {
                    read = (bool (*)(std::filesystem::path path, std::u32string& files))dlsym(module, "read");
                    if (read){
                        if (read(languageFile.path(), files)){
                            break;
                        }
                    }
                }
            }*/
        }
    }

    std::u32string System::readAllLocInDirectory(std::filesystem::path path){
        std::u32string result;
        readAllLocInDirectory(path, result);
        return result;
    }

    void System::loadFromDirectory(std::filesystem::path path) {

        std::u32string files{readAllLocInDirectory(path)};

        std::string key;

        std::u32string::iterator cursor = files.begin();
        while ((cursor = std::find_if(cursor, files.end(), findNotSpace)) != files.end()){
            if (*cursor == U'"') {
                std::u32string::iterator endText{searchQuoteMark(cursor + 1, files.end())};
                (*nowLanguage)[key] = {cursor + 1, endText};
                cursor = endText + 1;
            } else {
                std::u32string::iterator endName{std::find_if(cursor, files.end(), findSpace)};
                if (*cursor == U'-') {
                    nowLanguage = &text[{cursor + 1, endName}];
                } else {
                    key = {cursor, endName};
                }
                cursor = endName;
            }
        }
    }

    void System::clear() {
        text.clear();
        nowLanguage = nullptr;
        defaultLanguage = nullptr;
        strNowLanguage = "";
        strDefaultLanguage = "";
    }

    void System::setNowLanguage(std::string language) {
        strNowLanguage = language;
        nowLanguage = &text[language];
    }

    void System::setDefaultLanguage(std::string language) {
        strDefaultLanguage = language;
        defaultLanguage = &text[language];
    }

    std::u32string System::getText(std::string key) {
        if (nowLanguage && nowLanguage->find(key) != nowLanguage->end())
            return (*nowLanguage)[key];
        else if (defaultLanguage && defaultLanguage->find(key) != defaultLanguage->end())
            return (*defaultLanguage)[key];
        else
            throw LocalizationNonexistentKeyException{strNowLanguage, strDefaultLanguage, key};
    }

    std::u32string System::getText(std::string key, std::string language) {
        return System::text[language][key];
    }

    std::vector<std::string> System::getLanguages() {
        std::vector<std::string> result{};

        for (auto & pair : text) {
            result.push_back(pair.first);
        }

        return result;
    }

    void System::setModules(std::vector<std::string> paths) {
        for (auto path : paths) {
            //modules.push_back(dlopen(path.c_str(), RTLD_NOW));
        }
    }

    System::~System() {
        for (auto& module : modules) {
            //dlclose(module);
        }
    }
}
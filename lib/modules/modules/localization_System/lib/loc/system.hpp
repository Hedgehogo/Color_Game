#pragma once

#include <vector>
#include <map>
#include <string>
#include <exception>
#include <filesystem>

namespace loc {

    class LocalizationNonexistentKeyException : public std::exception{
    protected:
        std::string str;
        std::string nowLanguage;
        std::string defaultLanguage;
        std::string key;

    public:
        LocalizationNonexistentKeyException(std::string nowLanguage, std::string defaultLanguage, std::string key);
        const char* what() const noexcept override;
    };

    class System {
    protected:
        std::map<std::string, std::map<std::string, std::u32string>> text;
        std::string strNowLanguage;
        std::map<std::string, std::u32string>* nowLanguage{nullptr};
        std::string strDefaultLanguage;
        std::map<std::string, std::u32string>* defaultLanguage{nullptr};

        std::vector<void* > modules;

        virtual std::u32string readAllLocInDirectory(std::filesystem::path path);
        virtual void readAllLocInDirectory(std::filesystem::path path, std::u32string& files);
    public:
        virtual void loadFromDirectory(std::filesystem::path path);
        virtual void clear();

        virtual void setNowLanguage(std::string language);
        virtual void setDefaultLanguage(std::string language);

        virtual std::u32string getText(std::string key);
        virtual std::u32string getText(std::string key, std::string language);

        virtual std::vector<std::string> getLanguages();

        virtual void setModules(std::vector<std::string> paths);

        virtual ~System();
    };

    static System system;
} // ui
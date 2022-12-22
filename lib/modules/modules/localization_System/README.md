# Description

Localisation_System is a library that helps you to write a localisation for the program so that it can be easily updated and changed by the community 

# localization file syntax

* The name of the language is indicated with a "-" such as `-en`
* The key is written without any markings, for example `text1`
* the phrase is written in quotation marks and assigned to the last language and key, which makes it possible to write all keys for 1 language or all languages for 1 key
## example
```localization
-ru
  plug "вилка"
-en
  plug "plug"

spoon
  -ru "ложка"
  -en "spoon"
-jp
  plug   "フォーク"
  spoon  "スプーン"
```

# API Documentation
| function                                                      | description                                                                                     |
|:--------------------------------------------------------------|:------------------------------------------------------------------------------------------------|
| void loadFromDirectory(std::filesystem::path path)            | Load all localization files in the directory                                                    |
| void setNowLanguage(std::string language)                     | Setting the current language                                                                    |
| void setDefaultLanguage(std::string language)                 | If the phrase is not found in the current language, it will be searched in the default language |
| std::u32string getText(std::string key)                       | Returns the phrase for the given key                                                            |
| std::u32string getText(std::string key, std::string language) | Returns the phrase for the given key and language                                               |
| std::vector<std::string> getLanguages()                       | Returns the list of loaded languages                                                            |
| void setModule(std::string path)                              | Adds a module for reading the new file format                                                   |

# Modules System 

module is a dynamic library that stores a function `bool read(std::filesystem::path path, std::u32string& files)` which takes the path of the downloaded file and a link to a string with all the files, and returns whether the file was successfully read or not
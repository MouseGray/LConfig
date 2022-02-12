#pragma once

#include <string>
#include <unordered_map>

#include <lloggerlib.h>

class LConfig
{
    static constexpr char file_name[] = "Config.cfg";
    static const std::string no_value;
public:
    LConfig(LLogger& logger) noexcept;
    void Init();

    bool Has(const std::string& key) const noexcept;
    const std::string& Get(const std::string& key) const noexcept;
private:
    void AddOption(const std::string& line, size_t line_number);
    static void Trim(std::string& value) noexcept;

    std::unordered_map<std::string, std::string> mData;

    LLogger& mLogger;
};

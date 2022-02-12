#include "lconfig.h"

#include <filesystem>
#include <fstream>

const std::string LConfig::no_value{};

LConfig::LConfig(LLogger& logger) noexcept
    : mLogger(logger)
{
}

void LConfig::Init()
{
    mLogger.Log(LLogger::Level::Medium, "Config parsing started...");

    std::filesystem::path current_path = std::filesystem::current_path();
    current_path /= LConfig::file_name;

    mLogger.Log(LLogger::Level::High, "Path to config: $$", current_path);

    std::ifstream stream(current_path, std::fstream::in);

    if (stream.is_open()) {
        std::size_t line_number = 0;
        for (std::string line; std::getline(stream, line); ++line_number) {
            AddOption(line, line_number);
        }
    }
    else {
        mLogger.Error(LLogger::Level::Low, "Could not open config!");
    }

    mLogger.Log(LLogger::Level::Medium, "Config parsing finished...");
}

bool LConfig::Has(const std::string &key) const noexcept
{
    return mData.find(key) != mData.end();
}

const std::string &LConfig::Get(const std::string &key) const noexcept
{
    auto res_it = mData.find(key);
    if (res_it == mData.end()) {
        mLogger.Warning(LLogger::Level::Medium, "Requested value {$$} was not found in config", key);
        return LConfig::no_value;
    }
    return res_it->second;
}

void LConfig::AddOption(const std::string &line, std::size_t line_number)
{
    std::size_t splitter = line.find(':');
    if (splitter == std::string::npos) {
        mLogger.Warning(LLogger::Level::Low, "Invalid option in line $$.", line_number);
        return;
    }
    std::string key = line.substr(0, splitter);
    LConfig::Trim(key);
    if (key.empty()) {
        mLogger.Warning(LLogger::Level::Low, "Empty key in line $$.", line_number);
        return;
    }
    std::string value = line.substr(splitter + 1);
    LConfig::Trim(value);
    if (value.empty()) {
        mLogger.Warning(LLogger::Level::Low, "Empty value in line $$.", line_number);
        return;
    }
    mData.insert( { key, value } );
    mLogger.Log(LLogger::Level::Medium, "Added option {$$: $$}", key, value);
}

void LConfig::Trim(std::string &value) noexcept
{
    const char* ws = " \t\r\n";
    std::size_t start = value.find_first_not_of(ws);
    if (start == std::string::npos) {
        value.clear();
        return;
    }
    if (start != 0) {
        value.erase(0, start);
    }
    std::size_t end = value.find_last_not_of(ws);
    if (end + 1 != value.size()) {
        value.erase(end + 1);
    }
}

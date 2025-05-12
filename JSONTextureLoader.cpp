#include "JsonTextureLoader.h"

TextureCategory JSONTextureLoader::CategoryFromString(const string& str) {
    if (str == "Idle") return TextureCategory::Idle;
    if (str == "Move") return TextureCategory::Move;
    if (str == "Attack") return TextureCategory::Attack;
    if (str == "Death") return TextureCategory::Death;
    if (str == "Static") return TextureCategory::Static;
    if (str == "StaticAnimated") return TextureCategory::StaticAnimated;

    throw std::invalid_argument("Unknown category string: " + str);
};

UI_Parts JSONTextureLoader::PartFromString(const string& s) {
    if (s == "PlayerHealthBar") return UI_Parts::PlayerHealthBar;
    if (s == "PlayerHealthMeter") return UI_Parts::PlayerHealthMeter;
    if (s == "PlayerStaminaMeter") return UI_Parts::PlayerStaminaMeter;
    if (s == "PlayerManaMeter") return UI_Parts::PlayerManaMeter;
    throw std::invalid_argument("Unknown UI_Parts: " + s);
}

vector<TextureMeta> JSONTextureLoader::LoadTextureMeta(const string& path) {
    vector<TextureMeta> result;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open meta file: " + path);
    }

    json j;
    file >> j;

    for (auto& [key, val] : j.items()) {
        TextureMeta meta;
        meta.category = CategoryFromString(key);
        meta.folderPath = val["folderPath"];
        meta.fileName = val["fileName"];
        meta.frameWidth = val["frameWidth"];
        meta.frameHeight = val["frameHeight"];
        meta.numberOfColumns = val["columns"];
        meta.numberOfFrames = val["frames"];

        result.push_back(meta);
    }

    return result;
};

map<UI_Parts,Texture> JSONTextureLoader::LoadPlayerUITextures(const string& path)
{
    map<UI_Parts, Texture> result;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open meta file: " + path);
    }

    json j;
    file >> j;

    for (auto& [key, val] : j.items()) {
        Texture tex;
        UI_Parts part = PartFromString(val["UI_Parts"]);
        string folderPath = val["folderPath"];
        string fileName = val["fileName"];
        if (!tex.loadFromFile(folderPath+fileName)) {
            std::cout << "Failed to load: " << folderPath + fileName << "\n";
        }
        result.emplace(part,tex);
    }

    return result;
}

map<int, Texture> JSONTextureLoader::LoadStaticTextures(const string& path)
{
    map<int, Texture> result;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open meta file: " + path);
    }

    json j;
    file >> j;

    for (auto& [key, val] : j.items()) {
        Texture tex;
        int _key = stoi(key);
        string folderPath = val["folderPath"];
        string fileName = val["fileName"];
        std::cout << "Trying to load: " << folderPath + fileName << std::endl;
        if (!tex.loadFromFile(folderPath + fileName)) {
            std::cout << "Failed to load: " << folderPath + fileName << "\n";
        }
        result.emplace(_key, tex);
    }

    return result;
}
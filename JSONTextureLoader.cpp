#include "JsonTextureLoader.h"

TextureCategory JSONTextureLoader::CategoryFromString(const string& str) {
    if (str == "Idle") return TextureCategory::Idle;
    if (str == "Move") return TextureCategory::Move;
    if (str == "Attack") return TextureCategory::Attack;
    if (str == "Death") return TextureCategory::Death;
    if (str == "Static") return TextureCategory::Static;
    if (str == "StaticAnimated") return TextureCategory::StaticAnimated;

    throw std::invalid_argument("Unknown category string: " + str);
}

vector<TextureMeta> JSONTextureLoader::LoadTextureMeta(const string& path) {
    vector<TextureMeta> result;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open meta file: " + path);
    }

    json j;
    file >> j;

    for (auto& [key,val] : j.items()) {
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
}
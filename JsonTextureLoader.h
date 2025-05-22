#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "BaseMesh.h"
#include "JSONLibs/json.hpp"

using namespace std;
using json = nlohmann::json;

enum UI_Parts
{
    PlayerHealthBar,
    PlayerHealthMeter,
    PlayerStaminaMeter,
    PlayerManaMeter
};


static class JSONTextureLoader
{
private:

    static TextureCategory CategoryFromString(const std::string& str);
    static UI_Parts PartFromString(const string& s);

public:
    static vector<TextureMeta> LoadTextureMeta(const string& path);
    static map<UI_Parts, Texture> LoadPlayerUITextures(const string& path);
    static map<int, Texture> LoadStaticTextures(const string& path);
    static map<string, Texture> LoadLevelTextures(const string& path);
};

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "BaseMesh.h"
#include "JSONLibs/json.hpp"

using namespace std;
using json = nlohmann::json;

static class JSONTextureLoader
{
private:

    static TextureCategory CategoryFromString(const std::string& str);

public:
    static vector<TextureMeta> LoadTextureMeta(const string& path);
};

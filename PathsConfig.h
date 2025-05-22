#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const string JSON_TEXTURES_PATH = "JSONData/textures/";
const string PLAYER_UI_TEX_FILE = "Player_UI.json";
const string HOUSES_TEXTURES_JSON_FILE = "HousesTextures.json";
const string LADYARCHER_JSON_TEXTURES_FILE = "LadyArcherTextureMeta.json";
const string SKELETON_BASIC_JSON_TEXTURES_FILE = "Skeleton_Basic_Textures_Meta.json";
const string TREES_JSON_TEXTURES_FILE = "TreesTextures.json";
const string LADYSWORD_JSON_TEXTURES_FILE = "LadySwordTextureMeta.json";

namespace ArrowsPaths
{
	const string ARROW_TEXTURES_SIMPLE_FOLDER = "textures/Weapons/";
	const string ARROW_TEXTURES_EFFECTS_FOLDER = "textures/Weapons/Effects/";
	const string ARROW_TEXTURES_SIMPLE_FILE = "arrow.png";
	const string ARROW_TEXTURES_FIRE_FILE = "fire_arrow.png";
}

namespace TerrainTextures
{
	const string GRASS_DARK_GREEN = "textures/World/Grass/tileable-1-grey.png";
}


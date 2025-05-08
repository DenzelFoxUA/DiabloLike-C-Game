#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace ArcherLadyCharacterPaths
{
	const string LADY_ARCHER_TEXTURES_RUN_FOLDER = "textures/Characters/ArcherLady/Run_Bow/";
	const string LADY_ARCHER_TEXTURES_IDLE_FOLDER = "textures/Characters/ArcherLady/Idle_Bow/";
	const string LADY_ARCHER_TEXTURES_ATTACK_FOLDER = "textures/Characters/ArcherLady/Attack_Bow/";
	const string LADY_ARCHER_TEXTURES_DEATH_FOLDER = "textures/Characters/ArcherLady/Death_Bow/";

	const string LADY_ARCHER_TEXTURES_DEATH_FILE = "Death_Bow_Body";
	const string LADY_ARCHER_TEXTURES_IDLE_FILE = "Idle_Bow_Body";
	const string LADY_ARCHER_TEXTURES_RUN_FILE = "Run_Bow_Body";
	const string LADY_ARCHER_TEXTURES_ATTACK_FILE = "Attack_Bow_Body";

	
}

namespace SkeletonCharacterPaths
{
	const string SKELETON_TEXTURES_RUN_FOLDER = "textures/Characters/SceletonBasic/Run_Forward/";
	const string SKELETON_TEXTURES_IDLE_FOLDER = "textures/Characters/SceletonBasic/Idle_Simple/";
	const string SKELETON_TEXTURES_ATTACK_FOLDER = "textures/Characters/SceletonBasic/Attack_Slash_01/";
	const string SKELETON_TEXTURES_DEATH_FOLDER = "textures/Characters/SceletonBasic/Death_Back/";

	const string SKELETON_TEXTURES_DEATH_FILE = "GlowEyes_Death_Back_Body";
	const string SKELETON_TEXTURES_IDLE_FILE = "DarkEyes_Idle_Simple_Body";
	const string SKELETON_TEXTURES_RUN_FILE = "DarkEyes_Run_Forward_Body";
	const string SKELETON_TEXTURES_ATTACK_FILE = "DarkEyes_Attack_Slash_01_Body";


}

namespace Arrows
{
	const string ARROW_TEXTURES_SIMPLE_PATH = "textures/Weapons/";
	const string ARROW_TEXTURES_EFFECTS_PATH = "textures/Weapons/Effects/";
	const string ARROW_TEXTURES_SIMPLE_FILE = "arrow.png";
	const string ARROW_TEXTURES_FIRE_FILE = "fire_arrow.png";
}
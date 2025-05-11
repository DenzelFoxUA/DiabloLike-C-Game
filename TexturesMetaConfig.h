#pragma once
#include <SFML/Graphics.hpp>
#include "BaseMesh.h"
#include "CharacterMesh.h"
#include "LadyArcherMesh.h"
#include "LadyArcher.h"
#include "LadyArcherController.h"
#include "Skeleton.h"
#include "SkeletonMesh.h"
#include "SkeletonController.h"
#include <iostream>
#include "PathsConfig.h"
#include "JsonTextureLoader.h"


using namespace std;
using namespace ArcherLadyCharacterPaths;
using namespace ArrowsPaths;
using namespace SkeletonCharacterPaths;
using namespace SmallHousesPaths;
using namespace PlantsPaths;


vector<TextureMeta> LadyArcherMeta()
{
    Texture arrowTexture;
    if (!arrowTexture.loadFromFile(ARROW_TEXTURES_SIMPLE_FOLDER + ARROW_TEXTURES_SIMPLE_FILE))
    {
        std::cout << "Error loading arrow texture!\n";
    }

    //TextureMeta ladyArcherIdle;
    //ladyArcherIdle.category = TextureCategory::Idle;
    //ladyArcherIdle.fileName = LADY_ARCHER_TEXTURES_IDLE_FILE;
    //ladyArcherIdle.folderPath = LADY_ARCHER_TEXTURES_IDLE_FOLDER;
    //ladyArcherIdle.frameHeight = 180;
    //ladyArcherIdle.frameWidth = 180;
    //ladyArcherIdle.numberOfColumns = 4;
    //ladyArcherIdle.numberOfFrames = 16;

    //TextureMeta ladyArcherAttack;
    //ladyArcherAttack.category = TextureCategory::Attack;
    //ladyArcherAttack.fileName = LADY_ARCHER_TEXTURES_ATTACK_FILE;
    //ladyArcherAttack.folderPath = LADY_ARCHER_TEXTURES_ATTACK_FOLDER;
    //ladyArcherAttack.frameHeight = 180;
    //ladyArcherAttack.frameWidth = 180;
    //ladyArcherAttack.numberOfColumns = 6;
    //ladyArcherAttack.numberOfFrames = 24;

    //TextureMeta ladyArcherMove;
    //ladyArcherMove.category = TextureCategory::Move;
    //ladyArcherMove.fileName = LADY_ARCHER_TEXTURES_RUN_FILE;
    //ladyArcherMove.folderPath = LADY_ARCHER_TEXTURES_RUN_FOLDER;
    //ladyArcherMove.frameHeight = 180;
    //ladyArcherMove.frameWidth = 180;
    //ladyArcherMove.numberOfColumns = 5;
    //ladyArcherMove.numberOfFrames = 20;

    //TextureMeta ladyArcherDead;
    //ladyArcherDead.category = TextureCategory::Death;
    //ladyArcherDead.fileName = LADY_ARCHER_TEXTURES_DEATH_FILE;
    //ladyArcherDead.folderPath = LADY_ARCHER_TEXTURES_DEATH_FOLDER;
    //ladyArcherDead.frameHeight = 180;
    //ladyArcherDead.frameWidth = 180;
    //ladyArcherDead.numberOfColumns = 6;
    //ladyArcherDead.numberOfFrames = 30;

    return JSONTextureLoader::LoadTextureMeta(JSON_TEXTURES_PATH + LADYARCHER_JSON_TEXTURES_FILE);
        //{ ladyArcherIdle,ladyArcherAttack,ladyArcherMove,ladyArcherDead };
}

vector<TextureMeta> SkeletonTexturesMeta()
{
    TextureMeta idle_skeleton1;
    idle_skeleton1.category = TextureCategory::Idle;
    idle_skeleton1.fileName = SKELETON_TEXTURES_IDLE_FILE;
    idle_skeleton1.folderPath = SKELETON_TEXTURES_IDLE_FOLDER;
    idle_skeleton1.frameHeight = 180;
    idle_skeleton1.frameWidth = 180;
    idle_skeleton1.numberOfColumns = 4;
    idle_skeleton1.numberOfFrames = 8;

    TextureMeta move_skeleton1;
    move_skeleton1.category = TextureCategory::Move;
    move_skeleton1.fileName = SKELETON_TEXTURES_RUN_FILE;
    move_skeleton1.folderPath = SKELETON_TEXTURES_RUN_FOLDER;
    move_skeleton1.frameHeight = 180;
    move_skeleton1.frameWidth = 180;
    move_skeleton1.numberOfColumns = 4;
    move_skeleton1.numberOfFrames = 8;

    TextureMeta attack_skeleton1;
    attack_skeleton1.category = TextureCategory::Attack;
    attack_skeleton1.fileName = SKELETON_TEXTURES_ATTACK_FILE;
    attack_skeleton1.folderPath = SKELETON_TEXTURES_ATTACK_FOLDER;
    attack_skeleton1.frameHeight = 180;
    attack_skeleton1.frameWidth = 180;
    attack_skeleton1.numberOfColumns = 4;
    attack_skeleton1.numberOfFrames = 8;

    TextureMeta death_skeleton1;
    death_skeleton1.category = TextureCategory::Death;
    death_skeleton1.fileName = SKELETON_TEXTURES_DEATH_FILE;
    death_skeleton1.folderPath = SKELETON_TEXTURES_DEATH_FOLDER;
    death_skeleton1.frameHeight = 180;
    death_skeleton1.frameWidth = 180;
    death_skeleton1.numberOfColumns = 4;
    death_skeleton1.numberOfFrames = 16;

    

    return { idle_skeleton1, move_skeleton1,attack_skeleton1, death_skeleton1 };
}

TextureMeta SmallHouseTexturesMeta_3()
{
    TextureMeta staticHouse;
    staticHouse.category = TextureCategory::Static;
    staticHouse.fileName = HOUSE3_TEXTURE;
    staticHouse.folderPath = SMALL_HOUSES_TEXTURE_FOLDER;
    staticHouse.frameHeight = 447;
    staticHouse.frameWidth = 600;
    staticHouse.numberOfColumns = 1;
    staticHouse.numberOfFrames = 1;

    return staticHouse;
}

TextureMeta TreeTexturesMeta_1()
{
    TextureMeta staticTree;
    staticTree.category = TextureCategory::Static;
    staticTree.fileName = TREE_TEXTURE_1;
    staticTree.folderPath = TREE_TEXTURE_FOLDER;
    staticTree.frameHeight = 545;
    staticTree.frameWidth = 591;
    staticTree.numberOfColumns = 1;
    staticTree.numberOfFrames = 1;

    return staticTree;
}

TextureMeta TreeTexturesMeta_2()
{
    TextureMeta staticTree;
    staticTree.category = TextureCategory::Static;
    staticTree.fileName = TREE_TEXTURE_2;
    staticTree.folderPath = TREE_TEXTURE_FOLDER;
    staticTree.frameHeight = 556;
    staticTree.frameWidth = 602;
    staticTree.numberOfColumns = 1;
    staticTree.numberOfFrames = 1;

    return  staticTree;
}

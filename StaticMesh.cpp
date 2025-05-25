#include "StaticMesh.h"

//void StaticMesh::LoadTextures(string folderPath, string fileName) {
//
//    string path = folderPath + fileName;
//    
//    Texture tex;
//    if (!_textureStatic.loadFromFile(path)) 
//    {
//        std::cout << "Failed to load: " << path << "\n";
//        return;
//    }
//
//    top.setTexture(_textureStatic);
//    bottom.setTexture(_textureStatic);
//}


void StaticMesh::DrawTop(sf::RenderWindow& window, Shader& shader) {

    shader.setUniform("spritePos", top.getPosition());

    sf::RenderStates states;
    states.shader = &shader;
    states.blendMode = sf::BlendAlpha;

    window.draw(top, states);
}

void StaticMesh::DrawBottom(sf::RenderWindow& window) {
    window.draw(bottom);
}

Sprite& StaticMesh::SpriteTop() { return this->top; }
Sprite& StaticMesh::SpriteBottom() { return this->bottom; }


FloatRect StaticMesh::GetMapBounds() const {
    return this->_bounds;
}

Vector2f StaticMesh::GetPosition() const {
    return this->top.getPosition();
}

Vector2f StaticMesh::GetCenter(GetCenterOptions option) const
{
    if (option == GetCenterOptions::Actual)
    {
        FloatRect bounds = this->bottom.getGlobalBounds();
        return {
            bounds.left + bounds.width / 2.f,
            bounds.top + bounds.height
        };
    }
    else if (option == GetCenterOptions::Bottom)
    {
        FloatRect bounds = this->bottom.getGlobalBounds();
        return {
            bounds.left + bounds.width / 2.f,
            bounds.top + bounds.height / 2.f
        };
    }
    else
    {
        FloatRect bounds = this->top.getGlobalBounds();
        return {
            bounds.left + bounds.width / 2.f,
            bounds.top + bounds.height / 2.f
        };
    }

}



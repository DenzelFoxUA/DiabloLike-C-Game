
#pragma once
#include <vector>
#include <map>
#include <memory>
#include "Projectile.h"
#include "BaseUnit.h"


using namespace std;
using namespace sf;



class ProjectilesContainer
{
protected:
    vector<unique_ptr<IProjectileObject>> projectiles;

public:

    void AddProjectile(std::unique_ptr<IProjectileObject> projectile)
    {
        cout << "Projectile added!" << endl;
        projectiles.emplace_back(std::move(projectile));
    }
    
    
    void Update(float deltaTime, const std::vector<IBaseUnit*>& enemies)
    {
        for (auto it = projectiles.begin(); it != projectiles.end(); )
        {
            auto& proj = *it;

            if (proj->IsDead())
            {
                it = projectiles.erase(it);
                continue;
            }

            for (const auto& enemy : enemies)
            {
                if (!enemy->IsDead() && Distance(enemy->GetCenter(), proj->GetPosition()) <= proj->GetHitRadius())
                {
                    proj->ApplyDamageTo(enemy->GetEntity());
                    cout << "Arrow hit target with " << proj->GetDamage() << " damage!" << endl;
                    proj->MarkToDestroy();
                    break;
                }
            }

            proj->Update(deltaTime);
            ++it;
        }
    }

    void DrawAll(sf::RenderWindow& window)
    {
        for (auto& proj : projectiles)
            proj->Draw(window);
    }

private:
    float Distance(const sf::Vector2f& a, const sf::Vector2f& b) const
    {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
};

#include "LadyArcherController.h"

Vector2f LadyArcherController::Shot()
{
    return this->characterMesh.PendingDirection();
}

Vector2f LadyArcherController::ShotCharged()
{
    return this->characterMesh.PendingDirection();
}

//void LadyArcherController::Shoot(sf::Texture& arrowTexture, sf::Vector2f direction)
//{
//    equipedArrow.IsCharged() = false;
//    sf::Vector2f center = this->characterMesh.GetCenter();
//
//    auto mesh = std::make_unique<ArrowMesh>(arrowTexture, center, direction, 250.f, 6.f);
//    auto arrow = std::make_unique<Arrow>(equipedArrow); // копія
//
//    arrowControllers.emplace_back(std::make_unique<ArrowController>(
//        std::move(*mesh),
//        std::move(*arrow)
//    ));
//
//}

//void LadyArcherController::ShootCharged(sf::Texture& texture, sf::Vector2f direction, float charge)
//{
//    sf::Vector2f center = this->characterMesh.GetCenter();
//    ArrowMesh arrowMesh(texture, center, direction, 350.f, 8.f);
//    equipedArrow.IsCharged() = true;
//    arrowControllers.emplace_back(arrowMesh, equipedArrow);
//
//}

//void LadyArcherController::ShootCharged(sf::Texture& texture, sf::Vector2f direction, float charge)
//{
//    equipedArrow.IsCharged() = true;
//    equipedArrow.SetDamage(equipedArrow.GetDamage() + charge * 10.f); // приклад
//
//    sf::Vector2f center = this->characterMesh.GetCenter();
//
//    auto mesh = std::make_unique<ArrowMesh>(texture, center, direction, 250.f, 6.f);
//    auto arrow = std::make_unique<Arrow>(equipedArrow); // копія
//
//    arrowControllers.emplace_back(std::make_unique<ArrowController>(
//        std::move(*mesh),
//        std::move(*arrow)
//    ));
//
//}


void LadyArcherController::HandleInput(float deltaTime)
{
    PlayerController::HandleInput(deltaTime);

    if (characterMesh.IsChargingAttack()) {
        float& chargeTime = characterMesh.ChargeTime();
        chargeTime += deltaTime;
        if (chargeTime > characterMesh.MaxChargeTime())
            chargeTime = characterMesh.MaxChargeTime();
    }
}

void LadyArcherController::HandleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    bool& isAttacking = characterMesh.IsAttacking();
    bool& shotAlreadyCharged = characterMesh.IsCharged();
    bool& chargingShot = characterMesh.IsChargingAttack();
    float& chargeTime = characterMesh.ChargeTime();
    float& attackTimer = characterMesh.AttackTimer();
    bool& pendingNormalShot = characterMesh.PendingNormalAttack();
    bool& pendingChargedShot = characterMesh.PendingChargedAttack();
    float& pendingChargeTime = characterMesh.PendingChargeTime();
    Vector2f& pendingDirection = characterMesh.PendingDirection();

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (!isAttacking) {
            isAttacking = true;
            chargingShot = true;
            chargeTime = 0.f;
            shotAlreadyCharged = false;
            attackTimer = 0.f;

            characterMesh.CurrentState() = CharacterState::Attack;
            auto& dir = characterMesh.CurrentDir();

            const auto& meta = characterMesh.TextureData(TextureCategory::Attack);

            characterMesh.Animation().SetSheet(
                &characterMesh.AttackTextures()[dir],
                meta.frameWidth,
                meta.frameHeight,
                meta.numberOfColumns,
                meta.numberOfFrames,
                false);
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        if (chargingShot) {
            chargingShot = false;
            shotAlreadyCharged = false;

            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f direction = mousePos - characterMesh.GetCenter();

            if (chargeTime < 2.0f) {
                pendingNormalShot = true;
            }
            else {
                pendingChargedShot = true;
                pendingChargeTime = chargeTime;
            }

            pendingDirection = direction;

            // Повернути анімацію до нормального стану
            characterMesh.Animation().Resume();
        }
    }

}

void LadyArcherController::Update(float deltaTime, const sf::RenderWindow& window/*, CharacterMesh& targetMesh, Character& target*/)
{
    
    characterMesh.Update(deltaTime, window);

    //float& chargeTime = characterMesh.ChargeTime();
    //
    //bool& chargingShot = characterMesh.IsChargingAttack();

    //if (chargingShot) {
    //    
    //    chargeTime += deltaTime;
    //    if (chargeTime >= 2.0f) {
    //        characterMesh.Animation().FreezeOnMidFrame();
    //    }
    //}

    //if (characterMesh.IsAttacking() && characterMesh.Animation().IsFinished()) {
    //    if (characterMesh.PendingNormalAttack()) {
    //        Shoot(characterMesh.GetProjectileTexture(), characterMesh.PendingDirection());
    //        characterMesh.PendingNormalAttack() = false;
    //    }
    //    else if (characterMesh.PendingChargedAttack()) {
    //        ShootCharged(characterMesh.GetProjectileTexture(), characterMesh.PendingDirection(), characterMesh.PendingChargeTime());
    //        characterMesh.PendingChargedAttack() = false;
    //    }

    //    characterMesh.IsAttacking() = false;
    //    characterMesh.CurrentState() = CharacterState::Idle;
    //    characterMesh.Animation().Resume();
    //}



}

//
//void LadyArcherController::UpdateArrows(float deltaTime, const sf::RenderWindow& window, std::vector<IController*> targets)
//{
//    //for (auto it = arrowControllers.begin(); it != arrowControllers.end(); )
//    //{
//    //    auto& arrow = *it;
//    //    arrow->Update(deltaTime);
//    //    if (arrow->IsDead()) {
//    //        it = arrowControllers.erase(it);
//    //        continue;
//    //    }
//
//    //    for (auto& target : targets)
//    //    {
//    //        if (target->IsDead()) continue;
//
//    //        arrow->HandleBehavior(target->GetCenter(), target->GetEntity(), deltaTime);
//    //    }
//
//    //    ++it;
//    //}
//    for (auto it = arrowControllers.begin(); it != arrowControllers.end(); )
//    {
//        auto& arrow = *it;
//
//        bool arrowDied = false;
//
//        for (auto& target : targets)
//        {
//            if (target->IsDead()) continue;
//
//            if (arrow->IsDead()) {
//                arrowDied = true;
//                break; // перестаємо перевіряти інших ворогів
//            }
//
//            arrow->HandleBehavior(target->GetCenter(), target->GetEntity(), deltaTime);
//        }
//
//        if (!arrowDied && !arrow->IsDead())
//        {
//            arrow->Update(deltaTime);
//            ++it;
//        }
//        else
//        {
//            std::cout << "Arrow destroyed!\n";
//            it = arrowControllers.erase(it);
//        }
//    }
//}



//void LadyArcherController::Draw(sf::RenderWindow& window)
//{
//    characterMesh.Draw(window);
//    for (auto& ctrl : arrowControllers)
//    {
//        if (!ctrl.IsDead())
//        {
//            cout << "Drawed in archer controller!" << endl;
//            ctrl.Draw(window);
//        }
//            
//    }
//}

void LadyArcherController::Draw(sf::RenderWindow& window)
{
    characterMesh.Draw(window);

    //for (auto& arrow : arrowControllers)
    //{
    //    arrow->Draw(window);
    //}
}


void LadyArcherController::HandleBehavior(sf::Vector2f target, Character& enemy, float deltaTime)
{
    // Поки порожній — гравець сам себе контролює
}

Character& LadyArcherController::GetEntity()
{
    return this->characterEntity;
}

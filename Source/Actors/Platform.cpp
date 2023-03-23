#include "../Actors/Ability.h"
#include "../Components/AnimSpriteComponent.h"
#include "../Actors/Ball.h"
#include  "../GameMode/Game.h"
#include "../Actors/Laser.h"
#include "../Math/Math.h"
#include "../Actors/Platform.h"
#include "../Renderer/Renderer.h"
#include "../Window/Window.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureManager.h"
#include "../Components/SpriteComponent.h"

Platform::Platform(Game* game)
    : Actor(game)
    , mDirection(0)
    , mLaserCooldown(0.0f)
{
    Texture* texture = game->GetTextureManager()->GetTexture("Data/50-Breakout-Tiles.png");
    AnimSpriteComponent* animSpriteComponent = new AnimSpriteComponent(this);
    mDefaultAnimsprites = {
        texture,
        game->GetTextureManager()->GetTexture("Data/51-Breakout-Tiles.png"),
        game->GetTextureManager()->GetTexture("Data/52-Breakout-Tiles.png")
    };
    animSpriteComponent->SetAnimTextures(mDefaultAnimsprites);
    SetScale(0.24f);
    SetHeight(static_cast<float>(texture->GetTextureHeight()));
    SetWidth(static_cast<float>(texture->GetTextureWidth()));
    mSpeed = cDefaultSpeed;
}

Platform::~Platform()
{
    mGainedAbility.clear();
}

void Platform::ReturnDefaultAnimsprites()
{
    GetComponentOfType<AnimSpriteComponent>(TypeID::TAnimSpriteComponent)->SetAnimTextures(mDefaultAnimsprites);
    if (Texture* texture = GetGame()->GetTextureManager()->GetTexture("Data/50-Breakout-Tiles.png"))
    {
        SetHeight(static_cast<float>(texture->GetTextureHeight()));
        SetWidth(static_cast<float>(texture->GetTextureWidth()));
    }
}

void Platform::UpdateActor(float deltaTime)
{
    UpdateGainedAbilities(deltaTime);

    float screenWidth = GetGame()->GetWindow()->GetScreenWidth();
    float screenHeight = GetGame()->GetWindow()->GetScreenHeight();

    Vector2D position = GetPosition();
    position.mX += mDirection * mSpeed * deltaTime;
    float halfWidth = GetWidth()/ 2.0f;
    if (position.mX <= halfWidth)
    {
        position.mX = halfWidth;
    }
    else if (position.mX >= screenWidth - halfWidth)
    {
        position.mX = screenWidth - halfWidth;
    }

    SetPosition(position);
}

void Platform::ProcessKeyboard(const uint8_t* state)
{
    mDirection = 0;
    if (state[SDL_SCANCODE_RIGHT])
    {
        mDirection += 1;
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        mDirection -= 1;
    }
    if (state[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f && ShootingAbility())
    {
        Vector2D platformPosition;
        Platform* platform = GetGame()->GetPlatform();
        platformPosition = platform->GetPosition();

        Laser* laserOne = new Laser(GetGame());
        Vector2D positionFitstLaser;
        positionFitstLaser.mX = platformPosition.mX + (platform->GetWidth() / 2) - laserOne->GetWidth();
        positionFitstLaser.mY = platformPosition.mY - (platform->GetHeight() / 2) - laserOne->GetHeight() / 2;
        laserOne->SetPosition(positionFitstLaser);

        Laser* laserSecond = new Laser(GetGame());
        Vector2D positionSecondLaser;
        positionFitstLaser.mX = platformPosition.mX - (platform->GetWidth() / 2) + laserSecond->GetWidth();
        positionFitstLaser.mY = platformPosition.mY - (platform->GetHeight() / 2) - laserSecond->GetHeight() / 2;

        laserSecond->SetPosition(positionFitstLaser);

        mLaserCooldown = 0.9f;
    }
}

bool Platform::ShootingAbility()
{
    for (size_t i = 0; i < mGainedAbility.size(); i++)
    {
        if (mGainedAbility[i].mAbilityType == AbilityType::Shooting)
        {
            return true;
        }
    }
    return false;
}

void Platform::GainAbility(AbilityType mAbilityType)
{
    GainedAbility gainedAbility;
    gainedAbility.mAbilityType = mAbilityType;
    gainedAbility.mLifeSpan = 20;

    TextureManager* textureManager = GetGame()->GetTextureManager();

    float newSpeed = mSpeed;
    if (gainedAbility.mAbilityType == AbilityType::IncreaseSpeed)
    {
        const float maxSpeed = cDefaultSpeed * 2.0f;
        newSpeed = mSpeed * Ability::GetVelocityIncreased();
        newSpeed = Math::Min(newSpeed, maxSpeed);
        gainedAbility.mSpeedChange = newSpeed - mSpeed;
    }
    else if (gainedAbility.mAbilityType == AbilityType::DecreaseSpeed)
    {
        const float minSpeed = cDefaultSpeed * 0.5f;
        newSpeed = mSpeed * Ability::GetVelocityDecreased();
        newSpeed = Math::Max(newSpeed, minSpeed);
        gainedAbility.mSpeedChange = mSpeed - newSpeed;
    }
    else if (gainedAbility.mAbilityType == AbilityType::ExtensionPlatform)
    {
        std::vector<Texture*> animsprites = {
            textureManager->GetTexture("Data/65-Breakout-Tiles.png"),
            textureManager->GetTexture("Data/66-Breakout-Tiles.png"),
            textureManager->GetTexture("Data/67-Breakout-Tiles.png")
        };
        GetComponentOfType<AnimSpriteComponent>(TypeID::TAnimSpriteComponent)->SetAnimTextures(animsprites);
        if (Texture* texture = textureManager->GetTexture("Data/65-Breakout-Tiles.png"))
        {
            SetHeight(static_cast<float>(texture->GetTextureHeight()));
            SetWidth(static_cast<float>(texture->GetTextureWidth()));
        }

        auto RemoveFrom = std::remove_if(mGainedAbility.begin(), mGainedAbility.end(), [](const GainedAbility& gainedAbility) { return gainedAbility.mAbilityType == AbilityType::Shooting; });
        mGainedAbility.erase(RemoveFrom, mGainedAbility.end());
    }
    else if (gainedAbility.mAbilityType == AbilityType::ConstrictionPlatform)
    {
        std::vector<Texture*> animsprites = {
            textureManager->GetTexture("Data/57-Breakout-Tiles.png")
        };
        GetComponentOfType<AnimSpriteComponent>(TypeID::TAnimSpriteComponent)->SetAnimTextures(animsprites);
        if (Texture* texture = textureManager->GetTexture("Data/57-Breakout-Tiles.png"))
        {
            SetHeight(static_cast<float>(texture->GetTextureHeight()));
            SetWidth(static_cast<float>(texture->GetTextureWidth()));
        }

        auto RemoveFrom = std::remove_if(mGainedAbility.begin(), mGainedAbility.end(), [](const GainedAbility& gainedAbility) { return gainedAbility.mAbilityType == AbilityType::Shooting; });
        mGainedAbility.erase(RemoveFrom, mGainedAbility.end());
    }
    else if (gainedAbility.mAbilityType == AbilityType::Shooting)
    {
        std::vector<Texture*> animsprites = {
            textureManager->GetTexture("Data/53-Breakout-Tiles.png"),
            textureManager->GetTexture("Data/54-Breakout-Tiles.png"),
            textureManager->GetTexture("Data/55-Breakout-Tiles.png"),
        };
        GetComponentOfType<AnimSpriteComponent>(TypeID::TAnimSpriteComponent)->SetAnimTextures(animsprites);
        if (Texture* texture = textureManager->GetTexture("Data/53-Breakout-Tiles.png"))
        {
            SetHeight(static_cast<float>(texture->GetTextureHeight()));
            SetWidth(static_cast<float>(texture->GetTextureWidth()));
        }
    }
    mSpeed = newSpeed;

    mGainedAbility.push_back(gainedAbility);
}

void Platform::UpdateGainedAbilities(float deltaTime)
{
    if (!GetGame()->GetBall()->IsLaunched() && mGainedAbility.size() != 0)
    {
        for (size_t i = 0; i < mGainedAbility.size(); i++)
        {
            if (mGainedAbility[i].mAbilityType == AbilityType::ExtensionPlatform || mGainedAbility[i].mAbilityType == AbilityType::ConstrictionPlatform || mGainedAbility[i].mAbilityType == AbilityType::Shooting)
            {
                ReturnDefaultAnimsprites();
            }
            else
            {
                mSpeed = cDefaultSpeed;
            }
        }
        mGainedAbility.clear();
    }
    else
    {
        mLaserCooldown -= deltaTime;
        int platformChangingAbilitiesCount = 0;
        for (size_t i = 0; i < mGainedAbility.size(); i++)
        {
            if (mGainedAbility[i].mAbilityType == AbilityType::ExtensionPlatform || mGainedAbility[i].mAbilityType == AbilityType::ConstrictionPlatform || mGainedAbility[i].mAbilityType == AbilityType::Shooting)
            {
                platformChangingAbilitiesCount++;
            }
        }
        for (size_t i = 0; i < mGainedAbility.size(); i++)
        {
            mGainedAbility[i].mLifeSpan -= deltaTime;
            if (mGainedAbility[i].mLifeSpan <= 0)
            {
                if (mGainedAbility[i].mAbilityType == AbilityType::IncreaseSpeed)
                {
                    mSpeed = mSpeed - mGainedAbility[i].mSpeedChange;
                }
                else if (mGainedAbility[i].mAbilityType == AbilityType::DecreaseSpeed)
                {
                    mSpeed = mSpeed + mGainedAbility[i].mSpeedChange;
                }
                else if (platformChangingAbilitiesCount <= 1)
                {
                    ReturnDefaultAnimsprites();
                }
            }
        }

        auto RemoveFrom = std::remove_if(mGainedAbility.begin(), mGainedAbility.end(), [](const GainedAbility& gainedAbility) { return gainedAbility.mLifeSpan <= 0; });
        mGainedAbility.erase(RemoveFrom, mGainedAbility.end());
    }
}

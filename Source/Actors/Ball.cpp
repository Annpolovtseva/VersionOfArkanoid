#include "../Actors/Ball.h"
#include "../Actors/Block.h"
#include "../Math/Collision.h"
#include  "../GameMode/Game.h"
#include "../GameMode/GameMode.h"
#include "../Actors/Platform.h"
#include "../Renderer/Renderer.h"
#include "../Window/Window.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureManager.h"
#include "../Components/SpriteComponent.h"

Ball::Ball(Game* game)
    : Actor(game)
    , mVelocity(0.0f, 0.0f)
    , mCaught(false)
    , mLaunched(false)
{
    SpriteComponent* sprite = new SpriteComponent(this, 100);
    Texture* texture = game->GetTextureManager()->GetTexture("Data/58-Breakout-Tiles.png");
    sprite->SetTexture(texture);
    SetScale(0.125f);
    SetHeight(static_cast<float>(texture->GetTextureHeight()));
    SetWidth(static_cast<float>(texture->GetTextureWidth()));
}

Ball::~Ball()
{
}

void Ball::UpdateActor(float deltaTime)
{
    float screenWidth = GetGame()->GetWindow()->GetScreenWidth();
    float screenHeight = GetGame()->GetWindow()->GetScreenHeight();

    Vector2D ballPosition = GetPosition();

    const Vector2D size(116.39f, 30.719f);

    Vector2D platformPosition = GetPosition();
    Vector2D platformSize = size;

    float platformHalfWidth = platformSize.mX / 2.0f;;
    float platformHalfHeight = platformSize.mY / 2.0f;

    if (Platform* platform = GetGame()->GetPlatform())
    {
        platform = GetGame()->GetPlatform();
        platformPosition = platform->GetPosition();
        platformSize = platform->GetSize();

        platformHalfWidth = platform->GetWidth() / 2.0f;;
        platformHalfHeight = platform->GetHeight() / 2.0f;
    }

    if (!mLaunched)
    {
        ballPosition.mX = platformPosition.mX;
        ballPosition.mY = platformPosition.mY - platformHalfHeight - GetWidth() / 2.0f;
    }
    else
    {
        ballPosition.mX += mVelocity.mX * deltaTime;
        ballPosition.mY += mVelocity.mY * deltaTime;

        float ballRadius = GetWidth() / 2.0f;

        const float MinPossibleX = ballRadius;
        const float MaxPossibleX = screenWidth - ballRadius;
        const float MinPossibleY = ballRadius;

        if (ballPosition.mX <= MinPossibleX && mVelocity.mX < 0.0f)
        {
            mVelocity.mX *= -1;
            ballPosition.mX = MinPossibleX;
        }
        else if (ballPosition.mX >= MaxPossibleX && mVelocity.mX > 0.0f)
        {
            mVelocity.mX *= -1;
            ballPosition.mX = MaxPossibleX;
        }
        else if (ballPosition.mY <= MinPossibleY && mVelocity.mY < 0.0f)
        {
            mVelocity.mY *= -1;
            ballPosition.mY = MinPossibleY;
        }

        for (Block* block : GetGame()->GetBlocks())
        {
            if (block == nullptr)
            {
                continue;
            }
            CollisionResult result = CheckCollisionCircleToRectangle(ballPosition, ballRadius, block->GetPosition(), block->GetSize());
            if (result.objectsCollided)
            {
                block->TakeDamage();

                if (result.direction == Direction::LEFT || result.direction == Direction::RIGHT)
                {
                    mVelocity.mX = -mVelocity.mX;

                    float penetration = ballRadius - std::abs(result.collisionVector.mX);
                    if (result.direction == Direction::LEFT)
                    {
                        ballPosition.mX += penetration;
                    }
                    else
                    {
                        ballPosition.mX -= penetration;
                    }
                }
                else
                {
                    mVelocity.mY = -mVelocity.mY;

                    float penetration = ballRadius - std::abs(result.collisionVector.mY);
                    if (result.direction == Direction::UP)
                    {
                        ballPosition.mY += penetration;
                    }
                    else
                    {
                        ballPosition.mY -= penetration;
                    }
                }

                if (block->GetHealth() == 0)
                {
                    mVelocity = mVelocity * cVelocityDecreased;
                    if (mVelocity.GetLength() < cDefaultVelocity * 0.5f)
                    {
                        mVelocity.Normalize();
                        mVelocity = mVelocity * (cDefaultVelocity * 0.5f);
                    }
                }
            }
            if (block->GetHealth() <= 0)
            {
                block->SetState(State::EDead);
            }
        }

        CollisionResult result = CheckCollisionCircleToRectangle(ballPosition, ballRadius, platformPosition, platformSize);
        if (result.objectsCollided)
        {
            if (GetGame()->GetGameMode()->IsAllBlocksDestroyed())
            {
                mVelocity = Vector2D{ 0.0f, 0.0f };
                mCaught = true;
            }
            else
            {
                float distance = ballPosition.mX - platformPosition.mX;
                float percentage = distance / platformHalfWidth;

                const float strength = 1.732f;
                Vector2D oldVelocity = mVelocity;
                mVelocity.mX = std::abs(mVelocity.mY) * percentage * strength;
                mVelocity.Normalize();
                mVelocity = mVelocity * oldVelocity.GetLength();

                mVelocity.mY = -1.0f * std::abs(mVelocity.mY);
                mVelocity = mVelocity * cVelocityIncreased;
                if (mVelocity.GetLength() > cDefaultVelocity * 3.0f)
                {
                    mVelocity.Normalize();
                    mVelocity = mVelocity * (cDefaultVelocity * 3.0f);
                }
            }
        }
    }

    if (mCaught)
    {
        ballPosition.mX = platformPosition.mX;
        ballPosition.mY = platformPosition.mY - platformHalfHeight - GetWidth() / 2.0f;
    }
    SetPosition(ballPosition);
}

void Ball::ActorInput(const uint8_t* keyState)
{
}

Vector2D Ball::GetVelocity()
{
    return mVelocity;
}

bool Ball::IsCaught()
{
    return mCaught;
}

void Ball::SetVelocity(Vector2D velocity)
{
    mVelocity = velocity;
}

bool Ball::IsLaunched()
{
    return mLaunched;
}

float Ball::GetDefaultVelocity()
{
    return cDefaultVelocity;
}

void Ball::SetLaunched(bool launched)
{
    mLaunched = launched;
}
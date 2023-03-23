#pragma once

#include <vector>
#include <string>
#include "../Components/Component.h"
#include "../Math/Vector2D.h"

class Component;
class Game;

class Actor
{
public:
    enum class State
    {
        EActive,
        EPaused,
        EDead
    };

    Actor(Game* game);
    virtual ~Actor();

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    virtual void ActorInput(const uint8_t* keyState);

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    Component* GetComponentOfType(TypeID type);
    template<typename T>
    T* GetComponentOfType(TypeID type)
    {
        if (Component* component = GetComponentOfType(type))
        {
            return static_cast<T*>(component);
        }
        return nullptr;
    }

    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }

    void SetPosition(const Vector2D& pos) { mPosition = pos; }
    const Vector2D& GetPosition() const { return mPosition; }

    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }

    float GetHeight() const { return mHeight; }
    void SetHeight(float heigth) { mHeight = heigth * mScale; }
    float GetWidth() const { return mWidth; }
    void SetWidth(float width) { mWidth = width * mScale; }
    Vector2D GetSize() const { return Vector2D(mWidth, mHeight); }

    Game* GetGame() { return mGame; }

private:
    std::vector<class Component*> mComponents;

    Game* mGame;
    Vector2D mPosition;
    State mState;

    float mScale = 0.0f;
    float mHeight = 0.0f;
    float mWidth = 0.0f;
};
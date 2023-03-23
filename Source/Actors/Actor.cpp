#include "../Actors/Actor.h"
#include "../Components/Component.h"
#include "../GameMode/Game.h"

Actor::Actor(Game* game)
    : mState(State::EActive)
    , mPosition(0.0f, 0.0f)
    , mScale(1.0f)
    , mGame(game)
    , mWidth(0.0f)
    , mHeight(0.0f)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);

    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime)
{
    if (mState == State::EActive)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime)
{
    for (auto comp : mComponents)
    {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::AddComponent(Component* component)
{
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (;
        iter != mComponents.end();
        ++iter)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }

    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}

Component* Actor::GetComponentOfType(TypeID type)
{
    Component* temp = nullptr;
    for (Component* component : mComponents)
    {
        if (component->GetType() == type)
        {
            temp = component;
            break;
        }
    }
    return temp;
}
#pragma once

class Actor;

enum class TypeID
{
    TComponent,
    TSpriteComponent,
    TAnimSpriteComponent,
    TBGSpriteComponent
};

class Component
{
public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();

    virtual void Update(float deltaTime);

    int GetUpdateOrder() const { return mUpdateOrder; }

    virtual TypeID GetType() const = 0;

protected:
    Actor* mOwner;
    int mUpdateOrder;
};

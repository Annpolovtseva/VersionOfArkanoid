#pragma once
#include "../Math/Math.h"
#include "../Math/Vector2D.h"

enum class Direction
{
    DOWN,
    RIGHT,
    UP,
    LEFT
};

static Direction VectorDirection(Vector2D target)
{
    Vector2D axes[] =
    {
        Vector2D(0.0f, 1.0f),
        Vector2D(1.0f, 0.0f),
        Vector2D(0.0f, -1.0f),
        Vector2D(-1.0f, 0.0f)
    };
    float max = 0.0f;
    unsigned int bestMatch = -1;

    target.Normalize();
    for (unsigned int i = 0; i < 4; i++)
    {
        float dotProduct = Vector2D::Dot(target, axes[i]);
        if (dotProduct > max)
        {
            max = dotProduct;
            bestMatch = i;
        }
    }
    return (Direction)bestMatch;
}

struct CollisionResult
{
    Direction direction = Direction::DOWN;
    Vector2D collisionVector;
    bool objectsCollided = false;
};

static CollisionResult CheckCollisionCircleToRectangle(Vector2D circlePosition, float circleRadius, Vector2D rectanglePosition, Vector2D rectangleSize)
{
    Vector2D rectangleCentreToCircleCentre = circlePosition - rectanglePosition;

    float rectangleHalfWidth = rectangleSize.mX / 2.0f;
    float rectangleHalfHeight = rectangleSize.mY / 2.0f;
    rectangleCentreToCircleCentre.mX = Math::Clamp(rectangleCentreToCircleCentre.mX, -rectangleHalfWidth, rectangleHalfWidth);
    rectangleCentreToCircleCentre.mY = Math::Clamp(rectangleCentreToCircleCentre.mY, -rectangleHalfHeight, rectangleHalfHeight);

    Vector2D closestPointOnRectangle = rectanglePosition + rectangleCentreToCircleCentre;

    Vector2D circleCentreToClosestPoint = closestPointOnRectangle - circlePosition;

    CollisionResult result;
    result.objectsCollided = circleCentreToClosestPoint.GetLength() < circleRadius;
    if (result.objectsCollided)
    {
        result.direction = VectorDirection(circleCentreToClosestPoint);
        result.collisionVector = circleCentreToClosestPoint;
    }

    return result;
}

static bool CollisionRectangleToRectangle(Vector2D rectPosition1, Vector2D rectSize1, Vector2D rectPosition2, Vector2D rectSize2)
{
    Vector2D rectHalfSize1 = Vector2D(rectSize1.mX / 2.0f, rectSize1.mY / 2.0f);
    Vector2D rectHalfSize2 = Vector2D(rectSize2.mX / 2.0f, rectSize2.mY / 2.0f);

    bool collisionX = rectPosition1.mX - rectHalfSize1.mX < rectPosition2.mX + rectHalfSize2.mX && rectPosition1.mX + rectHalfSize1.mX > rectPosition2.mX - rectHalfSize2.mX;
    bool collisionY = rectPosition1.mY - rectHalfSize1.mY < rectPosition2.mY + rectHalfSize2.mY && rectPosition1.mY + rectHalfSize1.mY > rectPosition2.mY - rectHalfSize2.mY;

    return collisionX && collisionY;
}
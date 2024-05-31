#include "Ragdoll.h"

Ragdoll::Ragdoll(b2World* world, b2Vec2 position)
{
    float headRadius = 0.7f;
    float torsoWidth = 1.0f;
    float torsoHeight = 4.0f;
    float limbWidth = 0.5f;
    float limbHeight = 3.0f;

    b2Body* head = Box2DHelper::CreateCircularDynamicBody(world, headRadius, 1.0f, 0.3f, 0.3f);
    head->SetTransform(position, 0.0f);

    b2Body* torso = Box2DHelper::CreateRectangularDynamicBody(world, torsoWidth, torsoHeight, 1.0f, 0.3f, 0.3f);
    torso->SetTransform(position + b2Vec2(0.0f, -torsoHeight / 2), 0.0f);

    b2Body* leftArm = Box2DHelper::CreateRectangularDynamicBody(world, limbWidth, limbHeight, 1.0f, 0.3f, 0.3f);
    leftArm->SetTransform(position + b2Vec2(-torsoWidth / 2 - limbWidth / 2, -torsoHeight / 4), 0.0f);

    b2Body* rightArm = Box2DHelper::CreateRectangularDynamicBody(world, limbWidth, limbHeight, 1.0f, 0.3f, 0.3f);
    rightArm->SetTransform(position + b2Vec2(torsoWidth / 2 + limbWidth / 2, -torsoHeight / 4), 0.0f);

    b2Body* leftLeg = Box2DHelper::CreateRectangularDynamicBody(world, limbWidth, limbHeight, 1.0f, 0.3f, 0.3f);
    leftLeg->SetTransform(position + b2Vec2(-torsoWidth / 4, -torsoHeight - limbHeight / 2), 0.0f);

    b2Body* rightLeg = Box2DHelper::CreateRectangularDynamicBody(world, limbWidth, limbHeight, 1.0f, 0.3f, 0.3f);
    rightLeg->SetTransform(position + b2Vec2(torsoWidth / 4, -torsoHeight - limbHeight / 2), 0.0f);

    Box2DHelper::CreateRevoluteJoint(world, torso, torso->GetWorldCenter() + b2Vec2(0.0f, torsoHeight / 2), head,
        -0.5f * b2_pi, 0.5f * b2_pi, 0.0f, 0.0f, false, true);

    Box2DHelper::CreateRevoluteJoint(world, torso, torso->GetWorldCenter() + b2Vec2(-torsoWidth / 2, 0.0f), leftArm,
        -0.5f * b2_pi, 0.5f * b2_pi, 0.0f, 0.0f, false, true);

    Box2DHelper::CreateRevoluteJoint(world, torso, torso->GetWorldCenter() + b2Vec2(torsoWidth / 2, 0.0f), rightArm,
        -0.5f * b2_pi, 0.5f * b2_pi, 0.0f, 0.0f, false, true);

    Box2DHelper::CreateRevoluteJoint(world, torso, torso->GetWorldCenter() + b2Vec2(-torsoWidth / 4, -torsoHeight / 2), leftLeg,
        -0.5f * b2_pi, 0.5f * b2_pi, 0.0f, 0.0f, false, true);

    Box2DHelper::CreateRevoluteJoint(world, torso, torso->GetWorldCenter() + b2Vec2(torsoWidth / 4, -torsoHeight / 2), rightLeg,
        -0.5f * b2_pi, 0.5f * b2_pi, 0.0f, 0.0f, false, true);
}
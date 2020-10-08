#pragma once

#include <autogen/InnerNet/InnerNetObject.hpp>
#include <autogen/UnityEngine/Vector2.hpp>
#include <autogen/UnityEngine/Rigidbody2D.hpp>

struct CustomNetworkTransform : InnerNet::InnerNetObject {
    struct FloatRange_o *XRange;
    struct FloatRange_o *YRange;
    float sendInterval;
    float snapThreshold;
    float interpolateMovement;
    UnityEngine::Rigidbody2D* body;
    UnityEngine::Vector2 targetSyncPosition;
    UnityEngine::Vector2 targetSyncVelocity;
    std::uint16_t lastSequenceId;
    UnityEngine::Vector2 prevPosSent;
    UnityEngine::Vector2 prevVelSent;
};
CHECK_TYPE(CustomNetworkTransform, 0x58);
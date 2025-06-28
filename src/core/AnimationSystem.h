#pragma once

#include <cstdint>
#include <functional>

// Forward declarations for animation library types, we do this to
// reduce compile time dependencies.
namespace ozz {
namespace animation {
class Skeleton;
class Animation;
namespace sample {
struct PlaybackController;
}  // namespace sample
}  // namespace animation
}  // namespace ozz

class AnimationSystem {
   public:
    // Entity identifier
    using Entity = uint32_t;

    // Resource handles
    using SkeletonHandle = uint32_t;
    using AnimationHandle = uint32_t;

    // Blend mode for animations
    enum class BlendMode {
        Replace,  // Completely replaces the current pose
        Additive  // Adds on top of the current pose
    };

    // Joint pose data (output to renderer)
    struct JointPose {
        float matrix[16];  // 4x4 transformation matrix in column-major order
    };

    // Animation blend weight type
    using BlendWeight = float;

    // Animation event type
    enum class EventType { None, Start, End, Custom };

    // Animation event callback data
    struct EventData {
        Entity entity;
        AnimationHandle animation;
        EventType type;
        uint32_t customEventId;  // Only valid if type == EventType::Custom
        float normalizedTime;    // 0.0f to 1.0f
    };

    // Callback type for animation events (using std::function for flexibility)
    using EventCallback = std::function<void(const EventData&)>;

    virtual ~AnimationSystem() = default;

    // ================= Lifecycle Management =================
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;

    // ================= Resource Management =================
    virtual SkeletonHandle LoadSkeleton(const char* path) = 0;
    virtual AnimationHandle LoadAnimation(const char* path) = 0;
    virtual void UnloadSkeleton(SkeletonHandle handle) = 0;
    virtual void UnloadAnimation(AnimationHandle handle) = 0;

    // ================= Entity Management =================
    virtual Entity CreateEntity(SkeletonHandle skeleton) = 0;
    virtual void DestroyEntity(Entity entity) = 0;

    // ================= Animation Control =================
    virtual void PlayAnimation(Entity entity, AnimationHandle animation,
                               BlendMode mode = BlendMode::Replace) = 0;
    virtual void StopAnimation(Entity entity) = 0;
    virtual void SetPlaybackSpeed(Entity entity, float speed) = 0;
    virtual void SetLooping(Entity entity, bool loop) = 0;
    virtual void SetTimeRatio(Entity entity, float ratio) = 0;  // 0.0 to 1.0

    // ================= Advanced Animation Control =================
    // Multiple animation blending
    virtual void BlendAnimation(Entity entity, AnimationHandle animation, BlendWeight weight,
                                BlendMode mode = BlendMode::Replace) = 0;
    virtual void ClearAnimations(Entity entity) = 0;

    // Animation event registration
    virtual void RegisterEventCallback(Entity entity, EventCallback callback) = 0;
    virtual void UnregisterEventCallback(Entity entity) = 0;

    // ================= Core Update =================
    virtual void Update(float delta_time) = 0;

    // ================= Data Access Interface =================
    // Primary interface for render system integration
    virtual const JointPose* GetJointPoses(Entity entity) const = 0;
    virtual uint32_t GetJointCount(Entity entity) const = 0;

    // ================= Animation Information =================
    virtual float GetAnimationDuration(AnimationHandle animation) const = 0;
    virtual uint32_t GetAnimationNumTracks(AnimationHandle animation) const = 0;

    // ================= Skinning Support =================
    // Get inverse bind pose matrices for skinning
    virtual const float* GetInverseBindPoseMatrix(Entity entity, uint32_t joint_index) const = 0;

    // ================= Debug Utilities =================
    virtual const char* GetJointName(Entity entity, uint32_t joint_index) const = 0;
    virtual uint32_t GetJointIndex(Entity entity, const char* joint_name) const = 0;
    virtual bool DebugDrawSkeleton(Entity entity, const float* viewProjectionMatrix) = 0;

   protected:
    AnimationSystem() = default;
    AnimationSystem(const AnimationSystem&) = delete;
    AnimationSystem& operator=(const AnimationSystem&) = delete;
};

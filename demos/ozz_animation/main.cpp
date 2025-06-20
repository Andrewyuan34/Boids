#include "ozz/animation/runtime/animation.h"
#include "ozz/animation/runtime/skeleton.h"
#include "ozz/animation/runtime/sampling_job.h"
#include "ozz/animation/runtime/local_to_model_job.h"
#include "ozz/base/maths/soa_transform.h"
#include "ozz/base/maths/vec_float.h"

#include <iostream>

int main() {
    std::cout << "Ozz Animation Demo" << std::endl;
    
    // Create a simple skeleton
    ozz::animation::Skeleton skeleton;
    
    // Create a simple animation
    ozz::animation::Animation animation;
    
    return 0;
} 
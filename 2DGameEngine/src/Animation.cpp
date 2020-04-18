#include "Animation.h"

Animation::Animation() {
    
}

Animation::Animation(unsigned int index, unsigned int numFrames, unsigned int animationDurationMS) {
    this->index = index;
    this->numFrames = numFrames;
    this->animationDurationMS = animationDurationMS;
}

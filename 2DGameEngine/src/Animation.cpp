#include "Animation.h"

Animation::Animation() {
    
}

Animation::Animation(unsigned int sheetRow, unsigned int sheetColStart, unsigned int numFrames, unsigned int animationSpeed) {
    this->row = sheetRow;
    this->colStart = sheetColStart;
    this->numFrames = numFrames;
    this->animationDurationMS = animationSpeed;
}

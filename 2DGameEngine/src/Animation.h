#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
    unsigned int row;
    unsigned int colStart;
    unsigned int numFrames;
    unsigned int animationDurationMS;
    Animation();
    Animation(unsigned int sheetRow, unsigned int sheetColStart, unsigned int numFrames, unsigned int animationSpeed);
private:

};

#endif /* ANIMATION_H */


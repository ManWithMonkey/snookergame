#ifndef __GAMEUTILS_H__
#define __GAMEUTILS_H__

#include "NCursesHelper.hpp"
#include "DrawFunctions.hpp"
#include "vec2.hpp"
#include "MathFunctions.hpp"

struct Line{
    vec2 a, b;

    double holeBounceFactor = 1.0;
};

struct Ball{
    double r;

    vec2 pos;
    vec2 vel;
    vec2 dpos; 

    bool active = true;
};

struct Hole{
    vec2 pos;
    double holeRadius;
    double insideRadius;
    double pullStrength;

    bool IsClose(const Ball& ball);
    bool IsInside(const Ball& ball);
};

enum CueRotation{
    NO_ROTATION = 0,
    ROTATE_LEFT,
    ROTATE_RIGHT
};

struct Cue{
    bool active = true;

    int ballIndex;
    double angle = 0.0;

    double pullScale;
    double releaseMinStregth;
    double releaseMaxStregth;

    int rotationStatus = NO_ROTATION;

    // purely visual
    double lengthOnScreen;
    double distanceFromBallMin;
    double distanceFromBallMax;
};

// todo: use CollisionStruct for both ballball and ballline

// struct CollisionStruct{
//     double scalarOfDeltatime;
//     vec2 pos1, pos2;
//     vec2 dpos1, dpos2;
//     vec2 vel1, vel2;
//     int i = 0, j = 0;
//     bool nocollision = true;
// };

struct BallBallCollision{
    double scalarOfDeltatime;
    vec2 pos1, pos2;
    vec2 dpos1, dpos2;
    vec2 vel1, vel2;
    
    int i = 0, j = 0;
    bool nocollision = true;
};

struct BallLineCollision{
    double scalarOfDeltatime;
    vec2 pos;
    vec2 dpos;
    vec2 vel;
    
    int b = 0, l = 0;
    bool nocollision = true;
};

#endif // __GAMEUTILS_H__
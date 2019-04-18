#ifndef ALPHATIMETRAJECTORY_H
#define ALPHATIMETRAJECTORY_H

#include "vector.h"
#include <vector>

class SpeedProfile1D {
public:
    struct VT {
        float v;
        float t;
    };

    VT profile[4];
    unsigned int counter = 0;
    float acc;

public:
    float offsetForTime(float time) const {
        float offset = 0;
        for (unsigned int i = 0;i<counter-1;i++) {
            if (profile[i+1].t >= time) {
                float diff = profile[i+1].t == profile[i].t ? 1 : (time - profile[i].t) / (profile[i+1].t - profile[i].t);
                float speed = profile[i].v + diff * (profile[i+1].v - profile[i].v);
                float partDist = (profile[i].v + speed) * 0.5f * (time - profile[i].t);
                return offset + partDist;
            }
            offset += (profile[i].v + profile[i+1].v) * 0.5f * (profile[i+1].t - profile[i].t);
        }
        return offset;
    }

    float speedForTime(float time) const {
        for (unsigned int i = 0;i<counter-1;i++) {
            if (profile[i+1].t >= time) {
                float diff = profile[i+1].t == profile[i].t ? 1 : (time - profile[i].t) / (profile[i+1].t - profile[i].t);
                float speed = profile[i].v + diff * (profile[i+1].v - profile[i].v);
                return speed;
            }
        }
        return profile[counter-1].v;
    }

    float speedForTimeSlowDown(float time, float slowDownTime) const;

    float calculateSlowDownPos(float slowDownTime) const;

    float offsetForTimeSlowDown(float time, float slowDownTime) const;

    void integrateTime() {
        float totalTime = 0;
        for (unsigned int i = 0;i<counter;i++) {
            totalTime += profile[i].t;
            profile[i].t = totalTime;
        }
    }

    float timeWithSlowDown(float slowDownTime) const;
};
#include <QDebug>
class SpeedProfile
{
public:

    SpeedProfile1D xProfile;
    SpeedProfile1D yProfile;

    float inputTime;
    float inputAngle;

    bool valid = true;

    bool isValid() const { return valid; }

    void debug() {
        qDebug() <<"Zeiten: "<<xProfile.profile[xProfile.counter-1].t<<yProfile.profile[yProfile.counter-1].t;
    }

    Vector positionForTime(float time) const {
        return Vector(xProfile.offsetForTime(time), yProfile.offsetForTime(time));
    }

    Vector speedForTime(float time) const {
        return Vector(xProfile.speedForTime(time), yProfile.speedForTime(time));
    }

    Vector speedForTimeSlowDown(float time, float slowDownTime) const {
        return Vector(xProfile.speedForTimeSlowDown(time, slowDownTime), yProfile.speedForTimeSlowDown(time, slowDownTime));
    }

    Vector calculateSlowDownPos(float slowDownTime) const {
        return Vector(xProfile.calculateSlowDownPos(slowDownTime), yProfile.calculateSlowDownPos(slowDownTime));
    }

    Vector positionForTimeSlowDown(float time, float slowDownTime) const {
        return Vector(xProfile.offsetForTimeSlowDown(time, slowDownTime), yProfile.offsetForTimeSlowDown(time, slowDownTime));
    }

    float time() const {
        return std::max(xProfile.profile[xProfile.counter-1].t, yProfile.profile[yProfile.counter-1].t);
    }

    float timeWithSlowDown(float slowDownTime) const {
        return std::max(xProfile.timeWithSlowDown(slowDownTime), yProfile.timeWithSlowDown(slowDownTime));
    }
};

class AlphaTimeTrajectory
{
public:
    // validity checks
    static bool isInputValidExactEndSpeed(Vector v0, Vector v1, float time, float acc);
    static bool isInputValidFastEndSpeed(Vector v0, Vector v1, float time, float acc);
    static float minTimeExactEndSpeed(Vector v0, Vector v1, float acc);

    static std::vector<Vector> searchPoints(Vector v0, Vector v1, Vector position, float acc, float vMax, float slowDownTime);

    // search for position
    static SpeedProfile findTrajectoryFastEndSpeed(Vector v0, Vector v1, Vector position, float acc, float vMax, float slowDownTime);
    static SpeedProfile findTrajectoryExactEndSpeed(Vector v0, Vector v1, Vector position, float acc, float vMax, float slowDownTime);

    // speed profile output
    // WARNING: assumes that the input is valid and solvable (check beforehand with isInputValidFastEndSpeed)
    static SpeedProfile calculateTrajectoryFastEndSpeed(Vector v0, Vector v1, float time, float angle, float acc, float vMax);
    static SpeedProfile calculateTrajectoryExactEndSpeed(Vector v0, Vector v1, float time, float angle, float acc, float vMax);

    static void testSearch();

private:
    // pos only
    // WARNING: assumes that the input is valid and solvable (check beforehand with isInputValidFastEndSpeed)
    static Vector calculatePositionFastEndSpeed(Vector v0, Vector v1, float time, float angle, float acc, float vMax);
    static Vector calculatePositionExactEndSpeed(Vector v0, Vector v1, float time, float angle, float acc, float vMax);

    // helper functions
    // WARNING: assumes that the input is valid and solvable
    static float calculate1DTrajectoryFastEndSpeed(float v0, float v1, float time, bool directionPositive, float acc, float vMax);
    static void calculate1DTrajectoryFastEndSpeed(float v0, float v1, float time, bool directionPositive, float acc, float vMax, SpeedProfile1D &profile);
    static float calculateEndPos1D(float v0, float v1, float hintDist, float acc, float vMax);
    static void calculate1DSpeedProfile(float v0, float v1, float hintDist, float acc, float vMax, SpeedProfile1D &profile);
};

#endif // ALPHATIMETRAJECTORY_H
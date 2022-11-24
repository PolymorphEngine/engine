/*
** ${PROJECT}, 2022
** Time.cpp by 0xMemoryGrinder
** File description:
** Time.cpp
*/


#include "polymorph/time/Time.hpp"


polymorph::engine::time::Time::Time() : _lastTime(Clock::now()) {}

void polymorph::engine::time::Time::computeDeltaTime()
{
    auto now = Clock::now();
    std::chrono::duration<double> diff = now - _lastTime;

    deltaTime = diff.count();
    if (deltaTime > 0.016)
        deltaTime = 0.016;
    _lastTime = now;
}

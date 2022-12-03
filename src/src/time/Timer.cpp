/*
** ${PROJECT}, 2022
** Timer.cpp by 0xMemoryGrinder
** File description:
** Timer.cpp
*/


#include "polymorph/time/Timer.hpp"
#include "polymorph/time/Time.hpp"

polymorph::engine::time::Timer::Timer(polymorph::engine::time::Time &time, double delay) : time(time), delay(delay) {}

polymorph::engine::time::Timer::Timer(polymorph::engine::Engine &game, double delay) : time(game.getTime()), delay(delay) {}

polymorph::engine::time::Timer::Timer(polymorph::engine::GameObject &object, double delay) : time(object->time), delay(delay) {} // TODO: include entity definition

polymorph::engine::time::Timer::Timer(polymorph::engine::Component &component, double delay) : time(component.time), delay(delay) {} // TODO: include component definition

void polymorph::engine::time::Timer::tick()
{
    actual += time.deltaTime;
}

bool polymorph::engine::time::Timer::timeIsUp(bool isReset)
{
    if (actual >= delay) {
        if (isReset)
            actual = 0;
        return true;
    }
    return false;
}
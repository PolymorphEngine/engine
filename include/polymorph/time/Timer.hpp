/*
** ${PROJECT}, 2022
** Timer.hpp by 0xMemoryGrinder
** File description:
** Timer.hpp
*/


#pragma once

#include "polymorph/types/safeptr/safe_ptr.hpp"

namespace polymorph::engine
{
    class Engine;
    class Entity;
    class Component;
    using GameObject = safe_ptr<Entity>;
}

namespace polymorph::engine::time
{
    class Time;

    class Timer
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

        public:
            /**
             * @brief Create a new timer from a specified delay
             * @param delay The delay in seconds
             */
            explicit Timer(Time &time, double delay);

            /**
             * @brief Create a new timer from a specified delay using a the time in the engine
             * @param game The engine to get the time from
             * @param delay The delay in seconds
             */
            explicit Timer(Engine &game, double delay);

            /**
             * @brief Create a new timer from a specified delay using a the time in a GameObject
             * @param object The GameObject to get the time from
             * @param delay The delay in seconds
             */
            explicit Timer(GameObject &object, double delay);

            /**
             * @brief Create a new timer from a specified delay using a the time in a Component
             * @param component The Component to get the time from
             * @param delay The delay in seconds
             */
            explicit Timer(Component &component, double delay);

            Timer(const Timer &other) = default;

            Timer(Timer &&other) noexcept = default;

            Timer &operator=(const Timer &other) = default;


//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:
            /**
             * @property time The time to use and fetch deltaTime from
             */
            Time &time;

            /**
             * @property delay The delay in seconds
             */
            double delay = 0;

            /**
             * @property actual The current time of timer in seconds
             */
            double actual = 0;

        private:


//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @brief Update the actual time of the timer by adding the deltaTime to it
             */
            void tick();

            /**
             * @brief Check if the current time is greater than the delay and may reset the timer
             * @param isReset If true, the timer will be reset
             * @return true if the current time is greater than the delay
             */
            bool timeIsUp(bool isReset = true);;

        private:


//////////////////////--------------------------/////////////////////////

    };
}

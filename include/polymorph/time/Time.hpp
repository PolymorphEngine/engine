/*
** ${PROJECT}, 2022
** Time.hpp by 0xMemoryGrinder
** File description:
** Time.hpp
*/


#pragma once

#include <chrono>

namespace polymorph::engine::time
{

    class Time
    {
            using Clock = std::chrono::steady_clock;
            using Duration = std::chrono::time_point<Clock>;

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

        public:
            /**
             * @details Create a Time clock by initializing internal properties
             */
            explicit Time();


//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:
            /**
             * @property deltaTime the time between the last frame and the current frame
             */
            double deltaTime = 0.0f;

        private:
            /**
             * @property _lastTime the time of the last frame
             */
            Duration _lastTime;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @details Update the deltaTime of the current frame
             */
            void computeDeltaTime();

        private:


//////////////////////--------------------------/////////////////////////

    };
}

/*
** EPITECH PROJECT, 2020
** NoScenesFoundException.hpp
** File description:
** header for NoScenesFoundException.c
*/


#pragma once

#include "polymorph/debug/exception/ExceptionLogger.hpp"

namespace polymorph::engine::debug
{
    class NoScenesFoundException : public ExceptionLogger
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            NoScenesFoundException(Logger::severity level = Logger::MAJOR);

            ~NoScenesFoundException() override = default;

//////////////////////--------------------------/////////////////////////

    };
}

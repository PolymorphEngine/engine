/*
** EPITECH PROJECT, 2020
** MissingReferenceException.hpp
** File description:
** header for MissingReferenceException.c
*/


#pragma once

#include "polymorph/debug/exception/ExceptionLogger.hpp"

namespace polymorph::engine::debug
{
    template<typename T = void, typename U = void>
    class MissingReferenceException : public ExceptionLogger
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            MissingReferenceException(Logger::severity level = Logger::MAJOR) : ExceptionLogger("[MissingReferenceException] Undefined or missing reference", level) {};

            // TODO: constructor with GameObject as parameter

            //TODO: constructor with GameObject and Component as parameter

            //TODO: templated constructor with Component and property as parameter

            ~MissingReferenceException() override = default;

//////////////////////--------------------------/////////////////////////

    };
}

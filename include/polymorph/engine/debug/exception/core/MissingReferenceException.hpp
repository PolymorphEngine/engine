/*
** EPITECH PROJECT, 2020
** MissingReferenceException.hpp
** File description:
** header for MissingReferenceException.c
*/


#pragma once

#include "polymorph/engine/debug/exception/CoreException.hpp"

namespace polymorph::engine::debug
{
    class MissingReferenceException : public CoreException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            explicit MissingReferenceException(Logger::severity level = Logger::MAJOR) : CoreException("Undefined or missing reference to an object", level) {};

            ~MissingReferenceException() override = default;
            
            MissingReferenceException(std::string missing, Logger::severity level = Logger::MAJOR) : CoreException("Missing reference to '" + missing + "'", level) {};

            // TODO: constructor with GameObject as parameter

            //TODO: constructor with GameObject and Component as parameter

            //TODO: templated constructor with Component and property as parameter


//////////////////////--------------------------/////////////////////////

    };
}

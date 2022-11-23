/*
** EPITECH PROJECT, 2020
** CoreException.hpp
** File description:
** header for CoreException.c
*/


#pragma once
#include "polymorph/debug/exception/ExceptionLogger.hpp"

namespace polymorph::engine::debug
{
    class CoreException : public engine::debug::ExceptionLogger
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            CoreException(std::string message, Logger::severity level = Logger::severity::MAJOR);

            ~CoreException() override = default;

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:


        private:

//////////////////////--------------------------/////////////////////////

    };
}
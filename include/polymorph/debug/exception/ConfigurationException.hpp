/*
** EPITECH PROJECT, 2020
** ConfigurationException.hpp
** File description:
** header for ConfigurationException.c
*/


#pragma once

#include "polymorph/debug/exception/ExceptionLogger.hpp"

namespace polymorph::engine::debug
{


    class ConfigurationException : public ExceptionLogger
    {
        public:
            explicit ConfigurationException(std::string message,
                                   Logger::severity level = Logger::MAJOR);

            ~ConfigurationException() override = default;

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
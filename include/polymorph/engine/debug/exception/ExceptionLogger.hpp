/*
** EPITECH PROJECT, 2020
** ExceptionLogger.hpp
** File description:
** header for ExceptionLogger.c
*/


#pragma once
#include <exception>
#include <string>
#include "polymorph/engine/debug/Logger.hpp"

namespace polymorph::engine::debug
{
    class ExceptionLogger : public std::exception
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

        public:
            explicit ExceptionLogger(std::string message, Logger::severity level = Logger::severity::MAJOR);

            ///////////////////////////--------------------------///////////////////////////



            ///////////////////////////////// Properties /////////////////////////////////

        private:
            std::string _message;
            Logger::severity _level;

            ///////////////////////////--------------------------///////////////////////////



            ///////////////////////////////// Methods /////////////////////////////////

        public:
            const char *what() const noexcept override;

            ///////////////////////////--------------------------///////////////////////////

    };
}
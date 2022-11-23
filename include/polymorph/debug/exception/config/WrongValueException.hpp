/*
** EPITECH PROJECT, 2020
** WrongValueException.hpp
** File description:
** header for WrongValueException.c
*/


#pragma once


#include "polymorph/debug/exception/ConfigurationException.hpp"

namespace polymorph::engine::debug
{

    class WrongValueException final : public ConfigurationException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            WrongValueException(std::string entity, std::string component, std::string property, std::string value, std::string object = "", Logger::severity level = Logger::MAJOR);
            WrongValueException(std::string object, std::string property, std::string value, Logger::severity level = Logger::MAJOR);

            ~WrongValueException();

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
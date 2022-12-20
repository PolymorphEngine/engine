/*
** EPITECH PROJECT, 2020
** ConfigurationException.cpp
** File description:
** header for ConfigurationException.c
*/

#include "polymorph/engine/debug/exception/ConfigurationException.hpp"

polymorph::engine::debug::ConfigurationException::ConfigurationException(
        std::string message, polymorph::engine::debug::Logger::severity level)
        : ExceptionLogger("[ConfigurationException] "+message, level)
{

}

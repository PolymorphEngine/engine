/*
** EPITECH PROJECT, 2020
** MissingValueException.cpp
** File description:
** header for MissingValueException.c
*/

#include "polymorph/debug/exception/config/MissingValueException.hpp"

polymorph::engine::debug::MissingValueException::MissingValueException(std::string entity, std::string component, std::string property, std::string object, Logger::severity level) 
: ConfigurationException("missing value for property '" + property + (object.empty() ? "'" : "' for object '"+object+"'") + " for component '" + component + "' of entity '" + entity + "'.", level)
{

};

polymorph::engine::debug::MissingValueException::MissingValueException(
        std::string object, std::string property,
        polymorph::engine::debug::Logger::severity level)
        : ConfigurationException("missing value for property '" + property + "' for configuration '" + object + "'.", level)
{

};

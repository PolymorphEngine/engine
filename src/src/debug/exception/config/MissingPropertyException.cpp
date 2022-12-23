/*
** EPITECH PROJECT, 2020
** MissingPropertyException.cpp
** File description:
** header for MissingPropertyException.c
*/

#include "polymorph/engine/debug/exception/config/MissingPropertyException.hpp"

polymorph::engine::debug::MissingPropertyException::MissingPropertyException(
        std::string entity, std::string component, std::string property,
        std::string object, Logger::severity level) : ConfigurationException("missing property '" + property + (object.empty() ? "'" : "' for object '"+object+"'") + " for component '" + component + "' of entity '" + entity + "'.", level)
{

}

polymorph::engine::debug::MissingPropertyException::MissingPropertyException(
        std::string object, std::string property,
        polymorph::engine::debug::Logger::severity level)
        : ConfigurationException("missing property '" + property + "' for configuration '" + object + "'.", level)
{

}

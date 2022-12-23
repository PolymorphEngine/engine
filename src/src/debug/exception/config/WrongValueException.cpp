/*
** EPITECH PROJECT, 2020
** WrongValueException.cpp
** File description:
** header for WrongValueException.c
*/

#include "polymorph/engine/debug/exception/config/WrongValueException.hpp"

polymorph::engine::debug::WrongValueException::WrongValueException(
        std::string entity, std::string component, std::string property,
        std::string value, std::string object, Logger::severity level)
        : ConfigurationException("wrong value '" + value + "' for property '" + property + (object.empty() ? "'" : "' for object '"+object+"'") + " for component '" + component + "' of entity '" + entity + "'.", level)
{

}

polymorph::engine::debug::WrongValueException::WrongValueException(
        std::string object, std::string property, std::string value,
        polymorph::engine::debug::Logger::severity level)
        : ConfigurationException("wrong value '" + value + "' for property '" + property + "' for configuration '" + object + "'.", level)
{

}

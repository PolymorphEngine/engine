/*
** EPITECH PROJECT, 2020
** MissingComponentTypeException.cpp
** File description:
** header for MissingComponentTypeException.c
*/

#include "polymorph/debug/exception/config/MissingComponentTypeException.hpp"

polymorph::engine::debug::MissingComponentTypeException::MissingComponentTypeException(
        std::string entity) : ConfigurationException("missing component type for entity: '" + entity + "'.", Logger::severity::MAJOR)
{

}

/*
** EPITECH PROJECT, 2020
** MissingEntityException.cpp
** File description:
** header for MissingEntityException.c
*/

#include "polymorph/debug/exception/config/MissingEntityException.hpp"

polymorph::engine::debug::MissingEntityException::MissingEntityException(
        std::string entity, Logger::severity level)
        : ConfigurationException("Missing entity '"+entity + "', file not found.", level)
{

}

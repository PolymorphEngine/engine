/*
** EPITECH PROJECT, 2020
** AScriptFactory.cpp
** File description:
** header for AScriptFactory.c
*/

#include "polymorph/api/scripting/AComponentFactory.hpp"

namespace polymorph::engine::api
{

    void AComponentFactory::buildFactory()
    {
        _registerBuildables(_buildables);
    }

    bool AComponentFactory::hasComponent(const std::string &type) const
    {
        return _buildables.find(type) != _buildables.end();
    }
} // api
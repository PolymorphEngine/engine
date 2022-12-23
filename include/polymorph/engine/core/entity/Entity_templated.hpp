/*
** EPITECH PROJECT, 2020
** Entity_templated.hpp
** File description:
** header for Entity_templated.c
*/


#pragma once
#include "polymorph/engine/core/entity/Entity.hpp"
#include "polymorph/engine/core/Engine.hpp"
#include "polymorph/engine/core/component/AComponent.hpp"

namespace polymorph::engine
{
    template<typename T>
    safe_ptr<T> Entity::getComponent()
    {
        for (auto &components: _components)
            for (auto &component: components.second)
            {
                auto casted = std::dynamic_pointer_cast<T>(component);
                if (casted)
                    return safe_ptr<T>(casted);
            }
        return safe_ptr<T>(nullptr);
    }
    
    template<typename T>
    std::vector<safe_ptr<T>> Entity::getComponents()
    {
        std::vector<safe_ptr<T>> found;
        for (auto &components: _components)
            for (auto &component: components.second)
            {
                auto casted = std::dynamic_pointer_cast<T>(component);
                if (casted)
                    found.push_back(safe_ptr<T>(casted));
            }
        return found;
    }
    
    template<typename T>
    safe_ptr<T> Entity::addComponent()
    {
        std::string type = T::type;

        if (componentExist(type))
            return;
        //TODO : throw ?
        std::shared_ptr<AComponent> newComponent;
        std::shared_ptr<myxmlpp::Node> config = Game.getDefaultConfig(type);

        if (type == "Transform")
            newComponent = std::dynamic_pointer_cast<AComponent>(std::make_shared<TransformComponent>(config, safe_from_this()));
        if (newComponent == nullptr)
            newComponent = Plugin.tryCreateComponent(type, safe_from_this(), config);
        if (_components.contains(newComponent->getType()))
            _components[newComponent->getType()].push_back(newComponent);
        else
            _components["Default"].push_back(newComponent);
        if (type == "Transform")
            newComponent->transform = getComponent<TransformComponent>();
        newComponent->getConfig()->setGameObject(safe_from_this());
        newComponent->build();
        return safe_ptr<T>(std::dynamic_pointer_cast<T>(*newComponent));
    }

    template<typename T>
    bool Entity::componentExist()
    {
        for (auto &components: _components)
            for (auto &component: components.second)
            {
                auto casted = std::dynamic_pointer_cast<T>(component);
                if (casted)
                    return true;
            }
        return false;
    }
    
    template<typename T>
    bool Entity::deleteComponent()
    {
        for (auto &components: _components)
        {
            auto found = std::find_if(components.second.begin(), components.second.end(), [](auto &component) {
                return std::dynamic_pointer_cast<T>(component);
            });
            if (found) {
                components.second.erase(found);
                return true;
            }
        }
        return false;
    }
}

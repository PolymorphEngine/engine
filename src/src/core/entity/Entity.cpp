/*
** EPITECH PROJECT, 2020
** Entity.cpp
** File description:
** Entity.cpp
*/

#include "polymorph/engine/core/entity/Entity.hpp"
#include "polymorph/engine/core/entity/Entity_templated.hpp"
#include "polymorph/engine/core/Engine.hpp"
#include "polymorph/engine/core/Scene.hpp"
#include "polymorph/engine/core/component/TransformComponent.hpp"
#include "polymorph/engine/core/component/AComponent.hpp"
#include "polymorph/engine/config/XmlEntity.hpp"
#include "polymorph/engine/debug/exception/config/MissingComponentTypeException.hpp"

namespace polymorph::engine
{

    Entity::Entity(std::shared_ptr<config::XmlEntity> data, Engine &game)
    : Game(game), Debug(game.getLogger()), time(game.getTime()),
      Plugin(game.getPluginManager()), Scene(game.getSceneManager()),
      Resource(game.getAssetManager()), _xmlConfig(data)
    {
        name = data->getName();
        _stringId = data->getId();
        _tags = data->getTags();
        _active = data->isActive();
        _isPrefab = false;
        _wasPrefab = data->isPrefab();
        _prefabId = data->getPrefabId();
        for (auto &exec: Game.getExecOrder())
            _components[exec] = std::vector<std::shared_ptr<AComponent>>();
        _createComponents(data->getComponents());
    }

    Entity::Entity(std::shared_ptr<myxmlpp::Node> data, Engine &game)
    : Game(game), Debug(game.getLogger()), time(game.getTime()),
      Plugin(game.getPluginManager()), Scene(game.getSceneManager()), Resource(game.getAssetManager())
    {
        _xmlConfig = std::make_shared<config::XmlEntity>(data, Debug, Game);
        name = _xmlConfig->getName();
        _stringId = _xmlConfig->getId();
        _tags = _xmlConfig->getTags();
        _active = _xmlConfig->isActive();
        _isPrefab = false;
        _wasPrefab = _xmlConfig->isPrefab();
        _prefabId = _xmlConfig->getPrefabId();
        for (auto &exec: Game.getExecOrder())
            _components[exec] = std::vector<std::shared_ptr<AComponent>>();
        _createComponents(_xmlConfig->getComponents());
    }

    bool polymorph::engine::Entity::isActive() const
    {
        return _active;
    }

    bool polymorph::engine::Entity::isPrefab() const
    {
        return _isPrefab;
    }

    bool polymorph::engine::Entity::wasPrefab() const
    {
        return _wasPrefab;
    }

    void polymorph::engine::Entity::setIsPrefab(bool value)
    {
        _isPrefab = value;
    }

    void polymorph::engine::Entity::setWasPrefab(bool value)
    {
        _wasPrefab = value;
    }

    void polymorph::engine::Entity::setActive(bool active)
    {
        if (_active == active)
            return;
        _active = active;
        if (_active)
            _asBeenEnabled = true;
        else
            _asBeenDisabled = true;
    }

    bool polymorph::engine::Entity::hasTag(const std::string &tag) const
    {
        return std::find(_tags.begin(), _tags.end(), tag) != _tags.end();
    }

    std::vector<std::string>
    polymorph::engine::Entity::getTagsStartingWith(const std::string &begin) const
    {
        std::vector<std::string> found;
        for (auto &tag: _tags) {
            if (tag.find(begin) == 0)
                found.push_back(tag);
        }
        return found;
    }

    void polymorph::engine::Entity::addTag(const std::string &tag)
    {
        if (!hasTag(tag))
            _tags.push_back(tag);
    }

    void polymorph::engine::Entity::deleteTag(const std::string &tag)
    {
        if (hasTag(tag))
            _tags.erase(std::remove(_tags.begin(), _tags.end(), tag), _tags.end());
    }

    void polymorph::engine::Entity::awake(bool rescurse)
    {
        for (auto &exec: Game.getExecOrder()) {
            for (auto &component: _components[exec]) {
                if (!component->isAwoken()) {
                    component->onAwake();
                    component->setAsAwoken();
                }
            }
        }
        if (rescurse) {
            for (auto &child: **transform) {
                child->gameObject->awake(rescurse);
            }
        }
    }

    void polymorph::engine::Entity::start()
    {
        if (!_active)
            return;
        for (auto &exec: Game.getExecOrder()) {
            for (auto &component: _components[exec]) {
                if (!component->enabled)
                    continue;
                if (component->isStarted()) {
                    component->start();
                    component->setAsStarted();
                }
            }
        }
    }

    void polymorph::engine::Entity::startChildren()
    {
        for (auto &child: **transform) {
            child->gameObject->start();
        }
    }

    void polymorph::engine::Entity::build()
    {
        initTransform();
        for (auto &exec: Game.getExecOrder()) {
            for (auto &component: _components[exec]) {
                if (component->getType() != "Transform")
                    component->build();
            }
        }
    }

    void polymorph::engine::Entity::buildChildren()
    {
        for (auto &child: **transform) {
            child->gameObject->build();
        }
    }

    void polymorph::engine::Entity::update()
    {
        if (!_active)
            return;
        for (auto &exec: Game.getExecOrder()) {
            for (auto &component: _components[exec]) {
                if (!component->enabled)
                    continue;
                component->update();
            }
        }
        updateChildren();
    }

    void polymorph::engine::Entity::updateChildren()
    {
        if (!_active)
            return;
        for (auto &child: **transform) {
            child->gameObject->update();
        }
    }

    void polymorph::engine::Entity::lateUpdate()
    {
        if (!_active)
            return;
        for (auto &exec: Game.getExecOrder()) {
            for (auto &component: _components[exec]) {
                if (!component->enabled)
                    continue;
                component->lateUpdate();
            }
        }
        lateUpdateChildren();
    }

    void polymorph::engine::Entity::lateUpdateChildren()
    {
        if (!_active)
            return;
        for (auto &child: **transform) {
            child->gameObject->lateUpdate();
        }
    }

    void polymorph::engine::Entity::onEnable()
    {
        if (!_asBeenEnabled && !transform->parent())
            return;
        for (auto &exec: Game.getExecOrder()) {
            for (auto &component: _components[exec]) {
                if (!component->enabled)
                    continue;
                component->onEnable();
            }
        }
        onEnableChildren();
        _asBeenEnabled = false;
    }

    void polymorph::engine::Entity::onEnableChildren()
    {
        if (!_asBeenEnabled && !transform->parent())
            return;
        for (auto &child: **transform) {
            child->gameObject->onEnable();
        }
    }

    void polymorph::engine::Entity::onDisable()
    {
        if (!_asBeenDisabled && !transform->parent())
            return;
        for (auto &exec: Game.getExecOrder()) {
            for (auto &component: _components[exec]) {
                if (!component->enabled)
                    continue;
                component->onDisable();
            }
        }
        onDisableChildren();
        _asBeenDisabled = false;
    }

    void polymorph::engine::Entity::onDisableChildren()
    {
        if (!_asBeenDisabled && !transform->parent())
            return;
        for (auto &child: **transform) {
            child->gameObject->onDisable();
        }
    }

    void
    polymorph::engine::Entity::onSceneLoaded(std::shared_ptr<engine::Scene> scene)
    {
        if (!_active)
            return;
        for (auto &exec: Game.getExecOrder()) {
            for (auto &component: _components[exec]) {
                if (component->enabled)
                    component->onSceneLoaded(scene);
            }
        }
        onSceneLoadingChildren(scene);
    }

    void polymorph::engine::Entity::onSceneLoadingChildren(
            std::shared_ptr<engine::Scene> scene)
    {
        if (!_active)
            return;
        for (auto &child: **transform) {
            child->gameObject->onSceneLoaded(scene);
        }
    }

    void polymorph::engine::Entity::onSceneUnloaded(std::shared_ptr<engine::Scene> scene)
    {
        if (!_active)
            return;
        for (auto &exec: Game.getExecOrder()) {
            for (auto &component: _components[exec]) {
                if (component->enabled)
                    component->onSceneUnloaded(scene);
            }
        }
    }

    void polymorph::engine::Entity::onSceneUnloadingChildren(std::shared_ptr<engine::Scene> scene)
    {
        if (!_active)
            return;
        for (auto &child: **transform) {
            child->gameObject->onSceneUnloaded(scene);
        }
    }

    void polymorph::engine::Entity::save(bool saveAllComponentsFirst,
                                         std::string filePath)
    {
        if (saveAllComponentsFirst)
            for (auto &exec: Game.getExecOrder()) {
                for (auto &component: _components[exec]) {
                    component->saveAll();
                }
            }
        _xmlConfig->saveConfig(filePath, _components);
    }

    polymorph::engine::GameObject
    polymorph::engine::Entity::find(const std::string &nameToFind) const
    {
        for (auto &child: **transform) {
            if (child->gameObject->name == nameToFind)
                return child->gameObject;
        }
        return GameObject(nullptr);
    }

    polymorph::engine::GameObject
    polymorph::engine::Entity::findByPrefabId(const std::string &prefabId,
                                              bool _firstCall) const
    {
        GameObject highestParent = transform->parent()->gameObject;
        while (highestParent->transform->parent())
            highestParent = highestParent->transform->parent()->gameObject;
        return highestParent->_getByPrefabId(prefabId);
    }
    GameObject Entity::_getByPrefabId(std::string prefabId)
    {
        if (_prefabId == prefabId)
            return safe_from_this();
        for (auto &child : **transform) {
            if (child->gameObject->_prefabId == prefabId)
                return child->gameObject;
        }
        for (auto &child : **transform) {
            auto found = child->gameObject->_getByPrefabId(prefabId);
            if (found)
                return found;
        }
        return GameObject(nullptr);
    }

    polymorph::engine::GameObject
    polymorph::engine::Entity::childAt(std::size_t idx)
    {
        int i = 0;
        for (auto &child: **transform)
        {
            if (i == idx)
                return child->gameObject;
            if (i > idx)
                return GameObject(nullptr);
            ++i;
        }
        return GameObject(nullptr);
    }

    void polymorph::engine::Entity::initTransform()
    {
        if (_transformInitialized)
            return;
        transform->build();
        for (auto &child: **transform) {
            child->gameObject->initTransform();
        }
        _transformInitialized = true;
    }

    polymorph::engine::safe_ptr<polymorph::engine::AComponent>
    polymorph::engine::Entity::getComponent(const std::string &type)
    {
        for (auto &components: _components)
            for (auto &cpt: components.second)
                if (cpt->getType() == type)
                    return safe_ptr<AComponent>(cpt);
        return safe_ptr<AComponent>(nullptr);
    }


    std::string polymorph::engine::Entity::getName() const noexcept
    {
        return name;
    }

    std::string polymorph::engine::Entity::getId() const noexcept
    {
        return _stringId;
    }

    std::string polymorph::engine::Entity::getPrefabId() const noexcept
    {
        return _prefabId;
    }

    void polymorph::engine::Entity::setId(const std::string &id) noexcept
    {
        _stringId = id;
    }

    void polymorph::engine::Entity::setPrefabId(const std::string &id) noexcept
    {
        _prefabId = id;
    }

    std::shared_ptr<polymorph::engine::config::XmlEntity>
    polymorph::engine::Entity::getXmlConfig() const noexcept
    {
        return _xmlConfig;
    }

    bool polymorph::engine::Entity::operator==(
            polymorph::engine::Entity &entity) const noexcept
    {
        return _stringId == entity._stringId;
    }

    bool polymorph::engine::Entity::operator!=(
            polymorph::engine::Entity &entity) const noexcept
    {
        return _stringId != entity._stringId;
    }

    bool polymorph::engine::Entity::operator==(const std::string &id) const noexcept
    {
        return _stringId == id;
    }

    bool polymorph::engine::Entity::operator!=(const std::string &id) const noexcept
    {
        return _stringId != id;
    }

    bool polymorph::engine::Entity::componentExist(std::string &type) const noexcept
    {
        for (auto &components: _components)
            for (auto &component: components.second)
                if (component->getType() == type)
                    return true;
        return false;
    }

    void Entity::_createComponents(std::shared_ptr<myxmlpp::Node> components)
    {
        for (auto &cpt: *components) {
            try {
                _createComponent(cpt);
            } catch (debug::ExceptionLogger &e) {
                e.what();
                continue;
            }
        }
    }

    void Entity::_createComponent(std::shared_ptr<myxmlpp::Node> component)
    {
        std::string type;
        try {
            type = component->findAttribute("type")->getValue();
        } catch (myxmlpp::Exception &e) {
            throw debug::MissingComponentTypeException(name + "(" + _stringId + ")");
        }
        addComponent(type, component);
    }

    void Entity::addComponent(std::string &component,
                              std::shared_ptr<myxmlpp::Node> &config)
    {
        if (componentExist(component))
            return;
        //TODO : throw ?
        std::shared_ptr<AComponent> newComponent;

        if (component == "Transform")
            newComponent = std::make_shared<TransformComponent>(config, safe_from_this());
        if (newComponent == nullptr)
            newComponent = Plugin.tryCreateComponent(component, safe_from_this(), config);

        if (_components.contains(newComponent->getType()))
            _components[newComponent->getType()].push_back(newComponent);
        else
            _components["Default"].push_back(newComponent);
        if (component == "Transform")
            newComponent->transform = getComponent<TransformComponent>();
    }




}
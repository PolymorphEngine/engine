/*
** EPITECH PROJECT, 2020
** SceneManager.cpp
** File description:
** header for SceneManager.c
*/

#include "polymorph/engine/api/SceneManager.hpp"
#include "polymorph/engine/core/Engine.hpp"
#include "polymorph/engine/core/Scene.hpp"
#include "polymorph/engine/core/component/TransformComponent.hpp"
#include "polymorph/engine/config/XmlEntity.hpp"
#include "polymorph/engine/types/uuid.hpp"
#include "polymorph/engine/types/vector/Vector3.hpp"
#include "polymorph/engine/debug/exception/core/SceneNotFoundException.hpp"

polymorph::engine::api::SceneManager::SceneManager(polymorph::engine::Engine &game) : _game(game)
{}

polymorph::engine::api::SceneManager::SceneManager(polymorph::engine::Engine &game, std::shared_ptr<Scene> current) : _game(game), _current(current)
{}

std::vector<polymorph::engine::GameObject> polymorph::engine::api::SceneManager::getAll()
{
    if (_current == nullptr)
        return {};
    return _current->getAll();
}

polymorph::engine::GameObject polymorph::engine::api::SceneManager::find(const std::string &name)
{
    if (_current == nullptr)
        return GameObject(nullptr);
    return _current->find(name);
}

std::vector<polymorph::engine::GameObject> polymorph::engine::api::SceneManager::findAll(const std::string &name)
{
    if (_current == nullptr)
        return {};
    return _current->findAll(name);
}

polymorph::engine::GameObject polymorph::engine::api::SceneManager::findById(const std::string &id)
{
    if (_current == nullptr)
        return GameObject(nullptr);
    auto found = _current->findById(id);
    if (found)
        return found;
    auto prefabs = _game.getPrefabs();
    for (auto &prefab : prefabs) {
        if (*prefab == id || prefab->getPrefabId() == id)
            return GameObject(prefab);
    }
    return GameObject(nullptr);
}

polymorph::engine::GameObject polymorph::engine::api::SceneManager::findByTag(const std::string &tag)
{
    if (_current == nullptr)
        return GameObject(nullptr);
    return _current->findByTag(tag);
}

std::vector<polymorph::engine::GameObject> polymorph::engine::api::SceneManager::findAllByTag(const std::string &tag)
{
    if (_current == nullptr)
        return {};
    return _current->findAllByTag(tag);
}

std::shared_ptr<polymorph::engine::Scene> polymorph::engine::api::SceneManager::getCurrentScene() const
{
    return _current;
}

void polymorph::engine::api::SceneManager::setCurrentScene(std::shared_ptr<Scene> scene)
{
    _current = scene;
}

void polymorph::engine::api::SceneManager::destroy(polymorph::engine::GameObject &gameObject)
{
    if (_current == nullptr)
        return;
    _current->destroy(**gameObject);
}

void polymorph::engine::api::SceneManager::destroy(polymorph::engine::GameObject gameObject, float delay)
{
    if (_current == nullptr)
        return;
    _current->destroy(**gameObject, delay);
}

polymorph::engine::GameObject
polymorph::engine::api::SceneManager::instantiate(polymorph::engine::GameObject &gameObject)
{
    auto xml = gameObject->getXmlConfig();
    auto nEntity = std::make_shared<Entity>(xml, _game);
    nEntity->_createComponents();
    auto nId = polymorph::engine::uuid::uuid();

    nEntity->setId(nId);
    nEntity->setIsPrefab(false);
    nEntity->build();
    nEntity->awake();
    _current->addEntityToAddQueue(nEntity);
    return GameObject(nEntity);
}

polymorph::engine::GameObject
polymorph::engine::api::SceneManager::instantiate(polymorph::engine::GameObject gameObject,
                                                  const polymorph::engine::Vector3 &position)
{
    auto xml = gameObject->getXmlConfig();
    auto nEntity = std::make_shared<Entity>(xml, _game);
    nEntity->_createComponents();
    auto nId = polymorph::engine::uuid::uuid();

    nEntity->setId(nId);
    nEntity->setIsPrefab(false);
    _current->addEntityToAddQueue(nEntity);
    nEntity->build();
    nEntity->transform->setPosition(position);
    nEntity->awake();
    return GameObject(nEntity);
}

polymorph::engine::GameObject
polymorph::engine::api::SceneManager::instantiate(polymorph::engine::GameObject gameObject,
                                                  polymorph::engine::Transform parent)
{
    auto xml = gameObject->getXmlConfig();
    auto nEntity = std::make_shared<Entity>(xml, _game);
    nEntity->_createComponents();
    auto nId = polymorph::engine::uuid::uuid();

    nEntity->setId(nId);
    nEntity->setIsPrefab(false);
    _current->addEntityToAddQueue(nEntity);
    nEntity->build();
    nEntity->transform->setParent(parent);
    nEntity->transform->setPosition(parent->getPosition());
    nEntity->awake();
    return GameObject(nEntity);
}

polymorph::engine::GameObject
polymorph::engine::api::SceneManager::instantiate(polymorph::engine::GameObject gameObject,
                                                  polymorph::engine::Transform parent,
                                                  polymorph::engine::Vector3 offset)
{
    auto xml = gameObject->getXmlConfig();
    auto nEntity = std::make_shared<Entity>(xml, _game);
    nEntity->_createComponents();
    auto nId = polymorph::engine::uuid::uuid();

    nEntity->setId(nId);
    nEntity->setIsPrefab(false);
    _current->addEntityToAddQueue(nEntity);
    nEntity->build();
    nEntity->transform->setParent(parent);
    nEntity->transform->setPosition(parent->transform->getPosition() + offset);
    nEntity->awake();
    return GameObject(nEntity);
}

void polymorph::engine::api::SceneManager::setAtFront(polymorph::engine::GameObject gameObject)
{
    setAtIdx(gameObject, 0);
}

void polymorph::engine::api::SceneManager::setAtIdx(polymorph::engine::GameObject gameObject, std::size_t idx)
{
    auto it = _current->findItById(gameObject->getId());
    auto entity = _current->pop(it);

    _current->addEntityAtIdx(entity, idx);
}

void polymorph::engine::api::SceneManager::setAtBack(polymorph::engine::GameObject gameObject)
{
    auto nb = _current->countParents();

    setAtIdx(gameObject, nb);
}

void polymorph::engine::api::SceneManager::loadScene(std::string name)
{
    auto scene = _game.findSceneByName(name);

    if (!scene)
        throw debug::SceneNotFoundException(name, debug::Logger::MAJOR);
    _toLoad = scene;
    _sceneLoading = true;
}

bool polymorph::engine::api::SceneManager::isSceneUnloaded() const
{
    return _sceneLoading;
}

void polymorph::engine::api::SceneManager::checkQueuedScene()
{
    if (_toLoad) {
        _current->unloadScene();
        _current = _toLoad;
        _current->loadScene();
        _toLoad = nullptr;
    }
}

void polymorph::engine::api::SceneManager::resetLoading()
{
    _sceneLoading = false;
}

void polymorph::engine::api::SceneManager::createScene(std::string name)
{
    _game.addScene(std::make_shared<Scene>(name, _game));
}

void polymorph::engine::api::SceneManager::dontDestroyOnLoad(polymorph::engine::GameObject gameObject)
{
    KeepOnLoad.emplace_back(*gameObject);
    for (auto &child : **gameObject->transform)
        dontDestroyOnLoad(child->gameObject);
}

std::vector<std::shared_ptr<polymorph::engine::Entity>> &polymorph::engine::api::SceneManager::getKeepedEntities()
{
    return KeepOnLoad;
}

void polymorph::engine::api::SceneManager::save(bool saveAll, std::string saveDirectoryPath)
{
    if (_current == nullptr)
        return;
    _current->save(saveAll, std::move(saveDirectoryPath));
}

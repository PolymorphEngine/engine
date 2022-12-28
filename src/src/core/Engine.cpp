/*
** EPITECH PROJECT, 2020
** Engine.cpp
** File description:
** header for Engine.c
*/

#include <utility>

#include "polymorph/engine/core/Engine.hpp"
#include "polymorph/engine/config/XmlEntity.hpp"
#include "polymorph/engine/config/XmlComponent.hpp"
#include "polymorph/engine/debug/exception/ConfigurationException.hpp"

polymorph::engine::Engine::Engine(std::string projectName, std::string projectPath, std::string pluginsPath)
        : _projectName(std::move(projectName)), _projectPath(std::move(projectPath)), _pluginsPath(std::move(pluginsPath)),
          _pluginManager(*this), _sceneManager(*this), _assetManager(), _logger()
{
    _assetManager.addPath(_projectPath);

#ifdef _WIN32
    _logger.setLogDir(_projectPath + "\\Logs");
#else
    _logger.setLogDir(_projectPath + "/Logs");
#endif
    _openProject();
    _initDebugSettings();
    _initExectutionOrder();
    _initPluginsExecutionOrder();
    _initPrefabs();
    _initTemplates();
}

std::vector<std::string> &polymorph::engine::Engine::getExecOrder()
{
    return _execOrder;
}

std::vector<std::string> &polymorph::engine::Engine::getPluginExecOrder()
{
    return _pluginsExecOrder;
}

polymorph::engine::api::AssetManager &polymorph::engine::Engine::getAssetManager()
{
    return _assetManager;
}

polymorph::engine::api::SceneManager &polymorph::engine::Engine::getSceneManager()
{
    return _sceneManager;
}

polymorph::engine::debug::Logger &polymorph::engine::Engine::getLogger()
{
    return _logger;
}

polymorph::engine::time::Time &polymorph::engine::Engine::getTime()
{
    return _time;
}

int polymorph::engine::Engine::run()
{
    if (isExiting())
        return _exitCode;
    while (!_exit) {
        _time.computeDeltaTime();
        _sceneManager.checkQueuedScene();
        _sceneManager.resetLoading();
        _pluginManager.preProcessing();
        auto scene = _sceneManager.getCurrentScene();
        scene->start();
        scene->update();
        _pluginManager.lateUpdate();
        _pluginManager.postProcessing();
        scene->lateUpdate();
        scene->updateAddQueueList();
        scene->updateDestroyQueueList();
    }
    _pluginManager.endingScripts();
    return _exitCode;
}

void polymorph::engine::Engine::loadEngine()
{
    _pluginsExecOrder = _projectConfig->getPluginsExecOrder();
    _pluginManager.loadPlugins(_pluginsPath, *_projectConfig->getPlugins(), *this);
    _initGameData();
    _sceneManager.setCurrentScene(*_scenes.begin());
    _sceneManager.getCurrentScene()->loadScene();
    _time = time::Time();
    _pluginManager.startingScripts();
}

polymorph::engine::api::PluginManager &polymorph::engine::Engine::getPluginManager()
{
    return _pluginManager;
}

void polymorph::engine::Engine::exit(polymorph::engine::ExitCode code)
{
    _exitCode = code;
    _exit = true;
}

std::string polymorph::engine::Engine::getProjectPath()
{
    return _projectPath;
}

std::string polymorph::engine::Engine::getTitle()
{
    return _projectName;
}

std::vector<std::shared_ptr<polymorph::engine::config::XmlEntity>> polymorph::engine::Engine::getPrefabs()
{
    return _prefabs;
}

bool polymorph::engine::Engine::isDebugMode()
{
    return _logger.isDebugBuild();
}

std::vector<std::shared_ptr<myxmlpp::Node>> polymorph::engine::Engine::getDefaultConfigs()
{
    return _defaultConfigs;
}

std::shared_ptr<myxmlpp::Node> polymorph::engine::Engine::getDefaultConfig(const std::string &type)
{
    for (auto &c: _defaultConfigs) {
        try {
            auto foundType = c->findAttribute("type")->getValue();
            if (foundType == type)
                return c;
        } catch (const myxmlpp::Exception &e) {
            _logger.log("Error while searching default config " + type + ": " + std::string(e.what()), debug::Logger::MINOR);
        }
    }
    throw debug::CoreException("No default config available for type '"+type+"'.", debug::Logger::DEBUG);
}

std::shared_ptr<polymorph::engine::Scene> polymorph::engine::Engine::findSceneByName(const std::string &name)
{
    for (auto & scene : _scenes) {
        if (scene->name == name)
            return scene;
    }
    return nullptr;
}

std::shared_ptr<polymorph::engine::Scene> polymorph::engine::Engine::findSceneById(const std::string &id)
{
    for (auto & scene : _scenes) {
        if (scene->id == id)
            return scene;
    }
    return nullptr;
}

void polymorph::engine::Engine::addScene(const std::shared_ptr<Scene> &scene)
{
    _scenes.push_back(scene);
}

void polymorph::engine::Engine::_openProject()
{
    _projectConfig = std::make_unique<config::XmlEngine>(_assetManager.tryResolve(_projectName + ".pcf.engine"));
}

void polymorph::engine::Engine::_initExectutionOrder()
{
    _execOrder = _projectConfig->getExecOrder();
}

void polymorph::engine::Engine::_initPluginsExecutionOrder()
{
    _pluginsExecOrder = _projectConfig->getPluginsExecOrder();
}

void polymorph::engine::Engine::_initDebugSettings()
{
    if (_projectConfig->getDebugMode())
        _logger.initLogInstance(debug::Logger::Mode::DEBUG_MODE);
    else
        _logger.initLogInstance(debug::Logger::Mode::RELEASE_MODE);
}

void polymorph::engine::Engine::_initPrefabs()
{
    auto prefabs = _projectConfig->getPrefabs();

    for (auto &prefab : *prefabs) {
        try {
            auto entity = std::make_shared<config::XmlEntity>(prefab, _logger);
            _prefabs.push_back(entity);
        } catch (const std::exception &e) {
            e.what();
        }
    }
}

void polymorph::engine::Engine::_initTemplates()
{
    auto templates = _projectConfig->getTemplates();

    for (auto &tmpl : *templates) {
        try {
            auto path = _projectPath + "/" + tmpl->findAttribute("path")->getValue();
#ifdef _WIN32
            std::replace(path.begin(), path.end(), '/', '\\');
#endif
            auto templateDoc = myxmlpp::Doc(path);
            _defaultConfigs.emplace_back(templateDoc.getRoot());
        } catch (const myxmlpp::Exception &e) {
            _logger.log(e.what(), debug::Logger::MINOR);
        } catch (const debug::ConfigurationException &e) {
            e.what();
        }
    }

    auto toAdd = _pluginManager.getTemplates();
    _defaultConfigs.insert(_defaultConfigs.end(), toAdd.begin(), toAdd.end());
}

void polymorph::engine::Engine::_initGameData()
{
    auto scenes = _projectConfig->getScenes();

    if (scenes->empty())
        throw debug::CoreException("No scenes found in project config.", debug::Logger::MAJOR);
    for (auto &scene : *scenes) {
        try {
            _scenes.emplace_back(std::make_shared<polymorph::engine::Scene>(scene, *this));
        } catch (const debug::ConfigurationException &e) {
            e.what();
        }
    }
}

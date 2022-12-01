/*
** EPITECH PROJECT, 2020
** APlugin.cpp
** File description:
** APlugin.cpp
*/

#include "polymorph/api/plugin/APlugin.hpp"
#include "polymorph/config/XmlComponent.hpp"
#include "polymorph/debug/exception/plugin/CorruptedPluginException.hpp"
#include "polymorph/debug/exception/plugin/PluginNotFoundException.hpp"

namespace polymorph::engine::api
{

    APlugin::APlugin(config::XmlNode &data, Engine &game,
                     std::string PluginsPath) : _data(data), _game(game),
                                                pluginManager(game.getPluginManager()),
                                                assetManager(game.getAssetManager())
    {
        try {
            _packageName = _data.findAttribute("name")->getValue();
            _isEnabled = _data.findAttribute("enabled")->getValueBool();
        } catch (myxmlpp::AttributeNotFoundException &e) {
            throw debug::CorruptedPluginException((_packageName.empty()) ? _pluginsPath : _packageName);
        }
        _loadConfig();
        if (!_isEnabled)
            return;
        _loadTemplates();
        _loadPrefabs();
    }

    bool APlugin::isEnabled()
    {
        return _isEnabled;
    }

    bool APlugin::hasComponent(std::string &type)
    {
        return _factory->hasComponent(type);
    }

    bool APlugin::hasObject(std::string &type)
    {
        return _objectFactory->hasObject(type);
    }

    bool APlugin::hasPrefab(const std::string &id)
    {
        return (std::find_if(_prefabs.begin(), _prefabs.end(),
        [&id](const std::shared_ptr<config::XmlEntity> &prefab) {
            return (prefab->getId() == id);
        }) != _prefabs.end());
    }

    std::shared_ptr<config::XmlEntity> &
    APlugin::getPrefabConf(const std::string &id)
    {
        return *std::find_if(_prefabs.begin(), _prefabs.end(), [id](const std::shared_ptr<config::XmlEntity> &prefab) {
            return prefab->getId() == id;
        });
    }

    std::vector<config::XmlComponent> &APlugin::getComponentTemplates()
    {
        return _templates;
    }

    void APlugin::preUpdateInternalSystems(std::shared_ptr<Scene> &scene)
    {

    }

    void APlugin::updateInternalSystems(std::shared_ptr<Scene> &scene)
    {

    }

    void APlugin::postUpdateInternalSystems(std::shared_ptr<Scene> &scene)
    {

    }

    void APlugin::startScripts(std::shared_ptr<Scene> &scene)
    {

    }

    void APlugin::endScripts(std::shared_ptr<Scene> &scene)
    {

    }

    void APlugin::_loadPrefabs()
    {
        auto prefabs = _doc->getRoot()->findChild("Prefabs");

        for (auto &t: *prefabs) {
            _prefabs.emplace_back(std::make_shared<config::XmlEntity>(t, _game.getLogger()));
        }
    }

    void APlugin::_loadTemplates()
    {
        auto prefabs = _doc->getRoot()->findChild("Templates");

        for (auto &t: *prefabs) {
            _prefabs.emplace_back(std::make_shared<config::XmlComponent>(GameObject(), t, _game.getLogger()));
        }
    }

    void APlugin::_loadConfig()
    {
        try {
            _doc = std::make_shared<myxmlpp::Doc>(_pluginsPath + "/" + _packageName + ".pcf.plugin");
        } catch (myxmlpp::NoFileException &e) {
            throw debug::CorruptedPluginException(_packageName);
        } catch (myxmlpp::FileException &e) {
            throw debug::CorruptedPluginException(_packageName);
        } catch (myxmlpp::ParsingException &e) {
            throw debug::CorruptedPluginException(_packageName);
        }
    }

    std::string APlugin::getPluginName()
    {
        return _packageName;
    }

    void APlugin::build()
    {
        createConfig(_configs);
    }

    safe_ptr<APluginConfig> APlugin::getConfig(const std::string &type)
    {
        for (auto &config : _configs) {
            if (config->getType() == type)
                return safe_ptr<APluginConfig>(config);
        }
        return safe_ptr<APluginConfig>(nullptr);
    }
} // api
#include "AppConfig.h"
#include <QFile>
#include <QDebug>
#include <yaml-cpp/yaml.h>

AppConfig::AppConfig(const QString &path)
    : m_path(path)
{
    if (!QFile::exists(path)) {
        qWarning() << "Config file does not exist:" << path;
        m_valid = false;
        return;
    }

    YAML::Node root;
    try {
        root = YAML::LoadFile(path.toStdString());
    } catch (const std::exception &e) {
        qWarning() << "YAML parse error:" << e.what();
        m_valid = false;
        return;
    }

    m_valid = true;

    // 
    // Config
    //
    m_mainApp = loadNamedItem(root["app"]);

    m_leftClick = loadNamedItem(root["left_click"]);
    m_leftToggle = loadNamedItem(root["left_click_toggle"]);

    m_quitApp = loadNamedItem(root["quit"]);

    //
    // Menu
    //
    if (root["menu"] && root["menu"].IsSequence()) {
        for (const auto &item : root["menu"]) {

            // separator
            if (item["separator"] && item["separator"].as<bool>()) {
                MenuItem sep;
                sep.isSeparator = true;
                m_menuItems.append(sep);
                continue;
            }

            // menu entry with name + cmd
            if (item["name"] && item["cmd"]) {
                MenuItem mi;
                mi = loadNamedItem(item);
                m_menuItems.append(mi);
            }
        }
    }
}

bool AppConfig::isValid() const
{
    return m_valid;
}


MenuItem AppConfig::loadNamedItem(const YAML::Node &node)
{
    MenuItem item;

    if (!node) {
        return item;  // empty
    }

    if (node["name"])
        item.name = QString::fromStdString(node["name"].as<std::string>());

    if (node["cmd"])
        item.command = QString::fromStdString(node["cmd"].as<std::string>());

    if (node["tooltip"])
        item.tooltip = QString::fromStdString(node["tooltip"].as<std::string>());

    if (node["icon"])
        item.icon = QString::fromStdString(node["icon"].as<std::string>());

    return item;
}

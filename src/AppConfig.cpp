// AppConfig.cpp
#include "AppConfig.h"
#include <QSettings>
#include <QFile>
#include <QDebug>

AppConfig::AppConfig(const QString &path) : m_path(path)
{
    if (!QFile::exists(path)) {
        m_valid = false;
        return;
    }

    QSettings cfg(path, QSettings::IniFormat);
    m_appName = cfg.value("App/name", "").toString();
    m_startCmd = cfg.value("Commands/start_cmd", "").toString();
    m_stopCmd  = cfg.value("Commands/stop_cmd",  "").toString();
    m_iconNormal = cfg.value("Icons/normal_icon", "").toString();
    m_iconRunning = cfg.value("Icons/running_icon",  "").toString();
    m_valid = true;
}

bool AppConfig::isValid() const {
    return m_valid;
}

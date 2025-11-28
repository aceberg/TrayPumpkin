#include "ConfigFinder.h"

#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDebug>

QString ConfigFinder::getHomeConfigPath()
{
    QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return home + "/.config/TrayPumpkin/config.yaml";
}

QString ConfigFinder::getDefaultConfigPath()
{
    return "/usr/share/tray-pumpkin/default-config.yaml";
}

void ConfigFinder::ensureUserConfigExists()
{
    QString homeConfig = getHomeConfigPath();
    QString defaultConfig = getDefaultConfigPath();

    // If config already exists → no copying
    if (QFile::exists(homeConfig))
        return;

    // Make sure directory exists
    QFileInfo fi(homeConfig);
    QDir().mkpath(fi.path());

    // Copy config.yaml
    if (QFile::exists(defaultConfig)) {
        if (QFile::copy(defaultConfig, homeConfig)) {
            qDebug() << "Default config copied to" << homeConfig;
        } else {
            qWarning() << "Failed to copy default config to home directory";
        }
    }
}

QString ConfigFinder::findConfig(const QString &cmdPath)
{
    // 1. Custom config via -c
    if (!cmdPath.isEmpty()) {
        if (QFile::exists(cmdPath)) {
            qDebug() << "Using config from -c:" << cmdPath;
            return cmdPath;
        }
        qWarning() << "Config file from -c does not exist:" << cmdPath;
    }

    // 2. Ensure user's config exists (auto-copy)
    ensureUserConfigExists();

    QString homeConfig = getHomeConfigPath();
    if (QFile::exists(homeConfig)) {
        qDebug() << "Using home config:" << homeConfig;
        return homeConfig;
    }

    // No config found
    return QString();
}

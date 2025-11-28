#pragma once
#include <QString>

class ConfigFinder
{
public:
    // Returns chosen config file path, or empty on failure
    static QString findConfig(const QString &cmdPath);

private:
    static QString getHomeConfigPath();    // ~/.config/TrayPumpkin/config.yaml
    static QString getDefaultConfigPath(); // /usr/share/tray-pumpkin/default-config.yaml

    static void ensureUserConfigExists();
};

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "AppConfig.h"
#include "ConfigFinder.h"
#include "TrayController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    // Parse command line
    QCommandLineParser parser;
    parser.setApplicationDescription("Tray Pumpkin - configurable tray icon and menu");
    parser.addHelpOption();

    QCommandLineOption configOpt(
        QStringList() << "c" << "config",
        "Path to config file (YAML).",
        "file"
    );
    parser.addOption(configOpt);
    parser.process(app);

    QString cmdConfigPath = parser.value(configOpt);
    QString configPath = ConfigFinder::findConfig(cmdConfigPath);

    if (configPath.isEmpty()) {
        qCritical() << "No config.yaml found!";
        return 1;
    }

    AppConfig config(configPath);
    if (!config.isValid()) {
        qCritical() << "Invalid config:" << configPath;
        return 1;
    }

    TrayController controller(config);

    return app.exec();
}
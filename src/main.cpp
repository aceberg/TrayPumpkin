#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "AppConfig.h"
#include "TrayController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    // Parse command line
    QCommandLineParser parser;
    parser.setApplicationDescription("Tray Pumpkin - YAML Tray App");
    parser.addHelpOption();

    QCommandLineOption configOpt(
        QStringList() << "c" << "config",
        "Path to config file (YAML).",
        "file"
    );
    parser.addOption(configOpt);

    parser.process(app);

    QString configPath = parser.value(configOpt);
    if (configPath.isEmpty()) {
        qWarning() << "No config file provided. Use: ./tray-pumpkin -c config.yaml";
        return 1;
    }

    // Load configuration
    AppConfig config(configPath);
    if (!config.isValid()) {
        qWarning() << "Invalid config. Exiting.";
        return 1;
    }

    // Create tray controller
    TrayController controller(config);

    return app.exec();
}

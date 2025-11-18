#include <QApplication>
#include <QDebug>
#include "AppConfig.h"
#include "TrayController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString configPath = "config.ini";

    // parse command-line args
    for (int i = 1; i < argc; ++i) {
        QString arg = argv[i];
        if (arg == "-c" && i + 1 < argc)
            configPath = argv[++i];
        else if (arg.startsWith("-c="))
            configPath = arg.mid(3);
    }

    AppConfig config(configPath);
    if (!config.isValid()) {
        qWarning() << "Config not found:" << configPath;
        // continue but start/stop will do nothing
    }

    TrayController tray(config);
    return app.exec();
}

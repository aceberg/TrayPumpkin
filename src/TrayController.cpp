#include "TrayController.h"
#include <QAction>
#include <QApplication>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>

TrayController::TrayController(const AppConfig &config, QObject *parent)
    : QObject(parent), m_config(config)
{
    m_tray = new QSystemTrayIcon(this);
    m_menu = new QMenu();

    setupMenu();

    runMenuItem(m_config.mainApp());

    // Handle left click toggle Start/Stop
    connect(m_tray, &QSystemTrayIcon::activated,
            this, &TrayController::handleLeftClick);

    m_tray->setContextMenu(m_menu);
    m_tray->show();
}

//
// Build menu from YAML
//
void TrayController::setupMenu()
{
    //
    // About
    //
    QAction *aboutAction = m_menu->addAction("About " + m_config.mainApp().name);
    connect(aboutAction, &QAction::triggered, this, &TrayController::showAboutDialog);

    m_menu->addSeparator();

    //
    // Dynamic YAML menu items
    //
    for (const MenuItem &item : m_config.menuItems()) {
        if (item.isSeparator) {
            m_menu->addSeparator();
            continue;
        }

        QAction *action = m_menu->addAction(item.name);

        connect(action, &QAction::triggered, this, [this, item]() {
            runMenuItem(item);
        });
    }

    if (!m_config.menuItems().isEmpty())
        m_menu->addSeparator();

    //
    // Quit
    //
    m_quitAction = m_menu->addAction("Quit");
    connect(m_quitAction, &QAction::triggered, this, &TrayController::quitApp);
}

//
// Run cmd, change icon and tooltip
//
void TrayController::runMenuItem(const MenuItem &item)
{
    if (item.isSeparator)
        return;

    if (!item.command.isEmpty()) {
        QProcess::startDetached("/bin/sh", {"-c", item.command});
    }

    if (!item.icon.isEmpty())
        m_tray->setIcon(QIcon(item.icon));

    if (!item.tooltip.isEmpty())
        m_tray->setToolTip(item.tooltip);
}

//
// Toggle on left-click
//
void TrayController::handleLeftClick(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) { // left-click
        if (m_running && 
            (!m_config.leftToggle().command.isEmpty() 
            || !m_config.leftToggle().icon.isEmpty()
            || !m_config.leftToggle().tooltip.isEmpty())
        ) {
            m_running = false;
            runMenuItem(m_config.leftToggle());
        } else {
            m_running = true;
            runMenuItem(m_config.leftClick());
        }
    }
}

//
// Quit: first run quit cmd, then exit
//
void TrayController::quitApp()
{
    runMenuItem(m_config.quitApp());

    qApp->quit();
}


// 
// Show About
// 
void TrayController::showAboutDialog()
{
    QString iconPath = "/usr/share/tray-pumpkin/icons/tray-pumpkin.png";

    QPixmap iconPixmap(iconPath);
    if (iconPixmap.isNull()) {
        // fallback to a generic Qt icon
        iconPixmap = QApplication::windowIcon().pixmap(64, 64);
    }

    QString text = QString(R"(
        <b>TrayPumpkin</b><br>
        Version: <b>%1</b><br><br>
        Lightweight configurable tray icon and menu<br><br>
        Author: Andrew Erlikh<br>
        Licence: MIT<br>
        Homepage: <a href='https://github.com/aceberg/TrayPumpkin'>
        https://github.com/aceberg/TrayPumpkin</a><br>
        Donations: <a href='https://github.com/aceberg#donate'>
        https://github.com/aceberg#donate</a><br>
    )").arg(APP_VERSION);

    QMessageBox msgBox;
    msgBox.setWindowTitle("About TrayPumpkin");

    msgBox.setTextFormat(Qt::RichText);
    msgBox.setTextInteractionFlags(Qt::TextBrowserInteraction);
    msgBox.setText(text);

    msgBox.setIconPixmap(iconPixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    msgBox.exec();
}


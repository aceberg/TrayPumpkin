// TrayController.cpp
#include "TrayController.h"
#include "AppConfig.h"
#include <KStatusNotifierItem>
#include <QMenu>
#include <QProcess>
#include <QDebug>
#include <QApplication>

TrayController::TrayController(const AppConfig &config)
    : m_config(config),
      iconNormal(config.iconNormal()),
      iconRunning(config.iconRunning())
{
    m_menu = new QMenu();
    QAction *titleAction = m_menu->addAction(m_config.appName());
    titleAction->setEnabled(false);
    m_menu->addSeparator();
    QAction *startAction = m_menu->addAction("Start");
    QAction *stopAction  = m_menu->addAction("Stop");
    m_menu->addSeparator();
    QAction *quitAction  = m_menu->addAction("Quit");

    m_item = new KStatusNotifierItem();
    m_item->setToolTipTitle(m_config.appName());
    m_item->setContextMenu(m_menu);
    m_item->setCategory(KStatusNotifierItem::ApplicationStatus);
    m_item->setStatus(KStatusNotifierItem::Active);
    m_item->setIconByPixmap(iconNormal.pixmap(24,24));

    QObject::connect(startAction, &QAction::triggered, this, &TrayController::start);
    QObject::connect(stopAction,  &QAction::triggered, this, &TrayController::stop);
    QObject::connect(quitAction, &QAction::triggered, [this](){ 
        stop();
        qApp->quit(); 
    });

    QObject::connect(m_item, &KStatusNotifierItem::activateRequested,
                     this, &TrayController::toggle);
}

void TrayController::runCommand(const QString &cmd)
{
    if (cmd.isEmpty()) return;
    QProcess::startDetached("/bin/sh", {"-c", cmd});
}

void TrayController::start()
{
    running = true;
    m_item->setIconByPixmap(iconRunning.pixmap(24,24));
    runCommand(m_config.startCmd());
}

void TrayController::stop()
{
    running = false;
    m_item->setIconByPixmap(iconNormal.pixmap(24,24));
    runCommand(m_config.stopCmd());
}

void TrayController::toggle()
{
    running ? stop() : start();
}

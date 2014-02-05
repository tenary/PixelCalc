#include <QFileDialog>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMenuBar>
#include <QLabel>

#include "mainwindow.h"
#include "displaywidget.h"

QAction * addAction(QMenu * menu, QString title, QObject * receiver, const char * slot, QString key)
{
    QAction * action = new QAction(title, 0);
    if (key.size()) action->setShortcut(QKeySequence(key));

    QObject::connect(action, SIGNAL(triggered(bool)), receiver, slot);
    if (menu) menu->addAction(action);
    return action;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget * central_widget = new QWidget();
    QGridLayout * layout = new QGridLayout();

    QScrollArea * area = new QScrollArea();
    DisplayWidget * display = new DisplayWidget();
    QLabel * info_label = new QLabel("");

    area->setWidget(display);

    layout->addWidget(area);
    layout->addWidget(info_label);
    layout->setRowStretch(0, 1);

    central_widget->setLayout(layout);
    setCentralWidget(central_widget);

    initMenu();

    showMaximized();

    connect(this, SIGNAL(emitFileName(QString )), display, SLOT(loadFile(QString )));
}

void MainWindow::initMenu()
{
    QMenu * menu = menuBar()->addMenu(tr("Файл"));

    ::addAction(menu, tr("Открыть файл"), this, SLOT(openFile()), tr("Ctrl+O"));
    menu->addSeparator();
    ::addAction(menu, tr("Выход"), this, SLOT(close()), tr("Ctrl+Q"));
}

void MainWindow::openFile()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Открытие"));
    if (!file_name.isEmpty()) emit emitFileName(file_name);
}

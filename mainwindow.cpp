#include "mainwindow.h"
#include <QGridLayout>

MainWindow::MainWindow() {
    auto *widget = new QWidget;
    setCentralWidget(widget);

    auto *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(topFiller);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    setMinimumSize(160, 160);
    resize(480, 320);
}
#include "mainwindow.h"
#include <QGridLayout>
#include <QtMath>

MainWindow::MainWindow() {
    createSeries(1000, 2, 5, 1, 3, M_PI_2);
    prepareChart();

    auto *widget = new QWidget;
    setCentralWidget(widget);


    auto *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(chartView);
    widget->setLayout(layout);

    setMinimumSize(640, 480);
}

MainWindow::~MainWindow() {
    delete series;
    delete chart;
    delete chartView;
    delete[] sliders;
    delete sliders;
}

void MainWindow::createSeries(int size, qreal A, qreal a, qreal B, qreal b, qreal f) {
    series = new QLineSeries;
    for (int i = 0; i < size; ++i) {
        series->append(A * qSin(a * i + f), B * qCos(b * i));
    }
}

void MainWindow::prepareChart() {
    chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}
#include "mainwindow.h"
#include <QGridLayout>
#include <QtMath>

#define SERIES_SIZE 10000

MainWindow::MainWindow() {
    prepareSliders();
    createSeries(-2, 5, 1, 1, M_PI_2);
    prepareChart();

    centralWidget = new QWidget;
    setCentralWidget(centralWidget);


    auto *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(sliders[A]);
    layout->addWidget(sliders[a]);
    layout->addWidget(sliders[B]);
    layout->addWidget(sliders[b]);
    layout->addWidget(sliders[f]);
    layout->addWidget(chartView);
    centralWidget->setLayout(layout);

    setMinimumSize(640, 480);
}

MainWindow::~MainWindow() {
    delete series;
    delete chart;
    delete chartView;
    for (int i = 0; i < 5; ++i) {
        delete sliders[i];
    }
    delete centralWidget;
}

void MainWindow::prepareSliders() {
    for (int i = 0; i < 5; ++i) {
        sliders[i] = new QSlider(Qt::Horizontal);
        sliders[i]->setMaximum(-10);
        sliders[i]->setMaximum(10);
        sliders[i]->setValue(0);
        sliders[i]->setTickInterval(1);
        sliders[i]->setTickPosition(QSlider::TicksAbove);
        connect(sliders[i], &QSlider::sliderReleased, this, &MainWindow::inputChanged);
    }
}

void MainWindow::createSeries(qreal A, qreal a, qreal B, qreal b, qreal f) {
    series = new QLineSeries;
    qreal t = 0;
    for (int i = 0; i < SERIES_SIZE; ++i) {
        t += 0.1;
        series->append(A * qSin(a * t + f), B * qCos(b * t));
    }
}

void MainWindow::prepareChart() {
    chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::inputChanged() {
    createSeries(sliders[A]->value(), sliders[a]->value(), sliders[B]->value(),
                 sliders[b]->value(), sliders[f]->value());
    centralWidget->layout()->removeWidget(chartView);
    delete chart;
    delete chartView;
    prepareChart();
    centralWidget->layout()->addWidget(chartView);
    update();
}
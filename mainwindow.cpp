#include "mainwindow.h"
#include <QGridLayout>
#include <QtMath>

#define SERIES_SIZE 100000
#define T_INTERVAL 0.01

MainWindow::MainWindow() {


    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto dock = new QDockWidget(tr("Create your Lissajous curve"), this);
    slidersWidget = new QWidget(dock);
    slidersLayout = new QGridLayout(slidersWidget);
    auto *formula = new QLabel(tr("x=Asin(at+f) y=Bcos(bt)"), slidersWidget);
    slidersLayout->addWidget(formula, 0, 0, 1, 3);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWidget(slidersWidget);

    prepareSliders();
    prepareSliderLabels();
    createSeries(sliders[A]->value(), sliders[a]->value(), sliders[B]->value(), sliders[b]->value(),
                 sliders[f]->value());
    prepareChart();


    auto *centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->setContentsMargins(5, 5, 5, 5);
    centralLayout->addWidget(chartView);

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
    delete slidersWidget;
}

void MainWindow::prepareSliders() {
    for (int i = 0; i < 5; ++i) {
        sliders[i] = new QSlider(Qt::Horizontal);
        sliders[i]->setMaximum(-10);
        sliders[i]->setMaximum(10);
        sliders[i]->setValue(5 - i);
        sliders[i]->setTickInterval(1);
        sliders[i]->setTickPosition(QSlider::TicksAbove);
        connect(sliders[i], &QSlider::sliderReleased, this, &MainWindow::inputChanged);
        slidersLayout->addWidget(sliders[i], i + 1, 1, i + 1, 3);
    }
}

void MainWindow::createSeries(qreal A, qreal a, qreal B, qreal b, qreal f) {
    series = new QLineSeries;
    qreal t = 0;
    for (int i = 0; i < SERIES_SIZE; ++i) {
        t += T_INTERVAL;
        series->append(A * qSin(a * t + f), B * qSin(b * t));
    }
}

void MainWindow::prepareChart() {
    chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::inputChanged() {
    for (int i = 0; i < 5; ++i) {
        delete sliderLabels[i];
    }
    prepareSliderLabels();
    createSeries(sliders[A]->value(), sliders[a]->value(), sliders[B]->value(),
                 sliders[b]->value(), sliders[f]->value());
    centralWidget->layout()->removeWidget(chartView);
    delete chart;
    delete chartView;
    prepareChart();
    centralWidget->layout()->addWidget(chartView);
    update();
}

void MainWindow::prepareSliderLabels() {
    sliderLabels[A] = new QLabel((tr("A = ") + QString::number(sliders[A]->value())));
    sliderLabels[a] = new QLabel((tr("a = ") + QString::number(sliders[a]->value())));
    sliderLabels[B] = new QLabel((tr("B = ") + QString::number(sliders[B]->value())));
    sliderLabels[b] = new QLabel((tr("b = ") + QString::number(sliders[b]->value())));
    sliderLabels[f] = new QLabel((tr("f = ") + QString::number(sliders[f]->value())));
    for (int i = 0; i < 5; ++i) {
        slidersLayout->addWidget(sliderLabels[i], i + 1, 0, i + 1, 1);
    }

}
#ifndef LISSAJOU_MAINWINDOW_H
#define LISSAJOU_MAINWINDOW_H

#include <QMainWindow>
#include <QtGlobal>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QSlider>
#include <QPushButton>

enum variables {
    A = 0,
    a = 1,
    B = 2,
    b = 3,
    f = 4
};

using namespace QtCharts;

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow() override;

private:
    QWidget *centralWidget;
    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;

    QSlider *sliders[5];

    void prepareSliders();
    void createSeries(qreal A, qreal a, qreal B, qreal b, qreal f);
    void prepareChart();

private slots:
    void inputChanged();
};

#endif //LISSAJOU_MAINWINDOW_H

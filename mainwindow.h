#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <vector>
#include "mydialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void clearWindow();
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    void paintPixel(int x, int y, QRgb color);
    void paintSegment(int startX, int startY, int endX, int endY, QRgb color);
    void extPaintSegment(int startX, int startY, int endX, int endY, QRgb color, bool antial);
    void paintCircle(int centerX, int centerY, int r, QRgb color);
    void symetricPoints(int x, int y, int x0, int y0, QRgb color);
    void gradient(int steps, int startX, int endX, QRgb colorStart, QRgb colorEnd);
    QPoint singleBezierPoint(QPoint startPoint, QPoint endPoint, QPoint control1, QPoint control2, float t);
    void bezierCurve(QPoint start, QPoint end, QPoint control1, QPoint control2, QRgb color, float step);
    void floodFill(int x, int y, QRgb oldColor, QRgb newColor);
    void putPixel(QPoint p, QRgb color);
    QPoint translation(QPoint in, int movX, int movY);
    QPoint rotation(QPoint in, double fi);
    QPoint scale(QPoint in, double scalX, double scalY);
    QPoint shear(QPoint in, double shearX, double shearY);
    QPoint rotationAroundCenter(QPoint in, double fi);
    QPoint scaleAroundCenter(QPoint in, double scalX, double scalY);
    void bSpline(std::vector<QPoint>& points, QRgb color, float step);
    bool isConfig();
    void setConfig(bool state);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QImage result;
    int windowSizeX = 800;
    int windowSizeY = 600;
    bool configFlag;
};

#endif // MAINWINDOW_H

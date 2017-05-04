#include "mainwindow.h"
#include <QtWidgets/QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent)
{
    setMinimumSize(windowSizeX,windowSizeY);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, result);
}

/* Ustawia jeden pixel na podstawie wspułrzędnych */

void MainWindow::paintPixel(int x, int y, QRgb color)
{
    result.setPixel(x, y, color);
}

/* Rysuje linię algorytmem Bresenhama o podanym kolorze, pozwala ostatnim parametrem wybrać czy ma być włączony antyaliasing czy nie */
void MainWindow::extPaintSegment(int startX, int startY, int endX, int endY, QRgb color, bool antial)
{
    QColor colorHelp = QColor(color);

    int dirX;
    int dirY;

    if(startX <= endX)
    {
        dirX = 1;
    }
    else
    {
        dirX = -1;
    }

    if(startY <= endY)
    {
        dirY = 1;
    }
    else
    {
        dirY = -1;
    }

    int distX = abs(endX - startX);
    int distY = abs(endY - startY);
    int err;

    result.setPixel(startX, startY, color);
    if(distX >= distY)
    {
        err = distX/2;
        for(int i = 0; i < distX; i++)
        {
            startX = startX + dirX;
            err = err - distY;
            if(err < 0)
            {
                startY = startY + dirY;
                err = err + distX;
                if(antial == true)
                {
                if(dirY > 0)
                {
                    QColor bColor = result.pixelColor(QPoint(startX+1, startY-1));
                    QColor aColor = QColor(color);
                    result.setPixelColor(QPoint(startX, startY-1), QColor(qRgb((bColor.red()+aColor.red())/2, (bColor.green()+aColor.green())/2, (bColor.blue()+aColor.blue())/2)));
                    bColor = result.pixelColor(QPoint(startX+1, startY-1));
                    result.setPixelColor(QPoint(startX-1, startY), QColor(qRgb((bColor.red()+aColor.red())/2, (bColor.green()+aColor.green())/2, (bColor.blue()+aColor.blue())/2)));
                }
                else if(dirY < 0)
                {
                    QColor bColor = result.pixelColor(QPoint(startX+1, startY+1));
                    QColor aColor = QColor(color);
                    result.setPixelColor(startX, startY+1, QColor(qRgb((bColor.red()+aColor.red())/2, (bColor.green()+aColor.green())/2, (bColor.blue()+aColor.blue())/2)));
                    bColor = result.pixelColor(QPoint(startX-2, startY));
                    result.setPixelColor(startX-1, startY, QColor(qRgb((bColor.red()+aColor.red())/2, (bColor.green()+aColor.green())/2, (bColor.blue()+aColor.blue())/2)));
                }
                }
            }
            result.setPixel(startX, startY, color);
        }
        return;
    }
    else
    {
        err = distY/2;
        for(int i = 0; i < distY; i++)
        {
            startY = startY + dirY;
            err = err - distX;
            if(err < 0)
            {
                startX = startX + dirX;
                err = err + distY;
                if(antial == true)
                {
                if(dirX > 0)
                {
                    QColor aColor = QColor(color);
                    QColor bColor = result.pixelColor(QPoint(startX+1, startY+1));
                    result.setPixelColor(QPoint(startX, startY+1), QColor(qRgb((bColor.red()+aColor.red())/2, (bColor.green()+aColor.green())/2, (bColor.blue()+aColor.blue())/2)));
                    bColor = result.pixelColor(QPoint(startX-2, startY));
                    result.setPixelColor(QPoint(startX-1, startY), QColor(qRgb((bColor.red()+aColor.red())/2, (bColor.green()+aColor.green())/2, (bColor.blue()+aColor.blue())/2)));
                }
                else if(dirX < 0)
                {
                    QColor aColor = QColor(color);
                    QColor bColor = result.pixelColor(QPoint(startX-1, startY));
                    result.setPixelColor(startX, startY-1, QColor(qRgb((bColor.red()+aColor.red())/2, (bColor.green()+aColor.green())/2, (bColor.blue()+aColor.blue())/2)));
                    result.setPixelColor(startX+1, startY, QColor(qRgb((bColor.red()+aColor.red())/2, (bColor.green()+aColor.green())/2, (bColor.blue()+aColor.blue())/2)));
                }
                }
            }
            result.setPixel(startX, startY, color);
        }
        return;
    }
}

/* Funkcja pomocnicza */
inline void MainWindow::symetricPoints(int x, int y, int x0, int y0, QRgb color)
{
    result.setPixel(x+x0, y+y0, color);
    result.setPixel(y+x0, x+y0, color);
    result.setPixel(y+x0, -x+y0, color);
    result.setPixel(x+x0, -y+y0, color);
    result.setPixel(-y+x0, -x+y0, color);
    result.setPixel(-x+x0, -y+y0, color);
    result.setPixel(-y+x0, x+y0, color);
    result.setPixel(-x+x0, y+y0, color);
}


/* Rysuje okrąg pozwalając wybrać współrzędne środka, promień i kolor */
void MainWindow::paintCircle(int centerX, int centerY, int r, QRgb color)
{
    int x;
    int y;
    int d;

    x = 0;
    y = r;
    d = 5 - 4 * r;
    symetricPoints(x, y, centerX, centerY, color);
    while(y > x)
    {
        if(d < 0)
        {
            d = d + (x * 8 + 12);
            x++;
        }
        else
        {
            d = d + ((x - y) * 8 + 20);
            x++;
            y--;
        }
        symetricPoints(x, y, centerX, centerY, color);
    }
}


/* Funkcja pomocnicza */
inline float absFloat(float a)
{
    if(a < 0)
        return -a;
    return a;
}

void MainWindow::putPixel(QPoint p, QRgb color)
{
    result.setPixelColor(p.x(), p.y(), color);
}


/* Rysuje gradient o dowolnej współrzędnej końca i początku X, z dowolnymi kolorami. Można wybrać pewne warianty wg interfejsu klawiszowego */
void MainWindow::gradient(int steps, int startX, int endX, QRgb colorStart, QRgb colorEnd)
{
    if(steps <= 0)
    {
        return;
    }

   int dist = abs(endX - startX);
   int stepSize = dist/steps;

   //qDebug() << "Długość kroku: " << stepSize;

   int multiR = 1;
   int multiG = 1;
   int multiB = 1;

   QColor hColorStart = QColor(colorStart); //Zapisanie pomocniczo koloru do zmiennej
   QColor hColorEnd = QColor(colorEnd);

   if(hColorStart.redF() > hColorEnd.redF())
   {
       multiR = -1;
   }

   if(hColorStart.greenF() > hColorEnd.greenF())
   {
       multiG = -1;
   }

   if(hColorStart.blueF() > hColorEnd.blueF())
   {
       multiB = -1;
   }

   float rr, gg, bb;
    rr = absFloat(hColorEnd.redF() - hColorStart.redF())/dist*256;
    gg = absFloat(hColorEnd.greenF() - hColorStart.greenF())/dist*256;
    bb = absFloat(hColorEnd.blueF() - hColorStart.blueF())/dist*256;

    //qDebug() << "Różnica kolorów: " << rr << gg << bb;

    for(int i = startX; i < endX; i = i + stepSize)
    {
        for(int j = 0; j < stepSize; j++)
        {
            extPaintSegment(i+j, 0, i+j, 200, qRgb(hColorStart.red()+(i*multiR*rr), hColorStart.green()+(i*multiG*gg), hColorStart.blue()+(i*multiB*bb)), false);
        }
    }
}

/* Funkcja pomocnicza - rysuje punkty krzywej Bezier(2 punkty kontrolne), pozwala wybrać gęstość punktów <0, 1> */
/* Punkt startowy i końcowy koniecznie jako pierwszy i drugi parametr */
/* Kontrolne 1 i 2 jako kolejne 2 */
QPoint MainWindow::singleBezierPoint(QPoint startPoint, QPoint endPoint, QPoint control1, QPoint control2, float t)
{
    QPoint ret;
    ret.setX(pow(1-t, 3)*startPoint.x() + pow(1-t, 2)*3*t*control1.x() + (1-t)*3*t*t*control2.x() + t*t*t*endPoint.x());
    ret.setY(pow(1-t, 3)*startPoint.y() + pow(1-t, 2)*3*t*control1.y() + (1-t)*3*t*t*control2.y() + t*t*t*endPoint.y());
    //qDebug() << ret.x() << " " << ret.y();
    return ret;
}

/* Na podstawie funkcji pomocniczej łączy punkty odcinkami w wybranym kolorze */
void MainWindow::bezierCurve(QPoint start, QPoint end, QPoint control1, QPoint control2, QRgb color,float step)
{
    QPoint help = start;
    QPoint bezierPoint1;

    for(float i = step; i <= 1.0; i+=step)
    {
        bezierPoint1 = singleBezierPoint(start, end, control1, control2, i);
        extPaintSegment(help.x(), help.y(), bezierPoint1.x(), bezierPoint1.y(), color, true);
        help = bezierPoint1;
    }
}

/* Przyjmuje referencję na vector z punktami i rysuje krzywą B-splain o podanym kolorze. Największa skuteczność przy step = 0.01 */
void MainWindow::bSpline(std::vector<QPoint>& points, QRgb color, float step) {

    int parts = points.size()-3;

    QPoint control1;
    QPoint control2;
    QPoint start;
    QPoint end;

    for(int i = 0; i < parts; i++)
    {
        if(i == 0)
        {
            start = QPoint(points[0].x(), points[0].y());
            control1 = QPoint(points[1].x(), points[1].y());
            control2 = QPoint(0.5 * points[1].x() + 0.5 * points[2].x(), 0.5 * points[1].y() + 0.5 * points[2].y());

            int fx1 = 0.666 * points[2].x() + 0.333 * points[3].x();
            int fy1 = 0.666 * points[2].y() + 0.333 * points[3].y();
            end = QPoint(0.5 * control2.x() + 0.5 * fx1, 0.5 * control2.y() + 0.5 * fy1);
        }
        else if(i == parts-1)
        {
            control1 = QPoint(0.5 * points[parts].x() + 0.5 * points[parts + 1].x(), 0.5 * points[parts].y() + 0.5 * points[parts + 1].y());
            control2 = QPoint(points[parts+1].x(), points[parts+1].y());
            end = QPoint(points[parts+ 2].x(), points[parts+2].y());
        }
        else
        {
            control1 = QPoint(0.666 * points[i + 1].x() + 0.333 * points[i + 2].x(),0.666 * points[i + 1].y() + 0.333 * points[i + 2].y());
            control2 = QPoint(0.333 * points[i + 1].x() + 0.666 * points[i + 2].x(), 0.333 * points[i + 1].y() + 0.666 * points[i + 2].y());

            int fx1 = 0.666 * points[i + 2].x() + 0.333 * points[i + 3].x();
            int fy1 = 0.666 * points[i + 2].y() + 0.333 * points[i + 3].y();
            end = QPoint(0.5 * control2.x() + 0.5 * fx1, 0.5 * control2.y() + 0.5 * fy1);
        }

        bezierCurve(start, end, control1, control2, color, step);
        start = end;
    }
}

/* Rekurencyjny algorytm wypełniania obszarów */
void MainWindow::floodFill(int x, int y, QRgb oldColor, QRgb newColor)
{
    QColor pixelColor = result.pixelColor(x, y);
    QColor colorReplacement = QColor(newColor);
    if(pixelColor.toRgb() != oldColor)
    {
        return;
    }
    else
    {
        result.setPixelColor(x, y, colorReplacement);
        floodFill(x-1, y, oldColor, newColor);
        floodFill(x, y+1, oldColor, newColor);
        floodFill(x+1, y, oldColor, newColor);
        floodFill(x, y-1, oldColor, newColor);
    }
}

/* Przesunięcie punktu o X i Y */
QPoint MainWindow::translation(QPoint in, int movX, int movY)
{
    int matIn[3] = {in.x(), in.y(), 1};
    int matMul[3][3] = {1, 0, 0,
                        0, 1, 0,
                        movX, movY, 1};
    int matOut[3] = {0,0,0};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            matOut[i] = matOut[i] + matMul[j][i] * matIn[j];
        }
    }

    qDebug() << matOut[0] << ", " << matOut[1];

    return QPoint(matOut[0], matOut[1]);
}

/* Obrót punktu wokół środka układu wspólrzędnych - zgodnie z ruchem wskazówek zegara o kąt podany w radianach */
QPoint MainWindow::rotation(QPoint in, double fi)
{
    int matIn[3] = {in.x(), in.y(), 1};
    double cos_fi = cos(fi);
    double sin_fi = sin(fi);

    double matMul[3][3] = {cos_fi, sin_fi, 0,
                            -sin_fi, cos_fi, 0,
                            0, 0, 1};
    double matOut[3] = {0,0,0};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            matOut[i] = matOut[i] + matMul[j][i] * matIn[j];
        }
    }

    qDebug() << matOut[0] << ", " << matOut[1] << ", " << matOut[2];

    return QPoint((int) matOut[0], (int) matOut[1]);

}

/* Obrót punktu wokół środka obrazu o kąt podany w radianach */
QPoint MainWindow::rotationAroundCenter(QPoint in, double fi)
{
    int centerX = width()/2;
    int centerY = height()/2;

    in = QPoint(in.x() - centerX, in.y() - centerY);

    in = rotation(in, fi);

    in = QPoint(in.x() + centerX, in.y() + centerY);

    qDebug() << in.x() << "," << in.y();

    return in;
}

/* Skalowanie o zmiennoprzecinkowe wartości X i Y, względem środka układu współrzędnych */
QPoint MainWindow::scale(QPoint in, double scalX, double scalY)
{
    int matIn[3] = {in.x(), in.y(), 1};

    double matMul[3][3] = {scalX, 0, 0,
                            0, scalY, 0,
                            0, 0, 1};
    double matOut[3] = {0,0,0};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            matOut[i] = matOut[i] + matMul[j][i] * matIn[j];
        }
    }

    qDebug() << matOut[0] << ", " << matOut[1];

    return QPoint((int) matOut[0], (int) matOut[1]);

}

/* Skalowanie wg zmiennych X i Y, względem środka obrazu */
QPoint MainWindow::scaleAroundCenter(QPoint in, double scalX, double scalY)
{
    int centerX = width()/2;
    int centerY = height()/2;

    in = QPoint(in.x() - centerX, in.y() - centerY);

    in = scale(in, scalX, scalY);

    in = QPoint(in.x() + centerX, in.y() + centerY);

    qDebug() << in.x() << "," << in.y();

    return in;
}

/* Pochylenie wg wartości X i Y */
QPoint MainWindow::shear(QPoint in, double shearX, double shearY)
{
    int matIn[3] = {in.x(), in.y(), 1};

    double matMul[3][3] = {1, shearY, 0,
                            shearX, 1, 0,
                            0, 0, 1};
    double matOut[3] = {0,0,0};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            matOut[i] = matOut[i] + matMul[j][i] * matIn[j];
        }
    }

    qDebug() << matOut[0] << ", " << matOut[1];

    return QPoint((int) matOut[0], (int) matOut[1]);
}

void MainWindow::clearWindow()
{
    result = QImage(windowSizeX, windowSizeY, QImage::Format_RGB888);
    result.fill(qRgb(0,0,0));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        close();
        setConfig(false);
    }

    if(event->key() == Qt::Key_L)
    {
        qDebug() << "Wcisnąłeś (L)ine";
        extPaintSegment(10, 10, 789, 589, qRgb(255,0,0), true);
        update();
        setConfig(false);
    }

    if(event->key() == Qt::Key_C)
    {
        qDebug() << "Wcisnąłeś (C)ircle";
        paintCircle(width()/2, height()/2, 88, qRgb(88,88,88));
        update();
        setConfig(false);
    }

    if(event->key() == Qt::Key_B)
    {
        qDebug() << "Wcisnąłeś (B)ezier";
        bezierCurve(QPoint(100,300), QPoint(500, 50), QPoint(50, 100), QPoint(200, 100), qRgb(0,255,0), 0.05);
        update();
        setConfig(false);
    }

    if(event->key() == Qt::Key_S)
    {
        qDebug() << "Wcisnąłeś (S)pline";
        std::vector<QPoint> vec;
        vec.push_back(QPoint(100, 300));
        vec.push_back(QPoint(50, 100));
        vec.push_back(QPoint(300, 150));
        vec.push_back(QPoint(400, 300));
        vec.push_back(QPoint(500, 500));
        vec.push_back(QPoint(600, 550));

        bSpline(vec, qRgb(0,0,255), 0.01);
        update();
        setConfig(false);
    }

    /* Po wciśnięciu G tworzymy gradient. Do naciśnięcia X możemy wybrać trzy predefiniowane zestawy kolorów za pomocą 0, 1, 2. X lub inna opcja (Linia, Krzywa, ...) wychodzi z konfiguracji gradientu */
    if(event->key() == Qt::Key_G)
    {
        qDebug() << "Wcisnąłeś (G)radient";
        gradient(10, 50, 750, qRgb(255,255,255), qRgb(0,0,0));
        //Wchodzimy w tryb ustawiania koloru gradientu
        setConfig(true);
        update();
    }

    if(event->key() == Qt::Key_E)
    {
        qDebug() << "Wcisnąłeś (E)rase window";
        clearWindow();
        update();
        setConfig(false);
    }

    if(event->key() == Qt::Key_X && isConfig())
    {
        setConfig(false);
    }

    if(event->key() == Qt::Key_0 && isConfig())
    {
        gradient(10, 50, 750, qRgb(0,0,0), qRgb(255,255,255));
        update();
    }

    if(event->key() == Qt::Key_1 && isConfig())
    {
        gradient(10, 50, 750, qRgb(255,0,0), qRgb(88,88,88));
        update();
    }

    if(event->key() == Qt::Key_2 && isConfig())
    {
        gradient(10, 50, 750, qRgb(255,255,0), qRgb(0,0,255));
        update();
    }
}

void MainWindow::setConfig(bool state)
{
    this->configFlag = state;
}

bool MainWindow::isConfig()
{
    return this->configFlag;
}

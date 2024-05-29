#ifndef GRAPHICWINDOW_H
#define GRAPHICWINDOW_H

#include <QDialog>
#include "list.h"
#include <QFileDialog>
#include <QPainter>
#include "logic.h"
#include "QResizeEvent"

#define SPACER_FOR_VALUES_ON_OX 30
#define SPACER_FOR_VALUES_ON_OY 25
#define WIDTH 1280 + SPACER_FOR_VALUES_ON_OX
#define HEIGHT 720 + SPACER_FOR_VALUES_ON_OY
#define EPS 0.001

namespace Ui {
class GraphicWindow;
}

class GraphicWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GraphicWindow(AppContext* context, QWidget *parent = nullptr);
    ~GraphicWindow();
    void paintEvent();
    int width;
    int height;
    QPixmap* pix;

private:
    AppContext* context;
    Ui::GraphicWindow *ui;
    void resizeEvent(QResizeEvent *evt);
    void drawMarksOnOY(QPainter &painter, int minY, int yStep);
    void drawGraphic(QPainter &painter, int minY, int minX, int xStep, int yStep, int heightOX);
    bool initialized;
    int w;
    int h;
};

#endif // GRAPHICWINDOW_H

#include "graphicwindow.h"
#include "ui_graphicwindow.h"

GraphicWindow::GraphicWindow(AppContext* context, QWidget *parent): QDialog(parent), context(context), ui(new Ui::GraphicWindow),initialized(false)
{
    ui->setupUi(this);
    width = WIDTH;
    height = HEIGHT;
    pix = new QPixmap(width, height);
}

GraphicWindow::~GraphicWindow()
{
    delete ui;
}

void GraphicWindow::resizeEvent(QResizeEvent *evt)
{

    QPixmap bkgnd(*pix);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);

    QDialog::resizeEvent(evt);

}

void GraphicWindow::paintEvent() {
    QPainter painter(pix);
    pix->fill(Qt::white);
    painter.setPen(Qt::black);
    painter.drawPoint(0 + SPACER_FOR_VALUES_ON_OX, 0 + SPACER_FOR_VALUES_ON_OY);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(5 + SPACER_FOR_VALUES_ON_OX, 0, 5 + SPACER_FOR_VALUES_ON_OX, height - SPACER_FOR_VALUES_ON_OY);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    int maxX = context->lastYear;
    int minX = context->firstYear;
    float maxY = context->max;
    float minY = context->min;
    int xStep = ((width - SPACER_FOR_VALUES_ON_OX - 20) / (maxX - minX));
    float yStep = ((height - SPACER_FOR_VALUES_ON_OY - 40) * 0.91 / (maxY - minY));
    float heightOX = (((height - SPACER_FOR_VALUES_ON_OY - 40) - yStep * (0 - minY)) + 6);
    if (atoi(context->column) != 2) {
        painter.drawLine(0 + SPACER_FOR_VALUES_ON_OX, (height - SPACER_FOR_VALUES_ON_OY - 5) , width - 10, (height - SPACER_FOR_VALUES_ON_OY - 5));
    } else {
        painter.drawLine(0 + SPACER_FOR_VALUES_ON_OX, heightOX , width - 10, heightOX);
    }
    drawMarksOnOY(painter, minY, yStep);
    drawGraphic(painter, minY, minX, xStep, yStep, heightOX);


}

void GraphicWindow::drawMarksOnOY(QPainter &painter, int minY, int yStep) {
    Node* current = context->table->first;
    painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
    int fontSize = 12;
    QFont font("Franklin Gothic Book", fontSize);
    painter.setFont(font);
    while(current) {
        if (!(strcmp(current->data.region , context->region))) {
            int currentX = 0;
            int currentY = (((height - SPACER_FOR_VALUES_ON_OY - 40) - (yStep * (returnField(current, atoi(context->column)) - minY))) + 6);
            painter.drawPoint(currentX + SPACER_FOR_VALUES_ON_OX + 5, currentY);
            float value = returnField(current, atoi(context->column));
            QString oY = "%1";
            oY = oY.arg(value);
            painter.drawText(currentX + 3 , currentY, oY);
            current = current->next;
        } else {
            current = current->next;
        }
    }
}

void GraphicWindow::drawGraphic(QPainter &painter, int minY, int minX, int xStep, int yStep, int heightOX) {
    int previousX = 0 + SPACER_FOR_VALUES_ON_OX;
    int previousY = 0;
    Node* current = context->table->first;
    QPen penForMax = QPen(Qt::yellow, 7, Qt::SolidLine, Qt::RoundCap);
    QPen penForMedian = QPen(Qt::green, 7, Qt::SolidLine, Qt::RoundCap);
    QPen penForMin = QPen(Qt::blue, 7, Qt::SolidLine, Qt::RoundCap);
    QPen penForDefault = QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap);
    QPen penForGraph = QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap);
    int fontSize = 12;
    QFont font("Franklin Gothic Book", fontSize);
    painter.setFont(font);
    while (current) {
        if (!(strcmp(current->data.region , context->region))) {
            int currentX = ((xStep * (current->data.year - minX)) + 6) + SPACER_FOR_VALUES_ON_OX;
            int currentY = (((height - SPACER_FOR_VALUES_ON_OY - 40) - (yStep * (returnField(current, atoi(context->column)) - minY))) + 6);
            float value = returnField(current, atoi(context->column));
            if (fabs(value - context->max) < EPS) {
                painter.setPen(penForMax);
                painter.drawPoint(currentX, currentY);
            } else if (fabs(value - context->median) < EPS) {
                painter.setPen(penForMedian);
                painter.drawPoint(currentX, currentY);
            } else if (fabs(value - context->min) < EPS) {
                painter.setPen(penForMin);
                painter.drawPoint(currentX, currentY);
            } else {
                painter.setPen(penForDefault);
                painter.drawPoint(currentX, currentY);
            }
            painter.setPen(penForDefault);
            painter.drawPoint(currentX, (height - SPACER_FOR_VALUES_ON_OY - 5));
            float years = current->data.year;
            QString oY = "%1";
            QString oX = "%1";
            oY = oY.arg(value);
            oX = oX.arg(years);
            painter.drawText(currentX , currentY - SPACER_FOR_VALUES_ON_OY + 20, oY);
            if (atoi(context->column) != 2) {
                painter.drawText(currentX, (height - 10), oX);
            } else {
                painter.drawText(currentX, heightOX + 7, oX);
            }
            painter.setPen(penForGraph);
            if (previousX != 0 + SPACER_FOR_VALUES_ON_OX && previousY != 0) {
                painter.drawLine(currentX, currentY, previousX, previousY);
            }
            previousX = currentX;
            previousY = currentY;
            current = current->next;
        } else {
            current = current->next;
        }
    }
}

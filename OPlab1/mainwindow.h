#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appcontext.h"
#include <QClipboard>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    AppContext context;

private slots:
    void onInputBinSystemClicked();
    void onInputOctSystemClicked();
    void onInputDecSystemClicked();
    void onOutputBinSystemClicked();
    void onOutputOctSystemClicked();
    void onOutputDecSystemClicked();
    void onSwapClicked();
    void onCopyClicked();
    void onTranslateClicked();
    void updateLabel();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appcontext.h"
#include <QClipboard>

#define NO_ERRORS ""
#define NOT_CHECKED_INPUT_NUM_SYS "Не выбрана входная система счисления"
#define NOT_CHECKED_OUTPUT_NUM_SYS "Не выбрана выходная система счисления"
#define NOT_CHECKED_NUM_SYSTEMS "Не выбраны системы счисления"
#define INCORRECT_COMBINATION_OF_SYMBOLS "Введена недопустимая комбинация символов для выбранной системы счисления"
#define EXIT_FROM_INT "Выход за пределы значений 4-х байтового знакового целого числа"

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
    void errorHandler();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

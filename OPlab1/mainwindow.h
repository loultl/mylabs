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
#define NO_OUTPUT_FOR_SWAP "Не с чем менять входное значение"
#define BINARY 2
#define TERNARY 3
#define QUATERNARY 4
#define QUINARY 5
#define SENARY 6
#define SEPTENARY 7
#define OCTAL 8
#define NONARY 9
#define DECIMAL 10
#define UNDECIMAL 11
#define DUODECIMAL 12
#define TRIDECIMAL 13
#define TETRADECIMAL 14
#define PENTADECIMAL 15
#define HEXADECIMAL 16

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
    void inputOfInputNumSys();
    void inputOfOutputNumSys();
    void onSwapClicked();
    void onCopyClicked();
    void onTranslateClicked();
    void updateLabel();
    void errorHandler();
    void inputRadioButtonHandler();
    void outputRadioButtonHandler();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

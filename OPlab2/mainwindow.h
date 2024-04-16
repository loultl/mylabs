#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "appcontext.h"
#include "entrypoint.h"
#include <string.h>
#include "list.h"
#include <string>
#include <QTableView>
#include <QStandardItemModel>
#include "errors.h"

#define NO_ERRORS "Ошибок нет"
#define COLUMN_ERROR "Некорректный номер столбца"
#define REGION_ERROR "Некорректный регион"
#define FILE_NOT_CHOSEN_ERROR "Вы не выбрали файл"
#define FILE_ERROR "Файл не может быть открыт"
#define EMPTY_TABLE_ERROR "В таблице нет данных, невозможно посчитать параметры"
#define ALLOCATION_ERROR "Память не может быть выделена"


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

private slots:
    void onSelectFileButtonClicked();
    void onLoadDataButtonClicked();
    void onCalculateMetricsClicked();

    void setTable();
    void setRow(Node* current,int row);
    void setFullTable(Node* current);
    void setRegionTable(Node* current);

    void updateLabels();
    void errorsHandler();

private:
    Ui::MainWindow *ui;
    AppContext context;
};
#endif // MAINWINDOW_H

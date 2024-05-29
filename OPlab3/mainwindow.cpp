#include "mainwindow.h"
#include "graphicwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->selectButton, &QPushButton::clicked, this, &MainWindow::onSelectFileButtonClicked);
    connect(ui->loadDataButton, &QPushButton::clicked, this, &MainWindow::onLoadDataButtonClicked);
    connect(ui->calculateMetricsButton, &QPushButton::clicked, this, &MainWindow::onCalculateMetricsClicked);
    doOperation(Initialization, &context, NULL);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSelectFileButtonClicked() {
    AppParams param;
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите CSV файл", "", "CSV файлы (*.csv)");
    std::string stdStr = fileName.toStdString();
    const char* cStr = stdStr.c_str();
    strcpy(param.fileName, cStr);
    doOperation(SetFileName, &context, &param);
    ui->fileNameLabel->setText(context.fileName);
}

void MainWindow::onLoadDataButtonClicked() {
    AppParams param;
    std::string stdStrRegion = ui->regionLineEdit->text().toStdString();
    const char* cStrRegion = stdStrRegion.c_str();
    strcpy(param.region, cStrRegion);
    doOperation(SetRegion,&context,&param);
    doOperation(Loading,&context, NULL);
    updateLabels();
}

void MainWindow::onCalculateMetricsClicked() {
    AppParams param;
    std::string stdStrRegion = ui->regionLineEdit->text().toStdString();
    const char* cStrRegion = stdStrRegion.c_str();
    strcpy(param.region, cStrRegion);
    std::string stdStrColumn = ui->columnNumLineEdit->text().toStdString();
    const char* cStrColumn = stdStrColumn.c_str();
    strcpy(param.column, cStrColumn);
    doOperation(SetRegion, &context, &param);
    doOperation(SetIndex, &context, &param);
    doOperation(Calculation, &context, NULL);
    if (context.errorData == NoErrors && (strcmp(context.region, "") != 0)) {
        GraphicWindow graphWindow(&context);
        graphWindow.setModal(true);
        graphWindow.paintEvent();
        graphWindow.exec();
    }
    updateLabels();
}

void MainWindow::updateLabels() {
    if (context.table != NULL) {
        setTable();
    }
    ui->minLabel->setText(QString::number(context.min));
    ui->maxLabel->setText(QString::number(context.max));
    ui->medianLabel->setText(QString::number(context.median));
    ui->allLinesLabel->setText(QString::number(context.numberOfLines));
    ui->errorLinesLabel->setText(QString::number(context.numberOfErrorLines));
    ui->successLinesLabel->setText(QString::number(context.numberOfSuccessLines));
    errorsHandler();
}

void MainWindow::errorsHandler() {
    switch(context.errorData) {
    case NoErrors:
        ui->errorLabel->setText(NO_ERRORS);
        break;
    case FileError:
        ui->errorLabel->setText(FILE_ERROR);
        break;
    case ColumnError:
        ui->errorLabel->setText(COLUMN_ERROR);
        break;
    case RegionError:
        ui->errorLabel->setText(REGION_ERROR);
        break;
    case EmptyFileNameError:
        ui->errorLabel->setText(FILE_NOT_CHOSEN_ERROR);
        break;
    case EmptyTableError:
        ui->errorLabel->setText(EMPTY_TABLE_ERROR);
        break;
    case MemoryAllocationError:
        ui->errorLabel->setText(ALLOCATION_ERROR);
        break;
    }

}

void MainWindow::setTable() {
    char* tableHeader = (char*)malloc(INIT_TABLE_HEADER_LENGHT);
    strcpy(tableHeader, context.tableHeader);
    QStringList headers;
    char* token = strtok(tableHeader, ",");
    int columnCount = 0;
    while (token != NULL)
    {
        headers << token;
        token = strtok(NULL, ",");
        columnCount++;
    }
    ui->tableWidget->setRowCount(INIT_ROWS);
    ui->tableWidget->setColumnCount(columnCount);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    Node* current = context.table->first;
    if (!strcmp(context.region, "")) {
        setFullTable(current);
    } else {
        setRegionTable(current);
    }
    free(tableHeader);
}

void MainWindow::setFullTable(Node* current) {
    int row = 0;
    ui->tableWidget->setRowCount(context.numberOfSuccessLines);
    while (current) {
        setRow(current, row);
        current = current->next;
        ++row;
    }
}

void MainWindow::setRegionTable(Node* current) {
    int row = 0;
    while (current) {
        if (!strcmp(current->data.region, context.region)) {
            ui->tableWidget->insertRow(row);
            setRow(current,row);
            ++row;
        }
        current = current->next;
    }
}

void MainWindow::setRow(Node* current,int row) {
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(current->data.year)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString(current->data.region)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(current->data.naturalPopulationGrowth)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(current->data.birthRate)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(current->data.deathRate)));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(current->data.generalDemographicWeight)));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(current->data.urbanisation)));
}

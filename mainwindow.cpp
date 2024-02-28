#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "entrypoint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->inBinSys, &QPushButton::clicked, this, &MainWindow::onInputBinSystemClicked);
    connect(ui->inOctSys, &QPushButton::clicked, this, &MainWindow::onInputOctSystemClicked);
    connect(ui->inDecSys, &QPushButton::clicked, this, &MainWindow::onInputDecSystemClicked);
    connect(ui->outBinSys, &QPushButton::clicked, this, &MainWindow::onOutputBinSystemClicked);
    connect(ui->outOctSys, &QPushButton::clicked, this, &MainWindow::onOutputOctSystemClicked);
    connect(ui->outDecSys, &QPushButton::clicked, this, &MainWindow::onOutputDecSystemClicked);
    connect(ui->translateButton, &QPushButton::clicked, this, &MainWindow::onTranslateClicked);

    updateLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInputBinSystemClicked() {
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    param->inputNumSystem = 2;
    doOperation(InputOfInputNumSystem, &context, param);
    free(param);
}

void MainWindow::onInputOctSystemClicked() {
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    param->inputNumSystem = 8;
    doOperation(InputOfInputNumSystem, &context, param);
    free(param);
}

void MainWindow::onInputDecSystemClicked() {
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    param->inputNumSystem = 10;
    doOperation(InputOfInputNumSystem, &context, param);
    free(param);
}

void MainWindow::onOutputBinSystemClicked() {
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    param->outputNumSystem = 2;
    doOperation(InputOfOutputNumSystem, &context, param);
    free(param);
}

void MainWindow::onOutputOctSystemClicked() {
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    param->outputNumSystem = 8;
    doOperation(InputOfOutputNumSystem, &context, param);
    free(param);
}

void MainWindow::onOutputDecSystemClicked() {
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    param->outputNumSystem = 10;
    doOperation(InputOfOutputNumSystem, &context, param);
    free(param);
}

void MainWindow::onTranslateClicked()
{
    std::string str = ui->inputValue->text().toStdString();
    const char* cStr = str.c_str();
    const char* error = isValidInput(cStr, &context);
    if (error)
    {
        snprintf(context.errorLine, sizeof(context.errorLine), "Ошибка: %s", error);
        updateLabel();
        return;
    }
    AppParams* param = (AppParams*)malloc(sizeof(AppParams));
    if (param == nullptr)
    {
        snprintf(context.errorLine, sizeof(context.errorLine), "Ошибка: Ошибка выделения памяти для параметров");
        updateLabel();
        return;
    }
    param->newValue = cStr;
    doOperation(InputOfValue, &context, param);
    doOperation(Translate, &context, param);
    updateLabel();
    free(param);
}

void MainWindow::updateLabel() {
    if (context.errorLine[0] != '\0') {
        ui->errorLine->setText(QString::fromUtf8(context.errorLine));
        ui->translatedValue->clear();
    } else {
        ui->errorLine->clear();
        ui->translatedValue->setText(QString::fromUtf8(context.translatedValue));
    }
}



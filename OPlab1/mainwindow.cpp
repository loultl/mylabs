#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "entrypoint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    doOperation(Initialization, &context, nullptr);
    connect(ui->inBinSys, &QPushButton::clicked, this, &MainWindow::onInputBinSystemClicked);
    connect(ui->inOctSys, &QPushButton::clicked, this, &MainWindow::onInputOctSystemClicked);
    connect(ui->inDecSys, &QPushButton::clicked, this, &MainWindow::onInputDecSystemClicked);
    connect(ui->outBinSys, &QPushButton::clicked, this, &MainWindow::onOutputBinSystemClicked);
    connect(ui->outOctSys, &QPushButton::clicked, this, &MainWindow::onOutputOctSystemClicked);
    connect(ui->outDecSys, &QPushButton::clicked, this, &MainWindow::onOutputDecSystemClicked);
    connect(ui->swapButton, &QPushButton::clicked, this, &MainWindow::onSwapClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::onCopyClicked);
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

void MainWindow::onSwapClicked()
{
    doOperation(Swap, &context, nullptr);
    updateLabel();
}

void MainWindow::onCopyClicked()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    QString textToClipboard = ui->translatedValue->text();
    clipboard->setText(textToClipboard);
}

void MainWindow::onTranslateClicked()
{
    std::string str = ui->inputValue->text().toStdString();
    const char* cStr = str.c_str();
    AppParams* param = (AppParams*)malloc(sizeof(AppParams));
    param->newValue = cStr;
    doOperation(InputOfValue, &context, param);
    doOperation(Validation, &context, param);
    if (context.errorCode != NoErrors)
    {
        errorHandler();
    }
    else
    {
        doOperation(Translate, &context, param);
    }
    updateLabel();
    free(param);
}

void MainWindow::updateLabel()
{
    if (context.errorCode != NoErrors)
    {
        ui->translatedValue->clear();
    }
    else
    {
        ui->errorLine->clear();
        ui->inputValue->setText(context.inputValue);
        ui->translatedValue->setText(context.translatedValue);
    }
}

void MainWindow::errorHandler()
{
    switch(context.errorCode)
    {
    case(NotCheckedInputNumSystem):
        ui->errorLine->setText(NOT_CHECKED_INPUT_NUM_SYS);
        break;
    case(NotCheckedOutputNumSystem):
        ui->errorLine->setText(NOT_CHECKED_OUTPUT_NUM_SYS);
        break;
    case(NotCheckedNumSystems):
        ui->errorLine->setText(NOT_CHECKED_NUM_SYSTEMS);
        break;
    case(IncorrectCombibationOfSymbols):
        ui->errorLine->setText(INCORRECT_COMBINATION_OF_SYMBOLS);
        break;
    case(ExitFromInt):
        ui->errorLine->setText(EXIT_FROM_INT);
        break;
    }
}




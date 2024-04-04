#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "entrypoint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    doOperation(Initialization, &context, nullptr);
    connect(ui->swapButton, &QPushButton::clicked, this, &MainWindow::onSwapClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::onCopyClicked);
    connect(ui->translateButton, &QPushButton::clicked, this, &MainWindow::onTranslateClicked);
    updateLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inputOfInputNumSys()
{
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    if (ui->inBinSys->isChecked())
        param->inputNumSystem = BINARY;
    else if (ui->in3Sys->isChecked())
        param->inputNumSystem = TERNARY;
    else if (ui->in4Sys->isChecked())
        param->inputNumSystem = QUATERNARY;
    else if (ui->in5Sys->isChecked())
        param->inputNumSystem = QUINARY;
    else if (ui->in6Sys->isChecked())
        param->inputNumSystem = SENARY;
    else if (ui->in7Sys->isChecked())
        param->inputNumSystem = SEPTENARY;
    else if (ui->inOctSys->isChecked())
        param->inputNumSystem = OCTAL;
    else if (ui->in9Sys->isChecked())
        param->inputNumSystem = NONARY;
    else if (ui->inDecSys->isChecked())
        param->inputNumSystem = DECIMAL;
    else if (ui->in11Sys->isChecked())
        param->inputNumSystem = UNDECIMAL;
    else if (ui->in12Sys->isChecked())
        param->inputNumSystem = DUODECIMAL;
    else if (ui->in13Sys->isChecked())
        param->inputNumSystem = TRIDECIMAL;
    else if (ui->in14Sys->isChecked())
        param->inputNumSystem = TETRADECIMAL;
    else if (ui->in15Sys->isChecked())
        param->inputNumSystem = PENTADECIMAL;
    else if (ui->inHexSys->isChecked())
        param->inputNumSystem = HEXADECIMAL;
    else
        param->inputNumSystem = DEFAULT_VALUE;
    doOperation(InputOfInputNumSystem, &context, param);
    free(param);
}

void MainWindow::inputOfOutputNumSys()
{
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    if (ui->outBinSys->isChecked())
        param->outputNumSystem = BINARY;
    else if (ui->out3Sys->isChecked())
        param->outputNumSystem = TERNARY;
    else if (ui->out4Sys->isChecked())
        param->outputNumSystem = QUATERNARY;
    else if (ui->out5Sys->isChecked())
        param->outputNumSystem = QUINARY;
    else if (ui->out6Sys->isChecked())
        param->outputNumSystem = SENARY;
    else if (ui->out7Sys->isChecked())
        param->outputNumSystem = SEPTENARY;
    else if (ui->outOctSys->isChecked())
        param->outputNumSystem = OCTAL;
    else if (ui->out9Sys->isChecked())
        param->outputNumSystem = NONARY;
    else if (ui->outDecSys->isChecked())
        param->outputNumSystem = DECIMAL;
    else if (ui->out11Sys->isChecked())
        param->outputNumSystem = UNDECIMAL;
    else if (ui->out12Sys->isChecked())
        param->outputNumSystem = DUODECIMAL;
    else if (ui->out13Sys->isChecked())
        param->outputNumSystem = TRIDECIMAL;
    else if (ui->out14Sys->isChecked())
        param->outputNumSystem = TETRADECIMAL;
    else if (ui->out15Sys->isChecked())
        param->outputNumSystem = PENTADECIMAL;
    else if (ui->outHexSys->isChecked())
        param->outputNumSystem = HEXADECIMAL;
    else
        param->outputNumSystem = DEFAULT_VALUE;
    doOperation(InputOfOutputNumSystem, &context, param);
    free(param);
}

void MainWindow::onSwapClicked()
{
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    std::string str = ui->inputValue->text().toStdString();
    const char* cStr = str.c_str();
    param->newValue = (char*)cStr;

    doOperation(InputOfValue, &context, param);
    updateLabel();

    doOperation(Swap, &context, param);
    updateLabel();

    free(param);
}

void MainWindow::onCopyClicked()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    QString textToClipboard = ui->translatedValue->text();
    clipboard->setText(textToClipboard);
}

void MainWindow::onTranslateClicked()
{
    inputOfInputNumSys();
    inputOfOutputNumSys();
    std::string str = ui->inputValue->text().toStdString();
    const char* cStr = str.c_str();
    AppParams* param = (AppParams*)malloc(sizeof(AppParams));
    param->newValue = (char*)cStr;

    doOperation(InputOfValue, &context, param);
    updateLabel();

    doOperation(Validation, &context, param);
    updateLabel();

    if (context.errorCode == NoErrors)
    {
        doOperation(Translate, &context, param);
        updateLabel();
    }

    free(param);
}

void MainWindow::updateLabel()
{
    inputRadioButtonHandler();
    outputRadioButtonHandler();
    ui->inputValue->setText(context.inputValue);
    ui->translatedValue->setText(context.translatedValue);
    errorHandler();
    if (context.errorCode != NoErrors)
        ui->translatedValue->clear();
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
    case(NoOutputForSwap):
        ui->errorLine->setText(NO_OUTPUT_FOR_SWAP);
        break;
    case(NoErrors):
        ui->errorLine->clear();
        break;
    }

}

void MainWindow::inputRadioButtonHandler()
{
    switch(context.inputNumSystem)
    {
    case(BINARY):
        ui->inBinSys->setChecked(true);
        break;
    case(TERNARY):
        ui->in3Sys->setChecked(true);
        break;
    case(QUATERNARY):
        ui->in4Sys->setChecked(true);
        break;
    case(QUINARY):
        ui->in5Sys->setChecked(true);
        break;
    case(SENARY):
        ui->in6Sys->setChecked(true);
        break;
    case(SEPTENARY):
        ui->in7Sys->setChecked(true);
        break;
    case(OCTAL):
        ui->inOctSys->setChecked(true);
        break;
    case(NONARY):
        ui->in9Sys->setChecked(true);
        break;
    case(DECIMAL):
        ui->inDecSys->setChecked(true);
        break;
    case(UNDECIMAL):
        ui->in11Sys->setChecked(true);
        break;
    case(DUODECIMAL):
        ui->in12Sys->setChecked(true);
        break;
    case(TRIDECIMAL):
        ui->in13Sys->setChecked(true);
        break;
    case(TETRADECIMAL):
        ui->in14Sys->setChecked(true);
        break;
    case(PENTADECIMAL):
        ui->in15Sys->setChecked(true);
        break;
    case(HEXADECIMAL):
        ui->inHexSys->setChecked(true);
        break;
    }
}

void MainWindow::outputRadioButtonHandler()
{
    switch(context.outputNumSystem)
    {
    case(BINARY):
        ui->outBinSys->setChecked(true);
        break;
    case(TERNARY):
        ui->out3Sys->setChecked(true);
        break;
    case(QUATERNARY):
        ui->out4Sys->setChecked(true);
        break;
    case(QUINARY):
        ui->out5Sys->setChecked(true);
        break;
    case(SENARY):
        ui->out6Sys->setChecked(true);
        break;
    case(SEPTENARY):
        ui->out7Sys->setChecked(true);
        break;
    case(OCTAL):
        ui->outOctSys->setChecked(true);
        break;
    case(NONARY):
        ui->out9Sys->setChecked(true);
        break;
    case(DECIMAL):
        ui->outDecSys->setChecked(true);
        break;
    case(UNDECIMAL):
        ui->out11Sys->setChecked(true);
        break;
    case(DUODECIMAL):
        ui->out12Sys->setChecked(true);
        break;
    case(TRIDECIMAL):
        ui->out13Sys->setChecked(true);
        break;
    case(TETRADECIMAL):
        ui->out14Sys->setChecked(true);
        break;
    case(PENTADECIMAL):
        ui->out15Sys->setChecked(true);
        break;
    case(HEXADECIMAL):
        ui->outHexSys->setChecked(true);
        break;
    }
}




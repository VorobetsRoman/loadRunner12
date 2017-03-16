#include "loadrunner.h"
#include "ui_loadrunner.h"
#include <QPushButton>
#include <QDebug>
#include <QCheckBox>
#include <QTextCodec>
#include <QFileDialog>
#include <QMessageBox>




//===================================== Конструктор
LoadRunner::LoadRunner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadRunner)
{
    ui->setupUi(this);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    tableSetup();
}




//===================================== Деструктор
LoadRunner::~LoadRunner()
{
    for (TableRecord *tablerow : tableRows) {
        tablerow->deleteLater();
    }
    delete ui;
}




//===================================== Настройка таблицы
void LoadRunner::tableSetup()
{
    ui->tbwProgramList->setColumnCount(7);

    QStringList hHeader {"Программа", "загрузить", "аргументы", "задержка", "", "", "Control"};
    ui->tbwProgramList->setHorizontalHeaderLabels(hHeader);

    ui->tbwProgramList->setRowCount(rowCount);

    for (int row = 0; row < rowCount; row++) {
        TableRecord *lrRecord = new TableRecord();
        tableRows.append(lrRecord);
        ui->tbwProgramList->setCellWidget(row, 0, lrRecord->getProgName());
        ui->tbwProgramList->setCellWidget(row, 1, lrRecord->getPbSelect());
        ui->tbwProgramList->setCellWidget(row, 2, lrRecord->getArguments());
        ui->tbwProgramList->setCellWidget(row, 3, lrRecord->getDelay());
        ui->tbwProgramList->setCellWidget(row, 4, lrRecord->getPbStart());
        ui->tbwProgramList->setCellWidget(row, 5, lrRecord->getPbReset());
        ui->tbwProgramList->setCellWidget(row, 6, lrRecord->getCbControl());
    }

    ui->tbwProgramList->setColumnWidth(1, 30);
    ui->tbwProgramList->setColumnWidth(3, 50);
    ui->tbwProgramList->setColumnWidth(4, 30);
    ui->tbwProgramList->setColumnWidth(5, 30);
    ui->tbwProgramList->setColumnWidth(6, 30);
}




//=====================================
void LoadRunner::resizeEvent(QResizeEvent*)
{
    ui->tbwProgramList->setColumnWidth(0, ui->tbwProgramList->width() - 42
                                       - ui->tbwProgramList->columnWidth(1)
                                       - ui->tbwProgramList->columnWidth(2)
                                       - ui->tbwProgramList->columnWidth(3)
                                       - ui->tbwProgramList->columnWidth(4)
                                       - ui->tbwProgramList->columnWidth(5)
                                       - ui->tbwProgramList->columnWidth(6)
                                       );
}




//===================================== Кнопка загрузки
void LoadRunner::on_pbLoad_released()
{
    QString caption {"Открыть конфигурацию запуска"};
    QString fileName = QFileDialog::getOpenFileName(0, caption, qApp->applicationDirPath(), "*.prs", 0);
    if (fileName == "") return;

    QFile presetFile (fileName);
    if (!presetFile.open(QIODevice::ReadOnly))
    {
        QString title {"Ошибка открытия файла"};
        QString context {"Ошибка открытия файла для чтения"};
        QMessageBox::warning(0, title, context);
        return;
    }

    int row {0};
    while (!presetFile.atEnd()) {
        QString nextStr = presetFile.readLine();
        tableRows.at(row)->setDataFromFile(&nextStr);
        if (++row > ui->tbwProgramList->rowCount()) break;
    }
    presetFile.close();
}




//===================================== Кнопка сохранения
void LoadRunner::on_pbSave_released()
{
    QString caption {"Сохранить конфигурацию запуска"};
    QString fileName = QFileDialog::getSaveFileName(0, caption, qApp->applicationDirPath(), "*.prs", 0);
    if (fileName == "") return;

    QFile presetFile(fileName);
    if (!presetFile.open(QIODevice::WriteOnly))
    {
        QString title {"Ошибка открытия файла"};
        QString context {"Ошибка открытия файла для записи"};
        QMessageBox::warning(0, title, context);
        return;
    }

    for (TableRecord *tableRow : tableRows) {
        tableRow->saveToFile(&presetFile);
    }
    presetFile.close();
}




//===================================== Кнопка выполнения
void LoadRunner::on_pbRun_released()
{
    for (TableRecord *tableRow : tableRows) {
        tableRow->runProgram();
    }
}




//===================================== Чекбокс контроля
void LoadRunner::on_cbRunControl_toggled(bool newValue)
{
    for (TableRecord *tableRow : tableRows) {
        tableRow->setControl(newValue);
    }
}




//=====================================
void LoadRunner::on_pbStop_released()
{
    for (TableRecord *tableRow : tableRows) {
        tableRow->stopProgram();
    }
}




//=====================================
void LoadRunner::on_pbReset_released()
{
    for (TableRecord *tableRow : tableRows) {
        tableRow->resetProgram();
    }
}




//=====================================

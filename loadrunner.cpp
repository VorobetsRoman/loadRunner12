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
    for (LrRecord *tablerow : tableRows) {
        tablerow->deleteLater();
    }
    delete ui;
}




//===================================== Настройка таблицы
void LoadRunner::tableSetup()
{
    ui->tbwProgramList->setColumnCount(8);

    QStringList hHeader {"Программа", "загрузить", "аргументы", "задержка", "", "", "", "Control"};
    ui->tbwProgramList->setHorizontalHeaderLabels(hHeader);

    ui->tbwProgramList->setRowCount(rowCount);

    for (int row = 0; row < rowCount; row++) {
        LrRecord *lrRecord = new LrRecord();
        tableRows.append(lrRecord);
        ui->tbwProgramList->setCellWidget(row, 0, lrRecord->getProgName());
        ui->tbwProgramList->setCellWidget(row, 1, lrRecord->getTbSelect());
        ui->tbwProgramList->setCellWidget(row, 2, lrRecord->getArguments());
        ui->tbwProgramList->setCellWidget(row, 3, lrRecord->getDelay());
        ui->tbwProgramList->setCellWidget(row, 4, lrRecord->getPbStart());
        ui->tbwProgramList->setCellWidget(row, 5, lrRecord->getPbStop());
        ui->tbwProgramList->setCellWidget(row, 6, lrRecord->getPbReset());
        ui->tbwProgramList->setCellWidget(row, 7, lrRecord->getCbControl());
    }

    ui->tbwProgramList->setColumnWidth(1, 30);
    ui->tbwProgramList->setColumnWidth(3, 50);
    ui->tbwProgramList->setColumnWidth(4, 30);
    ui->tbwProgramList->setColumnWidth(5, 30);
    ui->tbwProgramList->setColumnWidth(6, 30);
    ui->tbwProgramList->setColumnWidth(7, 60);
}




//===================================== Заполнение таблицы
void LoadRunner::reFillingSlot()
{
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

    for (LrRecord *tableRow : tableRows) {
        tableRow->saveToFile(&presetFile);
    }
    presetFile.close();
}




//===================================== Кнопка выполнения
void LoadRunner::on_pbRun_released()
{
}




//===================================== Чекбокс контроля
void LoadRunner::on_cbRunControl_toggled(bool)
{
}




//=====================================



#include "loadrunner.h"
#include "ui_loadrunner.h"
#include <QPushButton>
#include <QDebug>
#include <QCheckBox>
#include <QTextCodec>




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
}




//===================================== Кнопка сохранения
void LoadRunner::on_pbSave_released()
{
}




//===================================== Кнопка выполнения
void LoadRunner::on_pbRun_released()
{
}




//===================================== Чекбокс контроля
void LoadRunner::on_cbRunControl_toggled(bool)
{
    for (QCheckBox *cb : cbControlList){
        cb->setChecked(!cb->isChecked());
    }
}





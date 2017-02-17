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
    sourceData = new SourceData;

    ui->setupUi(this);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    programList = &sourceData->programList;

    tableSetup();

    //Внутренние сообщения
    connect(sourceData,           &SourceData::reFilling,
            this,                 &LoadRunner::reFilling      );
}




//===================================== Деструктор
LoadRunner::~LoadRunner()
{
    delete ui;
    if (sourceData) sourceData->deleteLater();
    for (QToolButton *pb : pbSelectList) {
        pb->deleteLater();
    }
    for (QPushButton *pb : pbPlayList) {
        pb->deleteLater();
    }
    for (QPushButton *pb : pbStopList) {
        pb->deleteLater();
    }
    for (QPushButton *pb : pbResetList) {
        pb->deleteLater();
    }
    for (QCheckBox *cb : cbControlList) {
        cb->deleteLater();
    }
}




//===================================== Настройка таблицы
void LoadRunner::tableSetup()
{
    ui->tbwProgramList->setColumnCount(8);

    QStringList hHeader {"Программа", "загрузить", "аргументы", "задержка", "P", "S", "R", "Control"};
    ui->tbwProgramList->setHorizontalHeaderLabels(hHeader);

    ui->tbwProgramList->setRowCount(rowCount);

    for (int i = 0; i < rowCount; i++)
    {
        QToolButton* pbSelect   = new QToolButton();
        ui->tbwProgramList      ->setCellWidget (i, 1, pbSelect);
        pbSelectList            .append         (pbSelect);

        QPushButton* pbPlay     = new QPushButton(QString("P"));
        ui->tbwProgramList      ->setCellWidget (i, 4, pbPlay);
        pbPlayList              .append         (pbPlay);

        QPushButton* pbStop     = new QPushButton(QString("S"));
        ui->tbwProgramList      ->setCellWidget (i, 5, pbStop);
        pbStopList              .append         (pbStop);

        QPushButton* pbReset    = new QPushButton(QString("R"));
        ui->tbwProgramList      ->setCellWidget (i, 6, pbReset);
        pbResetList             .append         (pbReset);

        QCheckBox* cbControl    = new QCheckBox();
        ui->tbwProgramList      ->setCellWidget (i, 7, cbControl);
        cbControlList           .append         (cbControl);
    }
    ui->tbwProgramList->setColumnWidth(1, 30);
    ui->tbwProgramList->setColumnWidth(3, 50);
    ui->tbwProgramList->setColumnWidth(4, 30);
    ui->tbwProgramList->setColumnWidth(5, 30);
    ui->tbwProgramList->setColumnWidth(6, 30);
    ui->tbwProgramList->setColumnWidth(7, 60);

    //Табличные кнопки
    for (QToolButton *pb : pbSelectList) {
        connect(pb,     &QToolButton::released,
                this,   &LoadRunner ::pbSelectPressed);
    }
    for (QPushButton *pb : pbPlayList) {
        connect(pb,     &QPushButton::released,
                this,   &LoadRunner ::pbPlayPressed);
    }
    for (QPushButton *pb : pbStopList) {
        connect(pb,     &QPushButton::released,
                this,   &LoadRunner ::pbStopPressed);
    }
    for (QPushButton *pb : pbResetList) {
        connect(pb,     &QPushButton::released,
                this,   &LoadRunner ::pbResetPressed);
    }
    for (QCheckBox *cb : cbControlList) {
        connect(cb,     &QCheckBox  ::toggled,
                this,   &LoadRunner ::cbCheckChecked);
    }
}



//===================================== Заполнение таблицы
void LoadRunner::reFilling()
{
    for (int i {0}, m {programList->size()}; i < m; i++)
    {
        QTableWidgetItem* twiPr = new QTableWidgetItem(programList->at(i)->programName);
        ui->tbwProgramList->setItem(i, 0, twiPr);

        QTableWidgetItem* twiAr = new QTableWidgetItem(programList->at(i)->programArgs);
        ui->tbwProgramList->setItem(i, 2, twiAr);

        QTableWidgetItem* twiDl = new QTableWidgetItem(programList->at(i)->delay);
        ui->tbwProgramList->setItem(i, 3, twiDl);
    }
}




//===================================== Нажата кнопка "Выбрать"
void LoadRunner::pbSelectPressed()
{
    QToolButton*    pbSender    = (QToolButton*)sender();
    int             i           = pbSelectList.indexOf(pbSender);
    sourceData->dataEdited(i, 1, QString(""));
}




//===================================== Нажата кнопка "Запустить"
void LoadRunner::pbPlayPressed()
{
    QPushButton*    pbSender    = (QPushButton*)sender();
    int             i           = pbPlayList.indexOf(pbSender);
    sourceData->runSelected(i, 0);
}




//===================================== Нажата кнопка "Остановить"
void LoadRunner::pbStopPressed()
{
    QPushButton*    pbSender    = (QPushButton*)sender();
    int             i           = pbStopList.indexOf(pbSender);
    sourceData->runSelected(i, 1);
}




//===================================== Нажата кнопка "Перезапустить"
void LoadRunner::pbResetPressed()
{
    QPushButton*    pbSender    = (QPushButton*)sender();
    int             i           = pbResetList.indexOf(pbSender);
    sourceData->runSelected(i, 2);
}




//===================================== Проверка выполнения
void LoadRunner::cbCheckChecked(bool value)
{
    QCheckBox*  cbSender    = (QCheckBox*)sender();
    int         i           = cbControlList.indexOf(cbSender);
    sourceData->setChecked(i, value);
}




//================================================== Кнопка загрузки
void LoadRunner::on_pbLoad_released()
{
    sourceData->loadPreset();
}




//================================================== Кнопка сохранения
void LoadRunner::on_pbSave_released()
{
    sourceData->savePreset();
}




//================================================== Кнопка выполнения
void LoadRunner::on_pbRun_released()
{
    sourceData->run();
}




//================================================== Кнопка выхода
void LoadRunner::on_pbQuit_released()
{
//    this->close;
}




//================================================== Чекбокс контроля
void LoadRunner::on_cbRunControl_toggled(bool)
{
    for (QCheckBox *cb : cbControlList){
        cb->setChecked(!cb->isChecked());
    }
}




//================================================== Изменения в ячейке
void LoadRunner::on_tbwProgramList_cellChanged(int row, int column)
{
    QString value = ui->tbwProgramList->item(row, column)->text();
    sourceData->dataEdited(row, column, value);
}





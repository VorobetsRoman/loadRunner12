#include "loadrunner.h"
#include "ui_loadrunner.h"
#include <QPushButton>
#include <QDebug>
#include <sourcedata.h>
#include <QCheckBox>
#include <QTextCodec>




//===================================== Конструктор
LoadRunner::LoadRunner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadRunner)
{
    SourceData* sourceData = new SourceData;

    ui->setupUi(this);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    programList = &sourceData->programList;

    { //--------------------- Настройка таблицы
        ui->tbwProgramList->setColumnCount(8);

        QStringList hHeader;
        hHeader << "Программа" << "загрузить" << "аргументы" << "задержка" << "P" << "S" << "R" << "Control";
        ui->tbwProgramList->setHorizontalHeaderLabels(hHeader);

        ui->tbwProgramList->setRowCount(rowCount);

        for (int i = 0; i < rowCount; i++)
        {
            QPushButton* pbSelect   = new QPushButton(QString("..."));
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

    this->reFilling();
    } //---------------------



    //Нижние кнопки
    this->connect(ui->pbQuit,           &QPushButton::released,
                  this,                 &LoadRunner ::close         );
    this->connect(ui->pbLoad,           &QPushButton::released,
                  sourceData,           &SourceData ::loadPreset    );
    this->connect(ui->pbRun,            &QPushButton::released,
                  sourceData,           &SourceData ::run           );
    this->connect(ui->pbSave,           &QPushButton::released,
                  sourceData,           &SourceData ::savePreset    );
    this->connect(ui->cbRunControl,     &QCheckBox  ::toggled,
                  this,                 &LoadRunner ::cbCheckAll    );

    //Таблица
    this->connect(ui->tbwProgramList,   &QTableWidget::cellChanged,
                  this,                 &LoadRunner ::leEdited      );

    //Табличные кнопки
    for (int i = 0; i < rowCount; i++)
    {
        this->connect(pbSelectList.at(i),   &QPushButton::released,
                        this,               &LoadRunner ::pbSelectPressed);
        this->connect(pbPlayList.at(i),     &QPushButton::released,
                        this,               &LoadRunner ::pbPlayPressed );
        this->connect(pbStopList.at(i),     &QPushButton::released,
                        this,               &LoadRunner ::pbStopPressed );
        this->connect(pbResetList.at(i),    &QPushButton::released,
                        this,               &LoadRunner ::pbResetPressed);
        this->connect(cbControlList.at(i),  &QCheckBox  ::toggled,
                        this,               &LoadRunner ::cbCheckChecked);

    }

    //Внутренние сообщения
    this->connect(this,                 &LoadRunner::dataEdited,
                  sourceData,           &SourceData::dataEdited     );
    this->connect(sourceData,           &SourceData::reFilling,
                  this,                 &LoadRunner::reFilling      );
    this->connect(this,                 &LoadRunner::runSelected,
                  sourceData,           &SourceData::runSelected    );
    this->connect(this,                 &LoadRunner::setChecked,
                  sourceData,           &SourceData::setChecked     );
}




//===================================== Деструктор
LoadRunner::~LoadRunner()
{
    delete ui;
}




//===================================== Заполнение таблицы
void LoadRunner::reFilling()
{
    for (int i = 0; i < programList->size(); i++)
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
    QPushButton*    pbSender    = (QPushButton*)sender();
    int             i           = pbSelectList.indexOf(pbSender);
    emit dataEdited(i, 1, QString(""));
}




//===================================== Нажата кнопка "Запустить"
void LoadRunner::pbPlayPressed()
{
    QPushButton*    pbSender    = (QPushButton*)sender();
    int             i           = pbPlayList.indexOf(pbSender);
    emit runSelected(i, 0);
}





//===================================== Нажата кнопка "Остановить"
void LoadRunner::pbStopPressed()
{
    QPushButton*    pbSender    = (QPushButton*)sender();
    int             i           = pbStopList.indexOf(pbSender);
    emit runSelected(i, 1);
}




//===================================== Нажата кнопка "Перезапустить"
void LoadRunner::pbResetPressed()
{
    QPushButton*    pbSender    = (QPushButton*)sender();
    int             i           = pbResetList.indexOf(pbSender);
    emit runSelected(i, 2);
}




//===================================== Изменено содержимое поля
void LoadRunner::leEdited(int row, int column)
{
    QString value = ui->tbwProgramList->item(row, column)->text();
    emit dataEdited(row, column, value);
}




//===================================== Проверка выполнения
void LoadRunner::cbCheckChecked(bool value)
{
    QCheckBox*  cbSender    = (QCheckBox*)sender();
    int         i           = cbControlList.indexOf(cbSender);
    emit setChecked(i, value);
}




//===================================== Проверка выполнения
void LoadRunner::cbCheckAll(bool)
{
    for (int i = 0; i < rowCount; i++)
    {
        cbControlList.at(i)->setChecked(!cbControlList.at(i)->isChecked());
    }
}

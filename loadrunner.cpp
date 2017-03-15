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
    sourceData = new ProgramList();

    ui->setupUi(this);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //programList = &sourceData->programList;

    tableSetup();

    connect(sourceData,           &ProgramList::reFilling,
            this,                 &LoadRunner::reFillingSlot      );
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
        connect(pbSelect,   &QToolButton::released,
                this,       &LoadRunner ::pbSelectPressed);

        QPushButton* pbPlay     = new QPushButton();
        QPixmap playpixmap(":/buttons/media-play-16.png");
        pbPlay->setIcon(playpixmap);
        ui->tbwProgramList      ->setCellWidget (i, 4, pbPlay);
        pbPlayList              .append         (pbPlay);
        connect(pbPlay,     &QPushButton::released,
                this,       &LoadRunner ::pbPlayPressed);

        QPushButton* pbStop     = new QPushButton();
        QPixmap stopPixmap(":/buttons/media-stop-32.png");
        pbStop->setIcon(stopPixmap);
        ui->tbwProgramList      ->setCellWidget (i, 5, pbStop);
        pbStopList              .append         (pbStop);
        connect(pbStop,     &QPushButton::released,
                this,       &LoadRunner ::pbStopPressed);

        QPushButton* pbReset    = new QPushButton(QString("R"));
        ui->tbwProgramList      ->setCellWidget (i, 6, pbReset);
        pbResetList             .append         (pbReset);
        connect(pbReset,    &QPushButton::released,
                this,       &LoadRunner ::pbResetPressed);

        QCheckBox* cbControl    = new QCheckBox();
        ui->tbwProgramList      ->setCellWidget (i, 7, cbControl);
        cbControlList           .append         (cbControl);
        connect(cbControl,  &QCheckBox  ::toggled,
                this,       &LoadRunner ::cbCheckChecked);
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
    for (int i {0}, m {programList->size()}; i < m; i++)
    {
        ui->tbwProgramList->item(i, 0)->setText(programList->at(i)->getProgramName());
        ui->tbwProgramList->item(i, 2)->setText(programList->at(i)->getProgramArgs());
        ui->tbwProgramList->item(i, 3)->setText(QString::number(programList->at(i)->getDelay()));
    }
}




//===================================== Нажата кнопка "Выбрать"
void LoadRunner::pbSelectPressed()
{
    sourceData->dataEdited(pbSelectList.indexOf((QToolButton*)sender()), 1, QString(""));
}




//===================================== Нажата кнопка "Запустить"
void LoadRunner::pbPlayPressed()
{
    sourceData->runSelected(pbPlayList.indexOf((QPushButton*)sender()), 0);
}




//===================================== Нажата кнопка "Остановить"
void LoadRunner::pbStopPressed()
{
    sourceData->runSelected(pbStopList.indexOf((QPushButton*)sender()), 1);
}




//===================================== Нажата кнопка "Перезапустить"
void LoadRunner::pbResetPressed()
{
    sourceData->runSelected(pbResetList.indexOf((QPushButton*)sender()), 2);
}




//===================================== Проверка выполнения
void LoadRunner::cbCheckChecked(bool value)
{
    sourceData->setChecked(cbControlList.indexOf((QCheckBox*)sender()), value);
}




//================================================== Кнопка загрузки
void LoadRunner::on_pbLoad_released()
{
    sourceData->load();
}




//================================================== Кнопка сохранения
void LoadRunner::on_pbSave_released()
{
    sourceData->save();
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





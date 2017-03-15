#include "lrrecord.h"
#include <QToolButton>
#include <QPushButton>




//=====================================
LrRecord::LrRecord(QObject *parent) : QObject(parent)
{
}




//=====================================
LrRecord::LrRecord(QWidget *cell_0, QWidget *cell_1,
                   QWidget *cell_2, QWidget *cell_3,
                   QWidget *cell_4, QWidget *cell_5,
                   QWidget *cell_6, QWidget *cell_7, QObject *parent)
{
    QToolButton* pbSelect   = new QToolButton();
    cell_1->setw
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

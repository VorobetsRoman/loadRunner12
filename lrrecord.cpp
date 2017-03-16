#include "lrrecord.h"
#include <QToolButton>
#include <QPushButton>




//=====================================
LrRecord::LrRecord(QObject *parent) : QObject(parent)
{
}




//=====================================
LrRecord::~LrRecord()
{
    mprogram && mprogram->deleteLater();
    if (mprogram){
        mprogram->deleteLater();
    }
    if (progName) {
        progName->deleteLater();
    }
    if (tbSelect) {
        tbSelect->deleteLater();
    }
    if (arguments) {
        arguments->deleteLater();
    }
    if (delay) {
        delay->deleteLater();
    }
    if (pbStart) {
        pbStart->deleteLater();
    }
    if (pbStop) {
        pbStop->deleteLater();
    }
    if (pbReset) {
        pbReset->deleteLater();
    }
    if (cbControl) {
        cbControl->deleteLater();
    }
}




//=====================================
QLineEdit*      LrRecord::getProgName     ()
{
    if (!progName)
    {
        progName = new QLineEdit();
    }
    return progName;
}




//=====================================
QToolButton*    LrRecord::getTbSelect     ()
{
    if (!tbSelect)
    {
        tbSelect = new QToolButton();
    }
    return tbSelect;
}




//=====================================
QLineEdit*      LrRecord::getArguments    ()
{
    if (!arguments)
    {
        arguments = new QLineEdit("");
    }
    return arguments;
}




//=====================================
QLineEdit*      LrRecord::getDelay        ()
{
    if (!delay)
    {
        delay = new QLineEdit("0");
    }
    return delay;
}




//=====================================
QPushButton*    LrRecord::getPbStart      ()
{
    if (!pbStart)
    {
        QPixmap playpixmap(":/buttons/media-play-16.png");
        pbStart = new QPushButton(playPixmap, "");
    }
    return pbStart;
}




//=====================================
QPushButton*    LrRecord::getPbStop       ()
{
    if (!pbStop)
    {
        QPixmap stopPixmap(":/buttons/media-stop-32.png");
        pbStop = new QPushButton(stopPixmap, "");
    }
    return pbStop;
}




//=====================================
QPushButton*    LrRecord::getPbReset      ()
{
    if (!pbReset) {
        pbReset = new QPushButton();
    }
    return pbReset;
}




//=====================================
QCheckBox*      LrRecord::getCbControl    ()
{
    if (!cbControl)
    {
        cbControl = new QCheckBox("");
    }
    return cbControl;
}







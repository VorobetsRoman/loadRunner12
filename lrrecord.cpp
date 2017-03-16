#include "lrrecord.h"
#include <QToolButton>
#include <QPushButton>
#include <QFileDialog>




//=====================================
LrRecord::LrRecord(QObject *parent) : QObject(parent)
{
    mprogram = new MProgram();
    connect(mprogram,   &MProgram   ::newValues,
            this,       &LrRecord   ::newMprogramValues);
}




//=====================================
LrRecord::~LrRecord()
{
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
        connect(progName,   &QLineEdit  ::textChanged,
                mprogram,   &MProgram   ::setProgramName);
    }
    return progName;
}




//=====================================
QToolButton*    LrRecord::getTbSelect     ()
{
    if (!tbSelect)
    {
        tbSelect = new QToolButton();
        tbSelect->setStyleSheet("max-width:35px;");
        connect(tbSelect,   &QToolButton    ::released,
                this,       &LrRecord       ::setExeFileName);
    }
    return tbSelect;
}




//=====================================
QLineEdit*      LrRecord::getArguments    ()
{
    if (!arguments)
    {
        arguments = new QLineEdit("");
        connect(arguments,  &QLineEdit  ::textChanged,
                mprogram,   &MProgram   ::setProgramArgs);
    }
    return arguments;
}




//=====================================
QLineEdit*      LrRecord::getDelay        ()
{
    if (!delay)
    {
        delay = new QLineEdit();
        delay->setPlaceholderText("сек");
        delay->setInputMask("00");
        delay->setAlignment(Qt::AlignHCenter);
        connect(delay,      &QLineEdit  ::textChanged,
                this,       &LrRecord   ::setDelay);
    }
    return delay;
}




//=====================================
QPushButton*    LrRecord::getPbStart      ()
{
    if (!pbStart)
    {
        QPixmap playPixmap(":/buttons/media-play-16.png");
        pbStart = new QPushButton(playPixmap, "");
        pbStart->setStyleSheet("max-width:35px;");
        connect(pbStart,    &QPushButton    ::released,
                mprogram,   &MProgram       ::run);
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
        pbStop->setStyleSheet("max-width:35px;");
        connect(pbStop,     &QPushButton    ::released,
                mprogram,   &MProgram       ::stop);
    }
    return pbStop;
}




//=====================================
QPushButton*    LrRecord::getPbReset      ()
{
    if (!pbReset) {
        pbReset = new QPushButton();
        pbReset->setStyleSheet("max-width:35px;");
        connect(pbReset,    &QPushButton    ::released,
                mprogram,   &MProgram       ::reset);
    }
    return pbReset;
}




//=====================================
QCheckBox*      LrRecord::getCbControl    ()
{
    if (!cbControl)
    {
        cbControl = new QCheckBox("");
        cbControl->setStyleSheet("max-width:35px;");
        connect(cbControl,  &QCheckBox  ::toggled,
                mprogram,   &MProgram   ::setRunControl);
    }
    return cbControl;
}




//=====================================
void LrRecord::setExeFileName()
{
    QString caption {"Веберите исполняемый файл"};
    QString fileName = QFileDialog::getOpenFileName(0, caption, qApp->applicationDirPath(), "", 0);
    if (fileName != "") {
        mprogram->setExecutableFile(fileName);
        progName->setText(fileName);
    }
}




//=====================================
void LrRecord::setDelay(QString value)
{
    mprogram->setDelay(value.toInt());
}




//=====================================
void LrRecord::saveToFile(QFile *presetFile)
{
    mprogram->saveToFile(presetFile);
}




//=====================================
void LrRecord::setDataFromFile(QString *newData)
{
    mprogram->readFromFile(newData);
}




//=====================================
void LrRecord::newMprogramValues()
{
    progName->setText(mprogram->getProgramName());
    arguments->setText(mprogram->getProgramArgs());
    delay->setText(QString::number(mprogram->getDelay()));
}





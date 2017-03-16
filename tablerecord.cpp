#include "tablerecord.h"
#include <QToolButton>
#include <QPushButton>
#include <QFileDialog>




//=====================================
TableRecord::TableRecord(QObject *parent) : QObject(parent)
{
    mprogram = new MProgram();
    connect(mprogram,   &MProgram       ::newValues,
            this,       &TableRecord    ::newMprogramValues);
    connect(mprogram,   &MProgram       ::processChangedState,
            this,       &TableRecord    ::programChangedState);
}




//=====================================
TableRecord::~TableRecord()
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
    if (pbReset) {
        pbReset->deleteLater();
    }
    if (cbControl) {
        cbControl->deleteLater();
    }
}




//=====================================
QLineEdit*      TableRecord::getProgName     ()
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
QToolButton*    TableRecord::getTbSelect     ()
{
    if (!tbSelect)
    {
        tbSelect = new QToolButton();
        tbSelect->setStyleSheet("max-width:35px;");
        connect(tbSelect,   &QToolButton    ::released,
                this,       &TableRecord       ::setExeFileName);
    }
    return tbSelect;
}




//=====================================
QLineEdit*      TableRecord::getArguments    ()
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
QLineEdit*      TableRecord::getDelay        ()
{
    if (!delay)
    {
        delay = new QLineEdit();
        delay->setPlaceholderText("сек");
        delay->setInputMask("00");
        delay->setAlignment(Qt::AlignHCenter);
        connect(delay,      &QLineEdit  ::textChanged,
                this,       &TableRecord   ::setDelay);
    }
    return delay;
}




//=====================================
QPushButton*    TableRecord::getPbStart      ()
{
    if (!pbStart)
    {
        QPixmap playPixmap(":/buttons/media-play-16.png");
        pbStart = new QPushButton(playPixmap, "");
        pbStart->setStyleSheet("max-width:35px;");
        connect(pbStart,    &QPushButton    ::released,
                this,       &TableRecord       ::on_pbStart_released);
    }
    return pbStart;
}




//=====================================
QPushButton*    TableRecord::getPbReset      ()
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
QCheckBox*      TableRecord::getCbControl    ()
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
void TableRecord::setExeFileName()
{
    QString caption {"Веберите исполняемый файл"};
    QString fileName = QFileDialog::getOpenFileName(0, caption, qApp->applicationDirPath(), "", 0);
    if (fileName != "") {
        mprogram->setExecutableFile(fileName);
        progName->setText(fileName);
    }
}




//=====================================
void TableRecord::setDelay(QString value)
{
    mprogram->setDelay(value.toInt());
}




//=====================================
void TableRecord::saveToFile(QFile *presetFile)
{
    mprogram->saveToFile(presetFile);
}




//=====================================
void TableRecord::setDataFromFile(QString *newData)
{
    mprogram->readFromFile(newData);
}




//=====================================
void TableRecord::newMprogramValues()
{
    progName->setText(mprogram->getProgramName());
    arguments->setText(mprogram->getProgramArgs());
    delay->setText(QString::number(mprogram->getDelay()));
}




//=====================================
void TableRecord::on_pbStart_released()
{
    switch (programState) {
    case MP_RUNNING:
        mprogram->stop();
        break;
    case MP_FINISHED:
        mprogram->run();
        break;
    default:
        break;
    }
}




//=====================================
void TableRecord::programChangedState(int newState)
{
    programState = newState;
    switch (programState) {
    case MP_RUNNING:
    {
        QPixmap stopPixmap(":/buttons/media-stop-32.png");
        pbStart->setIcon(stopPixmap);
    }
        break;
    case MP_FINISHED:
    {
        QPixmap playPixmap(":/buttons/media-play-16.png");
        pbStart->setIcon(playPixmap);
    }
        break;
    default:
        break;
    }
}




//=====================================
void TableRecord::runProgram()
{
    mprogram->run();
}




//=====================================
void TableRecord::setControl(bool newValue)
{
    mprogram->setRunControl(newValue);
    cbControl->setChecked(newValue);
}




//=====================================
void TableRecord::stopProgram()
{
    mprogram->stop();
}




//=====================================
void TableRecord::resetProgram()
{
    mprogram->reset();
}



#include "mprogram.h"
#include <QProcess>
#include <QFile>
#include <QDebug>




//======================================== Конструктор
MProgram::MProgram(QObject *parent) :
    QObject(parent)
{
}




//======================================== Конструктор с параметром
MProgram::MProgram(QString* fileName, QObject *parent) :
    QObject(parent)
{
    setExecutableFile(*fileName);
}




//======================================== Деструктор
MProgram::~MProgram()
{
    if (myProcess)
    {
        if (myProcess->isOpen()){
            myProcess->close();
        }
        myProcess->deleteLater();
    }
}




//======================================= Задание выполняемого файла
void MProgram::setExecutableFile(QString newFileName)
{
    executableFileName = newFileName;
    int i = programName.lastIndexOf("/");
    programDirectory = programName.left(i);
}




//======================================== Задание имени программы (идентификатора)
void MProgram::setProgramName(QString newName) {
    programName = newName;
}




//======================================== Задание аргументов программы для запуска
void MProgram::setProgramArgs(QString arguments) {
    programArgs = arguments;
}




//======================================== Проверка выполнения
void MProgram::setRunControl(bool value)
{
    runControl = value;
}




//======================================== Выполнение
void MProgram::run()
{
    if (!myProcess)
    {
        QString executableFile;
        if (executableFileName != "") {
            executableFile = executableFileName;
        }
        else {
            if (programName != "") {
                executableFile = programName;
            }
            else return;
        }

        myProcess = new QProcess();
        connect(myProcess,    &QProcess::stateChanged,
                this,         &MProgram::stateChanged );
        connect(myProcess,    &QProcess::started,
                this,         &MProgram::started      );
        connect(myProcess,    SIGNAL  (finished(int, QProcess::ExitStatus)),
                this,         SLOT    (finished(int, QProcess::ExitStatus)));
        myProcess->setWorkingDirectory(programDirectory);
        myProcess->start(executableFile + " " + programArgs);
    }
}




//======================================== Выключение
void MProgram::stop()
{
    if (myProcess) {
        myProcess->kill();
    }
}




//======================================== Перезагрузка
void MProgram::reset()
{
    if (myProcess) {
        stop();
        run();
    }
}




//======================================== Сохранение в файл
void MProgram::saveToFile(QFile *file)
{
    if (executableFileName == "") return;

    QByteArray writeArray;
    writeArray.append(programName);
    writeArray.append(char(9));
    writeArray.append(executableFileName);
    writeArray.append(char(9));
    writeArray.append(programArgs);
    writeArray.append(char(9));
    writeArray.append(QString::number(delay));
    writeArray.append(char(10));
    file->write(writeArray);
}




//======================================== Чтение из файла
void MProgram::readFromFile(QString *newData)
{
    programName         = newData->section(char(9), 0, 0);
    executableFileName  = newData->section(char(9), 1, 1);
    programArgs         = newData->section(char(9), 2, 2);
    delay               = newData->section(char(9), 3, 3).toInt();

    int i = programName.lastIndexOf("/");
    programDirectory = programName.left(i);
    emit newValues();
}




//======================================== Изменение состояния //не используется
void MProgram::stateChanged(QProcess::ProcessState newstate)
{
    switch (newstate) {
    case QProcess::Running:
        break;
    case QProcess::NotRunning:
    {
        myProcess->deleteLater();
        myProcess = NULL;
    }
        break;
    case QProcess::Starting:
        break;
    }
}




//======================================= Сигнал о запуске
void MProgram::started()
{
    emit processChangedState(MP_RUNNING);
}




//======================================= Сигнал о выходе
void MProgram::finished(int, QProcess::ExitStatus)
{
    emit processChangedState(MP_FINISHED);
    if (runControl) this->run();
}








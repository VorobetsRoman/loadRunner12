#include "mprogram.h"
#include <QProcess>
#include <QFile>




//======================================== Конструктор
MProgram::MProgram(QObject *parent) :
    QObject(parent)
{
    programName = QString("");    
    initialization();
}




//======================================== Конструктор с параметром
MProgram::MProgram(QString* fileName, QObject *parent) :
    QObject(parent)
{
    programName = *fileName;

    int i = programName.lastIndexOf("/");
    programDirectory = programName.left(i);

    initialization();
}




//======================================== Деструктор
MProgram::~MProgram()
{
    if (myProcess){
        if (myProcess->isOpen()){
            myProcess->close();
        }
        myProcess->deleteLater();
    }
}




//======================================== Инициализация
void MProgram::initialization()
{
    programArgs = QString("");
    delay       = 0;
    running     = false;
    runControl  = false;
    myProcess   = new QProcess;
    this->connect(myProcess,    &QProcess::stateChanged,
                  this,         &MProgram::stateChanged );
    this->connect(myProcess,    &QProcess::started,
                  this,         &MProgram::started      );
/*    this->connect(myProcess,    &QProcess::finished,
                  this,         &MProgram::finished     );*/
    this->connect(myProcess,    SIGNAL  (finished(int,QProcess::ExitStatus)),
                  this,         SLOT    (finished(int,QProcess::ExitStatus)));
    this->connect(myProcess,    SIGNAL  (finished(int)),
                  this,         SLOT    (finished(int))                     );
}




//======================================== Выполнение
void MProgram::run()
{
    if (!running)
    {
        myProcess->setWorkingDirectory(programDirectory);
        myProcess->start(programName + " " + programArgs);
    }
}




//======================================== Выключение
void MProgram::stop()
{
    if (running) {
        myProcess->kill();
    }
}




//======================================== Выключение
void MProgram::reset()
{
    if (running) {
        myProcess->kill();
        myProcess->waitForFinished(2000);
        myProcess->start();
    }
}




//======================================== Сохранение в файл
void MProgram::saveToFile(QFile *file)
{
    QByteArray writeArray;
    writeArray.append(programName);
    writeArray.append("#");
    writeArray.append(programArgs);
    writeArray.append("#");
    writeArray.append(QString::number(delay));
    writeArray.append(char(10));
    file->write(writeArray);
}




//======================================== Чтение из файла
void MProgram::readFromFile(QFile *file)
{
    QByteArray  readArray   = file->readLine();
    QString     readString  = readArray.data();

    programName = readString.section("#", 0, 0);
    programArgs = readString.section("#", 1, 1);
    delay       = readString.section("#", 2, 2).toInt();

    int i = programName.lastIndexOf("/");
    programDirectory = programName.left(i);
}




//======================================== Проверка выполнения
void MProgram::setRunControl(bool value)
{
    runControl = value;
}




//======================================== Изменение состояния //не используется
void MProgram::stateChanged(QProcess::ProcessState newstate)
{
    switch (newstate) {
    case QProcess::Running:
        break;
    case QProcess::NotRunning:
        break;
    case QProcess::Starting:
        break;
    }
}




//======================================= Сигнал о запуске
void MProgram::started()
{
    running = true;
}




//======================================= Сигнал о выходе
void MProgram::finished(int, QProcess::ExitStatus)
{
    running = false;
    if (runControl) this->run();
}




//======================================= Сигнал о выходе 2
void MProgram::finished(int)
{
    running = false;
    if (runControl) this->run();
}






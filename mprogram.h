#ifndef MPROGRAM_H
#define MPROGRAM_H

#include <QObject>
#include <QtCore>
#include <QProcess>

//* Класс, описывающий одну программу
enum {MP_RUNNING, MP_FINISHED};

class MProgram : public QObject
{
    Q_OBJECT
public:
    explicit
            MProgram        (QObject *parent = 0);
    explicit
            MProgram        (QString* fileName, QObject *parent = 0);
            ~MProgram       ();
    void    setProgram      ();
    void    run             ();
    void    stop            ();
    void    reset           ();
    void    saveToFile      (QFile*);
    void    readFromFile    (QFile*);
    void    setRunControl   (bool value);

    QString getProgramName      ()  {return programName;}
    QString getProgramFullName  ()  {return programFileName;}
    QString getProgramArgs      ()  {return programArgs;}
    int     getDelay            ()  {return delay;}

signals:
    void    processChangedState(int newState);


private:
    QString programName     {""};       // название программы произвольное (отображается)
    QString programDirectory{""};       // директория программы
    QString programFileName {""};       // полный путь к исполняемому файлу программы
    QProcess *myProcess     {NULL};
    bool    runControl      {false};    // отметка о контроле за выполнением
    QString programArgs     {""};       // аргументы
    int     delay           {0};        // задержка перед запуском

private slots:
    void    stateChanged    (QProcess::ProcessState newstate);
    void    started         ();
    void    finished        (int, QProcess::ExitStatus);
    void    finished        (int);

};

#endif // MPROGRAM_H

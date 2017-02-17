#ifndef MPROGRAM_H
#define MPROGRAM_H

#include <QObject>
#include <QtCore>
#include <QProcess>

class MProgram : public QObject
{
    Q_OBJECT
public:
    explicit
            MProgram        (QObject *parent = 0);
            explicit
            MProgram        (QString* fileName, QObject *parent = 0);
            ~MProgram       ();
    void    run             ();
    void    stop            ();
    void    reset           ();
    void    saveToFile      (QFile*);
    void    readFromFile    (QFile*);
    void    setRunControl   (bool value);

    QString programName;    // путь к файлу
    QString programArgs;    // аргументы
    QString programDirectory;
    int     delay;          // задержка перед запуском
    bool    running;        // отметка о выполнении

private:
    void    initialization  ();

    QProcess *myProcess {NULL};
    bool    runControl;     // отметка о контроле за выполнением

private slots:
    void    stateChanged    (QProcess::ProcessState newstate);
    void    started         ();
    void    finished        (int, QProcess::ExitStatus);
    void    finished        (int);

};

#endif // MPROGRAM_H

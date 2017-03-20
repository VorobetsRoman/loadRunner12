#ifndef LRRECORD_H
#define LRRECORD_H

#include <QObject>
#include "mprogram.h"
#include <QLineEdit>
#include <QToolButton>
#include <QPushButton>
#include <QCheckBox>
#include <QTimer>



class TableRecord : public QObject
{
    Q_OBJECT
public:
    explicit TableRecord(QObject *parent = 0);
    ~TableRecord();
    QLineEdit*      getProgName     ();
    QPushButton*    getPbSelect     ();
    QLineEdit*      getArguments    ();
    QLineEdit*      getDelay        ();
    QPushButton*    getPbStart      ();
    QPushButton*    getPbReset      ();
    QCheckBox*      getCbControl    ();

    void saveToFile         (QFile *presetFile);
    void setDataFromFile    (QString *newData);
    void runProgram         ();
    void stopProgram        ();
    void resetProgram       ();
    void setControl         (bool);

signals:

public slots:

private:
    MProgram    *mprogram   {NULL};
    QLineEdit   *progName   {NULL};
    QPushButton *pbSelect   {NULL};
    QLineEdit   *arguments  {NULL};
    QLineEdit   *delay      {NULL};
    QPushButton *pbStart    {NULL};
    QPushButton *pbReset    {NULL};
    QCheckBox   *cbControl  {NULL};
    int         programState{MP_FINISHED};
    QTimer      *startTimer {NULL};

    void setExeFileName         ();
    void setDelay               (QString value);
    void newMprogramValues      ();
    void on_pbStart_released    ();
    void programChangedState    (int newState);
    void startTimerTimeout      ();
};

#endif // LRRECORD_H

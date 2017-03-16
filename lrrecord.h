#ifndef LRRECORD_H
#define LRRECORD_H

#include <QObject>
#include "mprogram.h"
#include <QLineEdit>
#include <QToolButton>
#include <QPushButton>
#include <QCheckBox>



class LrRecord : public QObject
{
    Q_OBJECT
public:
    explicit LrRecord(QObject *parent = 0);
    ~LrRecord();
    QLineEdit*      getProgName     ();
    QToolButton*    getTbSelect     ();
    QLineEdit*      getArguments    ();
    QLineEdit*      getDelay        ();
    QPushButton*    getPbStart      ();
    QPushButton*    getPbStop       ();
    QPushButton*    getPbReset      ();
    QCheckBox*      getCbControl    ();

    void saveToFile (QFile *presetFile);
    void setDataFromFile (QString *newData);

signals:

public slots:

private:
    MProgram    *mprogram   {NULL};
    QLineEdit   *progName   {NULL};
    QToolButton *tbSelect   {NULL};
    QLineEdit   *arguments  {NULL};
    QLineEdit   *delay      {NULL};
    QPushButton *pbStart    {NULL};
    QPushButton *pbStop     {NULL};
    QPushButton *pbReset    {NULL};
    QCheckBox   *cbControl  {NULL};

    void setExeFileName ();
    void setDelay       (QString value);
    void newMprogramValues  ();
};

#endif // LRRECORD_H

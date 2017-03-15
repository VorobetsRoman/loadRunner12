#ifndef LRRECORD_H
#define LRRECORD_H

#include <QObject>
#include "mprogram.h"
#include <QTableWidgetItem>
class LrRecord : public QObject
{
    Q_OBJECT
public:
    explicit LrRecord(QObject *parent = 0);
    explicit LrRecord(QWidget *cell_0, QWidget *cell_1,
                      QWidget *cell_2, QWidget *cell_3,
                      QWidget *cell_4, QWidget *cell_5,
                      QWidget *cell_6, QWidget *cell_7, QObject *parent = 0);
signals:

public slots:

private:
    MProgram *mprogram {NULL};
    QWidget *setName, *loadFile, *setArgs, *setDelay, *sayPlay,
            *sayStop, *sayReset, *sayControl;
};

#endif // LRRECORD_H

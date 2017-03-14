#ifndef SOURCEDATA_H
#define SOURCEDATA_H

#include <QObject>
#include <mprogram.h>

// Класс для работы со списком программ
class ProgramList : public QObject
{
    Q_OBJECT
public:
    explicit ProgramList(QObject *parent = 0);

signals:
    void reFilling  ();

public slots:
    void load ();
    void save ();
    void selectFile ();
    void dataEdited (int row, int column, QString);
    void run        ();
    void runSelected(int row, int type);
    void setChecked (int row, bool value);


private:
    QList <MProgram*> programList;

};

#endif // SOURCEDATA_H

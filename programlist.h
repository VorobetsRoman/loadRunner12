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
    void addProgram     ();
    void cutProgram     (int programId);
    void setDelay       (int programId, int value);
    void setAttributes  (int programId, QString attributes);
    void setName        (int programId, QString newName);
    void setFile        (int programId);
    void load           ();
    void save           ();
//    void changeValue    (int programId, int valueId, QString value);

signals:

public slots:
    void run        ();
    void runSelected(int row, int command);
    void setChecked (int row, bool value);


private:
    QList <MProgram*> programList;

};

#endif // SOURCEDATA_H

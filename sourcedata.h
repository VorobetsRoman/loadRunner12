#ifndef SOURCEDATA_H
#define SOURCEDATA_H

#include <QObject>
#include <mprogram.h>

class SourceData : public QObject
{
    Q_OBJECT
public:
    explicit SourceData(QObject *parent = 0);

    QList <MProgram*> programList;

signals:
    void reFilling  ();

public slots:
    void loadPreset ();
    void savePreset ();
    void selectFile ();
    void dataEdited (int row, int column, QString);
    void run        ();
    void runSelected(int row, int type);
    void setChecked (int row, bool value);

};

#endif // SOURCEDATA_H

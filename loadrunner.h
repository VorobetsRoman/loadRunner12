#ifndef LOADRUNNER_H
#define LOADRUNNER_H

#include <QWidget>
#include "tablerecord.h"
#include <QResizeEvent>

namespace Ui {
class LoadRunner;
}


class LoadRunner : public QWidget
{
    Q_OBJECT

public:
    explicit LoadRunner     (QWidget *parent = 0);
    ~LoadRunner             ();

signals:
    void loadPreset         ();
    void savePreset         ();
    void selectFile         ();
    void run                ();

public slots:
    virtual void resizeEvent(QResizeEvent *re);

private:
    static const int rowCount = 10;

    Ui::LoadRunner          *ui {NULL};
    QList <TableRecord*>       tableRows;

    void tableSetup         ();


private slots:
    void on_pbLoad_released ();
    void on_pbSave_released ();
    void on_pbRun_released  ();
    void on_cbRunControl_toggled(bool checked);
    void on_pbStop_released();
    void on_pbReset_released();
};

#endif // LOADRUNNER_H

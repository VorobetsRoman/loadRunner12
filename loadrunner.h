#ifndef LOADRUNNER_H
#define LOADRUNNER_H

#include <QWidget>
#include <QPushButton>
#include "mprogram.h"
#include <QCheckBox>
#include "programlist.h"
#include <QToolButton>

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
    void reFillingSlot          ();             // заполнение таблицы

private:
    static const int rowCount = 10;

    Ui::LoadRunner          *ui {NULL};
    QList <QToolButton*>    pbSelectList;   // список кнопок загрузки
    QList <QPushButton*>    pbPlayList,     // список кнопок запуска
                            pbStopList,     // список кнопок выключения
                            pbResetList;    // список кнопок перезапуска
    QList <QCheckBox*>      cbControlList;  // список отметок контроля
    QList <MProgram*>       *programList;   // список программ с аргументами и задержкой
    ProgramList* sourceData {NULL};

    void tableSetup         ();

private slots:
    void pbSelectPressed    ();
    void pbPlayPressed      ();
    void pbStopPressed      ();
    void pbResetPressed     ();
    void cbCheckChecked     (bool);
    void on_pbLoad_released ();
    void on_pbSave_released ();
    void on_pbRun_released  ();
    void on_pbQuit_released ();
    void on_cbRunControl_toggled(bool checked);
    void on_tbwProgramList_cellChanged(int row, int column);
};

#endif // LOADRUNNER_H

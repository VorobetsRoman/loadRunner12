#ifndef LOADRUNNER_H
#define LOADRUNNER_H

#include <QWidget>
#include <QPushButton>
#include <mprogram.h>
#include <QCheckBox>

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
    void dataEdited         (int, int, QString);
    void run                ();
    void runSelected        (int, int); //0play 1stop 2reset
    void setChecked         (int, bool);

public slots:
    void reFilling          ();             // заполнение таблицы

private:
    static const int rowCount = 10;

    Ui::LoadRunner          *ui;
    QList <QPushButton*>    pbSelectList,   // список кнопок загрузки
                            pbPlayList,     // список кнопок запуска
                            pbStopList,     // список кнопок выключения
                            pbResetList;    // список кнопок перезапуска
    QList <QCheckBox*>      cbControlList;  // список отметок контроля
    QList <MProgram*>       *programList;   // список программ с аргументами и задержкой

private slots:
    void pbSelectPressed    ();
    void pbPlayPressed      ();
    void pbStopPressed      ();
    void pbResetPressed     ();
    void leEdited           (int, int);
    void cbCheckChecked     (bool);
    void cbCheckAll         (bool);
};

#endif // LOADRUNNER_H

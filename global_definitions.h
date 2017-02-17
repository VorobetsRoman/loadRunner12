#ifndef GLOBAL_DEFINITIONS_H
#define GLOBAL_DEFINITIONS_H

#include <QtGlobal>

struct MProgram             // программа
{
    QString programName;    // путь к файлу
    QString programArgs;    // аргументы
    int     delay;          // задержка перед запуском
    bool    running;        // отметка о выполнении
};

#endif // GLOBAL_DEFINITIONS_H

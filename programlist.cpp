#include "programlist.h"
#include <QFile>
#include <QFileDialog>




//================================================== Конструктор
ProgramList::ProgramList(QObject *parent) :
    QObject(parent)
{
}




//================================================== Добавление в списко программы
void ProgramList::addProgram()
{
    QString fileName = QFileDialog::getOpenFileName(0, "Выберите исполняемый файл", qApp->applicationDirPath(), "");
    MProgram* myProgram = new MProgram(&fileName);
    programList.append(myProgram);
}




//==================================================
void ProgramList::cutProgram(int programId)
{
    programList.removeAt(programId);
}




//==================================================
void ProgramList::setDelay(int programId, int value)
{
    programList.at(programId)->setDelay(value);
}




//==================================================
void ProgramList::setAttributes(int programId, QString attributes)
{
    programList.at(programId)->setAttributes(attributes);
}




//==================================================
void ProgramList::setName(int programId, QString newName)
{
    programList.at(programId)->setName(newName);
}




//==================================================
void ProgramList::setFile(int programId)
{
    QString fileName = QFileDialog::getOpenFileName(0, "Выберите исполняемый файл", qApp->applicationDirPath(), "");
    programList.at(programId)->setProgram();
}




//================================================== Загрузка пресета
void ProgramList::load()
{
    programList.empty();
    QString fileName = QFileDialog::getOpenFileName(0, "Name for preset file", "", "*.prs");
    if (fileName.isEmpty()) return;

    QFile presetFile(fileName);

    presetFile.open(QIODevice::ReadOnly);
    while (!presetFile.atEnd())
    {
        MProgram* newProgram =new MProgram();
        newProgram->readFromFile(&presetFile);
        programList.append(newProgram);
    }
    presetFile.close();

}




//================================================== Сохранение пресета
void ProgramList::save()
{
    QString fileName = QFileDialog::getSaveFileName(0, "Name for preset file", "", "*.prs");
    QFile presetFile(fileName + ".prs");

    presetFile.open(QIODevice::WriteOnly);
    for (int i = 0; i < programList.size(); i++)
        programList.at(i)->saveToFile(&presetFile);
    presetFile.close();
}




//================================================== Выбор файла
void ProgramList::selectProgram()
{
    return;
}




//================================================== Изменено значение
void ProgramList::changeValue(int programId, int valueId, QString value)
{
//    switch (column) {
//    case 0:                                         // имя файла
//        if (row < programList.size())
//            programList.at(row)->programName = value;
//        else
//        {
//            MProgram* newRecord = new MProgram(&value);
//            programList.append(newRecord);
//        }
//        break;
//    case 1:                                         // нажата кнопка
//    {
//        QString fileName = QFileDialog::getOpenFileName(0, "Name of executing file", "", "");
//        if (fileName.isEmpty()) break;

//        if (row < programList.size())
//            programList.at(row)->programName = fileName;
//        else
//        {
//            MProgram* newRecord = new MProgram(&fileName);
//            programList.append(newRecord);
//        }
//        emit reFilling();
//    }
//        break;
//    case 2:                                         // список аргументов
//        if (row < programList.size())
//            programList.at(row)->programArgs = value;
//        else
//            emit reFilling();
//        break;
//    case 3:                                         // задержка
//        if (row < programList.size())
//            programList.at(row)->delay = value.toInt();
//        else
//            emit reFilling();
//        break;
//    }
}




//================================================== Выполнение
void ProgramList::run()
{
    for (int i = 0; i < programList.size(); i++) {
        programList.at(i)->run();
    }
}




//================================================== Выполнение индивидуальное
void ProgramList::runSelected(int row, int command)
{
    switch (command) {
    case 0:
        programList.at(row)->run();
        break;
    case 1:
        programList.at(row)->stop();
        break;
    case 2:
        programList.at(row)->reset();
        break;
    }
}




//================================================== Контроль выполнения
void ProgramList::setChecked(int row, bool value)
{
    if (row < programList.size()) {
        programList.at(row)->setRunControl(value);
    }
}





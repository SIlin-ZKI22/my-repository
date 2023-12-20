// files.h

#ifndef FILES_H
#define FILES_H

#include <QString>
#include <QList>
#include <QDebug>
#include <QDate>
#include <QFile>
#include <QTextStream>

class Files{
public:
    QString fname;
    QDate date;
    QString bytes;

    Files(const QString& fname, const QDate& date, const QString& bytes);
    QString print();
};

class FileReader {
public:
    static QList<Files> readFile(const QString& filePath);
};

#endif // FILES_H

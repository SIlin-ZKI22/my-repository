#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QDate>
#include <QFile>

#include <fstream>

class files
{
public:
    QString fname;
    QDate date;
    QString bytes;

    files(QString fname, QDate date, QString bytes)
        : fname(fname), date(date), bytes(bytes)
    {}

    void print()
    {
        qDebug() <<"file name - "<< fname;
        qDebug() <<"date - "<< date.toString("yyyy.MM.dd");
        qDebug() <<"bytes - "<< bytes <<"\n";
    }
};

int main()
{
    QFile file("C:\\Users\\admin\\Desktop\\lab1\\files.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 1;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split('\"');
        QString fname = fields[1];
        QString bytes = fields[3];
        QDate date = QDate::fromString(fields[2].trimmed(), "yyyy.MM.dd");
        // Обработка каждой строки данных
        files file (fname, date, bytes);
        file.print();
    }
    file.close();

    return 0;
}

#include <QCoreApplication>
#include <QDebug>
#include "files.h"
#include "files.cpp"

int main(){
    QString filePath = "C:/Users/admin/Desktop/lab1/files.txt";
    QList<Files> fileList = FileReader::readFile(filePath);

    for (Files& file : fileList) {
        file.print();
    }

    qint64 totalSize = FileProcessor::getTotalSize(fileList);
    qDebug() << "Total size of all files:" << totalSize << "bytes";

    return 0;
}

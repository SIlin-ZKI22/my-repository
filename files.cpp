#include "files.h"
Files::Files(const QString& fname, const QDate& date, const QString& bytes)
    : fname(fname), date(date), bytes(bytes) {}


QString Files::print() {
    QString output;
    output += "file name - " + fname;
    output += "date - " + date.toString("yyyy.MM.dd");
    output += "   bytes - " + bytes;
    qDebug() << output;
    return output;
};

class FileProcessor {
public:
    static qint64 getTotalSize(const QList<Files>& files) {
        qint64 totalSize = 0;
        for (const Files& file : files) {
            totalSize += file.bytes.toLongLong();
        }
        return totalSize;
    }
};

QVector<Files> FileReader::readFile(const QString& filePath) {
    QVector<Files> fileList;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open the file:" << filePath;
        return fileList;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split('\"');
        QString fname = fields[1];
        QString bytes = fields[3];
        QDate date = QDate::fromString(fields[2].trimmed(), "yyyy.MM.dd");
        fileList.append(Files(fname, date, bytes));
    }

    file.close();

    return fileList;
}

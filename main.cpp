#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QDate>
#include <QFile>

class Files{
public:
    QString fname;
    QDate date;
    QString bytes;

    Files(const QString& fname, const QDate& date, const QString& bytes)
        : fname(fname), date(date), bytes(bytes) {}

    QString print(){
        qDebug() << "file name - " << fname;
        qDebug() << "date - " << date.toString("yyyy.MM.dd");
        qDebug() << "bytes - " << bytes << "\n";
    }
};
class FileReader {
    public:
        static QList<Files> readFile(const QString& filePath) {
            QList<Files> fileList;

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
                Files file(fname, date, bytes);
                fileList.append(file);
            }

            file.close();

            return fileList;
        }
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

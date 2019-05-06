#ifndef ANFILEDATA_H
#define ANFILEDATA_H

//#include <QObject>
#include <QString>
#include <QVector>


class anFileData
{
    using anData = QVector<QString>;
public:
    anFileData()=default;
    ~anFileData()=default;

    anFileData(const anFileData& obj);
    anFileData& operator=(const anFileData& obj);

    anFileData(anFileData&& obj);
    anFileData& operator=(anFileData&& obj);

    void setFileName(const QString& filename){
        file_fullname_ = filename;
    }
    void push_data(QString&& data);
public:
    QString file_fullname_;
    anData file_context_;
};

using anFileData_v = QVector<anFileData>;

#endif // ANFILEDATA_H

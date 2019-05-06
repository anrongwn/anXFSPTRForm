#ifndef ANFILE_MAPREDUCE_H
#define ANFILE_MAPREDUCE_H

#include "anfiledata.h"

struct mapped{
    mapped()=default;

    anFileData operator()(const QString& filename){
        anFileData fd;
        fd.setFileName(filename);

        QFile f(filename);
        if (f.open(QIODevice::ReadOnly)){
            fd.push_data(f.readAll());
        }
        f.close();

        return fd;
    }

    typedef anFileData result_type;
};


struct reduced{
    reduced()=default;

    void operator ()(anFileData_v &form, const anFileData &data){
        form.push_back(data);
    }

};

#endif // ANFILE_MAPREDUCE_H

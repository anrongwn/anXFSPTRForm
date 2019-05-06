#ifndef ANFILE_MAPREDUCE_H
#define ANFILE_MAPREDUCE_H

#include "anfiledata.h"

struct mapped{
    mapped()=default;

    typedef anFileData result_type;
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

};


struct reduced{
    reduced()=default;

    typedef anFileData_v result_type;
    void operator ()(anFileData_v &form, const anFileData &data){
        form.push_back(data);
    }

};

#endif // ANFILE_MAPREDUCE_H

#include "anfiledata.h"
#include <utility>

/*
anFileData::anFileData()
{

}
*/

anFileData::anFileData(const anFileData &obj)
{
    file_fullname_ = obj.file_fullname_;
    file_context_ = obj.file_context_;
}

anFileData &anFileData::operator=(const anFileData &obj)
{
    if (this!=&obj){
        file_fullname_ = obj.file_fullname_;
        file_context_ = obj.file_context_;
    }

    return (*this);
}

anFileData::anFileData(anFileData &&obj)
{
    file_fullname_ = std::move(obj.file_fullname_);
    file_context_ = std::move(obj.file_context_);

    obj.file_fullname_="";
    obj.file_context_.clear();
}

anFileData &anFileData::operator=(anFileData &&obj)
{
    if (this!=&obj){
        file_fullname_ = std::move(obj.file_fullname_);
        file_context_ = std::move(obj.file_context_);

        obj.file_fullname_="";
        obj.file_context_.clear();
    }

    return (*this);

}

void anFileData::push_data(QString &&data)
{
    file_context_.push_back(std::forward<QString>(data));
}

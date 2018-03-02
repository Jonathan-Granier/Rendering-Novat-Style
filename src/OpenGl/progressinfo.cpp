#include "progressinfo.h"
#include <iostream>

ProgressInfo::ProgressInfo():
    _mark(100),
    _progress(0)
{}

void ProgressInfo::setMark(unsigned int mark)
{
    _mark = mark;
    emit progressBegin();
}

void ProgressInfo::setProgress(unsigned int progress)
{

    //std::cout << progress << " | " << _progress << " | " << progress*100/_mark << " | " << _progress*100/_mark << std::endl;
    /*if(progress*100/_mark > _progress*100/_mark)

    */

    _progress = progress;
    emit progressUpdate();

}

void ProgressInfo::endProgress()
{
    emit progressEnd();
}

unsigned int ProgressInfo::mark() const
{
    return _mark;
}

unsigned int ProgressInfo::progress() const
{
    return _progress;
}

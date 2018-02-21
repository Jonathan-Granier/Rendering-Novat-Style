#include "progressbar.h"


ProgressBar::ProgressBar(std::ostream &os):
    _mark(0),
    _progress(0),
    _os(os)
{}

void ProgressBar::update(const int &i, const int &n)
{
    int p(((float) i/(n-1))*100);
    _progress = p;
    if(_progress>_mark){
        _mark=_progress;
        _os << "[" <<_progress <<"%]" << std::endl;
    }

}

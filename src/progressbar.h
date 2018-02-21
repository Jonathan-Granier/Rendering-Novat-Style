#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <ostream>

class ProgressBar
{
public:
    ProgressBar(std::ostream &os);
    void init();
    void update(int const&i, int const& n);

private:
    unsigned int _mark;
    unsigned int _progress;
    std::ostream &_os;

};




#endif // PROGRESSBAR_H

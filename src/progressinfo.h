#ifndef PROGRESSINFO_H
#define PROGRESSINFO_H

#include <QObject>

class ProgressInfo : public QObject
{
    Q_OBJECT
public:
    ProgressInfo();

    void setMark(unsigned int mark);
    void setProgress(unsigned int progress);
    void endProgress();
    unsigned int mark() const;
    unsigned int progress() const;

signals:
    void progressBegin();
    void progressEnd();
    void progressUpdate();

private:
    unsigned int _mark;
    unsigned int _progress;

};




#endif // PROGRESSINFO_H

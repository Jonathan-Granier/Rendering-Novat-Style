#ifndef PROGRESSINFO_H
#define PROGRESSINFO_H

#include <QObject>
/**
 * @brief Store the information of a progress and emit 3 signal (begin, update and end).
 */
class ProgressInfo : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     */
    ProgressInfo();

    /**
     * @brief set the maximum of the progress , emit progressBegin
     * @param mark the maximum of the progress
     */
    void setMark(unsigned int mark);
    /**
     * @brief set the actual progress (between 0 and _mark). emit progressUpdate
     * @param progress
     */
    void setProgress(unsigned int progress);
    /**
     * @brief emit progressEnd
     */
    void endProgress();
    /**
     * @brief get _mark
     * @return the maximum of the progress
     */
    unsigned int mark() const;
    /**
     * @brief get _progress
     * @return the actual progress
     */
    unsigned int progress() const;

signals:
    /**
     * @brief the progress begin
     */
    void progressBegin();
    /**
     * @brief the progress is finished
     */
    void progressEnd();

    /**
     * @brief the progress update
     */
    void progressUpdate();

private:
    /**
     * @brief the maximum of the progress
     */
    unsigned int _mark;
    /**
     * @brief the actual progress
     */
    unsigned int _progress;

};




#endif // PROGRESSINFO_H

#ifndef EXRMANAGER_H
#define EXRMANAGER_H

#include <memory>
#include <QString>
#include <QObject>
#include <QJsonArray>

class EXRRateModel;
class EXRParser;
class EXRDownloader;
class EXRManager : public QObject
{
    Q_OBJECT
public:
    EXRManager();
    void init();
    Q_INVOKABLE void exec(const QString &strStartTime, const QString &strEndTime, int nNationCode);
    Q_INVOKABLE QJsonArray getNationCodes();
    Q_INVOKABLE QString getMaxRate();

signals:
    void sigExecBegin();
    void sigExecFinish();
    void sigParamError();

private:
    std::shared_ptr<EXRDownloader> m_pDownloader;
    std::shared_ptr<EXRParser> m_pParser;
    std::shared_ptr<EXRRateModel> m_pModel;
};

#endif // EXRMANAGER_H

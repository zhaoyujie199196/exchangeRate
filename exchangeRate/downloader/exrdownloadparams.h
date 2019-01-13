#ifndef EXRDOWNLOADPARAMS_H
#define EXRDOWNLOADPARAMS_H

#include <QString>

class IEXRParams
{
public:
    IEXRParams() {}
    virtual ~IEXRParams() {}
};

class EXRDownloadParams : public IEXRParams
{
public:
    QString m_strStartTime = "2019-01-01";
    QString m_strEndTime = "2019-01-11";
    int m_nNationCode = 3030;
    int m_nPageIndex = 1;
};

#endif // EXRDOWNLOADPARAMS_H

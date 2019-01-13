#include "exrmanager.h"
#include "downloader/exrdownloader.h"
#include "downloader/exrdownloadparams.h"
#include "parser/exrparseparam.h"
#include "parser/exrparser.h"
#include "model/exrrateitem.h"
#include "model/exrratemodel.h"
#include <QFile>
#include <QJsonObject>

EXRManager::EXRManager()
{

}

void EXRManager::init()
{
    m_pModel = std::shared_ptr<EXRRateModel>(new EXRRateModel);
    m_pParser = std::shared_ptr<EXRParser>(new EXRParser);
    m_pDownloader = std::shared_ptr<EXRDownloader>(new EXRDownloader);
}

#include <QDebug>
void EXRManager::exec(const QString &strStartTime, const QString &strEndTime, int nNationCode)
{
    qDebug()<<strStartTime<<" "<<strEndTime<<" "<<nNationCode;
    if (strStartTime.isEmpty() || strEndTime.isEmpty()
            || nNationCode == -1 || strStartTime > strEndTime)
    {
        emit sigParamError();
        return;
    }
    emit sigExecBegin();
    std::shared_ptr<EXRDownloadParams> pParam(new EXRDownloadParams);
    pParam->m_strStartTime = strStartTime;
    pParam->m_strEndTime = strEndTime;
    pParam->m_nNationCode = nNationCode;
    pParam->m_nPageIndex = 1;

    bool bNeedParsePageCount = true;
    int nPageCount = -1;
    m_pModel->clear();
    while(true)
    {
        QByteArray webDataArr = m_pDownloader->doDownload(pParam);
        std::shared_ptr<EXRParseParam> pParseParam(new EXRParseParam);
        pParseParam->m_dataArr = webDataArr;
        QVector<std::shared_ptr<EXRRateItem>> rateItemVec = m_pParser->doParse(pParseParam);
        m_pModel->append(rateItemVec);
        if (nPageCount != -1 && pParam->m_nPageIndex >= nPageCount)
            break;

        pParam->m_nPageIndex++;

        if (!bNeedParsePageCount)
            continue;
        nPageCount = m_pParser->parsePageCount(pParseParam);
        if (nPageCount != -1)
            bNeedParsePageCount = false;
    }
    emit sigExecFinish();
}

QJsonArray EXRManager::getNationCodes()
{
    QFile file("./nationCode");
    file.open(QIODevice::ReadOnly);
    QByteArray arr = file.readAll();
    file.close();
    QString strNationCodes;
    strNationCodes.append(arr);
    QJsonArray resultArr;
    QStringList nationCodeList = strNationCodes.split("\r\n");
    for (QString strNationCode : nationCodeList)
    {
        QStringList strTmpList = strNationCode.split(" ");
        if (strTmpList.size() != 2)
            continue;
        QJsonObject obj;
        obj.insert("nation", strTmpList[0]);
        obj.insert("code", strTmpList[1]);
        resultArr.append(obj);
    }
    return resultArr;
}

QString EXRManager::getMaxRate()
{
    int nCount = m_pModel->count();
    double dRate = 0;
    QString strRate;
    for (int i = 0; i < nCount; ++i)
    {
        std::shared_ptr<EXRRateItem> pItem = m_pModel->getItem(i);
        if (!pItem)
            continue;
        if (pItem->m_strRate5.toDouble() > dRate)
            strRate = QString::number(pItem->m_strRate5.toDouble() / 100, 'f', 4);
    }
    return strRate;
}


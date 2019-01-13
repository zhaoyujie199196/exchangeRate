#include "exrdownloader.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QFile>
#include "exrdownloadparams.h"

//#define SAVE_RECORD

//eractData  ：查询开始时间
//nothingcha ：查询结束时间
//pjname     ：目标国家编号
//page       ：获取第几页的数据
static const QString c_strChindBankChangeUrl = "http://srh.bankofchina.com/search/whpj/search.jsp?erectDate=%1&nothing=%2&pjname=%3&page=%4";

EXRDownloader::EXRDownloader()
{

}

QByteArray EXRDownloader::doDownload(std::shared_ptr<EXRDownloadParams> pParam)
{
    if (!pParam)
        return QByteArray();
    QString strUrl = makeUrl(pParam);
    if (strUrl.isEmpty())
        return QByteArray();
    QNetworkAccessManager *pManager = new QNetworkAccessManager;
//    connect(pManager, &QNetworkAccessManager::finished, this, &EXRDownloader::onReplyFinish);
    QNetworkRequest request;
    request.setUrl(QUrl(strUrl));
    QEventLoop loop;
    connect(pManager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    QNetworkReply *pReply = pManager->get(request);
    loop.exec();
    return onReplyFinish(pReply);
}

QString EXRDownloader::makeUrl(std::shared_ptr<EXRDownloadParams> pParam)
{
    if (!pParam)
        return "";
    QString strUrl = c_strChindBankChangeUrl.arg(pParam->m_strStartTime)
            .arg(pParam->m_strEndTime).arg(pParam->m_nNationCode) .arg(pParam->m_nPageIndex);
    return strUrl;
}

#include <qDebug>
QByteArray EXRDownloader::onReplyFinish(QNetworkReply *pReply)
{
   // qDebug()<<"onReplyFinish";
    QByteArray arr = pReply->readAll();

#ifdef SAVE_RECORD
    QFile file(QString("./webData_%1"));
    file.open(QIODevice::WriteOnly);
    file.write(arr);
    file.close();
#endif

    return arr;
}



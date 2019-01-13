#ifndef EXRDOWNLOADER_H
#define EXRDOWNLOADER_H

#include <QByteArray>
#include <QString>
#include <QObject>
#include <memory>

class QNetworkReply;
class EXRDownloadParams;
class EXRDownloader : public QObject
{
    Q_OBJECT
public:
    EXRDownloader();
    QByteArray doDownload(std::shared_ptr<EXRDownloadParams> pParam);

protected:
    QString makeUrl(std::shared_ptr<EXRDownloadParams> pParam);
    QByteArray onReplyFinish(QNetworkReply *reply);

protected:
};

#endif // EXRDOWNLOADER_H

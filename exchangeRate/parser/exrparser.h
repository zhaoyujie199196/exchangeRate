#ifndef EXRPARSER_H
#define EXRPARSER_H

#include <memory>
#include <QString>
#include <QStringList>
#include <QVector>

class EXRParseParam;
class EXRRateItem;
class EXRParser
{
public:
    QVector<std::shared_ptr<EXRRateItem>> doParse(std::shared_ptr<EXRParseParam> pParam);
    int parsePageCount(std::shared_ptr<EXRParseParam> pParam);

protected:
    QStringList parseTable(const QString &strTable);
    std::shared_ptr<EXRRateItem> parseRateItem(const QString &strItemString);
    int getPageData(const QString &strVarKey, const QString &strHtml);
};

#endif // EXRPARSER_H

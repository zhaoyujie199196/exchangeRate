#include "exrparser.h"
#include "exrparseparam.h"
#include "model/exrrateitem.h"
#include "model/exrratemodel.h"
#include <QString>
#include <QDebug>
#include <QRegExp>

static const QString c_strRegExp = "<tr>\r\n\t\t\t<td>([^<]*)</td>\r\n\t\t\t<td>([^<]*)</td>\r\n\t\t\t\t<td>([^<]*)</td>\r\n\t\t\t\t<td>([^<]*)</td>\r\n\t\t\t\t<td>([^<]*)</td>\r\n\t\t\t\t<td>([^<]*)</td>\r\n\t\t\t\t<td>([^<]*)</td>";

QVector<std::shared_ptr<EXRRateItem>> EXRParser::doParse(std::shared_ptr<EXRParseParam> pParam)
{
    QVector<std::shared_ptr<EXRRateItem>> resultItemVec;
    QString strHtml;
    strHtml.append(pParam->m_dataArr);
    QString strSpliter = "BOC_main publish";
    QStringList strList = strHtml.split(strSpliter);
    if (strList.size() != 2)
        return resultItemVec;
    strHtml = strList[1];
    int nTableIndex1 = strHtml.indexOf("<table");
    int nTableIndex2 = strHtml.indexOf("</table>");
    QString strTable = strHtml.mid(nTableIndex1, nTableIndex2 - nTableIndex1 + 8);
    QStringList tableItemList = parseTable(strTable);
    tableItemList.removeLast();
    tableItemList.removeFirst();
    parseRateItem(tableItemList[0]);
    for (auto strItemString : tableItemList)
    {
        std::shared_ptr<EXRRateItem> pRateItem = parseRateItem(strItemString);
        if (!pRateItem)
            continue;
        resultItemVec.append(pRateItem);
    }
    return resultItemVec;
}

QStringList EXRParser::parseTable(const QString &strTable)
{
    QStringList itemList;
    int nStartIndex = 0;
    while (true)
    {
        int nBeginIndex = strTable.indexOf("<tr>", nStartIndex);
        int nEndIndex = strTable.indexOf("</tr>", nStartIndex);
        nStartIndex = nEndIndex + 5;
        if (nBeginIndex == -1 || nEndIndex == -1)
            break;
        QString strItemString = strTable.mid(nBeginIndex, nEndIndex - nBeginIndex + 5);
        itemList.append(strItemString);
    }
    return itemList;
}

std::shared_ptr<EXRRateItem> EXRParser::parseRateItem(const QString &strItemString)
{
    QRegExp regexp(c_strRegExp);
    int nIndex = regexp.indexIn(strItemString);
    if (nIndex == -1)
        return nullptr;
    QStringList capTexts = regexp.capturedTexts();
    if (capTexts.size() != 8)
        return nullptr;
    std::shared_ptr<EXRRateItem> pRateItem(new EXRRateItem());
    pRateItem->m_strMoneyName = capTexts[1];
    pRateItem->m_strRate1 = capTexts[2];
    pRateItem->m_strRate2 = capTexts[3];
    pRateItem->m_strRate3 = capTexts[4];
    pRateItem->m_strRate4 = capTexts[5];
    pRateItem->m_strRate5 = capTexts[6];
    pRateItem->m_strTime = capTexts[7];
    return pRateItem;
}

int EXRParser::parsePageCount(std::shared_ptr<EXRParseParam> pParam)
{
    QString strHtml;
    strHtml.append(pParam->m_dataArr);
    int nRecordCount = getPageData("m_nRecordCount", strHtml);
    int nRecordCountPerPage = getPageData("m_nPageSize", strHtml);
    if (nRecordCount == -1 || nRecordCountPerPage == -1)
        return -1;
    return nRecordCount / nRecordCountPerPage + (nRecordCount % nRecordCountPerPage == 0 ? 0 : 1);
}

int EXRParser::getPageData(const QString &strVarKey, const QString &strHtml)
{
    QRegExp regexp(QString("var %1 = ([0-9]*);").arg(strVarKey));
    int nIndex = regexp.indexIn(strHtml);
    if (nIndex == -1)
        return -1;
    QStringList captureTexts = regexp.capturedTexts();
    if (captureTexts.size() != 2)
        return -1;
    int nResult = captureTexts[1].toInt();
    return nResult;
}

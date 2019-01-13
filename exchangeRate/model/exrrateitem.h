#ifndef EXRRATEITEM_H
#define EXRRATEITEM_H

#include <QString>

class EXRRateItem
{
public:
    QString m_strMoneyName;
    QString m_strRate1;    //现汇买入价
    QString m_strRate2;    //现钞买入价
    QString m_strRate3;    //现汇卖出价
    QString m_strRate4;    //现钞卖出价
    QString m_strRate5;    //中行折算价
    QString m_strTime;  //发布时间
};


#endif // EXRRATEITEM_H

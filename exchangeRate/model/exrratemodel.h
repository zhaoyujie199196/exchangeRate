#ifndef EXRRATEMODEL_H
#define EXRRATEMODEL_H

#include <memory>
#include <QVector>

class EXRRateItem;
class EXRRateModel
{
public:
    void append(std::shared_ptr<EXRRateItem> pItem);
    void append(const QVector<std::shared_ptr<EXRRateItem>> &itemVec);
    void clear();
    int count();
    std::shared_ptr<EXRRateItem> getItem(int nIndex);

private:
    QVector<std::shared_ptr<EXRRateItem>> m_ItemVec;
};


#endif // EXRRATEMODEL_H

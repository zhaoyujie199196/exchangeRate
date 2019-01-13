#include "exrratemodel.h"
#include "exrrateitem.h"

void EXRRateModel::append(std::shared_ptr<EXRRateItem> pItem)
{
    m_ItemVec.append(pItem);
}

void EXRRateModel::append(const QVector<std::shared_ptr<EXRRateItem>> &itemVec)
{
    m_ItemVec.append(itemVec);
}

void EXRRateModel::clear()
{
    m_ItemVec.clear();
}

int EXRRateModel::count()
{
    return m_ItemVec.size();
}

std::shared_ptr<EXRRateItem> EXRRateModel::getItem(int nIndex)
{
    if (nIndex < 0 || nIndex >= m_ItemVec.size())
        return nullptr;
    return m_ItemVec[nIndex];
}

#pragma once
#include <QVariant>

struct IVariantable
{
    virtual QVariant getData(int col) = 0;
};

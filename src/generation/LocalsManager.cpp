#include "generation/LocalsManager.h"

#include <cassert>

Local* LocalsManager::registerNewLocal(Local::Size type)
{
    auto newIndex = registerLocal(type);
    return new Local(newIndex, type, this);
}

void LocalsManager::freeLocal(Local* local)
{
    assert(local->owner_ == this);
    auto index = local->getIndex();
    auto size = local->getSize();
    locals_[index] = false;
    if (size == Local::Size::two)
    {
        locals_[index + 1] = false;
    }
}

int LocalsManager::registerLocal(Local::Size size)
{
    switch (size)
    {
    case Local::Size::one:
        for (int i = 0; i < locals_.size(); i++)
        {
            if (locals_[i] == false)
            {
                locals_[i] = true;
                return i;
            }
        }
        locals_.push_back(true);
        return locals_.size() - 1;
    case Local::Size::two:
        for (int i = 0; i < locals_.size(); i++)
        {
            if (locals_[i] == false)
            {
                if (i == locals_.size() - 1)
                {
                    locals_[i] = true;
                    locals_.push_back(true);
                    return i;
                }
                else if (locals_[i + 1] == false)
                {
                    locals_[i] = true;
                    locals_[i + 1] = true;
                    return i;
                }
            }
        }
        locals_.push_back(true);
        locals_.push_back(true);
        return locals_.size() - 2;
    }
}

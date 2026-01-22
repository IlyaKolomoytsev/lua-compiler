#include "generation/Local.h"

#include "generation/LocalsManager.h"

Local::~Local()
{
    owner_->freeLocal(this);
}

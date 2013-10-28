#include "builder.h"
#include "cases.h"
#include "human.h"

Forest *Builder::createForest() const
{
    return new Forest();
}

Ground *Builder::createGround() const
{
    return new Ground();
}

Human *Builder::createHuman() const
{
    return new Human();
}

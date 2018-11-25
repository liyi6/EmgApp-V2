#include "Utils.h"

QString Utils::getAppHomeDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/EmgApp";
}

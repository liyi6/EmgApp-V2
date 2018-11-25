#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QObject>
#include "Defines.h"

class AppContext : public QObject
{
    Q_OBJECT
public:
    static AppContext* instance();
    Context& getContext();

private:
    explicit AppContext(QObject *parent = nullptr);

private:
    static AppContext* m_instance;
    Context   m_context;
};

#endif // APPCONTEXT_H

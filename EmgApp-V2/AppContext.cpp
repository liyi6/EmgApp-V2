#include "AppContext.h"

AppContext* AppContext::m_instance = nullptr;

AppContext *AppContext::instance()
{
    if (!m_instance) {
        m_instance = new AppContext;
    }
    return m_instance;
}

void AppContext::destroyInstance()
{
    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

Context &AppContext::getContext()
{
    return m_context;
}

AppContext::AppContext(QObject *parent)
    : QObject(parent)
{

}

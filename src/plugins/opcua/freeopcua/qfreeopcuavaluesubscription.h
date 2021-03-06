/****************************************************************************
**
** Copyright (C) 2015 basysKom GmbH, opensource@basyskom.com
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtOpcUa module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QFREEOPCUAVALUESUBSCRIPTION_H
#define QFREEOPCUAVALUESUBSCRIPTION_H

#include <private/qopcuasubscriptionimpl_p.h>
#include <QtOpcUa/qopcuamonitoredevent.h>
#include <QtOpcUa/qopcuamonitoredvalue.h>

#include <opc/ua/subscription.h>

namespace OpcUa {
    class Event;
    class UaClient;
}

QT_BEGIN_NAMESPACE

class QFreeOpcUaClient;
class QOpcUaNode;
class QFreeOpcUaMonitoredValue;
class QOpcUaSubscription;

class QFreeOpcUaSubscription : public QOpcUaSubscriptionImpl, public OpcUa::SubscriptionHandler
{
public:
    explicit QFreeOpcUaSubscription(QFreeOpcUaClient *client, quint32 interval);
    ~QFreeOpcUaSubscription() Q_DECL_OVERRIDE;

    // FreeOPC-UA callbacks
    void DataChange(uint32_t handle, const OpcUa::Node &node, const OpcUa::Variant &val,
                    OpcUa::AttributeId attr) Q_DECL_OVERRIDE;
    void Event(quint32 handle, const OpcUa::Event &event) Q_DECL_OVERRIDE;

    QOpcUaMonitoredEvent *addEvent(QOpcUaNode *node) Q_DECL_OVERRIDE;
    void removeEvent(QOpcUaMonitoredEvent *event) Q_DECL_OVERRIDE;
    QOpcUaMonitoredValue *addValue(QOpcUaNode *node) Q_DECL_OVERRIDE;
    void removeValue(QOpcUaMonitoredValue *value) Q_DECL_OVERRIDE;

    QFreeOpcUaClient *m_client;
    QOpcUaSubscription *m_qsubscription;
    std::unique_ptr<OpcUa::Subscription> m_subscription;
    QMap<int32_t, QOpcUaMonitoredValue *> m_dataChangeHandles;
    QMap<int32_t, QOpcUaMonitoredEvent *> m_eventHandles;
};

QT_END_NAMESPACE

#endif // QFREEOPCUAVALUESUBSCRIPTION_H

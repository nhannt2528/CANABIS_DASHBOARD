#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H

#include <QObject>


class MqttService : public QObject
{
    Q_OBJECT
public:
    explicit MqttService(QObject *parent = nullptr);

signals:

};

#endif // MQTTSERVICE_H

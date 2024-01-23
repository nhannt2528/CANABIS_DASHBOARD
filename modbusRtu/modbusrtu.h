#ifndef MODBUSRTU_H
#define MODBUSRTU_H

#include <QObject>
#include <QtSerialBus/QModbusRtuSerialMaster>
#include <QtSerialBus/QModbusDataUnit>
#include <QtSerialBus/QModbusDevice>
#include <QtSerialPort/QSerialPort>
#include <QVariant>
#include <QDebug>
#include <QCoreApplication>


class ModbusRtu : public QObject
{
    Q_OBJECT
private:
    QSerialPort serialPort;
    QModbusRtuSerialMaster modbusMaster;
public:
   typedef enum{
        READ_SUCCESS,
        WRITE_SUCCESS,
        READ_ERROR,
        WRITE_ERROR,
        SEND_ERROR
    }modbus_status_t;
    explicit ModbusRtu(QObject *parent = nullptr);
    bool connectDevice();
    void disconnectDevice();
    modbus_status_t readCoils(uint8_t slaveID, uint8_t startAddress, int count, bool *data);
    modbus_status_t readDiscreteInputs(uint8_t slaveID, uint8_t startAddress, int count, bool *data);
    modbus_status_t readHoldingRegisters(uint8_t slaveID, uint8_t startAddress, int count, uint16_t *data);
    modbus_status_t readInputRegisters(uint8_t slaveID, uint8_t startAddress, int count, uint16_t *data);

    modbus_status_t writeCoils(uint8_t slaveID, uint8_t startAddress, uint8_t count, bool *data);
    modbus_status_t writeSingleCoil(uint8_t slaveID, uint8_t coilAddress, bool value);
    modbus_status_t writeHoldingRegister(uint8_t slaveID, uint8_t regAddress, uint8_t count, uint16_t data);
    void writeMultipleCoils(uint8_t slaveID, uint8_t startAddress, const QVector<bool> &coils);
    void writeMultipleHoldingRegisters(uint8_t slaveID, uint8_t startAddress, const QVector<quint16> &registers);

signals:
};

#endif // MODBUSRTU_H

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
    void readDiscreteInputs(uint8_t slaveID, uint8_t startAddress, int count);
    void readHoldingRegisters(uint8_t slaveID, uint8_t startAddress, int count);
    void readInputRegisters(uint8_t slaveID, uint8_t startAddress, int count);

    void writeCoils(uint8_t slaveID, uint8_t startAddress, const QVector<bool> &coils);
    void writeSingleCoil(uint8_t slaveID, uint8_t coilAddress, bool value);
    void writeHoldingRegister(uint8_t slaveID, uint8_t regAddress, quint16 value);
    void writeMultipleCoils(uint8_t slaveID, uint8_t startAddress, const QVector<bool> &coils);
    void writeMultipleHoldingRegisters(uint8_t slaveID, uint8_t startAddress, const QVector<quint16> &registers);

signals:
};

#endif // MODBUSRTU_H

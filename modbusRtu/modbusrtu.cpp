#include "modbusrtu.h"

ModbusRtu::ModbusRtu(QObject *parent)
    : QObject{parent}
{
    modbusMaster.setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM1");
    modbusMaster.setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    modbusMaster.setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    modbusMaster.setTimeout(1000);
}
bool ModbusRtu::connectDevice()
{
    bool check=false;
    if(!modbusMaster.connectDevice()){
        qDebug()<<"Cannot connect device";

    }
    else{
        qDebug()<<"Connected device";
    }
    return check;
}
void ModbusRtu::disconnectDevice()
{
    modbusMaster.disconnectDevice();
    serialPort.close();
}

ModbusRtu::modbus_status_t ModbusRtu::readCoils(uint8_t slaveID, uint8_t startAddress, int count, bool *data)
{
    QModbusDataUnit readUnit(QModbusDataUnit::Coils, startAddress, count);
    readUnit.setRegisterType(QModbusDataUnit::Coils);

    modbus_status_t status = SEND_ERROR;

    if (auto *reply = modbusMaster.sendReadRequest(readUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() == QModbusDevice::NoError) {
            const QModbusDataUnit result = reply->result();
            for (int i = 0; i < result.valueCount(); ++i) {
                data[i] = result.value(i);
            }
            status = READ_SUCCESS;
        } else {
            status = READ_ERROR;
            qDebug() << "khong doc duoc ID 1:" << reply->errorString();
        }
        reply->deleteLater();
    }
    else{
        status=SEND_ERROR;
    }

    return status;
}
ModbusRtu::modbus_status_t ModbusRtu::readDiscreteInputs(uint8_t slaveID, uint8_t startAddress, int count, bool *data)
{
    modbus_status_t status = SEND_ERROR;
    QModbusDataUnit readUnit(QModbusDataUnit::DiscreteInputs, startAddress, count);
    readUnit.setRegisterType(QModbusDataUnit::DiscreteInputs);

    if (auto *reply = modbusMaster.sendReadRequest(readUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() == QModbusDevice::NoError) {
            const QModbusDataUnit result = reply->result();
            for (int i = 0; i < result.valueCount(); ++i) {
                data[i] = result.value(i);
            }
            status = READ_SUCCESS;
        } else {
            status = READ_ERROR;

        }
        reply->deleteLater();
    } else {
        status=SEND_ERROR;
    }
    return status;
}
ModbusRtu::modbus_status_t ModbusRtu::readHoldingRegisters(uint8_t slaveID, uint8_t startAddress, int count, uint16_t *data)
{
    modbus_status_t status = SEND_ERROR;
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, startAddress, count);
    readUnit.setRegisterType(QModbusDataUnit::HoldingRegisters);

    if (auto *reply = modbusMaster.sendReadRequest(readUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() == QModbusDevice::NoError) {
            const QModbusDataUnit result = reply->result();
            for (int i = 0; i < result.valueCount(); ++i) {
                data[i] = result.value(i);
            }
            status = READ_SUCCESS;
        } else {
            status = READ_ERROR;
        }
        reply->deleteLater();
    } else {
        status=SEND_ERROR;
    }
    return status;
}

ModbusRtu::modbus_status_t ModbusRtu::readInputRegisters(uint8_t slaveID, uint8_t startAddress, int count, uint16_t *data)
{
    modbus_status_t status = SEND_ERROR;
    QModbusDataUnit readUnit(QModbusDataUnit::InputRegisters, startAddress, count);
    readUnit.setRegisterType(QModbusDataUnit::InputRegisters);

    if (auto *reply = modbusMaster.sendReadRequest(readUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        }
        if (reply->error() == QModbusDevice::NoError) {
            const QModbusDataUnit result = reply->result();
            for (int i = 0; i < result.valueCount(); ++i) {
                data[i] = result.value(i);
            }
            status = READ_SUCCESS;
        } else {
            status = READ_ERROR;
        }
        reply->deleteLater();
    } else {
        status=SEND_ERROR;
    }
    return status;
}
ModbusRtu::modbus_status_t ModbusRtu::writeCoils(uint8_t slaveID, uint8_t startAddress, uint8_t count, bool *data)
{
    modbus_status_t status = SEND_ERROR;
    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, startAddress, count);
    writeUnit.setRegisterType(QModbusDataUnit::Coils);
    for (int i = 0; i < count; ++i) {
        writeUnit.setValue(i, data[i]);
    }

    if (auto *reply = modbusMaster.sendWriteRequest(writeUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() == QModbusDevice::NoError) {
            status = WRITE_SUCCESS;
        } else {
            status = WRITE_ERROR;
        }
        reply->deleteLater();
    } else {
        status = SEND_ERROR;
    }
    return status;
}

ModbusRtu::modbus_status_t ModbusRtu::writeSingleCoil(uint8_t slaveID, uint8_t coilAddress, bool value)
{
    modbus_status_t status = SEND_ERROR;
    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, coilAddress, 1);
    writeUnit.setRegisterType(QModbusDataUnit::Coils);
    writeUnit.setValue(0, value);

    if (auto *reply = modbusMaster.sendWriteRequest(writeUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() == QModbusDevice::NoError) {
            status = WRITE_SUCCESS;
        } else {
            status = WRITE_ERROR;
        }
        reply->deleteLater();
    } else {
        status = SEND_ERROR;
    }
    return status;
}

ModbusRtu::modbus_status_t ModbusRtu::writeHoldingRegister(uint8_t slaveID, uint8_t regAddress, uint8_t count, uint16_t data)
{
    modbus_status_t status = SEND_ERROR;
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, regAddress, 1);
    writeUnit.setRegisterType(QModbusDataUnit::HoldingRegisters);
    writeUnit.setValue(0, data);

    if (auto *reply = modbusMaster.sendWriteRequest(writeUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() == QModbusDevice::NoError) {
            status = WRITE_SUCCESS;
        } else {
               status = WRITE_ERROR;
        }
        reply->deleteLater();
    } else {
         status = SEND_ERROR;
    }
     return status;
}

void ModbusRtu::writeMultipleCoils(uint8_t slaveID, uint8_t startAddress, const QVector<bool> &coils)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, startAddress, coils.size());
    writeUnit.setRegisterType(QModbusDataUnit::Coils);
    for (int i = 0; i < coils.size(); ++i) {
        writeUnit.setValue(i, coils[i]);
    }

    if (auto *reply = modbusMaster.sendWriteRequest(writeUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() != QModbusDevice::NoError) {
            // Xử lý lỗi khi gửi yêu cầu ghi
        } else {
            // Xử lý khi ghi thành công
        }
        reply->deleteLater();
    } else {
        // Xử lý lỗi khi không thể gửi yêu cầu ghi
    }
}

void ModbusRtu::writeMultipleHoldingRegisters(uint8_t slaveID, uint8_t startAddress, const QVector<quint16> &registers)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, startAddress, registers.size());
    writeUnit.setRegisterType(QModbusDataUnit::HoldingRegisters);
    for (int i = 0; i < registers.size(); ++i) {
        writeUnit.setValue(i, registers[i]);
    }

    if (auto *reply = modbusMaster.sendWriteRequest(writeUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() != QModbusDevice::NoError) {
            // Xử lý lỗi khi gửi yêu cầu ghi
        } else {

        }
        reply->deleteLater();
    } else {
        // Xử lý lỗi khi không thể gửi yêu cầu ghi
    }
}



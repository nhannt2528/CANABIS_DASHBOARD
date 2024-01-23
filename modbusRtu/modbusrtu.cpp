#include "modbusrtu.h"

ModbusRtu::ModbusRtu(QObject *parent)
    : QObject{parent}
{
    modbusMaster.setConnectionParameter(QModbusDevice::SerialPortNameParameter, "ttyUSB0");
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
            qDebug()<<"success";
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

    return status; // Trả về trạng thái ở cuối hàm
}
void ModbusRtu::readDiscreteInputs(uint8_t slaveID, uint8_t startAddress, int count)
{
    QModbusDataUnit readUnit(QModbusDataUnit::DiscreteInputs, startAddress, count);
    readUnit.setRegisterType(QModbusDataUnit::DiscreteInputs);

    if (auto *reply = modbusMaster.sendReadRequest(readUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() == QModbusDevice::NoError) {
            const QModbusDataUnit result = reply->result();
            // Xử lý dữ liệu đọc được từ Discrete Inputs ở đây
        } else {
            // Xử lý khi có lỗi trong quá trình đọc
        }
        reply->deleteLater();
    } else {
        // Xử lý khi không thể gửi yêu cầu đọc
    }
}
void ModbusRtu::readHoldingRegisters(uint8_t slaveID, uint8_t startAddress, int count)
{
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, startAddress, count);
    readUnit.setRegisterType(QModbusDataUnit::HoldingRegisters);

    if (auto *reply = modbusMaster.sendReadRequest(readUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() == QModbusDevice::NoError) {
            const QModbusDataUnit result = reply->result();
            // Xử lý dữ liệu đọc được từ Holding Registers ở đây
        } else {
            // Xử lý khi có lỗi trong quá trình đọc
        }
        reply->deleteLater();
    } else {
        // Xử lý khi không thể gửi yêu cầu đọc
    }
}

void ModbusRtu::readInputRegisters(uint8_t slaveID, uint8_t startAddress, int count)
{
    QModbusDataUnit readUnit(QModbusDataUnit::InputRegisters, startAddress, count);
    readUnit.setRegisterType(QModbusDataUnit::InputRegisters);

    if (auto *reply = modbusMaster.sendReadRequest(readUnit, slaveID)) {
        while (!reply->isFinished()) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        if (reply->error() == QModbusDevice::NoError) {
            const QModbusDataUnit result = reply->result();
            // Xử lý dữ liệu đọc được từ Input Registers ở đây
        } else {
            // Xử lý khi có lỗi trong quá trình đọc
        }
        reply->deleteLater();
    } else {
        // Xử lý khi không thể gửi yêu cầu đọc
    }
}
void ModbusRtu::writeCoils(uint8_t slaveID, uint8_t startAddress, const QVector<bool> &coils)
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

void ModbusRtu::writeSingleCoil(uint8_t slaveID, uint8_t coilAddress, bool value)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, coilAddress, 1);
    writeUnit.setRegisterType(QModbusDataUnit::Coils);
    writeUnit.setValue(0, value);

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

void ModbusRtu::writeHoldingRegister(uint8_t slaveID, uint8_t regAddress, quint16 value)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, regAddress, 1);
    writeUnit.setRegisterType(QModbusDataUnit::HoldingRegisters);
    writeUnit.setValue(0, value);

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
            // Xử lý khi ghi thành công
        }
        reply->deleteLater();
    } else {
        // Xử lý lỗi khi không thể gửi yêu cầu ghi
    }
}



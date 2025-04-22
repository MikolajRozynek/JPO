/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "stationsChanged",
    "",
    "statusChanged",
    "cityNameChanged",
    "sensorDataChanged",
    "sensorHistoryChanged",
    "selectedSensorChanged",
    "selectedStationIdChanged",
    "airQualityStatusChanged",
    "fetchStations",
    "fetchStationDetails",
    "stationId",
    "fetchSensorData",
    "fetchSensorHistory",
    "sensorId",
    "paramName",
    "paramFormula",
    "saveSensorDataToJson",
    "cityName",
    "fetchAirQualityForStation",
    "onNetworkReply",
    "QNetworkReply*",
    "reply",
    "handleStationDetailsReply",
    "handleSensorDataReply",
    "handleStationListReply",
    "handleSensorHistoryReply",
    "handleAirQualityResponse",
    "fetchSensorDataForParam",
    "fetchAirQualityStatus",
    "finalizeAndFilterSensorData",
    "stations",
    "QVariantList",
    "status",
    "sensorData",
    "sensorHistory",
    "selectedSensor",
    "QVariantMap",
    "airQualityStatus",
    "selectedStationId"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       8,  207, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  152,    2, 0x06,    9 /* Public */,
       3,    0,  153,    2, 0x06,   10 /* Public */,
       4,    0,  154,    2, 0x06,   11 /* Public */,
       5,    0,  155,    2, 0x06,   12 /* Public */,
       6,    0,  156,    2, 0x06,   13 /* Public */,
       7,    0,  157,    2, 0x06,   14 /* Public */,
       8,    0,  158,    2, 0x06,   15 /* Public */,
       9,    0,  159,    2, 0x06,   16 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,  160,    2, 0x0a,   17 /* Public */,
      11,    1,  161,    2, 0x0a,   18 /* Public */,
      13,    1,  164,    2, 0x0a,   20 /* Public */,
      14,    3,  167,    2, 0x0a,   22 /* Public */,
      18,    2,  174,    2, 0x0a,   26 /* Public */,
      20,    1,  179,    2, 0x0a,   29 /* Public */,
      21,    1,  182,    2, 0x08,   31 /* Private */,
      24,    1,  185,    2, 0x08,   33 /* Private */,
      25,    1,  188,    2, 0x08,   35 /* Private */,
      26,    1,  191,    2, 0x08,   37 /* Private */,
      27,    1,  194,    2, 0x08,   39 /* Private */,
      28,    1,  197,    2, 0x08,   41 /* Private */,
      29,    1,  200,    2, 0x08,   43 /* Private */,
      30,    1,  203,    2, 0x08,   45 /* Private */,
      31,    0,  206,    2, 0x08,   47 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,   15,   16,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   19,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      32, 0x80000000 | 33, 0x00015009, uint(0), 0,
      34, QMetaType::QString, 0x00015001, uint(1), 0,
      19, QMetaType::QString, 0x00015103, uint(2), 0,
      35, 0x80000000 | 33, 0x00015009, uint(3), 0,
      36, 0x80000000 | 33, 0x00015009, uint(4), 0,
      37, 0x80000000 | 38, 0x00015009, uint(5), 0,
      39, QMetaType::QString, 0x00015001, uint(7), 0,
      40, QMetaType::Int, 0x00015103, uint(6), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // property 'stations'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // property 'status'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'cityName'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'sensorData'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // property 'sensorHistory'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // property 'selectedSensor'
        QtPrivate::TypeAndForceComplete<QVariantMap, std::true_type>,
        // property 'airQualityStatus'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'selectedStationId'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'stationsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'statusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cityNameChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sensorDataChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sensorHistoryChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectedSensorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectedStationIdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'airQualityStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fetchStations'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fetchStationDetails'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'fetchSensorData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'fetchSensorHistory'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'saveSensorDataToJson'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'fetchAirQualityForStation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onNetworkReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>,
        // method 'handleStationDetailsReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>,
        // method 'handleSensorDataReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>,
        // method 'handleStationListReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>,
        // method 'handleSensorHistoryReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>,
        // method 'handleAirQualityResponse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>,
        // method 'fetchSensorDataForParam'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'fetchAirQualityStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'finalizeAndFilterSensorData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->stationsChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->cityNameChanged(); break;
        case 3: _t->sensorDataChanged(); break;
        case 4: _t->sensorHistoryChanged(); break;
        case 5: _t->selectedSensorChanged(); break;
        case 6: _t->selectedStationIdChanged(); break;
        case 7: _t->airQualityStatusChanged(); break;
        case 8: _t->fetchStations(); break;
        case 9: _t->fetchStationDetails((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->fetchSensorData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->fetchSensorHistory((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 12: _t->saveSensorDataToJson((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 13: _t->fetchAirQualityForStation((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->onNetworkReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 15: _t->handleStationDetailsReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 16: _t->handleSensorDataReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 17: _t->handleStationListReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 18: _t->handleSensorHistoryReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 19: _t->handleAirQualityResponse((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 20: _t->fetchSensorDataForParam((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 21: _t->fetchAirQualityStatus((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 22: _t->finalizeAndFilterSensorData(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::stationsChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::statusChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::cityNameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::sensorDataChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::sensorHistoryChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::selectedSensorChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::selectedStationIdChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (MainWindow::*)();
            if (_q_method_type _q_method = &MainWindow::airQualityStatusChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantList*>(_v) = _t->stations(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->status(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->cityName(); break;
        case 3: *reinterpret_cast< QVariantList*>(_v) = _t->sensorData(); break;
        case 4: *reinterpret_cast< QVariantList*>(_v) = _t->sensorHistory(); break;
        case 5: *reinterpret_cast< QVariantMap*>(_v) = _t->selectedSensor(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->airQualityStatus(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->selectedStationId(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setCityName(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->setSelectedStationId(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::stationsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::cityNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::sensorDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::sensorHistoryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::selectedSensorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::selectedStationIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MainWindow::airQualityStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP

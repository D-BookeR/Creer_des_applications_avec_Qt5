#ifndef ENGINIOBACKENDCONNECTION_P_H
#define ENGINIOBACKENDCONNECTION_P_H

#include <QtCore/qbasictimer.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qurl.h>
#include <QtNetwork/qabstractsocket.h>

#include "enginioclient_global.h"

class EnginioClient;
class EnginioReply;
class QTcpSocket;
class ENGINIOCLIENT_EXPORT EnginioBackendConnection : public QObject
{
    Q_OBJECT

    enum WebSocketOpcode
    {
        ContinuationFrameOp = 0x0,
        TextFrameOp = 0x1,
        BinaryFrameOp = 0x2,
        // %x3-7 are reserved for further non-control frames
        ConnectionCloseOp = 0x8,
        PingOp = 0x9,
        PongOp = 0xA
        // %xB-F are reserved for further control frames
    } _protocolOpcode;

    enum ProtocolDecodeState
    {
        HandshakePending,
        FrameHeaderPending,
        PayloadDataPending
    } _protocolDecodeState;

    bool _sentCloseFrame;
    bool _isFinalFragment;
    bool _isPayloadMasked;
    quint64 _payloadLength;
    QByteArray _applicationData;

    QUrl _socketUrl;
    QByteArray _handshakeReply;
    QTcpSocket *_tcpSocket;
    QBasicTimer _keepAliveTimer;
    QBasicTimer _pingTimeoutTimer;

public:
    enum WebSocketCloseStatus
    {
        UnknownCloseStatus = -1,
        NormalCloseStatus = 1000,
        GoingAwayCloseStatus = 1001,
        ProtocolErrorCloseStatus = 1002,
        UnsupportedDataTypeCloseStatus = 1003,
        // 1004 Reserved. Not used.
        // 1005 Missing status code. Not used.
        // 1006 Abnormal disconnect. Not used.
        InconsistentDataTypeCloseStatus = 1007,
        PolicyViolationCloseStatus = 1008,
        MessageTooBigCloseStatus = 1009,
        MissingExtensionClientCloseStatus = 1010,
        BadOperationServerCloseStatus = 1011
        // 1015 TLS handshake failed. Not used.
    };

    enum ConnectionState {
        DisconnectedState,
        ConnectingState,
        ConnectedState
    };

    explicit EnginioBackendConnection(QObject *parent = 0);

    bool isConnected() { return _protocolDecodeState > HandshakePending; }
    void connectToBackend(EnginioClient *client, const QJsonObject& messageFilter = QJsonObject());


    void close(WebSocketCloseStatus closeStatus = NormalCloseStatus);
    void ping();

signals:
    void stateChanged(ConnectionState state);
    void dataReceived(QJsonObject data);
    void timeOut();
    void pong();

private slots:
    void onEnginioFinished(EnginioReply *);
    void onSocketStateChanged(QAbstractSocket::SocketState);
    void onSocketConnectionError(QAbstractSocket::SocketError);
    void onSocketReadyRead();

private:
    void timerEvent(QTimerEvent *event);
    void protocolError(const char* message, WebSocketCloseStatus status = ProtocolErrorCloseStatus);
};

#endif // ENGINIOBACKENDCONNECTION_P_H

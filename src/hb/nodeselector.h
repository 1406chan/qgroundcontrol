#ifndef NODESELECTOR_H
#define NODESELECTOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QString>
#include <QVariantMap>

#include "pidiscoverer.h"

class NodeSelector : public QObject
{
    Q_OBJECT
public:
    explicit NodeSelector(QNetworkAccessManager *nam, QObject *parent = 0);
    virtual ~NodeSelector();
    QString deviceAddress() const;
    PiDiscoverer* discoverer() const { return m_discoverer; }
    QString videoUriForCurrentNode();

Q_SIGNALS:
    void thermalUrl(const QUrl &thermalUrl);

public Q_SLOTS:
    void onNewNodeDiscovered(const PiNode& node);
    void selectNext();
    void selectPrevious();
    PiNode currentNode() const;
    int currentNodeIndex() const { return m_currentIndex; }
    // returns port on the client side where udp packets are being sents
    int startStreaming(const PiNode& node, int width, int height, int fps, int bitrate);
    int startStreaming(int nodeIndex, int width, int height, int fps, int bitrate);
    void stopStreaming(int nodeIndex);
    bool startThermal(int nodeIndex);
    bool startThermal(const PiNode& node);
    void terminatePicam(const PiNode& node);
    void terminateThermal(int index);
    void terminateThermal(const PiNode& node);
    void shutdownAll();
    void restartAll();
    // mavproxy and thermal start automatically if the node is capable

private Q_SLOTS:
    void replyFinished();

private:
    void sendRequest(const QUrl &url, const QVariantMap &properties = QVariantMap());
    void terminateMavProxy(const PiNode& node);

    PiDiscoverer            *m_discoverer;
    QNetworkAccessManager   *m_nam;
    int                      m_currentIndex;
};

#endif // NODESELECTOR_H

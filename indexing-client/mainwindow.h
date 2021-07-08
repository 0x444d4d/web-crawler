#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRemoteObjectNode>
#include <QUrl>
#include "rep_remoteObject_replica.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    const QString REMOTE_OBJECT_REGISTRY = QStringLiteral("local:registry");
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startIndexingButton_clicked();
public slots:
    void updateResults(const QUrl &originalUrl, const QList<QUrl> &urlList);
    void onInitializedReplica();

private:
    QUrl requestedUrl_;
    Ui::MainWindow *ui;
    QRemoteObjectNode *remoteObjectNode_;
    QScopedPointer<IndexingServiceReplica, QScopedPointerDeleteLater> indexingService_;
};
#endif // MAINWINDOW_H

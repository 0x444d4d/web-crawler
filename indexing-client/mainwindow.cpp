#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , remoteObjectNode_(new QRemoteObjectNode(REMOTE_OBJECT_REGISTRY, this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInitializedReplica()
{
        requestedUrl_ = ui->inputSearch->text();
        indexingService_->request(ui->inputSearch->text(), ui->depthBox->value());
        disconnect(indexingService_.get(), &IndexingServiceReplica::initialized, this, &MainWindow::onInitializedReplica);
}

void MainWindow::on_startIndexingButton_clicked()
{
    if (indexingService_.isNull())
    {
        indexingService_.reset(remoteObjectNode_->acquire<IndexingServiceReplica>());
        connect(indexingService_.get(), &IndexingServiceReplica::response, this, &MainWindow::updateResults);
    }

    if (indexingService_->isReplicaValid())
    {
        requestedUrl_ = ui->inputSearch->text();
        indexingService_->request(ui->inputSearch->text(), ui->depthBox->value());
    }
    else
    {
        connect(indexingService_.get(), &IndexingServiceReplica::initialized, this, &MainWindow::onInitializedReplica);
    }
}


void MainWindow::updateResults(const QUrl &originalUrl, const QList<QUrl> &urlList)
{
    if (originalUrl == requestedUrl_)
    {
        qDebug() << "Recibida la sennal de indexingService";
        ui->ResultEdit->clear();
        for (auto url: urlList)
            ui->ResultEdit->append(url.toString());
    }
}

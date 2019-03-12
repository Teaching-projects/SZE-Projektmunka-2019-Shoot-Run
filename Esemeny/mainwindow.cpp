#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QPlainTextEdit>

MainWindow::MainWindow(EventController *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_eventController( controller )
{
    Q_ASSERT( m_eventController != nullptr );
    ui->setupUi(this);
    setupSignals();
    ui->actionAdd->setShortcut( QKeySequence::New );
    ui->actionEdit->setShortcut( tr( "Ctrl+E" ) );
    ui->actionRemove->setShortcut( QKeySequence::Delete );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupSignals()
{

    connect( ui->actionAdd, &QAction::triggered, this, &MainWindow::addEntry );
    connect( ui->actionRemove, &QAction::triggered, this, &MainWindow::removeEntry );
    connect( ui->actionEdit, &QAction::triggered, this, &MainWindow::editItem );
    connect( ui->buttonBox->button( QDialogButtonBox::Save ), &QPushButton::clicked,
             this, &MainWindow::saveItem );
    connect( ui->buttonBox->button( QDialogButtonBox::Discard ), &QPushButton::clicked,
             this, &MainWindow::discardItem );
    connect( ui->buttonBox->button( QDialogButtonBox::Reset ), &QPushButton::clicked,
             this, &MainWindow::resetItem );

    connect( ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
             this, SLOT(setWindowTitle(QString)));

    connect( ui->listWidget, &QListWidget::itemDoubleClicked, [this]( QListWidgetItem *item ) {
       ui->listWidget->setCurrentItem( item );
       editItem();
    });
}
void MainWindow::addEntry()
{
    if ( ui->stackedWidget->currentWidget() == ui->listPage ) {
        auto entry = m_eventController->createEntry();
        if ( entry ) {
            ui->listWidget->addItem( entry->name() );
            auto item = ui->listWidget->item( ui->listWidget->count() - 1 );
            if ( item ) {
                m_entryMap.insert( item, entry );
            }
        }
    }
}

/*
 * The user requested deletion of an address book entry
 */
void MainWindow::removeEntry()
{
    if ( ui->stackedWidget->currentWidget() == ui->listPage ) {
        // Get the currently selected item:
        auto item = ui->listWidget->currentItem();
        // Look up which entry is associated with it:
        auto entry = m_entryMap.value( item );
        // If both are valid...
        if ( item && entry ) {
            // ...we forward the deletion request to the controller. If this in turn suceeds...
            if ( m_eventController->deleteEntry( entry ) ) {
                // We remove the association and delete the UI item:
                m_entryMap.remove( item );
                delete item;
            }
        }
    }
}

/*
 * The user requested to edit an item (and hence show its details)
 */
void MainWindow::editItem()
{
    if ( ui->stackedWidget->currentWidget() == ui->listPage ) {
        // Get the UI item and the associated address book entry:
        auto item = ui->listWidget->currentItem();
        auto entry = m_entryMap.value( item );
        // If both exist...
        if ( item && entry ) {
            // Change the current page to the details page...
            ui->stackedWidget->setCurrentWidget( ui->detailsPage );
            // and call the resetItem() method, which will cause the current item's details to be shown
            resetItem();
        }
    }
}

/*
 * The user requested to save the current item
 */
void MainWindow::saveItem()
{
    // Get the current item and associated address book entry:
    auto item = ui->listWidget->currentItem();
    auto entry = m_entryMap.value( item );
    // If both exist:
    if ( item && entry ) {

        entry->setName( ui->nameEdit->text() );
        entry->setDate( ui->dataEdit->date() );
        // For the phone numbers, let's do some processing:
        QStringList numbers;
        // Split the (plain text) string and iterate over all entries:
        for ( auto number : ui->photoesEdit->toPlainText().split("\n") ) {
            // If a line is not empty, store it as phone number (without further checks for now...):
            if ( !number.isEmpty() ) {
                numbers.append( number );
            }
        }
        entry->setPhotoes( numbers );
        item->setText( entry->name() );
    }
    ui->stackedWidget->setCurrentWidget( ui->listPage );
}

void MainWindow::discardItem()
{
   ui->stackedWidget->setCurrentWidget( ui->listPage );
}

/*
 * The user requested to reset the UI (and discard any potential changes done on the current item)
 */
void MainWindow::resetItem()
{
    // Get the current UI item and its associated address book entry:
    auto item = ui->listWidget->currentItem();
    auto entry = m_entryMap.value( item );
    // If both exist...
    if ( item && entry ) {
        // Set the UI element's values to the entry's stored values:
        ui->nameEdit->setText( entry->name() );
        ui->photoesEdit->setPlainText( entry->photoes().join( "\n" ) );
        ui->dataEdit->setDate( entry->date() );
    }
}

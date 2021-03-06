#include "ConcertSearch.h"
#include "ui_ConcertSearch.h"

#include <QDebug>

#include "globals/Manager.h"

/**
 * @brief ConcertSearch::ConcertSearch
 * @param parent
 */
ConcertSearch::ConcertSearch(QWidget *parent) : QDialog(parent), ui(new Ui::ConcertSearch)
{
    ui->setupUi(this);

#ifdef Q_OS_MAC
    setWindowFlags((windowFlags() & ~Qt::WindowType_Mask) | Qt::Sheet);
    setStyleSheet(styleSheet() + " #ConcertSearch { border: 1px solid rgba(0, 0, 0, 100); border-top: none; }");
#else
    setWindowFlags((windowFlags() & ~Qt::WindowType_Mask) | Qt::Dialog);
#endif

    connect(ui->buttonClose, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->concertSearchWidget, SIGNAL(sigResultClicked()), this, SLOT(accept()));
}

/**
 * @brief ConcertSearch::~ConcertSearch
 */
ConcertSearch::~ConcertSearch()
{
    delete ui;
}

/**
 * @brief Returns an instance of the class
 * @param parent Parent widget
 * @return Instance of ConcertSearch
 */
ConcertSearch *ConcertSearch::instance(QWidget *parent)
{
    static ConcertSearch *m_instance = nullptr;
    if (m_instance == nullptr) {
        m_instance = new ConcertSearch(parent);
    }
    return m_instance;
}

/**
 * @brief Executes the search dialog
 * @param searchString Concert name/search string
 * @return Result of QDialog::exec
 * @see ConcertSearch::search
 */
int ConcertSearch::exec(QString searchString)
{
    qDebug() << "Entered";
    QSize newSize;
    newSize.setHeight(parentWidget()->size().height() - 200);
    newSize.setWidth(qMin(600, parentWidget()->size().width() - 400));
    resize(newSize);
    ui->concertSearchWidget->search(searchString);
    return QDialog::exec();
}

int ConcertSearch::exec()
{
    return 0;
}

/*** GETTER ***/

/**
 * @brief ConcertSearch::scraperNo
 * @return Current scraper number
 */
int ConcertSearch::scraperNo()
{
    return ui->concertSearchWidget->scraperNo();
}

/**
 * @brief ConcertSearch::scraperId
 * @return Scraper id of the concert last clicked in result table
 */
QString ConcertSearch::scraperId()
{
    return ui->concertSearchWidget->scraperId();
}

/**
 * @brief ConcertSearch::infosToLoad
 * @return List of infos to load from the scraper
 */
QList<int> ConcertSearch::infosToLoad()
{
    return ui->concertSearchWidget->infosToLoad();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include "plotwidget.h"
#include "plotmatrix.h"
#include "filterablelistwidget.h"
#include "tabbedplotwidget.h"

#include "../plugins/dataloader_base.h"
#include "../plugins/statepublisher_base.h"
#include "../plugins/datastreamer_base.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onUndoableChange();

private slots:

    void onTrackerTimeUpdated(double current_time );

    void onTrackerPositionUpdated(QPointF pos );

    void onSplitterMoved(int, int);

    void resizeEvent(QResizeEvent *) ;

    void onPlotAdded(PlotWidget* plot);

    void onActionSaveLayout();

    void onActionLoadLayout(bool reload_previous = false);

    void onActionLoadDataFile(bool reload_from_settings = false);

    void onActionLoadDataFile(QString filename);

    void onActionReloadDataFileFromSettings();

    void onActionReloadSameDataFile();

    void onActionReloadRecentLayout();

    void onActionLoadStreamer();

    void onPushButtonActivateTracker_toggled(bool checked);

    void onUndoInvoked();

    void onRedoInvoked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_tabbedAreaDestroyed(QObject*object);

    void onFloatingWindowDestroyed(QObject*object);

    void onCreateFloatingWindow(PlotMatrix* first_tab = NULL);

    void onPushButtonAddSubwindow_pressed();

    void onSwapPlots(PlotWidget* source, PlotWidget* destination);

    void onPushButtonStreaming_toggled(bool checked);

    void onReplotRequested();

    void on_streamingSpinBox_valueChanged(int value);

    void onDeleteLoadedData();

private:
    Ui::MainWindow *ui;

    std::vector<TabbedPlotWidget *> _tabbed_plotarea;
    std::vector<QMainWindow *>      _floating_window;

    /*   QAction* _action_loadRecentFile;
    QAction* _action_reloadFile;
    QAction* _action_loadRecentLayout;

    QAction* _action_SaveLayout;
    QAction* _action_LoadLayout;
    QAction* _action_LoadData;
*/
    QAction* _actionUndo;
    QAction* _actionRedo;

    //   QAction* _action_startDataStream;

    void createActions();

    FilterableListWidget* curvelist_widget;

    std::vector<PlotMatrix*> _plot_matrix_list;

    void updateInternalState();

    void getMaximumRangeX(double* minX, double* maxX);

    void buildData();

    PlotDataMap    _mapped_plot_data;

    void rearrangeGridLayout();

    QColor colorHint();

    void loadPlugins(QString subdir_name);

    std::map<QString,DataLoader*> data_loader;
    std::vector<StatePublisher*>  state_publisher;
    std::vector<DataStreamer*>    data_streamer;

    QDomDocument xmlSaveState();
    bool xmlLoadState(QDomDocument state_document);

    std::deque<QDomDocument> _undo_states;
    std::deque<QDomDocument> _redo_states;

    QElapsedTimer _undo_timer;

    QString _loaded_datafile;

    void createTabbedDialog(PlotMatrix *first_tab, bool undoable);

protected:
    void mousePressEvent(QMouseEvent *event) ;

    void dragEnterEvent(QDragEnterEvent *event) ;

    void deleteLoadedData(const QString &curve_name);

    QTimer *_replot_timer;

};

#endif // MAINWINDOW_H

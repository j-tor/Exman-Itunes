#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_return_B_1_clicked();
    void on_return_B_2_clicked();
    void on_return_B_3_clicked();
    void on_return_B_4_clicked();
    void on_return_B_5_clicked();
    void on_return_B_6_clicked();

    void on_add_Button_clicked();

    void on_review_Button_clicked();

    void on_dowload_Button_clicked();

    void on_song_Button_clicked(bool checked);

    void on_song_Button_clicked();

    void on_info_Button_clicked();

    void on_exit_Button_clicked();

    void on_add_Button_2_clicked();

    void on_review_Botton_clicked();

    void on_dowload_Button_2_clicked();

    void on_infoSong_Button_clicked();

    void on_update_SButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

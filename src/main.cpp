#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QScreen>
#include <QPixmap>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Main Canvas Window
    QWidget window;
    window.resize(800, 600);
    window.setWindowTitle("Percepti - Screen Capture Test");

    // Layout to hold our screenshot preview
    QVBoxLayout *layout = new QVBoxLayout(&window);
    QLabel *imageLabel = new QLabel("Waiting for screen capture...", &window);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("color: white; font-size: 16px;");
    layout->addWidget(imageLabel);

    // Single-shot timer: Wait 2 seconds, then take a screenshot
    QTimer::singleShot(2000, [&]() {
        QScreen *screen = QGuiApplication::primaryScreen();
        if (screen) {
            // Grab the entire primary screen
            QPixmap screenshot = screen->grabWindow(0);
            
            // Scale the screenshot down to fit neatly inside our 800x600 window
            QPixmap scaledPixmap = screenshot.scaled(imageLabel->size(), 
                                                     Qt::KeepAspectRatio, 
                                                     Qt::SmoothTransformation);
            
            imageLabel->setPixmap(scaledPixmap);
            qDebug() << "Screen captured successfully!";
        } else {
            imageLabel->setText("Failed to capture primary screen.");
        }
    });

    window.show();
    return app.exec();
}
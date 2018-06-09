////
//// Created by jon on 02/06/18.
////

#include <c++/7.3.0/iostream>
#include "borderlesswindow.h"

BorderlessWindow::BorderlessWindow(QWidget *parent) :
        QMainWindow(parent)
{

}

void BorderlessWindow::setMenuBar(QMenuBar *menuBar)
{
    QLayout *topLayout = layout();

    if (topLayout->menuBar() && topLayout->menuBar() != menuBar) {
        // Reparent corner widgets before we delete the old menu bar.
        QMenuBar *oldMenuBar = dynamic_cast<QMenuBar *>(topLayout->menuBar());
        if (menuBar) {
            // TopLeftCorner widget.
            QWidget *cornerWidget = oldMenuBar->cornerWidget(Qt::TopLeftCorner);
            if (cornerWidget)
                menuBar->setCornerWidget(cornerWidget, Qt::TopLeftCorner);
            // TopRightCorner widget.
            cornerWidget = oldMenuBar->cornerWidget(Qt::TopRightCorner);
            if (cornerWidget)
                menuBar->setCornerWidget(cornerWidget, Qt::TopRightCorner);
        }
        oldMenuBar->hide();
        oldMenuBar->deleteLater();
    }

    auto t_widget = new QWidget(this);

    auto t_layout = new QVBoxLayout(this);
    t_layout->setSpacing(0);
    t_layout->setMargin(0);
    t_layout->setContentsMargins(0, 0, 0, 0);

    auto t_title = new FlatTitleBar(this);
    t_title->setObjectName("title_bar");

    t_layout->addWidget(t_title);
    t_layout->addWidget(menuBar);

    t_widget->setLayout(t_layout);

    t_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    topLayout->setMenuBar(t_widget);
}

void BorderlessWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
#ifdef Q_OS_WIN
    window_borderless();
#endif
}

#ifdef Q_OS_WIN
void BorderlessWindow::window_borderless()
{
    if (isVisible())
    {
//        auto defaultStyle = (WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME);
//        SetWindowLongPtr((HWND)winId(), GWL_STYLE, WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX );

        window_shadow();

//        SetWindowPos((HWND)winId(), 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
    }
}

bool BorderlessWindow::testHitGlobal(QWidget* w, long x, long y)
{
    QPoint pg(x, y);
    QPoint p = w->mapFromGlobal(pg);

    return w->rect().contains(p);
}

void BorderlessWindow::window_shadow()
{
    const MARGINS shadow = { 1, 1, 1, 1 };
//    DwmExtendFrameIntoClientArea((HWND)winId(), &shadow);
}

bool BorderlessWindow::nativeEvent(const QByteArray& eventType, void *message, long *result)
{
    MSG* msg;
    if ( eventType == "windows_generic_MSG" )
        msg = reinterpret_cast<MSG*>(message);
    else
        return QWidget::nativeEvent(eventType, message, result);

    switch (msg->message)
    {
        case WM_NCCALCSIZE:
        {
            //this kills the window frame and title bar we added with
            //WS_THICKFRAME and WS_CAPTION
            *result = 0;
            return true;
        }
        case WM_NCHITTEST:
        {
            if (*result == HTCAPTION)
                return QWidget::nativeEvent(eventType, message, result);

            *result = 0;
            const LONG border_width = 8; //in pixels
            RECT winrect;
            GetWindowRect((HWND)winId(), &winrect);

            long x = GET_X_LPARAM(msg->lParam);
            long y = GET_Y_LPARAM(msg->lParam);

            bool resizeWidth = minimumWidth() != maximumWidth();
            bool resizeHeight = minimumHeight() != maximumHeight();

            if(resizeWidth)
            {
                //left border
                if (x >= winrect.left && x < winrect.left + border_width)
                {
                    *result = HTLEFT;
                }
                //right border
                if (x < winrect.right && x >= winrect.right - border_width)
                {
                    *result = HTRIGHT;
                }
            }
            if(resizeHeight)
            {
                //bottom border
                if (y < winrect.bottom && y >= winrect.bottom - border_width)
                {
                    *result = HTBOTTOM;
                }
                //top border
                if (y >= winrect.top && y < winrect.top + border_width)
                {
                    *result = HTTOP;
                }
            }
            if(resizeWidth && resizeHeight)
            {
                //bottom left corner
                if (x >= winrect.left && x < winrect.left + border_width &&
                    y < winrect.bottom && y >= winrect.bottom - border_width)
                {
                    *result = HTBOTTOMLEFT;
                }
                //bottom right corner
                if (x < winrect.right && x >= winrect.right - border_width &&
                    y < winrect.bottom && y >= winrect.bottom - border_width)
                {
                    *result = HTBOTTOMRIGHT;
                }
                //top left corner
                if (x >= winrect.left && x < winrect.left + border_width &&
                    y >= winrect.top && y < winrect.top + border_width)
                {
                    *result = HTTOPLEFT;
                }
                //top right corner
                if (x < winrect.right && x >= winrect.right - border_width &&
                    y >= winrect.top && y < winrect.top + border_width)
                {
                    *result = HTTOPRIGHT;
                }
            }

            // this handles if we are in the title bar, or the main content
            if(*result == 0) {
                // get the height of our title bar
                auto t_bar = menuWidget()->findChild<FlatTitleBar*>("title_bar");

                if (testHitGlobal(t_bar, x, y) && !t_bar->testHitButtonsGlobal(x, y))
                    *result = HTCAPTION; // this says we are in a title bar...
                else
                    *result = HTCLIENT; // this is client space
            }

            return true;
        } //end case WM_NCHITTEST
        case WM_CLOSE:
        {
            return close();
        }
        default: {
            return QWidget::nativeEvent(eventType, message, result);
        }
    }
}

#endif
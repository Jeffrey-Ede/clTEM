//
// Created by jonat on 13/01/2019.
//
#include <QtCore/QAbstractNativeEventFilter>
#include <theme/thememanager.h>

#ifndef CLTEM_ABSTRACTNATIVEEVENTFILTER_H
#define CLTEM_ABSTRACTNATIVEEVENTFILTER_H


class AbstractNativeEventFilterHelper : public QAbstractNativeEventFilter
{
public:
    AbstractNativeEventFilterHelper() {
        ThemeManager::setUseLightNative(detectUseLightTheme());
    }

private:

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override {
//        std::cout << "lol" << std::endl;

        if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
            if( static_cast<MSG*>(message)->message == WM_WININICHANGE) {
                // this catches the change of dark/light theme in windows, not sure if it get's called by much else?
                // see https://docs.microsoft.com/en-us/windows/desktop/winmsg/wm-wininichange
                // see https://stackoverflow.com/a/51336913
                ThemeManager::setUseLightNative(detectUseLightTheme());
            }

        return false; // false makes the message 'be handled further'
    }

    bool detectUseLightTheme() {
        // https://stackoverflow.com/questions/29795410/read-windows-registry-in-qt
        QSettings settings(R"(HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)", QSettings::NativeFormat);
        auto use_light = settings.value("AppsUseLightTheme").toBool();
        return use_light;
    }
};

#endif //CLTEM_ABSTRACTNATIVEEVENTFILTER_H
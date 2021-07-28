#pragma once
#include "App.xaml.g.h"

namespace winrt::StorageQueryTest::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
        void OnSuspending(IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&);
        void OnNavigationFailed(IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const&);
        void OnFileActivated(Windows::ApplicationModel::Activation::FileActivatedEventArgs const& args);
    private:
        void SetupRootFrame(Windows::ApplicationModel::Activation::FileActivatedEventArgs const& args);
    };
}

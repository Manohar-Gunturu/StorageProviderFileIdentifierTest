#pragma once

#include "MainPage.g.h"

#include <winrt/Windows.Storage.FileProperties.h>

using namespace winrt;
using namespace winrt::Windows;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::UI::Xaml;

namespace WS = winrt::Windows::Storage;

namespace winrt::StorageQueryTest::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();
        void OnNavigatedTo(Navigation::NavigationEventArgs const& e);

        IAsyncAction ClickHandler_GetFileCount(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void OnFileSystemChangeNotification(WS::Search::IStorageQueryResultBase /*sender*/, Windows::Foundation::IInspectable /*args*/);

    private:

        winrt::fire_and_forget BeginTest(Windows::ApplicationModel::Activation::FileActivatedEventArgs const& fileActivatedEventArgs);

        Storage::Search::StorageFileQueryResult m_query{ nullptr };
        uint32_t m_queryTotalItemCount{ 0 };
        //Collections::IVector<Storage::StorageFile> m_storageFiles{ nullptr };
        uint32_t m_queryIndex{ 0 };
        winrt::event_token m_fileSystemWatchToken{ };

		inline static const winrt::hstring ODID = L"System.StorageProviderFileIdentifier";

		// System properties to retrieve
		inline static const std::initializer_list SystemProperties
		{
			ODID
		};

    };

}

namespace winrt::StorageQueryTest::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}

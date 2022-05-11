#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <winrt/Windows.Storage.Search.h>

using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Search;
using namespace Windows::UI::Xaml;
using namespace winrt::Windows::ApplicationModel::Activation;

constexpr uint32_t BulkLoadStorageFileCount{ 50 };

namespace winrt::StorageQueryTest::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }


    void MainPage::OnNavigatedTo(Navigation::NavigationEventArgs const& e)
    {
        auto args = e.Parameter();
        auto fileActivatedEventArgs = args.try_as<FileActivatedEventArgs>();

        if (fileActivatedEventArgs) {
            BeginTest(fileActivatedEventArgs);
        }
    }


    IAsyncAction  MainPage::ClickHandler_GetFileCount(IInspectable const&, RoutedEventArgs const&)
    {
        m_queryTotalItemCount = co_await m_query.GetItemCountAsync();
        debugPrint(L"GetItemCountAsync() %d files\n", m_queryTotalItemCount);
    }

    void MainPage::OnFileSystemChangeNotification(WS::Search::IStorageQueryResultBase /*sender*/, Windows::Foundation::IInspectable /*args*/)
    {
        debugPrint(L"OnFileSystemChangeNotification()\n");
    }

    winrt::fire_and_forget MainPage::BeginTest(Windows::ApplicationModel::Activation::FileActivatedEventArgs const& fileActivatedEventArgs)
    {
        auto strong_this{ get_strong() };

        auto storageFile = fileActivatedEventArgs.Files().GetAt(0).try_as<WS::StorageFile>();
        auto query = fileActivatedEventArgs.NeighboringFilesQuery();
        if (storageFile != nullptr && query != nullptr)
        {
            m_query = query;
            m_fileSystemWatchToken = m_query.ContentsChanged({ get_strong(), &MainPage::OnFileSystemChangeNotification });
            m_queryTotalItemCount = co_await m_query.GetItemCountAsync();
            debugPrint(L"GetItemCountAsync() %d files\n", m_queryTotalItemCount);

            auto filesInQueryResult = co_await m_query.GetFilesAsync(0, m_queryTotalItemCount);

            for (auto file : filesInQueryResult)
            {
                auto retrievedProperties = co_await file.Properties().RetrievePropertiesAsync(SystemProperties);
                auto odidref = Windows::Foundation::IReference<hstring>(retrievedProperties.TryLookup(ODID).try_as<Windows::Foundation::IReference<hstring>>());
                auto filename = file.Name();
                auto odid = odidref.Value();

               debugPrint(L"file name %s, %s \n", filename.c_str(), odid.c_str());
            }
        }
    }



}

# StorageQueryTest
------
This sample app is used to demonstrate a problem we are encountering where the *NeighboringFilesQuery* appears to go *bad*

We launch the test app by opening a file so:

* Set the Configuration Properties > Debugging > Launch Application : NO

The app is has file type associations with .jpg, .jpeg, .png

For testing:
* use a folder with a few hundred .jpg(s).
* Right click on a file in the folder
* Open with > StorageQueryTest

This will launch the app with FileActivatedEventArgs from which we get the storage file and query.
* We get the index of the activated file.
* Get number of files in the query.
* Get a batch of files with GetFilesAsync starting at the index of the activated file.

```
auto storageFile = fileActivatedEventArgs.Files().GetAt(0).try_as<WS::StorageFile>();
auto query = fileActivatedEventArgs.NeighboringFilesQuery();

uint32_t queryFileIndex = co_await m_query.FindStartIndexAsync(storageFile);
m_queryTotalItemCount = co_await m_query.GetItemCountAsync();
m_queryIndex = queryFileIndex;
auto filesInQueryResult = co_await m_query.GetFilesAsync(m_queryIndex, 16);
```
We can successfully continue to get more files.
Click on "Load Storage Files", this will load a batch of storage files with the query
```
auto filesInQueryResult = co_await m_query.GetFilesAsync(m_queryIndex, BulkLoadStorageFileCount);
auto resultCount = filesInQueryResult.Size();
debugPrint(L"GetFilesAsync(%d, %d) returned %d files\n", m_queryIndex, BulkLoadStorageFileCount, resultCount);
m_queryIndex += resultCount;
```
## Problem Encounterd ##
Normally if we continue to call GetFilesAsync we can get all the files in the query. However if we call GetFilesAsync a few times (or not), then *wait* several minutes
GetFilesAsync will return a collection with 0 files. In addition at this point if you attemp to get the file count with the query
```
call auto totalItemCount = co_await m_query.GetItemCountAsync();
```
GetItemCountAsync() will never return. 

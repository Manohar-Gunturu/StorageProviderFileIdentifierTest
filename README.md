# StorageQueryTest
------
This sample app is used to demonstrate a problem we are encountering where the *NeighboringFilesQuery* appears to go *bad*

We launch the test app by opening a file so:

* Set the Configuration Properties > Debugging > Launch Application : NO
* Build Debug, x64
* Start Debugging (F5) / Green arrow

The app is has file type associations with .jpg, .jpeg, .png

For testing:
* Don't use One Drive folder.
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
After launching the app, press the button *Load More Storages Files* a few times to load batches of storage files.  Normally if we continue to call GetFilesAsync we can get all the files in the query. However if we call GetFilesAsync a few times (or not), then *wait* several minutes
GetFilesAsync will return a collection with 0 files. 

In the Debug Output, you will see something like:
```
GetItemCountAsync() 2820 files
...
GetFilesAsync(120, 50) returned 50 files
first file in results: 1Vol-slagq4.jpg , last file in results: 03Ltxc0w2Y4.jpg 
GetFilesAsync(170, 50) returned 50 files
first file in results: 3Anq9lRRFyo.jpg , last file in results: 4qQolDX6eSw.jpg 
GetFilesAsync(220, 50) returned 50 files
first file in results: 4rDCa5hBlCs.jpg , last file in results: 5wQKdLdizF4.jpg 

```
wait some time
```
GetFilesAsync(270, 50) returned 0 files
no more items, Something wrong
```
In addition at this point if you attemp to get the file count with the query, click on button *Get File Count*
```
call auto totalItemCount = co_await m_query.GetItemCountAsync();
```
GetItemCountAsync() will never return. 

Note: you can change BulkLoadStorageFileCount to a smaller number to reduce the number of files retrieved in each batch.

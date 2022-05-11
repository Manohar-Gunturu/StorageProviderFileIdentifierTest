# StorageQueryTest
------
This sample app is used to demonstrate a problem we are encountering where the *StorageProviderFileIdentifier* returns null

We launch the test app by opening a file so:

* Set the Configuration Properties > Debugging > Launch Application : NO
* Build Debug, x64
* Start Debugging (F5) / Green arrow

The app is has file type associations with .jpg, .jpeg, .png

For testing:
* use only One Drive folder
* Right click on a file in the folder
* Open with > StorageQueryTest
* MainPage::BeginTest prints StorageProviderFileIdentifier

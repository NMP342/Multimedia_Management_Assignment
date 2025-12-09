# Multimedia Management
Multimedia Management system contains 2 components: MultimediaManagementAssignment and PhysicalMediaFileHandleProcess


MultimediaManagementAssignment is a console application that provides functions to manage media files.

The application contains below functions:

- Display the media files list.
- Upload media file.
- Search media file by name.
- Filter media files by type or genre.
- Play media file.

<br>
PhysicalMediaFileHandleProcess is a console application that performs action related to physical media files.

The application contains below functions:

- Play media file.

<br>
These two system communicate via Named Pipe, where MultimediaManagementAssignment is client and PhysicalMediaFileHandleProcess is server.

PhysicalMediaFileHandleProcess receives message from MultimediaManagementAssignment to perfrom playing media file function.
<br><br>
<img width="631" height="121" alt="IPC" src="https://github.com/user-attachments/assets/8410b9ce-c7e9-4516-afc0-fe833cd239fa" />

# Class Digram

- MultimediaManagementAssignment 

<br>

<img width="1668" height="1934" alt="MultimediaManagement" src="https://github.com/user-attachments/assets/8f1161a6-bdb0-4568-a1c3-6afce8237410" /> <br><br>

- PhysicalMediaFileHandleProcess 

<br>
<img width="901" height="318" alt="PhysicalMediaFileHandleProcess" src="https://github.com/user-attachments/assets/6ccbea47-5bfe-4593-8d99-15ca38d6b182" />


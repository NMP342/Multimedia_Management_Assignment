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
<img width="1680" height="1934" alt="MultimediaManagement" src="https://github.com/user-attachments/assets/49a8272a-e5ac-46e3-9525-e0badd48c38c" /><br><br>

- PhysicalMediaFileHandleProcess 

<br>
<img width="901" height="318" alt="PhysicalMediaFileHandleProcess" src="https://github.com/user-attachments/assets/5018153f-7489-4d67-8ea9-11cb42eb5ea6" />


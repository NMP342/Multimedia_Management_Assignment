# Multimedia Management
This repository contains 2 system: MultimediaManagement system and PhysicalMediaFileHandleProcess


MultimediaManagementAssignment system is a console application that provide functions to manage media files.

  The application contains below functions:

- Display the media files list.
- Upload media file.
- Search media file by name.
- Filter media files by type or genre.
- Play media file.
  

PhysicalMediaFileHandleProcess system is a console application that parforms action related to physical media file.

The application contains below functions:

- Play media file.

These two system communicate via Named Pipe, where MultimediaManagementAssignment is client and PhysicalMediaFileHandleProcess is server.

PhysicalMediaFileHandleProcess receives message from MultimediaManagementAssignment to perfrom play media file function.


# Class Digram

- MultimediaManagementAssignment 

<br>
<img width="1549" height="1934" alt="MultimediaManagement" src="https://github.com/user-attachments/assets/69e00152-6ee0-407a-9044-34068ccb5062" /> <br><br>

- PhysicalMediaFileHandleProcess 

<br>
<img width="901" height="318" alt="PhysicalMediaFileHandleProcess" src="https://github.com/user-attachments/assets/9dfb28bd-b08a-4d04-8715-09628efc50d8" />


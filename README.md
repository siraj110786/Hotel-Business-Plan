# Hotel Management System (C++)

## Project Description
This is a console-based Hotel Management System developed in C++. It allows admins 
and customers to manage hotel operations such as room booking, event booking, customer
search, and record management using file handling.


##  Features

### Admin Features:
- Admin login system (password protected)
- View booking history
- Search customer by CNIC
- Remove customer and archive record

### Customer Features:
- Book a room (Simple, Moderate, Luxury)
- Automatic room assignment
- Book events

##  Room Categories
- Simple Rooms: 1 - 30 (150$)
- Moderate Rooms: 31 - 40 (180$)
- Luxury Rooms: 41 - 50 (210$)

##  File Handling Used
- `hotel.txt` → Stores booking records
- `events.txt` → Stores event bookings
- `serial.txt` → Stores serial number for bookings
- `archive.txt` → Stores deleted customer records

##  How to Run

1. Clone the repository
2. Open project in any C++ IDE (CodeBlocks / DevC++ / Visual Studio)
3. Compile and run `main.cpp`
4. Ensure all `.txt` files are in the same folder


##  Requirements
- C++ Compiler (GCC / MinGW)
- Basic understanding of file handling


##  Author
- Developed by: Your Name
- Purpose: University Project (C++ File Handling System)


##  Output Example
(Admin can view formatted booking records in console)


##  Note
This project uses basic file handling concepts and is designed for learning purposes.

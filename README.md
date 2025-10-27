S/W Detailed Level Design (DLD)
Project Name: Admin Panel Console Application (C++)
Author: Rustam Zaloldinov, Ekaterina Lugovets
Approver: Rustam Zaloldinov – Mid-developer
Date: October 2025
Team: Software Engineering Team
 
1. Overview

This document presents the Detailed Level Design (DLD) for the Admin Panel Console Application built in C++.
The system provides administrative functionality to manage users and their listings.
It allows creation, deletion, search, and data display for user and listing entities.
This DLD aligns with Agile development principles and reflects the software’s architectural and modular structure.

2. System Overview / Architectural Context

The Admin Panel system follows a layered architecture divided into three core modules:

1. Presentation Layer (Console UI)
   - Handles text-based user interaction through console commands and menu navigation.
2. Logic Layer (Core / AdminPanel)
   - Contains business logic for managing users, listings, and their relationships.
3. Data Layer (Models)
   - Encapsulates data entities (User, Listing) with attributes and relationships.

Each layer interacts only with the layer directly below it:
ConsoleUI → AdminPanel → User / Listing.

3. UML Class Diagram (Technical Design)

The following describes the main classes and their relationships:

- Class `AdminPanel`
    - Has a composition relationship with `User` (AdminPanel owns multiple User objects)
- Class `User`
    - Aggregates multiple `Listing` objects
- Class `Listing`
    - Represents an individual item or record owned by a User

Relationships:
AdminPanel → manages → User → has → Listing

4. Class Specifications
Class	Attributes	Methods
Listing	id: int
 title: string
 description: string
 price: double	N/A (Data structure only)
User	id: int
 name: string
 lastName: string
 age: int
 gender: string
 address: string
 listings: vector<Listing>	N/A (Used by AdminPanel)
AdminPanel	users: vector<User>
 nextUserId: int
 nextListingId: int	run()
 createUser()
 deleteUser()
 searchUser()
 showAllUsers()
 createListing()
 deleteListing()
5. Interfaces and Abstractions

At this stage, the system is implemented without formal interface classes.
Future abstraction layers may include:
- IStorage (for file or database persistence)
- IPrintable (for exportable reports)

6. Function Responsibilities
Class	Method	Purpose	Input	Output
AdminPanel	createUser()	Creates a new user and adds to vector<User>	User details via console input	User added to system
AdminPanel	createListing()	Creates a listing for a given user	User ID and listing data	Listing added to selected user
7. Operation Flow

1. The Admin launches the console application.
2. AdminPanel::run() displays menu options.
3. The admin selects an option (e.g., createUser).
4. The corresponding method executes, modifying in-memory user data.
5. Users may have listings created, viewed, or deleted.
6. The flow loops until exit (option 0) is selected.

Flow: ConsoleUI → AdminPanel → User / Listing

8. Enumerations & Constants

No enumerations currently defined.
Possible future additions: Gender (Enum), CommandType (Enum)

9. Validation Rules & Future Work

Validation Rules:
- Age must be positive integer.
- Price must be non-negative.

Future Enhancements:
- Data persistence (File/JSON)
- Admin authentication system
- Enhanced UI (menu formatting and color)
- Logging and error handling

10. Traceability Matrix
Mapping between SRS requirements and implemented design elements:
Requirement (SRS)	Class / Method (DLD)
Admin can manage users	AdminPanel::createUser(), deleteUser(), showAllUsers()
Admin can manage listings for users	AdminPanel::createListing(), deleteListing()
11. Code Structure and File Mapping
Class	File
Listing	src/models/Listing.h / Listing.cpp
User	src/models/User.h / User.cpp
AdminPanel	src/core/AdminPanel.h / AdminPanel.cpp
Main Entry Point	src/main.cpp
12. Revision History
Date	Version	Change Summary	Author
27-Oct-2025	1.0	Initial Detailed Design Document created for Admin Panel System	Rustam Zaloldinov

<img width="432" height="193" alt="image" src="https://github.com/user-attachments/assets/d1b46926-6c0f-437e-a982-b34f0f92fb0f" />

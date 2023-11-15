# DSA-Mini-Project
Student GradeBook manager

How to run the code?

1. The project is a menu driven program 
    -> user is required to give input (integer)

2. All student data is stored in a sample CSV file. When the program starts all data in the file is automatically fed to the function "buildBSTFromFile" which creates a binary search tree by taking every line in the file and inserting it into the BST according to the ID value (using insert function and file handling function)

3. The options included within the menu are -
    * Display students :
        -> display all students
        -> display students with specific cgpa
        -> display students who fall within a cgpa range
        -> display student who cleared cutoff cgpa (main feature)
    
    * Delete a student record
    * Search for a student 
    * Update a student's record
    * Exit program

4. For delete and search functions user has to give student ID only
5. For update function user has to give student ID and if student   exists then user has to enter the new cgpa as well

6. For the display function (depending upon option chosen):
    -> user can display all students
    -> user can give a specific cgpa as input 
    -> user can give lower limit and upper limit as input 
    -> user can give a cutoff cgpa as input 
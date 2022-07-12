# oop-project
Working time 2 weeks
General requirements:
• No memory leak.
• Test Code Coerage >99% on all code except UI
• Compiler set to "treat Warning as Errors", Warning Level /W4
• Fixed most errors reported by linter: Enabled "code analysis on build" selected ""C++ Core Check rules". I encourage you that to each error/suggestion reported to read the relevant part of guidline 
Iteration Requirements 1:
• Modify the application: use the vector class in the STL and replace all the forts in the application with algorithms from STL and variant c++11 de for (range for). Example of algorithms: copy_if (when filtering), find_if (search), sort
• Use exceptions to report errors (create your own classes for exceptions).
• Add new functionality (described to each problem). 
Iteration Requirements 2:
 Add the save part to files for products/movies/books, etc.
 Add the possibility of undo to the operations: add, delete and modify. 
For implementation use inheritance and polymorphism: 
• Create an abstract ActionUndo class that has only one method: doUndo. 
• Create 3 derived classes UndoAdauga, UndoSterge, UndoModify that in the doUndo method implements the part that restores the situation before to add/delete/modify.
• In the controller you will keep a list ofUndo Actions that can be executed in any moment. A polymorphic appeal will be made to the doUndo method.
• Pay attention to memory management, avoid the phenomenon of slicing.
8 Block administrator
Enter the ability to create a notification list. The user can create interactive a list of apartments to be notified.
Add the following actions (menu items):
• Clear list: Delete all apartments from the list.
• Add to list: add an apartment after no. of apartment
• Generates the list: the user enters the total number of apartments, the list is randomly populate with apartments
• Export. Save the list to the file: CVS or HTML. Save to file only when this menu was selected, the basket is not persistent (when restarting the application
the basket is empty again) , the user enters the name of the file where they are 
saves on every export.
 After each user action, the total number of apartments in the list is displayed
 
 Create the UI using Qt for the app you're working on
 1 Pattern Observer
Create two different windows that show the contents of the basket (CosCRUDGUI, 
CosReadOnlyGUI).
CosCRUDGUI – contains a list or table (items in the cart) and buttons 
emptying/generating.
CosReadOnlyGUI – uses drawing to present the number of elements in Cart. Overwrite the method: void paintEvent(QPaintEvent* ev) override and 
use QPainter class to draw.
On this window to appear geometric figures or images on random positions. Many figures how many elements the basket has.
On the main window of the application:
-add functionality that can add / delete / generate content Basket
-add 2 buttons that open windows that show the cart (CosCRUDGUI, CosReadOnlyGUI). At each press a new window opens.
Each window shows the contents of the same basket. Any modification of the basket must be 
to be automatically visible in all open windows (use the Observer template).
2 Model-View
For List/Table to use Qt View/Model components (classes QListView/QTableView ). Create your own model, a class that expands QAbstractListModel or QAbstractTableModel

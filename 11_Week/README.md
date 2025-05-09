## Задача
Да се реализира йерархията <b>FileSystemEntity</b> с наследници <b>SingleFile</b> и <b>Directory</b>, както и техните методи: <br></br>
-> int getSize(), Връща размера на файла<br></br>
-> char* getName(), Връща абсолютния път на файла<br></br>
-> Directory* getParent(), Връща името на папката/директорията, в която се намира файла.<br></br>
-> FileSystemEntity* find(const char* path), връща nullptr, ако не го намери<br></br>
//const char* pathExample = “/home/file1.txt” <br></br>
<br></br>
Directory има конструктори Directory(Directory* parentDir, const char* name).<br></br>
Directory(const char* name) играе ролята на корен във файловата директория.<br></br>
<br></br>
Directory има метод: void addEntity(const FileSystemEntity* entity), <br></br>
Ако елемента, който добавяме е бил в директория/папка, трябва да се премахне от старата папка и да се сложи в новата(текущата от която извикваме метода)<br></br>
Directory има метод: void removeEntity(const FileSystemEntity* entity)<br></br>
<br></br>
SingleFile има конструктори SingleFile(Directory* parentDir, const char* name, int size) и SingleFile(const char* name, const char* size)<br></br>
<br></br>
ПРИМЕРИ:<br></br>
FileSystemEntity* file = new SingleFile(“someFile.cpp”, 50);<br></br>
Directory dir(“home”);<br></br>
dir.addEntity(file);<br></br>
50 == dir.getSize() //true<br></br>
file == dir.find(“/home/someFile.cpp”); //true<br></br>

FileSystemEntity* file2 = new SingleFile(dir, “secondFile”, 24);<br></br>
74 == dir.getSize() //true<br></br>
dir.addEntity(file2);<br></br>
74 == dir.getSize() //true<br></br>
<br></br>
Directory dir2(“dir2”);<br></br>
dir2.addEntity(file);<br></br>
24 == dir.getSize(); //true<br></br>
50 == dir2.getSize(); //true<br></br>
dir.remove(file2);<br></br>
nullptr == dir.find(“/dir/secondFile”); //true<br></br>

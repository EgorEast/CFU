<!DOCTYPE HTML>
 <html>
 <body>
 
 МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>
 
### Отчёт по лабораторной работе №5 <br/> по дисциплине "Программирование"
<br/>
 
студента 1 курса группы ИВТ-б-о-192(1)<br/>
Слободского Егора Вячеславовича<br/>
направления подготовки 09.03.01 "Информатика и вычислительная техника"  
<br/>
 
<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>
 
Симферополь, 2019
 
 <hr>
 
# Лабораторная работа №5 Работа с текстовыми файлами

Цель:

1. Научиться работать с текстовыми файлами;<br/>
2. Закрепить навыки работы со структурами.<br/>
 
## Ход работы:
1. Из [репозитория](<https://github.com/rebeccabilbro/titanic>) из папки data скачайте файл **train.csv**;
2. На основании файла **data_dictionary.txt** создайте структуру для чтения записей из файла **train.csv**;
3. Ознакомьтесь с форматом файлов CSV и считайте все записи в массив/вектор;
4. Рассчитайте и сохраните в новый файл следующие характеристики (если нужные данные не указаны, игнорируйте пассажира):
  * Общее число выживших;
  * Число выживших из 1 класса;
  * Число выживших из 2 класса;
  * Число выживших из 3 класса;
  * Количество выживших женщин;
  * Количество выживших мужчин;
  * Средний возраст пассажира/женский/мужской;
  * Штат, в котором село больше всего пассажиров;
  * Список идентификаторов несовершеннолетних (младше 18) пассажиров, через запятую;<br/><br/>

  **Код программы "*main.cpp*":**
 
  ```C++
  //Стандартная библиотека
  #include <iostream>
  //Строки
  #include <string>
  //Библиотека для работы с потоками ввода-вывода 
  //(для чтения и записи данных в файлы)
  #include <fstream>
  //Векторы
  #include <vector>
  //Подключаю библиотеку для добавления возможности вводить и выводить русский язык
  #include <WinSock2.h>
  
  using namespace std;
  
  //Переменная, для перемещения по элементам строки, хранящей текст из документа
  int ultima;
  
  //Класс пассажира
  class Passenger {
  public:
    //ID пассажира
    int passengerId;
    //Статус: 0 = выжил/ 1 =не выжил
    bool survived;
    //Тип класса пассажира (1 = 1st; 2 = 2nd; 3 = 3rd)
    int pClass;
    //Имя
    string name;
    //Пол
    string sex;
    //Возраст
    int age;
    //Число братьев, сестер или супругов на борту у человека
    int sibSp;
    //Количество родителей или детей на борту
    int parch;
    //Номер билета
    string ticket;
    //Пассажирский тариф
    int fare;
    //Салон самолета
    string cabin;
    //Порт посадки: (C = Cherbourg; Q = Queenstown; S = Southampton)
    char embarked;
  };
  
  //Функция, для чтения из строки необходимого параметра и его возвращения
  string read(
    //Передаю саму строку
    string string, 
    //И разделитель
    std::string del) {
    //Задаю начальное положение для считывания, исходя из предыдущего результата
    int start = ultima;
    //Присваиваю концу размер этого значения от начала значения до его разделителя
    int end = string.find(del, start);
    //Конечное положение, которое будет начальным для следующего 
    ultima = end + del.size();
    //Возвращаю в виде строки искомое слово
    return string.substr(start, end - start);
  }
  
  int main() {
    //Делаю так, чтобы читался русский язык как при вводе текста, так и при выводе
    //Установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleCP(1251);
    //Установка кодовой страницы win-cp 1251 в поток вывода
    SetConsoleOutputCP(1251);
    //Создаю вектор, который будет хранить данные обо всех пассажирах
    vector
      //Тип объектов это класс Passenger
      <Passenger> 
      passengers;
    //Создаю экземпляр класса, предназначенный для чтения данных из файла 
    ifstream fin;
    //Переменая, для хранения пути к файлу для чтения
    string pathInput = "0";
    //Открытие и проверка на наличие файла
    do {
      cout << "Введите название файла, из которого хотите извлечь данные (train.csv): ";
      cin >> pathInput;
  
      //Загружаю таблицу в объект
      fin.open("Sources/" + pathInput);
      //Если не открывается
      if (!fin.is_open()) {
        cout << "Файл не открылся! Повторите попытку." << endl;
        pathInput = "0";
      }
    } while (pathInput == "0");
  
    //Строка, которая будет хранить в себе все данные из документа
    string strInData;
  
    //Получаю символы, записываю в строку с названиями колонок, до знака переноса строки
    getline(fin, strInData, '\r');
  
    //Заполняю поля пассажиров
    while (getline(fin, strInData, '\r')) {
      //Переменная, для хранения прочитанного значения
      string readText;
      //Инициализирую переменную старта чтения нулевым значением
      ultima = 0;
      //Создаю объект отдельного пассажира
      Passenger passenger;
      //Сами поля
      //Присваимаю значение переменной
      readText = read(strInData, ",");
      //Перевожу из string в int и присваиваю полю класса
      passenger.passengerId = stoi(readText);
  
      readText = read(strInData, ",");
      passenger.survived = stoi(readText);
  
      readText = read(strInData, ",\"");
      passenger.pClass = stoi(readText);
  
      passenger.name = read(strInData, "\",");
      readText = read(strInData, ",");
      if (readText == "male") passenger.sex = "Male";
      else passenger.sex = "Female";
  
      //Читаю и
      readText = read(strInData, ",");
      //Если поле с возрастом не пустое
      if (readText != "") {
        //Тогда из формата string конвертируется в double
        passenger.age = stod(readText);
      }
      //Если все-таки пусто, тогда присваиваю значение -1
      else passenger.age = -1;
  
      //Присваимаю значение, переводя из string в int
      readText = read(strInData, ",");
      passenger.sibSp = stoi(readText);
  
      readText = read(strInData, ",");
      passenger.parch = stoi(readText);
  
      passenger.ticket = read(strInData, ",");
  
      readText = read(strInData, ",");
      passenger.fare = stod(readText);
  
      passenger.cabin = read(strInData, ",");
  
      //Считывается последний параметр и обозначаю конец первой строки данных
      passenger.embarked = read(strInData, " ")[0];
  
      //Добавляю этого пассажира в список
      passengers.push_back(passenger);
    }
    //Переменные, которые будут хранить количество совпадений по категориям
    int survivors = 0,
      survivors1 = 0,
      survivors2 = 0,
      survivors3 = 0,
      embarkedC = 0,
      embarkedQ = 0,
      embarkedS = 0,
      totalPerson = 0,
      totalMen = 0,
      totalWomen = 0,
      survivorsWomen = 0,
      survivorsMen = 0;
    //Переменные будут хранитть возраст, для вычисления среднего возраста
    int agePerson = 0, ageMen = 0, ageWomen = 0;
    //Вектор, хранящий список (вектор) детей на борту
    vector<int> childrenId;
  
    //Прохожу по всему списку пассажиров
    for (int i = 0; i < passengers.size(); i++) {
      //Реализация подсчетов кол-ва пассажиров по типу класса
      if (passengers[i].embarked == 'S') embarkedS++;
      else if (passengers[i].embarked == 'C') embarkedC++;
      else if (passengers[i].embarked == 'Q') embarkedQ;
  
      //Проверяю возраст и добавляю в список детей от 0 до 18 лет
      if ((passengers[i].age != -1) && (passengers[i].age < 18))
        childrenId.push_back(passengers[i].passengerId);
  
      //Реализация подсчетов кол-ва выживших пассажиров
      if (passengers[i].survived) {
        survivors++;
        //Подсчет кол-ва выживших пассажиров по классам
        if (passengers[i].pClass == 1) survivors1++;
        else if (passengers[i].pClass == 2) survivors2++;
        else if (passengers[i].pClass == 3) survivors3++;
        
        if (passengers[i].age != -1) {
          //Теперь суммирую возраст и сохранияю количество пасажиров
          agePerson += passengers[i].age;
          //Подсчитываю количество пассажиров
          totalPerson++;
  
          //Подсчет кол-ва выживших пассажиров по полу
          if (passengers[i].sex == "Female") survivorsWomen++;
          else survivorsMen++;
  
          //Суммирую возраста и сохранияю количество женщин
          if (passengers[i].sex == "Female") {
            ageWomen += passengers[i].age;
            totalWomen++;
          }
          //Суммирую возраста и сохранияю количество мужчин 
          else {
            ageMen += passengers[i].age;
            totalMen++;
          }  
        }
      }
    }
  
    //Создаю экземпляр класса, предназначенный для записи данных в файл
    ofstream fout;
    //Переменая, для хранения пути к файлу для записи
    string pathOutput = "0";
    //Открываю файл и проверяю на возможность этого
    do {
      cout << "Введите название файла, в который хотите записать данные, без расширения (по умолчанию - '.txt'): ";
      cin >> pathOutput;
      //Добавляю в объект файл, куда буду записывать или создаю новый
      fout.open("Results/" + pathOutput + ".txt");
      /*//Если хочу добавить к существующей информации новую (в конец файла)
      fout.open("Results/" + pathOutput + ".txt", ofstream::app);*/
      //Если не получается открыть
      if (!fout.is_open()) {
        //Вывожу ошибку
        cout << "Ошибка открытия файла для записи" << endl;
        //Повторяю попытку
        pathOutput = "0";
      }
    } while (pathOutput == "0");
  
    //Вывод в файл полученных результатов
    fout << "Общее число выживших: " << survivors << endl;
    fout << "Число выживших из 1 класса: " << survivors1 << endl;
    fout << "Число выживших из 2 класса: " << survivors2 << endl;
    fout << "Число выживших из 3 класса: " << survivors3 << endl;
    fout << "Количество выживших женщин: " << survivorsWomen << endl;
    fout << "Количество выживших мужчин: " << survivorsMen << endl;
  
    //Вывод в файл среднего возраста
    if (totalPerson > 0) fout << "Средний возраст пассажира: " << agePerson / totalPerson << endl; 
    if (totalMen > 0) fout << "Средний возраст мужчин: " << ageMen / totalMen << endl;
    if (totalWomen > 0) fout << "Средний возраст женщин: " << ageWomen / totalWomen << endl;
    //Вывод о штате, в котором село больше всего пассажиров
    fout << "Штат(-ы), в котором село больше всего пассажиров: ";
  
    //Переменые для сравнения
    bool CMore = false, QMore = false, SMore = false;
  
    //Сравниваю показатели счетчиков и переменных для сравнения
    if (embarkedC > embarkedQ) { CMore = true; QMore = false; }
    else if (embarkedC < embarkedQ) { CMore = false; QMore = true; }
    else if (embarkedC == embarkedQ) { CMore = true; QMore = true; }
    
    if (CMore != QMore) {
      if (CMore) {
        if (embarkedC > embarkedS) { CMore = true; SMore = false; }
        else if (embarkedC < embarkedS) { CMore = false; SMore = true; }
        else if (embarkedC == embarkedS) { CMore = true; SMore = true; }
      }
  
      if (QMore) {
        if (embarkedQ > embarkedS) { QMore = true; SMore = false; }
        else if (embarkedQ < embarkedS) { QMore = false; SMore = true; }
        else if (embarkedQ == embarkedS) { QMore = true; SMore = true; }
      }
    }
    else {
      if (embarkedC > embarkedS) { CMore = true; SMore = false; }
      else if (embarkedC < embarkedS) { CMore = false; SMore = true; }
      else if (embarkedC == embarkedS) { CMore = true; SMore = true; }
  
      if (embarkedQ > embarkedS) { QMore = true; SMore = false; }
      else if (embarkedQ < embarkedS) { QMore = false; SMore = true; }
      else if (embarkedQ == embarkedS) { QMore = true; SMore = true; }
    }
  
    //Исходя из проверки вывожу результаты на экран
    if (CMore) {
      fout << "Cherbourg";
      if (QMore || SMore) fout << ", ";
      else fout << endl;
    }
    if (QMore) {
      fout << "Queenstown";
      if (SMore) fout << ", ";
      else fout << endl;
    }
    if (SMore) fout << "Southampton" << endl;
  
    //В конце вывожу идентификаторы детей
    fout << "Список идентификаторов несовершеннолетних пассажиров: ";
    for (int it = 0; it < childrenId.size(); it++) {
      if (it != (childrenId.size() - 1)) fout << childrenId[it] << ", ";
      else fout << childrenId[it] << '.' << endl;
    }
  
    cout << "Результаты подсчетов:" << endl;
    //Закрываю предыдущий файл для того, чтобы открыть файл с результатами
    fin.close();
    //Открываю этот файл с результатами
    fin.open("Results/" + pathOutput + ".txt");
    //Будет хранить текст для вывода в консоль
    string message;
    //Проверяю. Если не конец файла
    while (getline(fin, message, '\r')) {
      //Записываю линию в переменную message
      getline(fin, message, '\r');
      //Вывожу её в консоль
      cout << message << endl;
    }
  
    //Закрываю файлы, освобождаю ресурсы объектов fout и fin
    //Пока открыт этот файл нельзя будет обратиться из другого места к нему
    fout.close();
    fin.close();
  }
  ```
  
  **Ссылка на файл с результатами:**<br/>
  [results.txt](https://github.com/EgorEast/CFU/blob/master/Lab/5lab/5LabProj/Results/results.txt)
  
  **Результаты подсчетов**
  | Характеристика  | Результат |
| ------------- | ------------- |
| Общее число выживших | 342  |
| Число выживших из 1 класса  | 136  |
| Число выживших из 2 класса  | 87  |
| Число выживших из 3 класса  | 119  |
| Количество выживших женщин  | 233  |
| Количество выживших мужчин  | 109  |
| Средний возраст пассажира  | 28.3241  |
| Средний возраст мужчин  | 27.2366  |
|Средний возраст женщин  | 28.8376  |
|Штат, в котором село больше всего пассажиров | Southampton  |      
|Список идентификаторов несовершеннолетних пассажиров  | 8, 10, 11, 15, 17, 23, 25, 40, 44, 51, 59, 60, 64, 69, 72, 79, 85, 87, 112, 115, 120, 126, 139, 148, 157, 164, 165, 166, 172, 173, 183, 184, 185, 194, 206, 209, 221, 234, 238, 262, 267, 279, 283, 298, 306, 308, 330, 334, 341, 349, 353, 375, 382, 387, 390, 408, 420, 434, 436, 446, 447, 449, 470, 480, 481, 490, 501, 505, 531, 533, 536, 542, 543, 550, 551, 575, 619, 635, 643, 645, 684, 687, 690, 692, 721, 722, 732, 747, 751, 752, 756, 765, 778, 781, 782, 788, 789, 792, 803, 804, 814, 820, 825, 828, 831, 832, 842, 845, 851, 853, 854, 870, 876.|<br/>


   **Вывод:** в ходе данной лабораторной работы я изучил способ чтения и записи текстовых данных в файл. Научился работать с классами fstream, ofstream и ifstream.
  
 </body>
 </html>
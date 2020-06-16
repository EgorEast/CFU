<!DOCTYPE HTML>
 <html>
 <body>
 
 МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>
 
### Отчёт по лабораторной работе № <br/> по дисциплине "Программирование"
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
 
# Лабораторная работа №4 Иксики-нолики

Цель:<br/>

1. Закрепить навыки работы с перечислениями;<br/>
2. Закрепить навыки работы с структурами;<br/>
3. Освоить методы составления многофайловых программ.<br/>

## Постановка задачи<br/>
**Создайте три файла:**<br/>

1. Файл реализующий игру «Иксики-нолики» используя функции описанные в вспомогательном файле;<br/>
2. Вспомогательный файл. Содержит реализацию основных функций игры;<br/>
3. Заголовочный файл. Нужен для связи главного и вспомогательного файлов. Не забудьте добавить защиту от повторного включения файла.<br/>

  **Код основного файла *"main.cpp"*:**
 
  ```C++
  #include <iostream>
  #include <ctime>
  #include "Game.h"
  
  using namespace std;
  
  Game initGame(char userChar) {
    Game game;
    //Очищает игровое поле заполняя его пробелами
    for (char i = 0; i < 3; i++)
      for (char j = 0; j < 3; j++)
        game.bord[i][j] = ' ';
    //Случайным образом определяет чей ход
    srand(time(0));
    if (rand() % 2 + 1 == 1) game.isUserTurn = true;
    else game.isUserTurn = false;
    //Устанавливает символ для Игрока (Задаётся параметром userChar)
    game.userChar = userChar;
    //Устанавливает символ для бота
    if (game.userChar == 'x') game.botChar = '0';
    else game.botChar = 'x';
    //Статус игры, что она начата
    game.status = PLAY;
    //Возвращает заполненную структуру
    return game;
  }
  
  void updateDisplay(const Game game) {
    //Очищаю экран с помощью системной функции
    system("cls");
    //Отображает содержимое игрового поля
    cout << "\ta \tb \tc" ;
    for (int i = 0; i <= 2; i++) {
      cout << endl << i+1 << "\t";
      for (int j = 0; j <= 2; j++) {
        cout << game.bord[i][j] << "\t";
      }
      cout << endl;
    }
    cout << endl;
  }
  
  void botTurn(Game* game) {
    //Переменные для определения позиции пустых символов в линии
    short empCharPos = 0,
      //Количества символов, поставленными игроком в линии
      plSuppChar = 0,
      //Количества пустых ячеек в линии
      blankСhar = 0;
    //Прохожу по всему полю
    for (short i = 0; i < 3; i++)
      for (short j = 0; j < 3; j++)
        //Если встречаю любой символ кроме пробела
        if (game->bord[i][j] != ' ')
          //Тогда подсчитываю количество этих символов
          empCharPos++;
    //Если сумма символов = 0, тоесть поле пустое, тогда бот ходит в случайное место и заканчивает ход
    if (empCharPos == 0) {
      game->bord[1][1] = game->botChar;
      return;
    }
    //Обнуляю счетчик символов
    empCharPos = 0;
    //Теперь снова прохожу по карте, но теперь по диагонали
    for (short i = 0; i < 3; i++) {
      //Если на какой-либо из клеток этой диагонали окажется символ игрока
      if (game->bord[i][i] == game->userChar)
        //Тогда подсчитываю количество символов игрока в этой диагонали
        plSuppChar++;
      //И смотрю пустую клетку в этой диагонали. Если же есть пустая клетка
      if (game->bord[i][i] == ' ') {
        //Тогда запоминаю, что в этой линии есть пустая клетка
        blankСhar++;
        //Записываю положение этой клетки
        empCharPos = i;
      }
    }
    //Если в этой диагонали присутствуют два символа игрока и одна пустая клетка
    if ((plSuppChar == 2) && (blankСhar == 1)) {
      //Тогда ставлю в эту пустую клетку символ бота
      game->bord[empCharPos][empCharPos] = game->botChar;
      return;
    }
  
    //Для новой проверки обнуляю счетчики
    plSuppChar = 0;
    blankСhar = 0;
  
    //Прохожусь по другой диагонали. Та-же логика
    for (short i = 0; i < 3; i++) {
      if (game->bord[i][2 - i] == game->userChar)
        plSuppChar++;
  
      if (game->bord[i][2 - i] == ' ') {
        blankСhar++;
        empCharPos = i;
      }
    }
    if ((plSuppChar == 2) && (blankСhar == 1)) {
      game->bord[empCharPos][2 - empCharPos] = game->botChar;
      return;
    }
  
    //Проверяю все столбики, начиная с первого
    for (short i = 0; i < 3; i++) {
      //На каждом столбце обнуляю счетчики
      plSuppChar = 0;
      blankСhar = 0;
      //Прохожу по столбцу
      for (short j = 0; j < 3; j++) {
        //Задаю позиции пустой ячейки порядковый номер этой ячейки, чтобы восстановить потом
        empCharPos = j;
        //Если попадаю на символ игрока
        if (game->bord[i][j] == game->userChar) {
          //То добавляю в счетчик
          plSuppChar++;
          //И если количество символов игрока в линии равно 2
          if (plSuppChar == 2) {
            //Тогда в счетчик j передаю это количество, что есть весь столбец
            j = plSuppChar;
  
            //И теперь, пока он не пройдет по этому столбцу
            while (j >= 0) {
              //Ищет пустую клетку
              if (game->bord[i][j] == ' ') {
                //Если нашел - тогда заполняет
                game->bord[i][j] = game->botChar;
                return;
              }
              //Если же не нашел, то идет к следующему элементу
              j--;
            }
          }
          //Возвращаю значение 
          j = empCharPos;
        }
        //Теперь прохожу по рядам
        if (game->bord[j][i] == game->userChar) {
          blankСhar++;
          if (blankСhar == 2) {
            j = blankСhar;
  
            while (j >= 0) {
              if (game->bord[j][i] == ' ') {
                game->bord[j][i] = game->botChar;
                return;
              }
  
              j--;
            }
          }
          j = empCharPos;
        }
      }
    }
  
    //Теперь выбираю случайную позицию
    do {
      //Ограничиваю тремя значениями
      plSuppChar = rand() % 3;
      blankСhar = rand() % 3;
      //И ставлю в пустую клетку
      if (game->bord[plSuppChar][blankСhar] == ' ') {
        game->bord[plSuppChar][blankСhar] = game->botChar;
        return;
      }
  
    } while (true);
  }
  
  void userTurn(Game* game) {
    //Переменная для символов
    char symbol;
    //Переменная для цифр
    short numeral;
    //Переменная для проверки корректности ввода
    bool correctly = false;
  
    std::cout << "Твой ход. Введи координаты через пробел (буква, цифра): ";
    while (!correctly) {
      std::cin >> symbol >> numeral;
      //Проверка по букве
      switch (symbol) {
      case 'a': symbol = 0;
        break;
      case 'b': symbol = 1;
        break;
      case 'c': symbol = 2;
        break;
      default:
        std::cout << "Неправильно введена буква!" << endl;
        break;
      }
      //Проверка по цифре
      switch (numeral) {
        //Уменьшаю их на единицу, так как массив начинает нумерацию с нуля
      case 1: numeral--;
        break;
      case 2: numeral--;
        break;
      case 3: numeral--;
        break;
      default:
        std::cout << "Неправильно введена цифра!" << endl;
        break;
      }
      //Если попадаю в пустое место поля, тогда выхожу из цикла
      if (game->bord[numeral][symbol] == ' ') correctly = true;
      //Если неверно, то повторяю чнова ввод
      else cout << "Нельзя сюда поставить!" << endl;
  
    }
    //Ставлю символ
    game->bord[numeral][symbol] = game->userChar;
  }
  
  bool updateGame(Game* game) {
    //Проверяю циклом победу игрока или бота по строкам и столбцам
    for (short i = 0; i < 3; i++)
    {
      //Проверяю строчки
      if (game->bord[0][i] == 'x' || game->bord[0][i] == '0')
      {
        //Если весь столбец заполнен одинаковыми символами
        if ((game->bord[1][i] == game->bord[0][i]) && (game->bord[2][i] == game->bord[0][i]))
        {
          //Если эти символы принадлежат игроку
          if (game->bord[0][i] == game->userChar)
            //Победил игрок
            game->status = USER_WIN;
          else
            //Иначе: победил бот
            game->status = BOT_WIN;
          //Заканчиваю игру
          return false;
        }
      }
  
      
      //Прохожу по столбцам
      if (game->bord[i][0] == 'x' || game->bord[i][0] == '0')
      {
        //Та-же логика
        if ((game->bord[i][1] == game->bord[i][0]) && (game->bord[i][2] == game->bord[i][0]))
        {
          if (game->bord[i][0] == game->userChar)
            game->status = USER_WIN;
          else
            game->status = BOT_WIN;
          return false;
        }
      }
    }
  
    //Прохожу по одной диагонали
    if (game->bord[2][0] == 'x' || game->bord[2][0] == '0')
    {
      if ((game->bord[1][1] == game->bord[0][2]) && (game->bord[1][1] == game->bord[2][0]))
      {
        if (game->bord[1][1] == game->userChar)
          game->status = USER_WIN;
        else
          game->status = BOT_WIN;
        return false;
      }
    }
  
    //Прохожу по другой
    if (game->bord[0][0] == 'x' || game->bord[0][0] == '0')
    {
      if ((game->bord[1][1] == game->bord[0][0]) && (game->bord[2][2] == game->bord[0][0]))
      {
        if (game->bord[2][2] == game->userChar)
          game->status = USER_WIN;
        else
          game->status = BOT_WIN;
        return false;
      }
    }
  
    //Проверяю на ничью
    bool deadHeat = false;
    for (short i = 0; i < 3; i++)
      for (short j = 0; j < 3; j++)
        //Если есть хоть одна пустая клетка, тогда нет ничьей
        if (game->bord[i][j] == ' ') deadHeat = false;
    //Если же есть ничья
    if (deadHeat){
      //Тогда тичья
      game->status = NOT_WIN;
      //Заканчиваю игру
      return false;
    }
  
    //Передаю ход боту
    game->isUserTurn = !game->isUserTurn;
    //Продолжаю игру
    return true;
  }
   
  ```
 
   **Код вспомогательного файла *"Game.cpp"*:**
 
  ```C++
  #include <iostream>
  #include "Game.h"
  
  using namespace std;
  int main() {
    
    setlocale(LC_ALL, "Russian");
    char play = 'Y';
    while (play == 'Y') {
      char character = ' ';
  
      while (character != 'x' && character != '0') {
        cout << "Выбери кем будешь играть (x или 0): ";
        cin >> character;
      }
  
      //Создаю экземпляр структуры и передаю в него выбранный персонаж
      Game game = initGame(character);
  
      //Запускаю игру. Работает, пока обновление игры истинно
      while (!updateGame(&game))
      {
        //Обновляю дисплей
        updateDisplay(game);
        //Если переходит ход к игроку, то игрок ходит
        if (game.isUserTurn) userTurn(&game);
        //Иначе ходит бот
        else botTurn(&game);
        //И снова обновляю дисплей
        updateDisplay(game);
      }
  
      //Условия победы
      if (game.status == USER_WIN) cout << "Ты победил :D" << endl;
      if (game.status == BOT_WIN) cout << "Бот победил :(" << endl;
      if (game.status == NOT_WIN) cout << "Ничья :|" << endl;
  
      //И цикл для завершения или продолжения игры
      while (play != 'N') {
        cout << "Хочешь повторить? (Y/N):";
        cin >> play;
        if (play != 'Y' && play != 'N'){ 
          cout << "Неверно введен символ" << endl; 
          continue;
        }
        if (play == 'Y' || play == 'N') break;
      }
    }
    return 0;
  }
  ```
  
   **Код заголовочного файла *"Game.h"*:**
  
  ```C++
  #pragma once
  /* Состояния игры */
  enum Status {
  PLAY,            // Игра продолжается
  USER_WIN,        // Игрок победил
  BOT_WIN,         // Бот победил
  NOT_WIN          // Ничья. Победителя нет, но и на поле нет свободной ячейки
  };
  struct Game {
  char bord[3][3];  // Игровое поле
  bool isUserTurn;  // Чей ход. Если пользователя, то isUserTurn = true
  char userChar;    // Символ которым играет пользователь
  char botChar;     // Символ которым играет бот
  Status status;
  };
  
  /**
  * Выполняет следующие действия:
  *  1. Очищает игровое поле заполняя его пробелами
  *  2. Случайным образом определяет чей ход
  *  3. Устанавливает символ для Игрока (Задаётся параметром userChar)
  *  4. Устанавливает символ для бота
  *  5. Возвращает заполненную структуру
  */
  Game initGame(char userChar);
  //*
  //* Выполняет следующие действия:
  //*  1. Очищает экран
  //*  2. Отображает содержимое игрового поля. Например так (можно по своему):
  //*         a   b   c
  //*       -------------
  //*     1 | O | O | X |
  //*       -------------
  //*     2 |   |   |   |
  //*       -------------
  //*     3 |   |   | X |
  //*       -------------
  
  void updateDisplay(const Game game);
  /**
  * Выполняет ход бота. В выбранную ячейку устанавливается символ которым играет бот.
  * Бот должен определять строку, столбец или диагональ в которой у игрока больше всего иксиков/ноликов и ставить туда свой символ. Если на поле ещё нет меток, бот должен ставить свой знак в центр. В остальных случаях бот ходит рандомно.
  */
  void botTurn(Game* game);
  /**
  * Функция отвечает за ход игрока. Если игрок вводит не допустимые
  * значения, ругнуться и попросить ввести заново
  */
  void userTurn(Game* game);
  /**
  * Функция определяет как изменилось состояние игры после последнего хода.
  * Функция сохраняет новое состояние игры в структуре game и передаёт ход другому
  * игроку.
  * Функция возвращает true, если есть победитель или ничья, иначе false.
  */
  bool updateGame(Game* game);
  ```

   **Вывод:** в ходе данной лабораторной работы я закрепил навыки работы с перечислениями, навыки работы со структурами, а также освоил методы составления многофайловых программ путем добавления заголовочных и вспомогательных файлов. 
  
 </body>
 </html>
#include <iostream> //для работы с потоками ввода и вывода
#include <fstream> //для работы с методами чтения, записи и удаления в файлах
#include <string> //для метод строк
#include <Windows.h>//для определенной функции system
#include <conio.h>
#include <vector>
#include <sstream> 

using namespace std;

//прототипы функций
void DataInitialization();//инициализация данных
void DataEntry();//ввод данных вручную
void DataReading(string fileName);//чтение данных
void Print();//вывод данных
bool DataCleaning();//очистка данных
void DataChange();//изменение данных
void Copy();//копирование данных
int AmountOfData();//количество данных
void DeleteData();//удаление данных
void AddData();//добавление данных
void SaveBufferToFile(const string& targetFileName);//cохранение расписания в файл
bool isValidDate(const std::string& dateStr);//проверка на дурака даты
bool isValidTime(const std::string& timeStr);//проверка на дурака времени

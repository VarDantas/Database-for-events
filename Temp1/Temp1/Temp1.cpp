#include "Fun.h"
int _stateMenu;
void Menu() {
	cout << "Выберите действие:" << endl
		<< "(0) Выход из программы." << endl
		<< "(1) Ввод данных." << endl
		<< "(2) Вывод данных." << endl
		<< "(3) Изменение данных." << endl
		<< "(4) Удаление данных." << endl
		<< "(5) Добавление данных." << endl
		<< "(6) Сохранение расписания в файл." << endl
		<< "Ваш выбор: ";
	cin >> _stateMenu;
}
/*
		Данные:
		*Название события
		*Место
		*Дата
		*Время
		*Участники
		
		Дата и время добавления:
		*добавления
		*изменения
		*удаления
*/
void main() {
	//руссификация консоли ввода/вывода
	SetConsoleCP(1251);//установка кодовой таблицы win-cp 1252 в поток ввода
	SetConsoleOutputCP(1251);//установка кодовой таблицы win-cp в поток вывода
	
	DataInitialization();

	Menu();
	int _actions;
	string fileName;

	while (_stateMenu != 0) {
		switch (_stateMenu) {
		case 1:
			system("cls");//очистка консоли

			cout << "Ввод вручную или из файла?: " << endl
				<< "(1) вручную" << endl
				<< "(2) из файла" << endl;
			cin >> _actions;

			system("cls");//очистка консоли

			if (_actions == 1) {
				//ввод вручную
				DataEntry();
			}
			if(_actions == 2) {
				//чтение из файла
				cout << "Введите название файла: ";
				cin >> fileName;

				DataReading(fileName);
			}
			else {
				cout << "Некорректный выбор действия!";
			}

			system("pause");//задержка консоли
			system("cls");//очистка консоли
			Menu();
			break;
		//////////////////////////////////////////////
		case 2:
			system("cls");//очистка консоли

			Print();

			system("pause");//задержка консоли
			system("cls");//очистка консоли
			Menu();
			break;
		//////////////////////////////////////////////
		case 3:
			system("cls");//очистка консоли

			DataChange();

			system("pause");//задержка консоли
			system("cls");//очистка консоли
			Menu();
			break;
		/////////////////////////////////////////////
		case 4:
			system("cls");//очистка консоли

			DeleteData();

			system("pause");//задержка консоли
			system("cls");//очистка консоли
			Menu();
			break;
		////////////////////////////////////////////
		case 5:
			system("cls");//очистка консоли

			AddData();

			system("pause");//задержка консоли
			system("cls");//очистка консоли
			Menu();
			break;
		///////////////////////////////////////////
		case 6:
			system("cls");//очистка консоли

			string targetFileName;

			cout << "Введите имя файла для сохранения данных: ";
			cin >> targetFileName;

			SaveBufferToFile(targetFileName);

			system("pause");//задержка консоли
			system("cls");//очистка консоли
			Menu();
			break;
		///////////////////////////////////////////
		/*default:
			cout << "Неправильно выбран пункт меню!" << endl;
			break;*/
		}
	}
	system("cls"); //очистка консоли
	if (DataCleaning())
		cout << "Данные очищены!" << endl;
	else
		cout << "Данные не очищены!" << endl;

	cout << "Разработка завершена." << endl;
	system("pause");
}
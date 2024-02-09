#include "Fun.h"

void DataInitialization() {
	//создадим временный файл, в котором будет храниться актуальная информация. т.е. создадим буфет
	ofstream _buf("Buffer.txt");

	if (!_buf)
		cout << "Ошибка создания буферного файла!" << endl;
	
	_buf.close();
}

void DataEntry() {
	//ввод данных вручную

	//временные переменные
	string nameEvent;
	string place;
	string data;
	string time;
	string participants;
	int n;

	//Временная переменная для даты и времени
	SYSTEMTIME st;
	GetLocalTime(&st);
	
	cout << "Введите количество данных: ";
	cin >> n;

	//открываем буфетный файл и записываем в него данные
	ofstream record("Buffer.txt", ios::app);//"ios::app" это помогает записать данные в конец файла

	if (record) {//если файл открылся
		record << n << endl;//записываем количество элементов о которых мы хотим записать данные

		for (int i = 0; i < n; i++) {
			cout << "Введите название события: ";
			cin >> nameEvent;

			cout << "Введите место: ";
			cin >> place;

			cout << "Введите дату: ";
			cin >> data;

			isValidDate(data);

			cout << "Введите время: ";
			cin >> time;

			isValidTime(time);

			cout << "Введите участников события: ";
			cin >> participants;

			record << nameEvent << endl;
			record << place << endl;
			record << data << endl;
			record << time << endl;
			record << participants << endl;
			record << st.wDay << "/" << st.wMonth << "/" << st.wYear << endl;
			if (i < n - 1)
				record << st.wHour << ":" << st.wMinute << endl;
			else
				record << st.wHour << ":" << st.wMinute;

			cout << "_______________________________________________" << endl;
		}
	}
	else
		cout << "Ошибка открытия файла!" << endl;
	record.close();
}

void DataReading(string fileName) {
	//чтение данных из файла

	ifstream reading(fileName);//открывает файл с именем "fileName" для чтения (при помощи объекта "ifstream")
	ofstream record("Buffer.txt", ios::out);//ios::out указывает на режим открытия файла - только для записи

	if (reading) {
		if (record) {
			//временные переменные
			string nameEvent;
			string place;
			string data;
			string time;
			string participants;
			int n;

			//Временная переменная для даты и времени
			SYSTEMTIME st;
			GetLocalTime(&st);

			//считываем данные из файла

			reading >> n;//Считывает количество записей из файла и сохраняет его в переменную n
			record << n << endl;//Записывает количество записей в файл

			for (int i = 0; i < n; i++) {
				reading >> nameEvent;
				reading >> place;
				reading >> data;
				isValidDate(data);
				reading >> time;
				isValidTime(time);
				reading >> participants;

				record << nameEvent << endl;
				record << place << endl;
				record << data << endl;
				record << time << endl;
				record << participants << endl;
				record << st.wDay << "/" << st.wMonth << "/" << st.wYear << endl;
				if (i < n - 1)
					record << st.wHour << ":" << st.wMinute << endl;
				else
					record << st.wHour << ":" << st.wMinute;
			}
			cout << "Данные считаны!" << endl;
		}
		else
			cout << "Ошибка открытия буфета!" << endl;
	}
	else
		cout << "Ошибка открытия файла!" << endl;

	//закрытие файла
	reading.close();
	record.close();
}

//void drawTable(int rows, int columns) {
//	// Верхняя граница таблицы
//	std::cout << '+';
//	for (int i = 0; i < columns * 20 - 1; ++i) {
//		std::cout << '-';
//	}
//	std::cout << '+' << std::endl;
//
//	// Вывод тела таблицы
//	for (int i = 0; i < rows; ++i) {
//		std::cout << '|';
//		for (int j = 0; j < columns; ++j) {
//			std::cout << "                   |";
//		}
//		std::cout << std::endl;
//
//		// Горизонтальные разделители между строками
//		if (i < rows - 1) {
//			std::cout << '+';
//			for (int j = 0; j < columns; ++j) {
//				std::cout << "-------------------+";
//			}
//			std::cout << std::endl;
//		}
//	}
//
//	// Нижняя граница таблицы
//	std::cout << '+';
//	for (int i = 0; i < columns * 20 - 1; ++i) {
//		std::cout << '-';
//	}
//	std::cout << '+' << std::endl;
//}

void Print() {
	std::ifstream reading("Buffer.txt");

	if (reading) {
		// Временные переменные
		std::string nameEvent;
		std::string place;
		std::string data;
		std::string time;
		std::string participants;
		int n;
		bool exit = false;

		// Временная переменная для даты и времени
		std::string dataDobav;
		std::string timeDobav;

		reading >> n; // Считывает количество записей из файла и сохраняет его в переменную n
		std::cout << "Количество данных: " << n << std::endl << std::endl;

		//drawTable(n, 1); // Отображаем таблицу с нужным количеством строк

		int currentRow = 0; // Текущая выбранная строка

		while (!exit) {
			// Перемещение на нужную строку
			std::cout << "\r";
			for (int i = 0; i < n; ++i) {
				if (i == currentRow) {
					std::cout << "| >>>>>>>>>>>>>>>>>>>>|";
				}
				else {
					std::cout << "|событие №" << i+1 <<"           |";
				}
			}

			std::cout.flush();

			int key = _getch(); // Считываем код клавиши

			// Перемещение по таблице с помощью клавиш стрелок
			switch (key) {
			case 27: // ESC
				exit = true;
				break;
			case 224: // Код для стрелок
				key = _getch();
				switch (key) {
				case 72: // Стрелка вверх
					if (currentRow > 0) {
						--currentRow;
					}
					break;

				case 80: // Стрелка вниз
					if (currentRow < n - 1) {
						++currentRow;
					}
					break;
				}
				break;

			case 13: // Клавиша Enter для выбора события
				// Очистка таблицы и вывод информации о событии
				std::cout << "\r";
				for (int i = 0; i < n; ++i) {
					std::cout << "|                     |";
				}
				std::cout << std::endl;

				std::cout << "Событие № " << currentRow + 1 << std::endl;

				reading >> nameEvent;
				std::cout << "Название мероприятия: " << nameEvent << std::endl;

				reading >> place;
				std::cout << "Место: " << place << std::endl;

				reading >> data;
				std::cout << "Дата: " << data << std::endl;

				reading >> time;
				std::cout << "Время: " << time << std::endl;

				reading >> participants;
				std::cout << "Участники: " << participants << std::endl;

				reading >> dataDobav;
				std::cout << "Дата добавления/изменения: " << dataDobav << endl;

				reading >> timeDobav;
				std::cout << "Время добавления/изменения: " << timeDobav << endl;

				std::cout << "----------------------------------" << endl;
			}
		}
	}
}

void DataChange() {
	//изменение данных

	//сохраним ещё раз данные
	//очистим буфет и снова начнём записывать данные в него
	//дойдем до необходимого и изменим его данные

	Copy();

	ifstream reading("Buffer_.txt");
	ofstream record("Buffer.txt", ios::out);//очистка файла

	if (reading) {
		if (record) {
			//временные переменные
			string nameEvent;
			string place;
			string data;
			string time;
			string participants;
			int n, _n;

			//Временная переменная для даты и времени
			string dataChange;
			string timeChange;
			SYSTEMTIME st;
			GetLocalTime(&st);

			//считываем из буфетного файла новый
			reading >> n;

			cout << "Выберите номер изменяемого элемента (от 1 до " << n << "): ";
			cin >> _n;
			_n--;

			system("cls");

			record << n << endl;

			if (_n >= 0 && _n < n) {
				for (int i = 0; i < n; i++) {
					if (i != _n) {
						reading >> nameEvent;
						record << nameEvent << endl;

						reading >> place;
						record << place << endl;

						reading >> data;
						record << data << endl;

						reading >> time;
						record << time << endl;

						reading >> participants;
						record << participants << endl;

						reading >> dataChange;
						record << dataChange << endl;

						reading >> timeChange;
						if (i < n - 1)
							record << timeChange << endl;
						else
							record << timeChange;
					}
					else {
						cout << "Введите название события: ";
						cin >> nameEvent;

						cout << "Введите место: ";
						cin >> place;

						cout << "Введите дату: ";
						cin >> data;
						isValidDate(data);

						cout << "Введите время: ";
						cin >> time;
						isValidTime(time);

						cout << "Введите участников: ";
						cin >> participants;

						record << nameEvent << endl;
						record << place << endl;
						record << data << endl;
						record << time << endl;
						record << participants << endl;
						record << st.wDay << "/" << st.wMonth << "/" << st.wYear << endl;
						if (i < n - 1)
							record << st.wHour << ":" << st.wMinute << endl;
						else
							record << st.wHour << ":" << st.wMinute;

						reading >> nameEvent;
						reading >> place;
						reading >> data;
						reading >> time;
						reading >> participants;
						reading >> dataChange;
						reading >> timeChange;
					}
				}
				cout << "Данные изменены!" << endl;
			}
			else
				cout << "Номер введен не верно!" << endl;
		}
		else
			cout << "Ошибка открытия файла!" << endl;
	}
	else
		cout << "Ошибка открытия буферного файла!" << endl;

	record.close();
	reading.close();

	remove("Buffer_.txt");
}

void Copy() {
	//копирование в новый файл
	ifstream reading("Buffer.txt");
	ofstream record("Buffer_.txt", ios::out);

	if (reading) {
		if (record) {
			//временные переменные
			string nameEvent;
			string place;
			string data;
			string time;
			string participants;
			int n;

			//Временная переменная для даты и времени
			string dataChange;
			string timeChange;

			//считываем из буфетного файла в новый
			reading >> n;
			record << n << endl;

			for (int i = 0; i < n; i++) {
				reading >> nameEvent;
				record << nameEvent << endl;

				reading >> place;
				record << place << endl;

				reading >> data;
				record << data << endl;

				reading >> time;
				record << time << endl;

				reading >> participants;
				record << participants << endl;

				reading >> dataChange;
				record << dataChange << endl;

				reading >> timeChange;
				if (i < n - 1)
					record << timeChange << endl;
				else
					record << timeChange;
			}
		}
		else
			cout << "Ошибка открытия файла!" << endl;
	}
	else
		cout << "Ошибка открытия буферного файла!" << endl;

	record.close();
	reading.close();
}

void DeleteData() {
	//удаление данных

	//запоминаем данные
	//перезаписываем в исходный буфер
	//кроме удаляемого

	Copy();

	ifstream reading("Buffer_.txt");
	ofstream record("Buffer.txt", ios::out);//удаляем содержимое файла с помощью ios::out

	if (reading) {
		if (record) {
			//временные переменные
			string nameEvent;
			string place;
			string data;
			string time;
			string participants;
			int n, _n;

			//Временная переменная для даты и времени
			string dataChange;
			string timeChange;
			SYSTEMTIME st;
			GetLocalTime(&st);

			//считываем из буферного файла в новый
			reading >> n;
			int b = n - 1;

			cout << "Выберите номер удаляемого элемента(от 1 до " << n << "): ";
			cin >> _n;
			_n--;

			system("cls");

			record << b << endl;
			if (_n >= 0 && _n < n) {
				for (int i = 0; i < n; i++) {
					if (i != _n) {
						reading >> nameEvent;
						record << nameEvent << endl;

						reading >> place;
						record << place << endl;

						reading >> data;
						record << data << endl;

						reading >> time;
						record << time << endl;

						reading >> participants;
						record << participants << endl;

						reading >> dataChange;
						record << dataChange << endl;

						reading >> timeChange;
						if (i < n - 1)
							record << timeChange << endl;
						else
							record << timeChange;
					}
					else {
						reading >> nameEvent;
						reading >> place;
						reading >> data;
						reading >> time;
						reading >> participants;
						reading >> dataChange;
						reading >> timeChange;
					}
				}
				cout << "Данные удалены!" << endl;
				cout << "Дата удаления: " << st.wDay << "/" << st.wMonth << "/" << st.wYear << endl;
				cout << "Время удаления: " << st.wHour << ":" << st.wMinute << endl;
			}
			else
				cout << "Номер введен не верно!" << endl;
		}
		else
			cout << "Ошибка открытия файла!" << endl;
	}
	else
		cout << "Ошибка открытия буферного файла!" << endl;

	record.close();
	reading.close();

	remove("Buffer_.txt");
}

void AddData() {
	//добавить данные

	//временные переменные
	string nameEvent;
	string place;
	string data;
	string time;
	string participants;
	int n = AmountOfData() + 1;

	//Временная переменная для даты и времени
	SYSTEMTIME st;
	GetLocalTime(&st);

	//открытие буферного файла
	ofstream record("Buffer.txt", ios::app);//записывает данные в конец
	ofstream record_("Buffer.txt", ios::out | ios::in);//записывает в начало, перезаписывает данные которые там уже имеются

	if (record_) {
		record_ << n << endl;

		cout << "Введите название события: ";
		cin >> nameEvent;

		cout << "Введите место: ";
		cin >> place;

		cout << "Введите дату: ";
		cin >> data;
		isValidDate(data);

		cout << "Введите время: ";
		cin >> time;
		isValidTime(time);

		cout << "Введите участников: ";
		cin >> participants;

		record << nameEvent << endl;
		record << place << endl;
		record << data << endl;
		record << time << endl;
		record << participants << endl;
		record << st.wDay << "/" << st.wMonth << "/" << st.wYear << endl;
		record << st.wHour << ":" << st.wMinute;
	}
	else
		cout << "Ошибка открытия файла!" << endl;

	record.close();
	record_.close();
}

int AmountOfData(){
	//выводит количество данных из файла
	ifstream _buf("Buffer.txt");
	int n;

	if (_buf) {
		_buf >> n;
	}
	else
		cout << "Ошибка открытия буферного файла!" << endl;

	_buf.close();
	return n;
}

bool DataCleaning() {
	//очистка буфера

	bool clear = false;

	//открываем файл
	fstream _buf("Buffer.txt", ios::out);

	if (!_buf)
		cout << "Ошибка открытия буфернорго файла!" << endl;

	//очищаем
	_buf.clear();

	//проверка, что файл чист
	if (_buf.peek() == EOF)//если первый элемент равен последнему
		clear = true;
	else
		clear = false;

	_buf.close();
	remove("Buffer.txt");
	return clear;
}

void SaveBufferToFile(const string& targetFileName) {
	ifstream bufferFile("Buffer.txt");
	ofstream targetFile(targetFileName);
	if (bufferFile) {
		if (targetFile) {
			//временные переменные
			string nameEvent;
			string place;
			string data;
			string time;
			string participants;
			int n;

			//Временная переменная для даты и времени
			string dataChange;
			string timeChange;

			//считываем из буфетного файла в новый
			bufferFile >> n;
			targetFile << n << endl;

			for (int i = 0; i < n; i++) {
				bufferFile >> nameEvent;
				targetFile << nameEvent << endl;

				bufferFile >> place;
				targetFile << place << endl;

				bufferFile >> data;
				targetFile << data << endl;

				bufferFile >> time;
				targetFile << time << endl;

				bufferFile >> participants;
				targetFile << participants << endl;

				bufferFile >> dataChange;
				targetFile << dataChange << endl;

				bufferFile >> timeChange;
				if (i < n - 1)
					targetFile << timeChange << endl;
				else
					targetFile << timeChange;
			}
		}
		else
			cout << "Ошибка открытия файла!" << endl;
	}
	else
		cout << "Ошибка открытия буферного файла!" << endl;
	bufferFile.close();
	targetFile.close();
}

bool isValidDate(const std::string& dateStr) {
	std::istringstream iss(dateStr);
	int day, month, year;
	char dot1, dot2;

	// Пытаемся извлечь значения дня, месяца и года из строки 
	if (iss >> day >> dot1 >> month >> dot2 >> year) {
		// Проверяем, что все символы были успешно извлечены и соответствуют ожидаемому формату 
		if (dot1 == '.' && dot2 == '.' && day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 0 && year <= 99) {
			return true;
		}
	}
	std::cerr << "Ошибка: Некорректный формат даты: " << dateStr << std::endl;
	return false;
}

bool isValidTime(const std::string& timeStr) {    // Проверяем, что строка имеет длину 5 и содержит двоеточие
	if (timeStr.length() != 5 || timeStr[2] != ':') {
		std::cerr << "Ошибка: Некорректный формат времени: " << timeStr << std::endl;
		return false;
	}
	// Проверяем, что все символы до и после двоеточия являются цифрами
	if (timeStr.find_first_not_of("0123456789") != std::string::npos) {
		std::cerr << "Ошибка: Некорректный формат времени: " << timeStr << std::endl;
		return false;
	}
	// Преобразуем строковые значения часов и минут в целочисленные значения
	int hours = std::stoi(timeStr.substr(0, 2));    int minutes = std::stoi(timeStr.substr(3, 2));
	// Проверяем, что значения часов и минут находятся в допустимом диапазоне
	if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
		std::cerr << "Ошибка: Некорректный формат времени: " << timeStr << std::endl;
		return false;
	}
	return true;
}

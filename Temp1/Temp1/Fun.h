#include <iostream> //��� ������ � �������� ����� � ������
#include <fstream> //��� ������ � �������� ������, ������ � �������� � ������
#include <string> //��� ����� �����
#include <Windows.h>//��� ������������ ������� system
#include <conio.h>
#include <vector>
#include <sstream> 

using namespace std;

//��������� �������
void DataInitialization();//������������� ������
void DataEntry();//���� ������ �������
void DataReading(string fileName);//������ ������
void Print();//����� ������
bool DataCleaning();//������� ������
void DataChange();//��������� ������
void Copy();//����������� ������
int AmountOfData();//���������� ������
void DeleteData();//�������� ������
void AddData();//���������� ������
void SaveBufferToFile(const string& targetFileName);//c��������� ���������� � ����
bool isValidDate(const std::string& dateStr);//�������� �� ������ ����
bool isValidTime(const std::string& timeStr);//�������� �� ������ �������

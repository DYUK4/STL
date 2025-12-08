#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4326)
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\----------------------------------------------------\n"


const std::map<int, std::string>VIOLATIONS =
{
	{1,"Ремень безопасности"},
	{2,"Парковка в неположенном месте"},
	{3,"Пересечение сплошной"},
	{4,"Превышение скорости"},
	{5,"Отсутствие водительского удостоверения"},
	{6,"Отсутствие права управленя автомобилем"},
	{7,"Отсутствие страховки"},
	{8,"Проезд на красный"},
	{9,"Выезд на встречную полосу"},
	{10,"Дрифт на перекрестке"},
	{11,"Езда в нетрезвом состоянии"},
	{12,"Оскорбление офицера" },
	{13,"Внесение изменений в конструкцию автомобиля"},
	{14,"Перевозка негабаритного груза"},
	{15,"Превышение максимальной нагрузки на ось"},
	{16,"Перевозка рубенка без кресла"},
};

class Crime // совершеное правонарушение
{
	// td::string license_plate;// регистрационный номер
	int id;//нарушение
	std::string place;
	tm time; //std::string time;
public:
	/*const std::string& get_licence_plate()const 
	{ return license_plate; }*/

	int get_violation_id()const 
	{ return id; }

	const std::string& get_violation()const 
	{ return VIOLATIONS.at(id); }

	const std::string& get_place()const
	{return place;}

	const std::string get_time()const // убрать & - с ним ошибка вывода
	{
		std::string result = asctime(&time);
		result.pop_back();
		//return asctime(&time); 
		//return result;
		const int SIZE = 256;
		char formatted[SIZE]{};
		strftime(formatted, SIZE, "%R %e. %m.%Y", &time);
		return formatted;
	}

	
	//==========================================================================================
	/*void set_license_plate(const std::string& license_plate)
	{ this->license_plate = license_plate;}*/

	void set_violation_id(int id) 
	{ this->id = id; }

	void set_place(const std::string& place) 
	{ this->place = place; }

	void set_time(const std::string& time) 
	{ 
		//1) создаем строку для того чтоды пропарсить полученную строку:
		char* time_buffer = new char[time.size() + 1] {};
		//2) копируем полученную строку в буфуе:
		strcpy(time_buffer, time.c_str());
		//Функция strcpy(dst,src); копирует содержимое источника (src-Source) в сероку получателя(dst - Destanition)
		
		//3) элементы времени . Создаем массив для хранения элементов времени:
		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);
		  // Функция  std::atoi() 'ASCII - string to int' преобразует строку целое число.

		delete[]time_buffer; // был нужен для того чтобы пропарсить строку с временем

		//4) сохраняем элементы времени с струкуру 'tm':
		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4] - 1900; // идет отсчет времени

		//this->time = time;
	}

	//======================= Constructors:======================================

	Crime
	(
		//const std::string& license_plate,
		int violation_id,
		const std::string& place,
		const std::string& time
	)
	{
		//set_license_plate(license_plate);
		this->time = {};
		this->set_violation_id(violation_id);
		this->set_place(place);
		this->set_time(time);
#ifdef DEBUG
		cout << "Constructor:\t" << this << endl;
#endif // DEBUG
	}
	~Crime()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG

	}
};

std::ostream& operator << (std::ostream& os, const Crime& obj)
{
	return os << obj.get_time() << ":\t" << obj.get_place() <<" - " << obj.get_violation();
}



void print(const std::map <std::string, std::list <Crime> >& base);
void save(const std::map <std::string, std::list <Crime> >& base,const std::string& filename);

void main()
{
	setlocale(LC_ALL, "");

	/*Crime crime(1, "ул.Ленина", "18:10 1.09.2024");
	cout << crime << endl;*/

	std::map<std::string, std::list<Crime>> base =
	{
		{"a777bb",{Crime(1, "ул.Ленина", "18:10 1.09.2024"), Crime(2,"пл.Свободы","12:25 20.08.2024")}},
		{"a000bb",{Crime(6, "ул.Космонавтов", "11:50 1.08.2024"), Crime(8,"ул.Космонавтов","17:25 01.08.2024")}},
		{"a001bb",{Crime(10, "ул.Пролетарская", "21:50 1.08.2024"), Crime(9,"ул.Космонавтов","21:25 01.08.2024"), Crime(11,"ул.Космонавтов","21:50 01.08.2024"), Crime(12,"ул.Космонавтов","22:05 01.08.2024")}}
	};
	print(base);
	save(base,"base.txt");

}
void print(const std::map <std::string, std::list <Crime> >& base)
{
	cout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin(); map_it != base.end(); ++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;

		}
		cout << delimiter << endl;
	}
}
void save(const std::map <std::string, std::list <Crime> >& base, const std::string& filename)
{
	std::ofstream fout(filename);
	fout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin(); map_it != base.end(); ++map_it)
	{
		fout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			fout << "\t" << *it << endl;

		}
		fout << delimiter << endl;
		std::string command = "Notepad " + filename;
		system(command.c_str());
	}
}

//  47  1:25
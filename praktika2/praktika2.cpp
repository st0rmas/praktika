#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

struct Student {
    char name[20];
    char surname[20];
    char middlename[20];
    int year;
    int course;
    int matan;
    int kult;
    int vp;
    int angem;
};
int N, commandID;
const int LENGTH = 96;
//меню и остальное
void menu();
void pause();
void menupunkts();
void OutputPunkts();
void OutputOneStudent(Student* students, int i);
//добавление, изменение и удаление записей, вывод на экран базы и запрос
void PlusStudent(Student students[]);
void StudentEnter(Student students[]);
void EnterRecord(Student* students);
void ChangeRecord(Student* students);
void DeleteRecord(Student* students);
void EnterZapros(Student* students);

void SortArrays(Student* students);
void SortNumbersUp(Student* students, int p);
void SortNumbersDown(Student* students, int p);
void SortSurnameUp(Student* students);
void SortSurnameDown(Student* students);
//проверка данных
int TrueNumber(int& n);
void RangeNumber(int& n, int RightBorder, int LeftBorder);
void TrueString(char* str);
//работа с файлами
void GetDataFromFile(Student* students);
void EnterDataToFile(Student* students);
void EnterDataBaseToFile(Student* students);
void GetDatabaseFromBin(Student* students);
void ConvertTextbaseToBin(Student* students);

int main() {
    int a = 5;
    setlocale(LC_ALL, "ru");
    cout << "Введите максимальное количество студентов в базе данных: ";
    TrueNumber(N);  
    system("cls");
    menu();
    Student* students = new Student[N]{};
    cin >> commandID;
    while (commandID)
    {
        system("cls");
        if (commandID==0)
        {
            break;
        }
        switch (commandID)
        {
        case 1:
            PlusStudent(students);
            break;
        case 2:
            GetDataFromFile(students);
            break;
        case 3:
            GetDatabaseFromBin(students);
            break;
        case 4:
            
            StudentEnter(students);
            break;
        case 5:
            EnterDataBaseToFile(students);
            break;
        case 6:
            EnterZapros(students);
            break;
        case 7:
            EnterDataToFile(students);
            break;
        case 8:
            ConvertTextbaseToBin(students);
            break;
        case 9:
            EnterRecord(students);
            break;
        case 10:
            ChangeRecord(students);
            break;
        case 11:
            DeleteRecord(students);
            break;
        case 12:
            SortArrays(students);
            break;
        default:
            cout << "Неизвестная команда"<<endl;
            break;
        }
        pause();
    }
}


//Функция вывода консольного меню программы
void menu() {
    setlocale(0, "");
    cout << "Выберите, что вы хотите сделать: \n";
    cout << "1)Ввод информации с клавиатуры \n";
    cout << "2)Ввод из уже существующего текстового файла \n";
    cout << "3)Ввод информации их уже созданного бинарного файла \n";
    cout << "4)Вывод данных на экран \n";
    cout << "5)Вывод данных в файл \n";
    cout << "6)Распечатку информации данных по запросу \n";
    cout << "7)Перевод базы данных в текстовый файл \n";
    cout << "8)Перевод содержимого текстового файла в бинарный файл \n";
    cout << "9)Добавление записи \n";
    cout << "10)Изменение записи \n";
    cout << "11)Удаление записи \n";
    cout << "12)Сортировка \n";
    cout << "0)Выход \n";
}

//Функции работы с файлами
void GetDataFromFile(Student* students) {
    char file_name[100];
    cout << "Введите путь к текстовому файлу, из которого хотите получить данные: ";
    cin >> file_name;
    ifstream fin(file_name);
    if (!fin.is_open())
    {
        cout << "Файл не найден" << endl;
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            fin >> students[i].name;
            fin >> students[i].surname;
            fin >> students[i].middlename;
            fin >> students[i].year;
            fin >> students[i].course;
            fin >> students[i].matan;
            fin >> students[i].vp;
            fin >> students[i].kult;
            fin >> students[i].angem;
        }
        cout << "Студенты добавлены в базу данных" << endl;
    }

    fin.close();
}
void EnterDataToFile(Student* students) {
    int count = 0;
    char file_name[100];
    cout << "Введите путь к текстовому файлу, в который нужно загрузить базу данных: ";
    cin >> file_name;
    ofstream fout(file_name);
    for (int i = 0; i < N; i++)
    {
        if (students[i].course != 0)
        {
            count++;
        }
    }
    for (int i = 0; i < count; i++)
    {
        fout << students[i].name << " " << students[i].surname << " " << students[i].middlename << " " << students[i].year << " " << students[i].course << " " << students[i].matan << " " << students[i].vp << " " << students[i].kult << " " << students[i].angem << endl;
    }
    fout.close();
    cout << "База данных успешно добавлена в текстовый файл!" << endl;
}
void EnterDataBaseToFile(Student* students) {
    int count = 0, StudentCount;
    for (int i = 0; i < N; i++)
    {
        if (students[i].course != 0)
        {
            count++;
        }
    }
    char file_name[100];
    cout << "Введите путь к файлу для вывода данных: ";
    cin >> file_name;
    ofstream fout(file_name, ios::app);
    if (!fout.is_open())
    {
        cout << "Файл не существует!" << endl;
    }
    else
    {
        cout << "Какое количество студентов вы хотите ввести в файл? Введите значение: ";
        TrueNumber(StudentCount);
        system("cls");
        for (int i = count; i < count + StudentCount; i++)
        {
            cout << "Студент " << i + 1 << endl;
            cout << "Введите\nИмя: ";
            TrueString(students[i].name);
            cout << "Фамилия: ";
            TrueString(students[i].surname);
            cout << "Отчество: ";
            TrueString(students[i].middlename);
            cout << "Год рождения: ";
            TrueNumber(students[i].year);
            RangeNumber(students[i].year, 1900, 2018);
            cout << "Курс: ";
            TrueNumber(students[i].course);
            RangeNumber(students[i].course, 1, 6);
            cout << "Оценка по матану: ";
            TrueNumber(students[i].matan);
            RangeNumber(students[i].matan, 2, 5);
            cout << "Оценка по культурологии: ";
            TrueNumber(students[i].kult);
            RangeNumber(students[i].kult, 2, 5);
            cout << "Оценка по ВП: ";
            TrueNumber(students[i].vp);
            RangeNumber(students[i].vp, 2, 5);
            cout << "Оценка по аналитической геометрии: ";
            TrueNumber(students[i].angem);
            RangeNumber(students[i].angem, 2, 5);
            cout << "Студент добавлен!" << endl;
            system("cls");
            fout << students[i].name << " " << students[i].surname << " " << students[i].middlename << " " << students[i].year << " " << students[i].course << " " << students[i].matan << " " << students[i].vp << " " << students[i].kult << " " << students[i].angem << endl;
        }
    }
    fout.close();
}
void ConvertTextbaseToBin(Student* students) {
    char file_name[100];
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        count++;
    }
    cout << "Введите путь к текстовому файлу, который хотите преобразовать в бинарный: ";
    cin >> file_name;
    ifstream fin(file_name);
    if (!fin.is_open())
    {
        cout << "Файл не найден!" << endl;
    }
    else
    {
        ofstream bin("DataBase.bin", ios::binary | ios::out);
        for (int i = 0; i < count; i++)
        {
            fin >> students[i].name;
            fin >> students[i].surname;
            fin >> students[i].middlename;
            fin >> students[i].year;
            fin >> students[i].course;
            fin >> students[i].matan;
            fin >> students[i].vp;
            fin >> students[i].kult;
            fin >> students[i].angem;
            bin.write((char*)&students[i], sizeof(Student));
        }
        fin.close();
        bin.close();
        cout << "База данных успешно перенесена из текстового файла в бинарный!" << endl;
    }
}
void GetDatabaseFromBin(Student* students) {
    char file_name[200];
    cout << "Введите путь к бинарному файлу: ";
    cin >> file_name;
    ifstream bin(file_name, ios::binary);
    for (int i = 0; i < N; i++)
    {
        bin.read((char*)&students[i], sizeof(Student));
    }

    bin.close();
    
    cout << "База данных успешно импортирована из бинарного файла!" << endl;
}

//Функции работы с добавлением, изменением и выводом запроса студентов
void PlusStudent(Student *students) {

    int StudentCount, count=0;
    cout << "Введите количество студентов, которое хотите ввести: ";
    TrueNumber(StudentCount);
    
    for (int i = 0; i < N; i++)
    {
        if (students[i].course!=0)
        {
            count++;
        }
    }
    bool flag = false;
    do
    {
        flag = false;
        if (StudentCount > N - count)
        {
            cout << "Слишком большое количество студентов. Максимальное количество: " << N - count << ". Введите число еще раз: ";
            cin >> StudentCount;
            flag = true;
        }
    } while (flag);
   
    for (int i = count; i < count+StudentCount; i++)
    {
        cout << "Студент " << i + 1 << endl;
        cout << "Введите\nИмя: ";
        TrueString(students[i].name);

        cout << "Фамилия: ";
        TrueString(students[i].surname);
        cout << "Отчество: ";
        TrueString(students[i].middlename);
        cout << "Год рождения: ";
        TrueNumber(students[i].year);
        RangeNumber(students[i].year, 1900, 2018);
        cout << "Курс: ";
        TrueNumber(students[i].course);
        RangeNumber(students[i].course, 1, 6);
        cout << "Оценка по матану: ";
        TrueNumber(students[i].matan);
        RangeNumber(students[i].matan, 2, 5);
        cout << "Оценка по культурологии: ";
        TrueNumber(students[i].kult);
        RangeNumber(students[i].kult, 2, 5);
        cout << "Оценка по ВП: ";
        TrueNumber(students[i].vp);
        RangeNumber(students[i].vp, 2, 5);
        cout << "Оценка по аналитической геометрии: ";
        TrueNumber(students[i].angem);
        RangeNumber(students[i].angem, 2, 5);
        cout << "Студент добавлен!" << endl;
        system("pause");
        system("cls");
    }
}
void StudentEnter(Student* students) {
    
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (students[i].course != 0)
        {
            count++;
        }
    }
    if (count==0)
    {
        cout << "База данных пустая!" << endl;
    }
    else
    {
        menupunkts();
        for (int j = 0; j < LENGTH; j++)
        {
            cout << "-";
        }
        cout << endl;
        for (int i = 0; i < count; i++)
        {
            cout << setiosflags(ios::left) << setw(3) << i + 1 << "|" << setw(10) << students[i].name << "|" << setw(10) << students[i].surname << "|" << setw(15) << students[i].middlename << "|" << setw(10) <<
                students[i].year << "|" << setw(10) << students[i].course << "|" << setw(7) << students[i].matan << "|" << setw(4) << students[i].kult << "|" << setw(6) << students[i].vp << "|" <<
                setw(11) << students[i].angem << "|" << endl;
            for (int j = 0; j < LENGTH; j++)
            {
                cout << "-";
            }
            cout << endl;
        }

        cout << endl;
    }
    
}
void EnterRecord(Student* students) {
    int RecordNumber, count = 0, WhereEnter;
    for (int i = 0; i < N; i++)
    {
        if (students[i].course != 0)
        {
            count++;
        }
    }
    if (count==N)
    {
        cout << "Максимально количество студентов в базе данных, невозможно добавить еще одного" << endl;
    }
    else
    {
        cout << "Куда вы хотите добавить свою запись?\n1. В начало\n2. В середину\n3. В конец\nВыберите пункт: " << endl;
        TrueNumber(RecordNumber);
        switch (RecordNumber)
        {
        case 1:
            system("cls");
            for (int i = N - 1; i > 0; i--)
            {
                students[i] = students[i - 1];
            }
            cout << "Введите\nИмя: ";
            TrueString(students[0].name);
            cout << "Фамилия: ";
            TrueString(students[0].surname);
            cout << "Отчество: ";
            TrueString(students[0].middlename);
            cout << "Год рождения: ";
            TrueNumber(students[0].year);
            RangeNumber(students[0].year, 1900, 2018);
            cout << "Курс: ";
            TrueNumber(students[0].course);
            RangeNumber(students[0].course, 1, 6);
            cout << "Оценка по матану: ";
            TrueNumber(students[0].matan);
            RangeNumber(students[0].matan, 2, 5);
            cout << "Оценка по культурологии: ";
            TrueNumber(students[0].kult);
            RangeNumber(students[0].kult, 2, 5);
            cout << "Оценка по ВП: ";
            TrueNumber(students[0].vp);
            RangeNumber(students[0].vp, 2, 5);
            cout << "Оценка по аналитической геометрии: ";
            TrueNumber(students[0].angem);
            RangeNumber(students[0].angem, 2, 5);

            cout << "Студент добавлен!" << endl;
            break;
        case 2:
            cout << "После какого студента вы хотите добавить запись? Введите номер: ";
            TrueNumber(WhereEnter);
            for (int i = N - 1; i > WhereEnter; i--)
            {
                students[i] = students[i - 1];
            }
            system("cls");
            cout << "Введите\nИмя: ";
            TrueString(students[WhereEnter].name);
            cout << "Фамилия: ";
            TrueString(students[WhereEnter].surname);
            cout << "Отчество: ";
            TrueString(students[WhereEnter].middlename);
            cout << "Год рождения: ";
            TrueNumber(students[WhereEnter].year);
            RangeNumber(students[WhereEnter].year, 1900, 2018);
            cout << "Курс: ";
            TrueNumber(students[WhereEnter].course);
            RangeNumber(students[WhereEnter].course, 1, 6);
            cout << "Оценка по матану: ";
            TrueNumber(students[WhereEnter].matan);
            RangeNumber(students[WhereEnter].matan, 2, 5);
            cout << "Оценка по культурологии: ";
            TrueNumber(students[WhereEnter].kult);
            RangeNumber(students[WhereEnter].kult, 2, 5);
            cout << "Оценка по ВП: ";
            TrueNumber(students[WhereEnter].vp);
            RangeNumber(students[WhereEnter].vp, 2, 5);
            cout << "Оценка по аналитической геометрии: ";
            TrueNumber(students[WhereEnter].angem);
            RangeNumber(students[WhereEnter].angem, 2, 5);

            cout << "Студент добавлен!" << endl;
            break;
        case 3:
            system("cls");
            cout << "Введите\nИмя: ";
            TrueString(students[count].name);
            cout << "Фамилия: ";
            TrueString(students[count].surname);
            cout << "Отчество: ";
            TrueString(students[count].middlename);
            cout << "Год рождения: ";
            TrueNumber(students[count].year);
            RangeNumber(students[count].year, 1900, 2018);
            cout << "Курс: ";
            TrueNumber(students[count].course);
            RangeNumber(students[count].course, 1, 6);
            cout << "Оценка по матану: ";
            TrueNumber(students[count].matan);
            RangeNumber(students[count].matan, 2, 5);
            cout << "Оценка по культурологии: ";
            TrueNumber(students[count].kult);
            RangeNumber(students[count].kult, 2, 5);
            cout << "Оценка по ВП: ";
            TrueNumber(students[count].vp);
            RangeNumber(students[count].vp, 2, 5);
            cout << "Оценка по аналитической геометрии: ";
            TrueNumber(students[count].angem);
            RangeNumber(students[count].angem, 2, 5);
            cout << "Студент добавлен!" << endl;
            break;
        default:
            cout << "Неизвестная команда" << endl;
            break;
        }
    }
  
}
void ChangeRecord(Student* students) {
    int change, MenuChoose;
    cout << "Какую запись вы желаете изменить? Введите номер: ";
    TrueNumber(change);
    cout << endl;
    cout << "Что вы желаете изменить? Введите пункт: " << endl;
    OutputPunkts();
    TrueNumber(MenuChoose);
    cout << "Введите новое значение: ";
    switch (MenuChoose)
    {
    case 1:
        TrueString(students[change-1].name);
        break;
    case 2:
        TrueString(students[change - 1].surname);
        break;
    case 3:
        TrueString(students[change - 1].middlename);
        break;
    case 4:
        TrueNumber(students[change - 1].year);
        RangeNumber(students[change - 1].year, 1900, 2018);
        break;
    case 5:
        TrueNumber(students[change - 1].course);
        RangeNumber(students[change - 1].course, 1, 6);
        break;
    case 6:
        TrueNumber(students[change - 1].matan);
        RangeNumber(students[change - 1].matan, 2, 5);
        break;
    case 7:
        TrueNumber(students[change - 1].vp);
        RangeNumber(students[change - 1].vp, 2, 5);
        break;
    case 8:
        TrueNumber(students[change - 1].kult);
        RangeNumber(students[change - 1].kult, 2, 5);
        break;
    case 9:
        TrueNumber(students[change - 1].angem);
        RangeNumber(students[change - 1].angem, 2, 5);
        break;
    default:
        cout << "Неизвестная команда" << endl;
        break;
    }
    cout << endl;
    cout << "Запись изменена!" << endl << endl;
    
}
void DeleteRecord(Student* students) {
    int DeleteNumber, count=0;
    for (int i = 0; i < N; i++)
    {
        if (students[i].course != 0)
        {
            count++;
        }
    }
    if (count==0)
    {
        cout << "База данных пустая" << endl;
    }
    else
    {
        cout << "Какую запись вы хотите удалить? Введите её номер: ";
        TrueNumber(DeleteNumber);
        if (DeleteNumber==count)
        {
            students[DeleteNumber - 1].course = 0;
            cout << "Запись удалена!" << endl << endl;
        }
        else if (DeleteNumber>count)
        {
            cout << "Удаление невозможно, студента не существует" << endl;
        }
        else
        {
            for (int i = DeleteNumber - 1; i < N; i++)
            {
                students[i] = students[i + 1];
            }
            cout << "Запись удалена!" << endl << endl;
        }
        
        cout << endl;
       
    }
}
void EnterZapros(Student* students) {
    int count = 0, step = 0;   
    for (int i = 0; i < N; i++)
    {
        if (students[i].course != 0)
        {
            count++;
        }
    }
    Student* BufferStudents = new Student[count];  
    double* zapros = new double[count] {};
    for (int i = 0; i < count; i++)
    {
        if (students[i].course==2)
        {
            BufferStudents[step] = students[i];
            step++;          
        }
    }
    for (int j = 0; j < step; j++)
    {
        for (int i=j+1;  i < step;  i++)
        {
            if (((BufferStudents[j].matan + BufferStudents[j].vp + BufferStudents[j].kult + BufferStudents[j].angem) / 4.) > ((BufferStudents[i].matan + BufferStudents[i].vp + BufferStudents[i].kult + BufferStudents[i].angem) / 4.))
            {
                swap(BufferStudents[j], BufferStudents[i]);
            }
        }
    }
    cout << setiosflags(ios::left) << setw(3) << "№" << "|" << setw(10) << "Name" << "|" << setw(10) << "Surname" << "|" <<
        setw(15) << "Middle Name" << "|" << setw(10) << "Year" << "|" << setw(10) << "Course" << "|" << setw(7) << "Matan" << "|"
        << setw(4) << "Kult" << "|" << setw(6) << "VP" << "|" << setw(10) << "Analit Geom" << "|" << "\n";
    for (int i = 0; i < step; i++)
    {
        OutputOneStudent(BufferStudents, i);
    }
    for (int j = 0; j < LENGTH; j++)
    {
        cout << "-";
    }
    cout << endl;

    delete[] zapros; delete[] BufferStudents;
}

//Функции сортировки данных
void SortArrays(Student* students) {
    int ChooseSort;
    if (students[0].course==0)
    {
        cout << "База пустая, нельзя отсортировать" << endl;
    }
    else
    {
        cout << "Выберите, что вы хотите отсортировать?\n1. Фамилия\n2. Год рождения\n3. Курс\n4. Средний балл предметов\nВыберите пункт: ";
        TrueNumber(ChooseSort);
        system("cls");
        int UpOrDown;
        cout << "Выберите, как хотите отсортировать данные:\n1.По убыванию\n2.По возрастанию\nВыберите пункт: ";
        TrueNumber(UpOrDown);
        switch (UpOrDown)
        {
        case 1:
            switch (ChooseSort)
            {
            case 1:
                SortSurnameDown(students);
                break;
            case 2:
                SortNumbersUp(students,1);
                break;
            case 3:
                SortNumbersDown(students, 2);
                
                break;
            case 4:
                SortNumbersDown(students, 3);
                break;
            default:
                cout << "Неизвестная команда!";
                break;
            }
            break;
        case 2:
            switch (ChooseSort)
            {
            case 1:
                SortSurnameUp(students);
                break;
            case 2:
                SortNumbersDown(students, 1);                
                break;
            case 3:
                SortNumbersUp(students, 2);
                break;
            case 4:
              
                SortNumbersUp(students, 3);
                break;
            default:
                cout << "Неизвестная команда!";
                break;
            }
            break;
        default:
            cout << "Неизвестная команда!" << endl;
            break;
        }

        cout << "Сортировка успешно выполнена!" << endl;
    }
    
}
void SortNumbersUp(Student* students, int p) {
    int count=0;
    for (int i = 0; i < N; i++)
    {
        if (students[i].course!=0)
        {
            count++;
        }
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            switch (p)
            {
            case 1:
                if (students[i].year > students[j].year)
                {
                    swap(students[i], students[j]);
                }
                break;
            case 2:
                if (students[i].course > students[j].course)
                {
                    swap(students[i], students[j]);
                }
                break;
            case 3:
                if (((students[i].matan + students[i].vp + students[i].kult + students[i].angem) / 4.) > ((students[j].matan + students[j].vp + students[j].kult + students[j].angem) / 4.))
                {
                    swap(students[i], students[j]);
                }
                break;
            default:
                cout << "Неизвестная команда!";
                break;
            }
        }
    }
}
void SortNumbersDown(Student* students, int p) {
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (students[i].course != 0)
        {
            count++;
        }
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            switch (p)
            {
            case 1:
                if (students[i].year < students[j].year)
                {
                    swap(students[i], students[j]);
                }
                break;
            case 2:
                if (students[i].course < students[j].course)
                {
                    swap(students[i], students[j]);
                }
                break;
            case 3:
                if (((students[i].matan + students[i].vp + students[i].kult + students[i].angem) / 4.) < ((students[j].matan + students[j].vp + students[j].kult + students[j].angem) / 4.))
                {
                    swap(students[i], students[j]);
                }
                break;
            default:
                cout << "Неизвестная команда!";
                break;
            }
        }
    }
}
void SortSurnameUp(Student* students) {
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (students[i].course != 0)
        {
            count++;
        }
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            
                if (students[i].surname[0]>students[j].surname[0])
                {
                    swap(students[i], students[j]);
                }        
        }
    }
}
void SortSurnameDown(Student* students) {
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (students[i].course != 0)
        {
            count++;
        }
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {

            if (students[i].surname[0] < students[j].surname[0])
            {
                swap(students[i], students[j]);
            }
        }
    }
}

//Функции вывода пунктов меню, одного студента и паузы
void OutputPunkts() {
    cout << "1. Имя" << endl;
    cout << "2. Фамилия" << endl;
    cout << "3. Отчество" << endl;
    cout << "4. Год рождения" << endl;
    cout << "5. Курс" << endl;
    cout << "6. Оценка по мат.анализу" << endl;
    cout << "7. Оценка по ВП" << endl;
    cout << "8. Оценка по культурологии" << endl;
    cout << "9. Оценка по анал. геометрии" << endl;
}
void OutputOneStudent(Student *students, int i){
    for (int i = 0; i < LENGTH; i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << setiosflags(ios::left) << setw(3) << i+1 << "|" << setw(10) << students[i].name << "|" << setw(10) << students[i].surname << "|" << setw(15) << students[i].middlename << "|" << setw(10) <<
        students[i].year << "|" << setw(10) << students[i].course << "|" << setw(7) << students[i].matan << "|" << setw(4) << students[i].kult << "|" << setw(6) << students[i].vp << "|" <<
        setw(11) << students[i].angem << "|" << endl;
    
}
void pause() {
    char temp;
    cout << "Введите любой символ, чтобы продолжить: ";
    cin >> temp;
    system("cls");
    menu();
    cin >> commandID;
}
void menupunkts() {
    cout << setiosflags(ios::left) << setw(3) << "№" << "|" << setw(10) << "Name" << "|" << setw(10) << "Surname" << "|" <<
        setw(15) << "Middle Name" << "|" << setw(10) << "Year" << "|" << setw(10) << "Course" << "|" << setw(7) << "Matan" << "|"
        << setw(4) << "Kult" << "|" << setw(6) << "VP" << "|" << setw(10) << "Analit Geom" << "|" << "\n";
    
}

//Функции проверки введенных пользователем данных на правильность типа и правдоподобность
int TrueNumber(int& n) {
    bool flag = false;
    
    do
    {
        flag = false;
        if ((cin >> n).fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Неправильный тип данных, попробуйте еще раз. Введите число: ";
            flag = true;
        }
        else if (N <= 0)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Число студентов должно быть больше 0. Введите значение еще раз: ";
            flag = true;
        }

    } while (flag);
    
    return n;
}
void RangeNumber(int& n, int RightBorder, int LeftBorder) {
    bool flag = false;
    do
    {
        flag = false;
        if (n<RightBorder || n>LeftBorder)
        {
            cout << "Число не входит в допустимый диапазон. Введите еще раз: ";
            cin >> n;
            flag = true;
        }
    } while (flag);

}
void TrueString(char *str) {
    bool flag = false;
    
    do
    {
        cin >> str;
        flag = false;
        for (int i = 0; i < strlen(str); i++)
        {
            
                if (isdigit(str[i]))
                {
                    
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    flag = true;
                    cout << "Неверный тип данных, введите еще раз: ";
                    
                }     
        }        
    } while (flag);
    
}

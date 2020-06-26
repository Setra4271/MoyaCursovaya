#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <algorithm>
#include <Windows.h>
using namespace std;
class filePath
{
public:
    static string nodes;
    static string lodgers;
    static string flats;
    static string houses;
};
string filePath::nodes = "nodes.txt";
string filePath::lodgers = "lodgers.txt";
string filePath::flats = "flats.txt";
string filePath::houses = "houses.txt";
int getItem(int min, int max)
{
    int x = -1;
    while (x < min || x > max)
    {
        x = _getch() - 48;
    }
    return x;
}
enum class LodgerType
{
    noworker,
    worker,
    student,
    retiree
};
class Lodger
{
public:
    Lodger(int id, string name, string surname, int age, LodgerType type)
    {
        setId(id);
        setName(name);
        setSurname(surname);
        setAge(age);
        setType(type);
    }
    Lodger(string name, string surname, int age, LodgerType type)
    {
        setName(name);
        setSurname(surname);
        setAge(age);
        setType(type);
    }
    Lodger()
    {
        setName("None");
        setSurname("None");
        setAge(0);
        setType(LodgerType::noworker);
    }
    int getId()
    {
        return this->id;
    }
    string getName()
    {
        return this->name;
    }
    string getSurname()
    {
        return this->surname;
    }
    int getAge()
    {
        return this->age;
    }
    LodgerType getType()
    {
        return this->type;
    }
    string getTypeSuchString()
    {
        switch (type)
        {
        case LodgerType::noworker:
            return "Безработный";
            break;
        case LodgerType::worker:
            return "Работает";
            break;
        case LodgerType::student:
            return "Студент";
            break;
        case LodgerType::retiree:
            return "Пенсионер";
            break;
        default:
            return "Не известно";
            break;
        }
    }
    void setId(int id)
    {
        if (id >= 0)
        {
            this->id = id;
        }
        else
        {
            this->id = 0;
        }
    }
    void setName(string name)
    {
        if (!name.empty())
        {
            this->name = name;
        }
        else
        {
            throw new exception("Неверное имя квартиранта", 1);
        }
    }
    void setSurname(string surname)
    {
        if (!surname.empty())
        {
            this->surname = surname;
        }
        else
        {
            throw new exception("Неверная фамилия квартиранта", 2);
        }
    }
    void setAge(int age)
    {
        if (age >= 0 && age < 130)
        {
            this->age = age;
        }
        else
        {
            throw new exception("Неверный возраст квартиранта", 3);
        }
    }
    void setType(LodgerType type)
    {
        this->type = type;
    }
    void print()
    {
        cout << "ID: " << getId() << endl;
        cout << "Имя: " << getName() << endl;
        cout << "Фамилия: " << getSurname() << endl;
        cout << "Возраст: " << getAge() << endl;
        cout << "Род занятий: " << getTypeSuchString() << endl;
    }
private:
    int id;
    string name;
    string surname;
    int age;
    LodgerType type;
};
class Flat
{
public:
    Flat(int id, int number, double priceMillion)
    {
        setId(id);
        setNumber(number);
        setPrice(priceMillion);
    }
    Flat()
    {
        setId(0);
        setNumber(0);
        setPrice(0);
    }
    void addLodger(Lodger* lodger)
    {
        lodgers.push_back(lodger);
    }
    void print()
    {
        cout << "------Квартира №" << number << endl;
        cout << "------Стоимость " << priceMillion << " млн.р." << endl;
        for (auto& it : lodgers)
        {
            it->print();
            cout << endl;
        }
    }
    int getId()
    {
        return this->id;
    }
    int getNumber()
    {
        return this->number;
    }
    double getPrice()
    {
        return this->priceMillion;
    }
    void setId(int id)
    {
        this->id = id;
    }
    void setNumber(int number)
    {
        this->number = number;
    }
    void setPrice(double priceMillion)
    {
        this->priceMillion = priceMillion;
    }
    vector<Lodger> getLodgers()
    {
        vector<Lodger> lodgersTemp;
        for (auto it : lodgers)
        {
            lodgersTemp.push_back(*it);
        }
        return lodgersTemp;
    }

    Lodger* getLodgerById(int id)
    {
        for (auto& it : lodgers)
        {
            if (it->getId() == id)
            {
                return it;
            }
        }
        return nullptr;
    }
    int lodgersCount()
    {
        return lodgers.size();
    }
    vector<Lodger*> Lodgers()
    {
        return lodgers;
    }
    bool removeLodgerById(int id)
    {
        int size1 = lodgers.size();
        auto it = lodgers.erase(remove_if(lodgers.begin(), lodgers.end(),
            [&](auto& lodger) {return lodger->getId() == id; }), lodgers.end()
        );
        int size2 = lodgers.size();
        if ((size1 - size2) != 0) return true;
        else return false;
    }
private:
    int getMaxId()
    {
        int max = 0;
        for (auto it : lodgers)
        {
            if (it->getId() > 0) max = it->getId();
        }
    }
private:
    int id;
    int number;
    double priceMillion;
    vector<Lodger*> lodgers;
};
class House
{
public:
    House(int id, int number, string street)
    {
        setId(id);
        setNumber(number);
        setStreet(street);
    }
    House()
    {
        setId(0);
        setNumber(0);
        setStreet("None");
    }
    void print()
    {
        //cout << setw(5) << "Дом №" << number << "" << endl;
        printf("||||||||||||||||||||||||||||||||||||Дом №%03d|||||||||||||||||||||||||||||||||||\n", number);
        printf("||||||||||||||||||||||||||||||||Улица %03s|||||||||||||||||||||||||||||||\n", street.c_str());
        //cout << "|||||||||||||||| Улица " << street << " ||||||||||||||||" << endl;
        for (auto it : flats)
        {
            it->print();
        }
    }
    void printMin()
    {
        printf("----------------ID №%03d--------------\n", id);
        cout << "Дом №" << number << " улица " << street << endl;
        cout << " Квартир: " << flatsCount() << endl;
        cout << " Жильцов: " << lodgerlCount() << endl;
        cout << "--------------------------------------" << endl;
    }
    void addFlat(Flat* flat)
    {
        flats.push_back(flat);
    }
    int getId()
    {
        return this->id;
    }
    int getNumber()
    {
        return this->number;
    }
    string getStreet()
    {
        return this->street;
    }
    void setId(int id)
    {
        this->id = id;
    }
    void setNumber(int number)
    {
        this->number = number;
    }
    void setStreet(string street)
    {
        this->street = street;
    }
    vector<Flat> getFlats()
    {
        vector<Flat> flatsTemp;
        for (auto it : flats)
        {
            flatsTemp.push_back(*it);
        }
        return flatsTemp;
    }
    Flat* getFlatById(int id)
    {
        for (auto& it : flats)
        {
            if (it->getId() == id)
            {
                return it;
            }
        }
        return nullptr;
    }
    int flatsCount()
    {
        return flats.size();
    }
    int lodgerlCount()
    {
        int count = 0;
        for (auto it : flats)
        {
            count += it->lodgersCount();
        }
        return count;
    }
    vector<Flat*> Flats()
    {
        return flats;
    }
private:
    int id;
    int number;
    string street;
    vector<Flat*> flats;
};
class Core
{
public:
    Core()
    {
    };
    void addHouse(House* house)
    {
        houses.push_back(house);
    }
    void addLoder(Flat* flat, Lodger* lodger)
    {
        if (flat != nullptr)flat->addLodger(lodger);
    }
    Flat* getFlat(int houseId, int flatId)
    {
        Flat* flatTemp = nullptr;
        for (auto& house : houses)
            for (auto& flat : house->Flats())
            {
                if (house->getId() == houseId && flat->getId() == flatId)
                {
                    flatTemp = flat;
                    return flatTemp;
                }
            }
        return flatTemp;
    }
    void loadHouses()
    {
        ifstream fp;
        fp.open(filePath::houses);
        while (!fp.eof())
        {
            int id;
            int number;
            string street;
            fp >> id;
            fp >> number;
            fp >> street;
            houses.push_back(new House(id, number, street));
        }
        fp.close();
    }
    void loadFlats()
    {
        ifstream fp;
        fp.open(filePath::flats);
        while (!fp.eof())
        {
            int id;
            int number;
            double priceMillion;
            fp >> id;
            fp >> number;
            fp >> priceMillion;
            flats.push_back(new Flat(id, number, priceMillion));
        }
        fp.close();
    }
    void loadLodgers()
    {
        ifstream fp;
        fp.open(filePath::lodgers);
        while (!fp.eof())
        {
            int id;
            string surname;
            string name;
            int age;
            int type;
            fp >> id;
            fp >> surname;
            fp >> name;
            fp >> age;
            fp >> type;
            lodgers.push_back(new Lodger(id, name, surname, age, static_cast<LodgerType>(type)));
        }
        fp.close();
    }
    void loadNodes()
    {
        ifstream fp;
        fp.open(filePath::nodes);
        string line;
        stringstream ss;
        while (getline(fp, line))
        {
            if (!line.empty())
            {
                ss << line;
                int houseId;
                int flatId;
                int lodgerId;
                ss >> houseId;
                ss >> flatId;
                ss >> lodgerId;
                House* house = getHouseById(houseId);
                Flat* flat = getTempFlatById(flatId);
                Lodger* lodger = getTempLodgerById(lodgerId);
                if (!flatIsExsist(flat->getId())) house->addFlat(flat);
                flat->addLodger(lodger);
                ss.clear();
            }
        }
        fp.close();
    }
    void load()
    {
        loadHouses();
        loadFlats();
        loadLodgers();
        loadNodes();
    }
    void saveHouses()
    {
        ofstream fp;
        fp.open(filePath::houses);
        bool needEndl = true;
        for (auto it : houses)
        {
            fp << it->getId() << " ";
            fp << it->getNumber() << " ";
            fp << it->getStreet();
            if (!houses.empty())
            {
                auto last = houses[houses.size() - 1];
                if (it->getId() == last->getId())
                {
                    needEndl = false;
                }
            }
            if (needEndl) fp << endl;
        }
    }
    /*
    void saveFlats()
    {
        ofstream fp;
        fp.open(filePath::flats);
        bool needEndl = true;
        for(auto house : houses)
        for (auto it : house->Flats())
        {
            fp << it->getId() << " ";
            fp << it->getNumber() << " ";
            fp << it->getPrice();
            if (!flats.empty())
            {
                auto last = flats[flats.size() - 1];
                if (it->getId() == last->getId())
                {
                    needEndl = false;
                }
            }
            if (needEndl) fp << endl;
        }
    }
    */
    void saveFlats()
    {
        ofstream fp;
        flats.clear();
        fp.open(filePath::flats);
        bool needEndl = true;
        for (auto house : houses)
            for (auto flat : house->Flats())
            {
                flats.push_back(flat);
            }
        sort(flats.begin(), flats.end(), [&](Flat* flat1, Flat* flat2) {
            return flat1->getId() < flat2->getId();
            });
        for (auto flat : flats)
        {
            fp << flat->getId() << " ";
            fp << flat->getNumber() << " ";
            fp << flat->getPrice() << " ";
            if (!flats.empty())
            {
                auto last = flats[flats.size() - 1];
                if (flat->getId() == last->getId())
                {
                    needEndl = false;
                }
            }
            if (needEndl) {
                fp << endl;
            }
        }
    }
    void saveLodgers()
    {
        ofstream fp;
        lodgers.clear();
        fp.open(filePath::lodgers);
        bool needEndl = true;
        for (auto house : houses)
            for (auto flat : house->Flats())
                for (auto lodger : flat->Lodgers())
                {
                    lodgers.push_back(lodger);
                }
        sort(lodgers.begin(), lodgers.end(), [&](Lodger* lodger1, Lodger* lodger2) {
            return lodger1->getId() < lodger2->getId();
            });
        for (auto lodger : lodgers)
        {
            fp << lodger->getId() << " ";
            fp << lodger->getSurname() << " ";
            fp << lodger->getName() << " ";
            fp << lodger->getAge() << " ";
            fp << static_cast<int>(lodger->getType());
            if (!lodgers.empty())
            {
                auto last = lodgers[lodgers.size() - 1];
                if (lodger->getId() == last->getId())
                {
                    needEndl = false;
                }
            }
            if (needEndl) {
                fp << endl;
            }
        }
    }
    void saveNodes()
    {
        ofstream fp;
        fp.open(filePath::nodes);
        for (auto house : houses)
        {
            for (auto flat : house->getFlats())
            {
                for (auto lodger : flat.getLodgers())
                {
                    fp << house->getId() << " " << flat.getId() << " " << lodger.getId();
                    fp << endl;
                }
            }
        }
    }
    void save()
    {
        saveHouses();
        saveFlats();
        saveLodgers();
        saveNodes();
    }
    House* getHouseById(int id)
    {
        for (auto& it : houses)
        {
            if (it->getId() == id)
            {
                return it;
            }
        }
        return nullptr;
    }
    House* getHouseByNumber(int number)
    {
        for (auto& it : houses)
        {
            if (it->getNumber() == number)
            {
                return it;
            }
        }
        return nullptr;
    }
    Flat* getFlatById(int id)
    {
        for (auto& house : houses)
        {
            for (auto& flat : house->getFlats())
            {
                if (flat.getId() == id)
                {
                    return &flat;
                }
            }
        }
        return nullptr;
    }
    Lodger* getLodgerById(int id)
    {
        for (auto& house : houses)
        {
            for (auto& flat : house->Flats())
            {
                for (auto& lodger : flat->Lodgers())
                {
                    if (lodger->getId() == id)
                    {
                        return lodger;
                    }
                }
            }
        }
        return nullptr;
    }
    Flat* getTempFlatById(int id)
    {
        for (auto& it : flats)
        {
            if (it->getId() == id)
            {
                return it;
            }
        }
        return nullptr;
    }
    Lodger* getTempLodgerById(int id)
    {
        for (auto& it : lodgers)
        {
            if (it->getId() == id)
            {
                return it;
            }
        }
        return nullptr;
    }
    void print()
    {
        for (auto house : houses)
        {
            house->print();
        }
    }
    bool houseIsExsist(int id)
    {
        for (auto it : houses)
        {
            if (it->getId() == id) return true;
        }
        return false;
    }
    bool flatIsExsist(int id)
    {
        for (auto item : houses)
        {
            for (auto it : item->getFlats())
            {
                if (it.getId() == id) return true;
            }
        }
        return false;
    }
    bool lodgerIsExsist(int id)
    {
        for (auto it : lodgers)
        {
            if (it->getId() == id) return true;
        }
        return false;
    }
    void printMinAllHouses()
    {
        for (auto it : houses)
        {
            it->printMin();
        }
    }
    void printMinAllHouses(vector<House> vec)
    {
        for (auto it : vec)
        {
            it.printMin();
        }
    }
    vector<House> getSortedHousesById()
    {
        vector<House> vec;
        for (auto it : houses) vec.push_back(*it);
        sort(vec.begin(), vec.end(), [&](House a, House b) {
            if (getSortedDirection)
            {
                return (a.getId() < b.getId());
            }
            else
            {
                return (a.getId() > b.getId());
            }
            });
        getSortedDirection = !getSortedDirection;
        return vec;
    }
    vector<House> getSortedHousesByNumber()
    {
        vector<House> vec;
        for (auto it : houses) vec.push_back(*it);
        sort(vec.begin(), vec.end(), [&](House a, House b) {
            if (getSortedDirection)
            {
                return (a.getNumber() < b.getNumber());
            }
            else
            {
                return (a.getNumber() > b.getNumber());
            }
            });
        getSortedDirection = !getSortedDirection;
        return vec;
    }
    vector<House> getSortedHousesByStreet()
    {
        vector<House> vec;
        for (auto it : houses) vec.push_back(*it);
        sort(vec.begin(), vec.end(), [&](House a, House b) {
            if (getSortedDirection)
            {
                return (a.getStreet() < b.getStreet());
            }
            else
            {
                return (a.getStreet() > b.getStreet());
            }
            });
        getSortedDirection = !getSortedDirection;
        return vec;
    }
    vector<Flat> getFlatsByLodgerName(string name)
    {
        vector<Flat> vec;
        bool needPush = true;
        for (auto house : houses)
        {
            for (auto flat : house->getFlats())
            {
                for (auto lodger : flat.getLodgers())
                {
                    if (lodger.getName() == name && needPush)
                    {
                        vec.push_back(flat);
                        needPush = false;
                    }
                }
                needPush = true;
            }
        }
        return vec;
    }
    vector<Flat> getFlatsByLodgerSurname(string surname)
    {
        vector<Flat> vec;
        bool needPush = true;
        for (auto house : houses)
        {
            for (auto flat : house->getFlats())
            {
                for (auto lodger : flat.getLodgers())
                {
                    if (lodger.getSurname() == surname && needPush)
                    {
                        vec.push_back(flat);
                        needPush = false;
                    }
                }
                needPush = true;
            }
        }
        return vec;
    }
    Flat getFlatWithMaxLodgersInHouse(House* house)
    {
        size_t max = 0;
        Flat findFlat = Flat();
        for (auto& flat : house->getFlats())
        {
            if (flat.getLodgers().size() > max)
            {
                max = flat.getLodgers().size();
                findFlat = flat;
            }
        }
        return findFlat;
    }
    Flat getFlatWithMaxLodgers()
    {
        size_t max = 0;
        Flat flatTemp = Flat();
        for (auto& house : houses)
        {
            for (auto& flat : house->getFlats())
            {
                if (flat.getLodgers().size() > max)
                {
                    max = flat.getLodgers().size();
                    flatTemp = flat;
                }
            }
        }
        return flatTemp;
    }
    Lodger getYoungestLodgerInHouse(House* house)
    {
        Lodger lodgerTemp = Lodger();
        int minAge = 130;
        for (auto& flat : house->getFlats())
        {
            for (auto& lodger : flat.getLodgers())
            {
                if (lodger.getAge() < minAge)
                {
                    minAge = lodger.getAge();
                    lodgerTemp = lodger;
                }
            }
        }
        return lodgerTemp;
    }
    Lodger getOlderLodgerInHouse(House* house)
    {
        Lodger lodgerTemp = Lodger();
        int maxAge = 0;
        for (auto& flat : house->getFlats())
        {
            for (auto& lodger : flat.getLodgers())
            {
                if (lodger.getAge() > maxAge)
                {
                    maxAge = lodger.getAge();
                    lodgerTemp = lodger;
                }
            }
        }
        return lodgerTemp;
    }
    Lodger getYoungestLodger()
    {
        Lodger lodgerTemp = Lodger();
        int minAge = 130;
        for (auto& house : houses)
        {
            for (auto& flat : house->getFlats())
            {
                for (auto& lodger : flat.getLodgers())
                {
                    if (lodger.getAge() < minAge)
                    {
                        minAge = lodger.getAge();
                        lodgerTemp = lodger;
                    }
                }
            }
        }
        return lodgerTemp;
    }
    Lodger getOlderLodger()
    {
        Lodger lodgerTemp = Lodger();
        int maxAge = 0;
        for (auto& house : houses)
        {
            for (auto& flat : house->getFlats())
            {
                for (auto& lodger : flat.getLodgers())
                {
                    if (lodger.getAge() > maxAge)
                    {
                        maxAge = lodger.getAge();
                        lodgerTemp = lodger;
                    }
                }
            }
        }
        return lodgerTemp;
    }
    vector<Lodger> getRetiriesFromLodgerInHouse(House* house)
    {
        vector<Lodger> tempLodgers;
        for (auto& flat : house->getFlats())
        {
            for (auto& lodger : flat.getLodgers())
            {
                if (lodger.getType() == LodgerType::retiree)
                {
                    tempLodgers.push_back(lodger);
                }
            }
        }
        return tempLodgers;
    }
    vector<Lodger> getRetiriesFromLodger()
    {
        vector<Lodger> tempLodgers;
        for (auto& house : houses)
        {
            for (auto& flat : house->getFlats())
            {
                for (auto& lodger : flat.getLodgers())
                {
                    if (lodger.getType() == LodgerType::retiree)
                    {
                        tempLodgers.push_back(lodger);
                    }
                }
            }
        }
        return tempLodgers;
    }
    vector<Lodger> getStudentsFromLodgerInHouse(House* house)
    {
        vector<Lodger> tempLodgers;
        for (auto& flat : house->getFlats())
        {
            for (auto& lodger : flat.getLodgers())
            {
                if (lodger.getType() == LodgerType::student)
                {
                    tempLodgers.push_back(lodger);
                }
            }
        }
        return tempLodgers;
    }
    vector<Lodger> getStudentsFromLodger()
    {
        vector<Lodger> tempLodgers;
        for (auto& house : houses)
        {
            for (auto& flat : house->getFlats())
            {
                for (auto& lodger : flat.getLodgers())
                {
                    if (lodger.getType() == LodgerType::student)
                    {
                        tempLodgers.push_back(lodger);
                    }
                }
            }
        }
        return tempLodgers;
    }
    bool removeHouseById(int id)
    {
        int size1 = houses.size();
        auto it = houses.erase(remove_if(houses.begin(), houses.end(),
            [&](auto& house) {return house->getId() == id; }), houses.end()
        );
        int size2 = houses.size();
        if ((size1 - size2) != 0) return true;
        else return false;
    }
    bool removeLodgerById(int id)
    {
        for (auto& house : houses)
        {
            for (auto& flat : house->Flats())
            {
                bool isRemoved = flat->removeLodgerById(id);
                if (isRemoved)
                {
                    return true;
                }
            }
        }
        return false;
    }
    int getHousesMaxId()
    {
        int max = 0;
        for (auto it : houses)if (it->getId() > max)max = it->getId();
        return max;
    }
    int getLodgerMaxId()
    {
        int max = 0;
        for (auto& house : houses)
        {
            for (auto& flat : house->getFlats())
            {
                for (auto& lodger : flat.getLodgers())
                {
                    int id = lodger.getId();
                    if (id > max) max = id;
                }
            }
        }
        return max;
    }
    void sortHousesById()
    {
        sort(houses.begin(), houses.end(), [](auto& house1, auto& house2) {
            return house1->getId() < house2->getId();
            });
    }


private:
    vector<House*> houses;
    vector<Flat*> flats;
    vector<Lodger*> lodgers;
    bool getSortedDirection = true;
};
class Menu
{
public:
    Menu()
    {
        core = new Core();
        core->load();
        Menu::menu();
    }
    ~Menu()
    {
    }
    static const int getValue(string msg)
    {
        while (true)
        {
            cout << msg << ":";
            int a;
            cin >> a;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(32767, '\n');
                system("cls");
            }
            else
            {
                return a;
            }
        }
    }
    static const int getValue(int min, int max, string msg)
    {
        while (true)
        {
            cout << msg << ":";
            int a;
            cin >> a;
            if (cin.fail() || !(a >= min && a <= max))
            {
                cin.clear();
                cin.ignore(32767, '\n');
                system("cls");
            }
            else
            {
                return a;
            }
        }
    }
    void menu()
    {
        int mode = -1;
        while (mode < 0 || mode > 3)
        {
            system("cls");
            cout << "1. Дома" << endl;
            cout << "2. Квартиры" << endl;
            cout << "3. Жильцы" << endl;
            cout << "0. Выход" << endl;
            mode = getItem(0, 3);
            switch (mode)
            {
            case 1:
                menu1();
                break;
            case 2:
                menu2();
                break;
            case 3:
                menu3();
                break;
            case 0:
                core->save();
                return;
                break;
            }
            mode = -1;
        }
    }
    void menu1()
    {
        int mode = -1;
        while (mode < 0 || mode > 4)
        {
            system("cls");
            cout << "1. Вывод" << endl;
            cout << "2. Добавление" << endl;
            cout << "3. Удаление" << endl;
            cout << "4. Редактировать" << endl;
            cout << "0. Назад" << endl;
            mode = getItem(0, 4);
            switch (mode)
            {
            case 1:
                menu11();
                break;
            case 2:
                menu12();
                break;
            case 3:
                menu13();
                break;
            case 4:
                menu14();
                break;
            case 0:
                return;
                break;
            }
            mode = -1;
        }
    }
    void menu11()
    {
        int mode = -1;
        while (mode < 0 || mode > 3)
        {
            system("cls");
            cout << "1. По ID" << endl;
            cout << "2. По номеру дома" << endl;
            cout << "3. По улице" << endl;
            cout << "4. Все дома" << endl;
            cout << "0. Назад" << endl;
            mode = getItem(0, 4);
            switch (mode)
            {
            case 1:
                menu111();
                break;
            case 2:
                menu112();
                break;
            case 3:
                menu113();
                break;
            case 4:
                menu114();
                break;
            case 0:
                return;
                break;
            }
            mode = -1;
        }
    }
    void menu111()
    {
        system("cls");
        core->printMinAllHouses(core->getSortedHousesById());
        system("pause");
    }
    void menu112()
    {
        system("cls");
        core->printMinAllHouses(core->getSortedHousesByNumber());
        system("pause");
    }
    void menu113()
    {
        system("cls");
        core->printMinAllHouses(core->getSortedHousesByStreet());
        system("pause");
    }
    void menu114()
    {
        system("cls");
        core->print();
        system("pause");
    }
    void menu12()
    {
        system("cls");
        int id, number;
        string street;
        id = core->getHousesMaxId() + 1;
        number = number = getValue(1, 1000, "Номер нового дома(1-1000)");
        cout << "Улица:";
        cin >> street;
        core->addHouse(new House(id, number, street));
        system("pause");
    }
    void menu13()
    {
        system("cls");
        int id = getValue("ID дома для удаления");
        auto isComplete = core->removeHouseById(id);
        if (isComplete)
        {
            cout << "Дом с ID " << id << " удалён" << endl;
        }
        else
        {
            cout << "Дом с ID " << id << " не найден" << endl;
        }
        system("pause");
    }
    void menu14()
    {
        system("cls");
        int id = getValue("ID дома для редактирования");
        auto it = core->getHouseById(id);
        if (it != nullptr)
        {
            int number;
            string street;
            number = getValue(1, 1000, "Номер дома(1-1000)");
            cout << "Улица:";
            cin >> street;
            it->setNumber(number);
            it->setStreet(street);
        }
        else
        {
            cout << "Дом с ID " << id << " не найден" << endl;
        }
        core->sortHousesById();
        system("pause");
    }
    void menu2()
    {
        int mode = -1;
        while (mode < 0 || mode > 3)
        {
            system("cls");
            cout << "1. Поиск по данным жильца" << endl;
            cout << "2. Квартира с макс жильцами в доме" << endl;
            cout << "3. Квартира с макс жильцами среди всех домов" << endl;
            cout << "0. Назад" << endl;
            mode = getItem(0, 3);
            switch (mode)
            {
            case 1:
                menu21();
                break;
            case 2:
                menu22();
                break;
            case 3:
                menu23();
                break;
            case 0:
                return;
                break;
            }
            mode = -1;
        }
    }
    void menu21()
    {
        int mode = -1;
        while (mode < 0 || mode > 2)
        {
            system("cls");
            cout << "1. Поиск по имени жильца" << endl;
            cout << "2. Поиск по фамилии жильца" << endl;
            cout << "0. Назад" << endl;
            mode = getItem(0, 2);
            switch (mode)
            {
            case 1:
                menu211();
                break;
            case 2:
                menu212();
                break;
            case 0:
                return;
                break;
            }
            mode = -1;
        }
    }
    void menu211()
    {
        system("cls");
        string name;
        cout << "Имя жильца:";
        cin >> name;
        auto flats = core->getFlatsByLodgerName(name);
        if (!flats.empty())
        {
            for (auto it : flats)
            {
                it.print();
            }
        }
        else
        {
            cout << "Квартир с этим жильцом не найдено" << endl;
        }
        system("pause");
    }
    void menu212()
    {
        system("cls");
        string surname;
        cout << "Фамилия жильца:";
        cin >> surname;
        auto flats = core->getFlatsByLodgerSurname(surname);
        if (!flats.empty())
        {
            for (auto it : flats)
            {
                it.print();
            }
        }
        else
        {
            cout << "Квартир с этим жильцом не найдено" << endl;
        }
        system("pause");
    }
    void menu22()
    {
        system("cls");
        int houseNumber = getValue("Номер дома");
        auto house = core->getHouseByNumber(houseNumber);
        if (house == nullptr)
        {
            cout << "Дома с таким номером нет" << endl;
        }
        else if (house->getFlats().empty())
        {
            cout << "Этот дом не имеет квартир" << endl;
        }
        else
        {
            core->getFlatWithMaxLodgersInHouse(house).print();
        }
        system("pause");
    }
    void menu23()
    {
        system("cls");
        cout << "Квартира с самым большим кол-ом жильцов:" << endl;
        core->getFlatWithMaxLodgers().print();
        system("pause");
    }
    void menu3()
    {
        int mode = -1;
        while (mode < 0 || mode > 7)
        {
            system("cls");
            cout << "1. Самый юный жилец" << endl;
            cout << "2. Самый пожилой жилец" << endl;
            cout << "3. Поиск студентов" << endl;
            cout << "4. Поиск пенсионеров" << endl;
            cout << "5. Редактировать" << endl;
            cout << "6. Удалить" << endl;
            cout << "7. Добавить" << endl;
            cout << "0. Назад" << endl;
            mode = getItem(0, 7);
            switch (mode)
            {
            case 1:
                menu31();
                break;
            case 2:
                menu32();
                break;
            case 3:
                menu33();
                break;
            case 4:
                menu34();
                break;
            case 5:
                menu35();
                break;
            case 6:
                menu36();
                break;
            case 7:
                menu37();
                break;
            case 0:
                return;
                break;
            }
            mode = -1;
        }
    }
    void menu31()
    {
        int mode = -1;
        while (mode < 0 || mode > 2)
        {
            system("cls");
            cout << "1. По всем домам" << endl;
            cout << "2. В доме" << endl;
            cout << "0. Назад" << endl;
            mode = getItem(0, 2);
            switch (mode)
            {
            case 1:
                menu311();
                break;
            case 2:
                menu312();
                break;
            case 0:
                return;
                break;
            }
            mode = -1;
        }
    }
    void menu32()
    {
        int mode = -1;
        while (mode < 0 || mode > 2)
        {
            system("cls");
            cout << "1. По всем домам" << endl;
            cout << "2. В доме" << endl;
            cout << "0. Назад" << endl;
            mode = getItem(0, 2);
            switch (mode)
            {
            case 1:
                menu321();
                break;
            case 2:
                menu322();
                break;
            case 0:
                return;
                break;
            }
            mode = -1;
        }
    }
    void menu33()
    {
        int mode = -1;
        while (mode < 0 || mode > 2)
        {
            system("cls");
            cout << "1. По всем домам" << endl;
            cout << "2. В доме" << endl;
            cout << "0. Назад" << endl;
            mode = getItem(0, 2);
            switch (mode)
            {
            case 1:
                menu331();
                break;
            case 2:
                menu332();
                break;
            case 0:
                return;
                break;
            }
            mode = -1;
        }
    }
    void menu34()
    {
        int mode = -1;
        while (mode < 0 || mode > 2)
        {
            system("cls");
            cout << "1. По всем домам" << endl;
            cout << "2. В доме" << endl;
            cout << "0. Назад" << endl;
            mode = getItem(0, 2);
            switch (mode)
            {
            case 1:
                menu341();
                break;
            case 2:
                menu342();
                break;
            case 0:
                return;
                break;
            }
            mode = -1;
        }
    }
    void menu35()
    {
        system("cls");
        int id = getValue("ID жильца для редактирования");
        auto lodgerPtr = core->getLodgerById(id);
        if (lodgerPtr != nullptr)
        {
            string name;
            string surname;
            int age;
            int type;
            cout << "Имя:";
            cin >> name;
            cout << "Фамилия:";
            cin >> surname;
            age = getValue(0, 150, "Возраст");
            type = getValue(0, 3, "Род занятий:\n"
                "0. Безработный\n"
                "1. Работает\n"
                "2. Студент\n"
                "3. Пенсионер\n");
            lodgerPtr->setName(name);
            lodgerPtr->setSurname(surname);
            lodgerPtr->setAge(age);
            lodgerPtr->setType(static_cast<LodgerType>(type));
        }
        else
        {
            cout << "Такого жильца не найдено" << endl;
        }
        system("pause");
    }
    void menu36()
    {
        system("cls");
        int id = getValue("ID жильца для удаления");
        auto isRemoved = core->removeLodgerById(id);
        if (isRemoved)
        {
            cout << "Такого жильца не найдено" << endl;
        }
        else
        {
            cout << "Такой жилец не найден:" << endl;
        }
        system("pause");
    }
    void menu37()
    {
        system("cls");
        int idHouse, idFlat;
        idHouse = getValue("ID дома");
        idFlat = getValue("ID квартиры");
        auto flatTemp = core->getFlat(idHouse, idFlat);
        if (flatTemp != nullptr)
        {
            int id;
            string name;
            string surname;
            int age;
            int type;
            id = core->getLodgerMaxId() + 1;
            cout << "Имя:";
            cin >> name;
            cout << "Фамилия:";
            cin >> surname;
            age = getValue(0, 150, "Возраст");
            type = getValue(0, 3, "Род занятий:\n"
                "0. Безработный\n"
                "1. Работает\n"
                "2. Студент\n"
                "3. Пенсионер\n");
            flatTemp->addLodger(new Lodger(id, name, surname, age, static_cast<LodgerType>(type)));
        }
        else
        {
            cout << "Такого дома или квартиры не найдено" << endl;
        }
        system("pause");
    }
    void menu311()
    {
        system("cls");
        cout << "Самый юный жилец по всем домам:" << endl;
        core->getYoungestLodger().print();
        system("pause");
    }
    void menu312()
    {
        system("cls");
        int houseNumber = getValue("Номер дома");
        auto house = core->getHouseByNumber(houseNumber);
        if (house == nullptr)
        {
            cout << "Дома с таким номером нет" << endl;
        }
        else if (house->getFlats().empty())
        {
            cout << "Этот дом не имеет квартир" << endl;
        }
        else
        {
            cout << "Самый юный жилец в доме:" << endl;
            core->getYoungestLodgerInHouse(house).print();
        }
        system("pause");
    }
    void menu321()
    {
        system("cls");
        cout << "Самый пожилой жилец по всем домам:" << endl;
        core->getOlderLodger().print();
        system("pause");
    }
    void menu322()
    {
        system("cls");
        int houseNumber = getValue("Номер дома");
        auto house = core->getHouseByNumber(houseNumber);
        if (house == nullptr)
        {
            cout << "Дома с таким номером нет" << endl;
        }
        else if (house->getFlats().empty())
        {
            cout << "Этот дом не имеет квартир" << endl;
        }
        else
        {
            cout << "Самый юный жилец в доме:" << endl;
            core->getOlderLodgerInHouse(house).print();
        }
        system("pause");
    }
    void menu331()
    {
        system("cls");
        auto lodgers = core->getStudentsFromLodger();
        if (!lodgers.empty())
        {
            cout << "Студенты со всех домов:" << endl;
            for (auto lodger : lodgers)
            {
                lodger.print();
            }
        }
        else
        {
            cout << "Студентов не найдено" << endl;
        }
        system("pause");
    }
    void menu332()
    {
        system("cls");
        int houseNumber = getValue("Номер дома");
        auto house = core->getHouseByNumber(houseNumber);
        if (house == nullptr)
        {
            cout << "Дома с таким номером нет" << endl;
        }
        else if (house->getFlats().empty())
        {
            cout << "Этот дом не имеет квартир" << endl;
        }
        else
        {
            auto students = core->getStudentsFromLodgerInHouse(house);
            if (!students.empty())
            {
                cout << "Студенты в доме №" << house->getNumber() << endl;
                for (auto student : students)
                {
                    student.print();
                }
            }
            else
            {
                cout << "Студентов нет в доме №" << house->getNumber() << endl;
            }
        }
        system("pause");
    }
    void menu341()
    {
        system("cls");
        auto lodgers = core->getRetiriesFromLodger();
        if (!lodgers.empty())
        {
            cout << "Пенсионеры со всех домов:" << endl;
            for (auto lodger : lodgers)
            {
                lodger.print();
            }
        }
        else
        {
            cout << "Пенсионеров не найдено" << endl;
        }
        system("pause");
    }
    void menu342()
    {
        system("cls");
        int houseNumber = getValue("Номер дома");
        auto house = core->getHouseByNumber(houseNumber);
        if (house == nullptr)
        {
            cout << "Дома с таким номером нет" << endl;
        }
        else if (house->getFlats().empty())
        {
            cout << "Этот дом не имеет квартир" << endl;
        }
        else
        {
            auto lodgers = core->getRetiriesFromLodgerInHouse(house);
            if (!lodgers.empty())
            {
                cout << "Пенсионеры в доме №" << house->getNumber() << endl;
                for (auto retiree : lodgers)
                {
                    retiree.print();
                }
            }
            else
            {
                cout << "Пенсионеров нет в доме №" << house->getNumber() << endl;
            }
        }
        system("pause");
    }
private:
    Core* core;
};
int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    auto menu = new Menu();
}

#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <vector>
#include "TaskManager.h"

using namespace std;
using namespace std::chrono;

system_clock::time_point readDueDate() {
    cout << "Įveskite terminą (YYYY-MM-DD HH:MM): ";
    string line;
    getline(cin, line);
    std::tm tm = {};
    std::istringstream ss(line);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
    if (ss.fail()) {
        cout << "Neteisingas formatas, nustatytas dabartinis laikas.\n";
        return system_clock::now();
    }
    return system_clock::from_time_t(std::mktime(&tm));
}

void printTask(const Task& t) {
    time_t tt = system_clock::to_time_t(t.dueDate);
    std::tm* lt = std::localtime(&tt);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", lt);
    cout << t.id
         << ". [" << (t.completed ? "X" : " ") << "] "
         << t.title << " (terminas: " << buf << ")\n"
         << "   " << t.description << "\n";
}

int main() {
    TaskManager mgr("tasks.json");
    bool running = true;

    while (running) {
        cout << "\n=== Užduočių valdymas ===\n"
             << "1. Sukurti naują užduotį\n"
             << "2. Peržiūrėti visas užduotis\n"
             << "3. Pažymėti užduotį kaip atliktą\n"
             << "4. Ištrinti užduotį\n"
             << "5. Išeiti\n"
             << "Pasirinkimas: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            cout << "Pavadinimas: ";
            string title; getline(cin, title);
            cout << "Aprašymas: ";
            string desc; getline(cin, desc);
            auto due = readDueDate();
            Task t = mgr.addTask(title, desc, due);
            cout << "Užduotis sukurta (ID=" << t.id << ").\n";

        } else if (choice == "2") {
            cout << "Rikiuoti pagal terminą? (t/N): ";
            string r; getline(cin, r);
            if (r == "t" || r == "T") mgr.sortByDueDate();

            cout << "Paieškos raktinis žodis (palikti tuščią – visas): ";
            string term; getline(cin, term);
            vector<Task> list = term.empty()
                ? mgr.listAll()
                : mgr.searchByTitle(term);

            if (list.empty()) {
                cout << "Nerasta jokių užduočių.\n";
            } else {
                for (auto& t : list) printTask(t);
            }

        } else if (choice == "3") {
            cout << "Įveskite užduoties ID: ";
            string id; getline(cin, id);
            int iid = stoi(id);
            if (mgr.markCompleted(iid))
                cout << "Užduotis pažymėta kaip atlikta.\n";
            else
                cout << "Užduotis su tokiu ID nerasta.\n";

        } else if (choice == "4") {
            cout << "Įveskite užduoties ID: ";
            string id; getline(cin, id);
            int iid = stoi(id);
            if (mgr.deleteById(iid))
                cout << "Užduotis ištrinta.\n";
            else
                cout << "Užduotis su tokiu ID nerasta.\n";

        } else if (choice == "5") {
            running = false;

        } else {
            cout << "Neteisingas pasirinkimas, pamėginkite dar kartą.\n";
        }

        mgr.save();
    }

    cout << "Programa baigė darbą.\n";
    return 0;
}

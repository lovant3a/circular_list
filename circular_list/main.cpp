#include <iostream>
#include <deque>
#include <string>
#include <limits>
#include <locale.h>
#include "circular_list.h"

using namespace std;

void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    deque<CircularList<int>> lists;
    int activeIdx = -1;
    int choice = 0;

    setlocale(LC_ALL, "Russian.UTF8");

    while (true) {
        cout << "всего списков: " << lists.size() << "\n";

        if (activeIdx >= 0 && activeIdx < (int)lists.size()) {
            cout << "активный список: [" << activeIdx << "]\n";
            cout << lists[activeIdx] << "\n";
        }
        else {
            cout << "активный список НЕ ВЫБРАН\n";
        }

        cout << "  1. создать новый пустой список (и выбрать его)\n";
        cout << "  2. выбрать существующий список по индексу\n";
        cout << "  3. вставить значение ДО текущего элемента (копия)\n";
        cout << "  4. вставить значение ПОСЛЕ текущего элемента (копия)\n";
        cout << "  5. удалить текущий элемент\n";
        cout << "  6. перейти к следующему элементу (>>)\n";
        cout << "  7. перейти к предыдущему элементу (<<)\n";
        cout << "  8. показать значение текущего элемента\n";
        cout << "  9. вывести весь список на экран\n";
        cout << " 10. создать копию текущего списка\n";             
        cout << "  0. выход из программы\n";
        cout << "выберите команду: ";

        if (!(cin >> choice)) {
            clearCin();
            cout << "ошибка: введите число от 0 до 10.\n";          
            continue;
        }

        try {
            if (choice >= 3 && choice <= 10 && activeIdx == -1) {   
                cout << "сначала создайте или выберите список\n";
                continue;
            }

            switch (choice) {
            case 1: {
                lists.emplace_back();
                activeIdx = lists.size() - 1;
                cout << "создан список [" << activeIdx << "]\n";
                break;
            }
            case 2: {
                if (lists.empty()) {
                    cout << "списков пока нет\n";
                    continue;
                }
                cout << "доступные списки: 0.." << lists.size() - 1 << "\n";
                cout << "выберите список: ";
                int idx;
                if (!(cin >> idx) || idx < 0 || idx >= (int)lists.size()) {
                    clearCin();
                    cout << "неверный индекс\n";
                }
                else {
                    activeIdx = idx;
                    cout << "выбран список [" << activeIdx << "]\n";
                }
                break;
            }
            case 3: {
                cout << "введите целое число для вставки (ДО): ";
                int val;
                if (!(cin >> val)) { clearCin(); throw ListException(103); }
                lists[activeIdx].insert_before(val);
                cout << "вставлено " << val << " перед текущим элементом\n";
                break;
            }
            case 4: {
                cout << "введите целое число для вставки (ПОСЛЕ): ";
                int val;
                if (!(cin >> val)) { clearCin(); throw ListException(103); }
                lists[activeIdx].insert_after(val);
                cout << "вставлено " << val << " после текущего элемента\n";
                break;
            }
            case 5: {
                lists[activeIdx].remove_current();
                cout << "текущий элемент удалён\n";
                break;
            }
            case 6: {
                lists[activeIdx].next();
                cout << "переход к следующему элементу\n";
                break;
            }
            case 7: {
                lists[activeIdx].prev();
                cout << "переход к предыдущему элементу\n";
                break;
            }
            case 8: {
                cout << "значение текущего элемента: " << *(lists[activeIdx].get()) << "\n";
                break;
            }
            case 9: {
                cout << "содержимое списка [" << activeIdx << "]:\n";
                cout << lists[activeIdx] << "\n";
                break;
            }
            case 10: {                                               
                if (lists[activeIdx].empty()) {
                    cout << "список пуст, копировать нечего\n";
                }
                else {
                    lists.push_back(lists[activeIdx].clone());
                    activeIdx = lists.size() - 1;
                    cout << "копия создана и выбрана как список [" << activeIdx << "]\n";
                }
                break;
            }
            case 0: {
                cout << "завершение работы\n";
                return 0;
            }
            default:
                cout << "неизвестная команда\n";
            }
        }
        catch (const ListException& e) {
            cerr << "\nОШИБКА СПИСКА (код " << e.getCode() << "): " << e.what() << "\n";
        }
        catch (const exception& e) {
            cerr << "\nОШИБКА: " << e.what() << "\n";
        }
    }

    return 0;
}

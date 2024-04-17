#include <iostream>
#include <windows.h>

using namespace std;

const int WIDTH = 20; // Szerokość pola tekstowego
const int HEIGHT = 1; // Wysokość pola tekstowego

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setConsoleColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawTextField(int x, int y, int width, int height) {
    gotoxy(x, y);
    cout << char(201); // lewy górny róg

    for (int i = 0; i < width - 2; ++i)
        cout << char(205); // poziome linie

    cout << char(187); // prawy górny róg
    gotoxy(x, y + 1);

    for (int i = 0; i < height; ++i) {
        cout << char(186); // pionowe linie
        for (int j = 0; j < width - 2; ++j)
            cout << ' '; // wypełnienie
        cout << char(186) << endl; // pionowe linie
        gotoxy(x, y + i + 2);
    }

    cout << char(200); // lewy dolny róg
    for (int i = 0; i < width - 2; ++i)
        cout << char(205); // poziome linie
    cout << char(188); // prawy dolny róg
}

void moveCursorLeft(int& cursorX) {
    if (cursorX > 0)
        cursorX--;
}

void moveCursorRight(int& cursorX, int textLength, int fieldWidth) {
    if (cursorX < textLength && cursorX < fieldWidth - 3) // -3 bo musimy zachować miejsce na prawy obramowanie
        cursorX++;
}

int main() {
    int cursorX = 0;
    int fieldX = 5;
    int fieldY = 5;
    char input;
    string text = "";

    // Ustawienie koloru
    setConsoleColor(15); // Biały tekst na czarnym tle

    // Narysowanie pola tekstowego
    drawTextField(fieldX, fieldY, WIDTH, HEIGHT);

    gotoxy(fieldX + 1, fieldY + 1);

    while (true) {
        input = cin.get();

        if (input == 27) // ESC - wyjście z programu
            break;
        else if (input == 13) // Enter - zakończ wprowadzanie tekstu
            break;
        else if (input == 8 && !text.empty() && cursorX > 0) { // Backspace - usuń ostatni znak
            text.erase(cursorX - 1, 1);
            cursorX--;
            gotoxy(fieldX + 1, fieldY + 1);
            cout << text << ' ';
            gotoxy(fieldX + 1 + cursorX, fieldY + 1);
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // lewa strzałka
            moveCursorLeft(cursorX);
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // prawa strzałka
            moveCursorRight(cursorX, text.length(), WIDTH);
        }
        else if (text.length() < WIDTH - 2 && cursorX < WIDTH - 3) { // Sprawdź czy długość tekstu nie przekracza szerokości pola, a kursor nie jest na skraju
            text.insert(cursorX, 1, input);
            cout << input;
            cursorX++;
        }
    }

    return 0;
}

















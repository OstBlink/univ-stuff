#include <iostream>

int main() {
    short x, a, y1, y2, y;
    setlocale(LC_ALL, "ru");

    std::cout << "Введите значение x: ";
    std::cin >> x;
    std::cout << "Введите значение a: ";
    std::cin >> a;

    __asm {
        mov ax, x            // Загружаем x в ax
        cmp ax, 4            // Сравниваем x с 4
        jg GreaterThan4      // Если |x| > 4, переходим к GreaterThan4

        // Если |x| <= 4
        mov bx, a            // Загружаем a в bx
        add bx, 4            // bx = a + 4
        mov y1, bx           // y1 = 4 + a
        jmp EndY1            // Переход к EndY1

    GreaterThan4:
        shl ax, 1            // y1 = 2 * x (умножаем x на 2)
        mov y1, ax           // Сохраняем результат в y1

    EndY1:
        mov ax, x            // Загружаем x в ax
        cmp ax, a            // Сравниваем x с a
        jl LessThanA         // Если x < a, переходим к LessThanA

        // Если x >= a
        mov y2, ax           // y2 = x
        jmp EndY2            // Переход к EndY2

    LessThanA:
        mov bx, a            // Загружаем a в bx
        sub bx, x            // y2 = a - x
        mov y2, bx           // Сохраняем результат в y2

    EndY2:
        mov ax, y1           // Загружаем y1 в ax
        add ax, y2           // y = y1 + y2
        mov y, ax            // Сохраняем результат в y
    }

    std::cout << "y = " << y << std::endl;

    return 0;
}
/* Алгоритм токенизации чисел из произвольной входной строки. Придуман с нуля и работает без strtok ;)   */
/* Программа выводит все числа, а через перевод строки - первое из них с максимальным количеством чисел. */

#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>


void print_substring(char* string, int start, int len)
{
    for (int i = start; i < start+len; i++)
        putchar(string[i]);
    puts(""); /* новая строка */
}

int main(void)
{
    /* токены это срезы (подстроки) строки */
    int result_start = -1; /* -1 для обработки возможно пустой строки */
    int result_len = 0;

    /* ввод */
    char input[81];
    fgets(input, sizeof(input), stdin); /* fgets помещает '\n' в конец строки, а дальше '\0' */

    int tok = 0; /* внутри ли токена мы? т.е. обработана ли первая цифра токена? (0 - нет, 1 - да) */
    int tok_start, tok_len; /* токен - это начальный индекс в строке и длина */

    char c; /* текущий символ строки */
    for (int i = 0; i < 81; i++)
    {
        c = input[i];

        if (!isdigit(c)) /* (*) */
        {
            /* сейчас надо определить, является символ на предыдущей итерации концом токена */
            if (tok == 1) /* если да */
            {
                tok = 0; /* отмечаем, что мы снаружи токена */

                print_substring(input, tok_start, tok_len); /* печатаем наш токен */

                /* а сейчас надо сравнить длину нашего токена с длиной результата */
                /* (результат это токен с максимальной длиной по завершению алгоритма) */

                /* если длина текущего токена больше максимальной известной на данный момент длины */
                if (tok_len > result_len) /* (**) */
                {
                    /* result_start в самом начале равен -1, это означает, что */
                    /* -1 так и останется -1, если if выше (**) не сработает ни разу, что м.б. */
                    /* только если токенов во входной строке нет вовсе */
                    /* т.е. tok всегда был равен 0 => if (tok == 1) не выполнится никогда */
                    result_start = tok_start;

                    /* result_len в самом начале равен 0, значит, на первой итерации (**) выполнится */
                    /* если токен найден (минимальная длина токена - 1) */
                    result_len = tok_len;
                }
            }

            /* условие остановки цикла */
            if (c == '\0')
                break;

            continue; /* пропускаем всё, что не явл. цифрой */
        }

        /* если мы дошли до этого места, то была найдена цифра */
        /* но не факт, что она первая - мы можем находиться внутри токена */

        /* если мы пока что не внутри токена */
        if (tok == 0)
        {
            tok = 1; /* то мы внутри токена сейчас */ 
            tok_start = i; /* i является стартовым индексом токена */
            tok_len = 0; /* а длину токена мы будем в будущем инкрементировать на каждой итерации */
        }

        tok_len++; /* собственно, инкремент */
    }

    if (result_start != -1) /* если токен найден */
    {
        puts("");
        print_substring(input, result_start, result_len);
    }
}

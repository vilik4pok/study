#include <stdio.h>
#include <WinSock2.h>

//используемые структуры для tcp modbus, для удобного представления и работы с пакетом
struct modbus {
    unsigned short transaction_id, protocol_id, length;
    unsigned char unit_id;
};

struct package {
    struct modbus mbus;
    char data[MAXBYTE - sizeof(struct modbus)];
};

struct sum {
    int x, y;
};

//фунция для формирование ответа сервера на команду пинг
void onPing(struct package* pack)
{
    strcpy((char*)pack->data, (char*)"Server is working!");
    pack->mbus.length = strlen((char*)pack->data) + 2;
}

//фунция для формирование ответа сервера на команду приветствие
void onGreeting(struct package* pack)
{
    char str[sizeof(pack->data)];
    unsigned newLen = (unsigned)(pack->mbus.length + 6) < sizeof(str) ? (unsigned)pack->mbus.length + 6 : sizeof(str) - 1;
    snprintf((char*)&str, newLen, "Hello, %s", pack->data);
    snprintf((char*)pack->data, newLen, "%s", str);
    pack->mbus.length = strlen((char*)pack->data) + 2;
}

//фунция для формирование ответа сервера на команду, сложи 2 числа
void onSum(struct package* pack)
{
    struct sum sum;
    memcpy((void*)&sum, (void*)pack->data, pack->mbus.length-1);
    int result = sum.x + sum.y;
    memcpy((void*)pack->data, (void*)&result, sizeof(int));
    pack->mbus.length = sizeof(int) + 1;
}

int main(){
    // Инициализируем DLL
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);
    // Создаем сокет
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    // Привязываем сокет
    sockaddr_in sockAddr;
    memset (& sockAddr, 0, sizeof (sockAddr)); // Каждый байт заполняется 0
    sockAddr.sin_family = PF_INET; // Использовать IPv4-адрес
    sockAddr.sin_addr.s_addr = inet_addr ("0.0.0.0"); // Определенный IP-адрес
    sockAddr.sin_port = htons (502); // Порт
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    // Входим в состояние мониторинга
    listen(servSock, 20);
    SOCKADDR clntAddr;
    SOCKET clntSock;
    int nSize;
    struct package package;

    while(1){
        nSize = sizeof(SOCKADDR);
        clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
        // Получение клиентского запроса
        recv(clntSock, (char*)&package, MAXBYTE, NULL);
        switch(package.mbus.unit_id)
        {
            case 65: onPing(&package); break;
            case 66: onGreeting(&package); break;
            case 67: onSum(&package); break;
        }
        // Отправляем данные клиенту
        send(clntSock, (char*)&package, sizeof(struct modbus) + package.mbus.length - 1, NULL);
    }
    // Закрываем сокеты
    closesocket(clntSock);
    closesocket(servSock);
    // Прекращаем использование DLL
    WSACleanup();
    return 0;
}

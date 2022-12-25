#include <WinSock2.h>
#define WIN32
#ifdef WIN32
#include <windows.h>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "hidapi.h"
#include <stdint.h>
#define MAX_STR 255
#include <locale.h>
#include <string.h>
#include <wchar.h>

//используемые структуры для tcp modbus, для удобного представления и работы с пакетом
struct modbus {
    unsigned short transaction_id, protocol_id, length;
    unsigned char unit_id;
};

struct package {
    struct modbus mbus;
    char data[MAXBYTE - sizeof(struct modbus)];
};

struct color {
    short red, green, blue;
};

//фунция для формирование ответа сервера на команду пинг
void onPing(struct package* pack)
{
    strcpy((char*)pack->data, (char*)"Server is working!");
    pack->mbus.length = strlen((char*)pack->data) + 2;
}

void onFill(unsigned char* buf, hid_device *handle, struct package* pack)
{
    int res;
    buf[0]=0x04;
    buf[3]=pack->data[0];
    for (int i=0;i<128;i++)
    {
        for (int j=0;j<64;j++)
        {
            buf[1]=i;
            buf[2]=j;
            res = hid_send_feature_report(handle,buf,4);
            if (res < 0)
            {
                strcpy((char*)pack->data, (char*)"Error!");
                pack->mbus.length = strlen("Error!") + 2;
                return;
            }
        }
    }
    strcpy((char*)pack->data, (char*)"Screen is filled!");
    pack->mbus.length = strlen("Screen is filled!") + 2;
}

void onColor(unsigned char* buf,hid_device *handle, struct package* pack){

    int res;
    buf[0]=0x02;//формируем команду для изменения яркости светодиода
    memcpy((void*)(buf+1), (void*)pack->data, sizeof(struct color));
    res = hid_send_feature_report(handle,buf,7);
    if (res < 0)
    {
        strcpy((char*)pack->data, (char*)"Error!");
        pack->mbus.length = strlen("Error!") + 2;
    }
    else
    {
        strcpy((char*)pack->data, (char*)"Color is definded!");
        pack->mbus.length = strlen("Color is definded!") + 2;
    }
}

void resistorState(unsigned char* buf,hid_device *handle, struct package* pack)
{
    int res;
    buf[0] = 0x3; //состояние резистора
    res = hid_get_feature_report(handle, buf, sizeof(buf));
    if (res < 0)
    {
        strcpy((char*)pack->data, (char*)"Error!");
        pack->mbus.length = strlen("Error!") + 2;
    }
    else
    {
        memcpy((void*)pack->data, (void*)(buf+1), sizeof(short));
        pack->mbus.length = sizeof(short) + 1;
    }
}
int main(int argc, char* argv[]){
    // Инициализируем DLL
    (void)argc;
    (void)argv;
    if (hid_init())
		return -1;
	int res, i;
	unsigned char buf[256];
	hid_device *handle;
	handle = hid_open(0x1234, 0x0001, NULL);
	if (!handle) {
		printf("unable to open device\n");
 		return 1;
	}
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
            case 66: onColor(buf, handle, &package); break;
            case 67: onFill(buf, handle, &package); break;
            case 68: resistorState(buf, handle, &package); break;
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

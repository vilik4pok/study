#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <malloc.h>

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

//функция для формаирования стандартого пакета
struct package* getPackage(unsigned char unit_id)
{
    struct package* pack = (struct package*)malloc(sizeof(struct package));
    pack->mbus.length = 1;
    pack->mbus.unit_id = unit_id;
    pack->mbus.transaction_id = pack->mbus.protocol_id = 0;
    return pack;
}

//функция для формаирования пакета пинга
void ping(SOCKET sock)
{
    struct package* sendpackage = getPackage(65), recvpackage;

    send(sock, (char*)sendpackage, sizeof(modbus) + sendpackage->mbus.length - 1, NULL);
    int sendresult = recv(sock, (char*)&recvpackage, MAXBYTE, NULL);

    if(sendresult != -1)
        printf("Message form server: %s\n", recvpackage.data);
    else
        printf("timeout\n");
    free(sendpackage);
}

struct color* readColors()
{
    struct color* colors = (struct color*)malloc(sizeof(struct color));
    printf("Enter red: ");
    scanf("%hd", &colors->red);
    printf("Enter green: ");
    scanf("%hd", &colors->blue);
    printf("Enter blue: ");
    scanf("%hd", &colors->green);
    return colors;
}

void fillScreen(SOCKET sock, char color)
{
    struct package* sendpackage = getPackage(67), recvpackage;
    sendpackage->data[0] = color;
    sendpackage->mbus.length = 2;
    send(sock, (char*)sendpackage, sizeof(struct modbus) + sendpackage->mbus.length - 1, NULL);
    int sendresult = recv(sock, (char*)&recvpackage, MAXBYTE, NULL);

    if(sendresult != -1)
        printf("Message form server: %s\n", recvpackage.data);
    else
        printf("timeout\n");
    free(sendpackage);
}

void sendColors(SOCKET sock)
{
    struct package* sendpackage = getPackage(66), recvpackage;
    //memset(sendpackage->data, 0, MAXBYTE - sizeof(struct modbus));
    struct color* colors = readColors();

    memcpy((void*)sendpackage->data, (void*)colors, sizeof(struct color));
    sendpackage->mbus.length = sizeof(struct color) + 1;
    send(sock, (char*)sendpackage, sizeof(struct modbus) + sendpackage->mbus.length - 1, NULL);
    int sendresult = recv(sock, (char*)&recvpackage, MAXBYTE, NULL);

    if(sendresult != -1)
        printf("Message form server: %s\n", recvpackage.data);
    else
        printf("timeout\n");
    free(sendpackage);
    free(colors);
}

void getResistorState(SOCKET sock)
{
    struct package* sendpackage = getPackage(68), recvpackage;
    //memset(sendpackage->data, 0, MAXBYTE - sizeof(struct modbus));

    send(sock, (char*)sendpackage, sizeof(struct modbus) + sendpackage->mbus.length - 1, NULL);
    int sendresult = recv(sock, (char*)&recvpackage, MAXBYTE, NULL);

    if(sendresult != -1)
        printf("Message form server: %hd\n", *((short*)recvpackage.data));
    else
        printf("timeout\n");
    free(sendpackage);
}
//функция создания сокета
SOCKET getSocket()
{
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
     // Инициируем запрос к серверу
    sockaddr_in sockAddr;
    memset (& sockAddr, 0, sizeof (sockAddr)); // Каждый байт заполняется 0
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //127.0.0.1
    sockAddr.sin_port = htons(502);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    return sock;
}

int main(){
     // Инициализируем DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    int _continue = 1, chose = 0;
    SOCKET sock;
    while(_continue)
    {
        sock = getSocket();
        system("cls");
        printf("%s\n%s\n%s\n%s\n%s\n","1. Ping", "2. Color", "3. Fill screen", "4. Resistor state", "5. Close");
        scanf("%d",&chose);
        switch(chose)
        {
            case 1: ping(sock); break;
            case 2: sendColors(sock); break;
            case 3:
                printf("%s\n%s\n","1. Black", "2. Blue");
                scanf("%d", &chose);
                switch(chose)
                {
                    case 1 : fillScreen(sock, 0); break;
                    case 2 : fillScreen(sock, 1); break;
                    default: break;
                };
                break;
            case 4: getResistorState(sock); break;
            case 5: _continue = 0; break;
        }
        fflush(stdin);
        system("pause");
    }
    //закрытие сокета
    closesocket(sock);
    // Прекращаем использование DLL
    WSACleanup();
    return 0;
}

#include <stdio.h>
#include <WinSock2.h>

//������������ ��������� ��� tcp modbus, ��� �������� ������������� � ������ � �������
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

//������ ��� ������������ ������ ������� �� ������� ����
void onPing(struct package* pack)
{
    strcpy((char*)pack->data, (char*)"Server is working!");
    pack->mbus.length = strlen((char*)pack->data) + 2;
}

//������ ��� ������������ ������ ������� �� ������� �����������
void onGreeting(struct package* pack)
{
    char str[sizeof(pack->data)];
    unsigned newLen = (unsigned)(pack->mbus.length + 6) < sizeof(str) ? (unsigned)pack->mbus.length + 6 : sizeof(str) - 1;
    snprintf((char*)&str, newLen, "Hello, %s", pack->data);
    snprintf((char*)pack->data, newLen, "%s", str);
    pack->mbus.length = strlen((char*)pack->data) + 2;
}

//������ ��� ������������ ������ ������� �� �������, ����� 2 �����
void onSum(struct package* pack)
{
    struct sum sum;
    memcpy((void*)&sum, (void*)pack->data, pack->mbus.length-1);
    int result = sum.x + sum.y;
    memcpy((void*)pack->data, (void*)&result, sizeof(int));
    pack->mbus.length = sizeof(int) + 1;
}

int main(){
    // �������������� DLL
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);
    // ������� �����
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    // ����������� �����
    sockaddr_in sockAddr;
    memset (& sockAddr, 0, sizeof (sockAddr)); // ������ ���� ����������� 0
    sockAddr.sin_family = PF_INET; // ������������ IPv4-�����
    sockAddr.sin_addr.s_addr = inet_addr ("0.0.0.0"); // ������������ IP-�����
    sockAddr.sin_port = htons (502); // ����
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    // ������ � ��������� �����������
    listen(servSock, 20);
    SOCKADDR clntAddr;
    SOCKET clntSock;
    int nSize;
    struct package package;

    while(1){
        nSize = sizeof(SOCKADDR);
        clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
        // ��������� ����������� �������
        recv(clntSock, (char*)&package, MAXBYTE, NULL);
        switch(package.mbus.unit_id)
        {
            case 65: onPing(&package); break;
            case 66: onGreeting(&package); break;
            case 67: onSum(&package); break;
        }
        // ���������� ������ �������
        send(clntSock, (char*)&package, sizeof(struct modbus) + package.mbus.length - 1, NULL);
    }
    // ��������� ������
    closesocket(clntSock);
    closesocket(servSock);
    // ���������� ������������� DLL
    WSACleanup();
    return 0;
}

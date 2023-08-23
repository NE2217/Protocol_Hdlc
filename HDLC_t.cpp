#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h> 
#include <stdint.h>
#include <iostream>
#include "HDLC_PROTOCOL.h"

using namespace std;

void* A[3];

uint8_t pack_b[100], buf[100] = {NULL};
uint8_t buf_test[] = {0x7E, 0xA0, 0x23, 0x00, 0x02, 0x44, 0xC9,
0x61, 0x93, 0x44, 0x0B, 0x81, 0x80, 0x14, 0x05, 0x02,
0x04, 0x00, 0x06, 0x02, 0x04, 0x00, 0x07, 0x04, 0x00, 0x00, 0x00, 0x01, 0x08,
0x04, 0x00, 0x00, 0x00, 0x01, 0x72, 0xE3, 0x7E};
uint8_t buf_test_1[] = { 0x7E, 0xA0, 0x23, 0x61, 0x00, 0x02, 0x44, 0xC9,
0x73, 0xD9, 0xB6, 0x81, 0x80, 0x14, 0x05, 0x02, 0x04, 0x00, 0x06, 0x02, 0x04, 0x00, 0x07, 0x04,
0x00, 0x00, 0x00, 0x01, 0x08, 0x04, 0x00, 0x00, 0x00, 0x01, 0x72, 0xE3, 0x7E};
uint8_t buf_test_2[] = { 0x7E, 0xA0, 0x4F, 0x00, 0x02, 0x44, 0xC9, 0x61, 0x10, 0xC8, 0xA8, 0xE6, 0xE6,
0x00, 0x60, 0x3E, 0xA1, 0x09, 0x06, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01, 0x8A, 0x02, 0x07,
0x80, 0x8B, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x02, 0x02, 0xAC, 0x12, 0x80, 0x10, 0x30, 0x31, 0x32,
0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0xBE, 0x10, 0x04, 0x0E,
0x01, 0x00, 0x00, 0x00, 0x06, 0x5F, 0x1F, 0x04, 0x00, 0xFF, 0xFF, 0xFF,0x08, 0x00, 0x3D, 0x69, 0x7E };
uint8_t buf_test_3[] = { 0x7E, 0xA0, 0x5B, 0x61, 0x00, 0x02, 0x44, 0xC9, 0x30, 0xE6, 0x09, 0xE6,
0xE7, 0x00, 0x61, 0x4A, 0xA1, 0x09, 0x06, 0x07, 0x60, 0x85, 0x74, 0x05,
0x08, 0x01, 0x01, 0xA2, 0x03, 0x02, 0x01, 0x00, 0xA3, 0x05, 0xA1, 0x03, 0x02,
0x01, 0x0E, 0x88, 0x02, 0x07, 0x80, 0x89, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x02, 0x02,
0xAA, 0x12, 0x80, 0x10, 0x36, 0x6F, 0x58, 0x70, 0x50, 0x39, 0x3E, 0x56, 0x65, 0x4D, 0x79,
0x34, 0x65, 0x5C, 0x4E, 0x72, 0xBE, 0x10, 0x04, 0x0E, 0x08, 0x00, 0x06, 0x5F,
0x1F, 0x04, 0x00, 0x00, 0x18, 0x1D, 0x04, 0x00, 0x00, 0x07, 0x0E, 0xDA, 0x7E };
uint8_t inf=0;
HDLC_pocket* pack = (HDLC_pocket*) buf;
struct HDLC_get_pocket get_pack = {NULL};
uint8_t ERROR_repack=10;

struct HDLC_data_U data_U_pack = { NULL };
struct HDLC_data_I data_I_pack = { NULL };
struct HDLC_data_P data_P_pack = { NULL };
struct HDLC_data_U data_U_repack;
struct HDLC_data_I data_I_repack;
struct HDLC_data_P data_P_repack;
uint16_t len_U, len_I, len_P=NULL;

uint8_t x, o;

void main() {
	setlocale(LC_ALL, "Russian");

	f_HDLC_pack(buf, 100);

	/*pack->data.point = pack->data.point + 100;
	*pack->data.point = 10;
	*(pack->data.point+1) = 15;*/

	data_I_pack.param = 'I';
	data_I_pack.value = 25;
	data_P_pack.param = 'P';
	data_P_pack.tupe = 'S';
	data_P_pack.value = 100;
	data_U_pack.param = 'U';
	data_U_pack.value = 220;

	x = 1;
	o = 2;
	
	cout << "���� CRC = 0x" << hex << (int) pppfcs16(PPPINITFCS16, buf_test, f_HDLC_packSize(buf_test)-3) << dec << endl;

	cout << "���� ��������" << endl << "������ ��������� = " << (int)f_HDLC_packSize(buf) << endl;
	ERROR_repack = f_HDLC_repack(buf, 100);
	f_HDLC_RepackData();
	cout << endl << endl;

	cout << "������ 1" << endl << "������ ��������� = " << (int)f_HDLC_packSize(buf_test) << endl;
	ERROR_repack=f_HDLC_repack(buf_test, 100);
	f_HDLC_RepackData();
	cout << endl << endl;

	cout << "����� 1" << endl << "������ ��������� = " << (int)f_HDLC_packSize(buf_test_1) << endl;
	ERROR_repack = f_HDLC_repack(buf_test_1, 100);
	f_HDLC_RepackData();
	cout << endl << endl;
	
	cout << "������ 2" << endl << "������ ��������� = " << (int)f_HDLC_packSize(buf_test_2) << endl;
	ERROR_repack = f_HDLC_repack(buf_test_2, 100);
	f_HDLC_RepackData();
	cout << endl << endl;

	cout << "����� 2" << endl << "������ ��������� = " << (int)f_HDLC_packSize(buf_test_3) << endl;
	ERROR_repack = f_HDLC_repack(buf_test_3, 100);
	f_HDLC_RepackData();
	cout << endl << endl;
	//f_HDLC_Print(&get_pack);
	

/*
	len_U=f_HDLC_packData(&data_U_pack);
	cout << "������ U =      " << (int)len_U << endl;
	len_I=f_HDLC_packData(&data_I_pack);
	cout << "������ I =      " << (int)len_I << endl;
	len_P=f_HDLC_packData(&data_P_pack);
	cout << "������ P =      " << (int)len_P << endl;

	data_U_repack = { NULL };
	data_I_repack = { NULL };
	data_P_repack = { NULL };

	A[0] = (uint8_t*)&data_U_pack;
	A[1] = (uint8_t*)&data_I_pack;
	A[2] = (uint8_t*)&data_P_pack;

	f_HDLC_repackData((uint8_t*)A[0], len_U);
	f_HDLC_repackData((uint8_t*)A[1], len_I);
	f_HDLC_repackData((uint8_t*)A[2], len_P);
	
	data_U_repack = f_GetVoltage();
	data_I_repack = f_GetCurrent();
	data_P_repack = f_GetPower();

	if ((data_U_pack.param == data_U_repack.param) &&
		(data_U_pack.value == data_U_repack.value)) {
		cout << "���������� �������" << endl;
	}
	else { cout << "���������� ���������" << endl; }

	if ((data_I_pack.param == data_I_repack.param) &&
		(data_I_pack.value == data_I_repack.value)) {
		cout << "��� ������" << endl;
	}
	else { cout << "��� ��������" << endl; }

	if ((data_P_pack.param == data_P_repack.param) &&
		(data_P_pack.value == data_P_repack.value) &&
		(data_P_pack.tupe == data_P_repack.tupe)) {
		cout << "�������� �������" << endl;
	}
	else { cout << "�������� ���������" << endl; }

	//cout << endl << "�������� ������ " <<sizeof(struct HDLC_data_U)<< endl;

		//7E -����
		//A0 -�����
		//23 -��������
		//00 02 00 21 61 93 7C A0 81 80 14 05 02           
		//04 00 06 02 04 00 07 04 00 00 00 01 08 04 00 00
		//00 01 -����
		//72 E3 -CRC
		//7E -����

		//7E -����
		//A0 -�����
		//0A -��������
		//00 02 00 21 61 53 CA
		//44 -CRC
		//7E -����
*/
}
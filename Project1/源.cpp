#include <windows.h>
#define _USE_MATH_DEFINES 1
#include <cmath>
#pragma comment(lib, "winmm.lib")
#include "virtual_screen.h"
#include"majiaqi.h"
#include <iostream>

using namespace std;

#define PI acos( -1.0 )
HDC dc = GetDC(NULL);
HDC dcCopy = CreateCompatibleDC(dc);
int w = GetSystemMetrics(0);
int h = GetSystemMetrics(1);

DWORD random() {
	DWORD number = __rdtsc();

	number ^= number << 13;
	number ^= number << 17;
	number ^= number << 5;

	return number;
}
DWORD xs;

void SeedXorshift32(DWORD dwSeed) {
	xs = dwSeed;
}

DWORD Xorshift32(VOID) {
	xs ^= xs << 13;
	xs ^= xs >> 17;
	xs ^= xs << 5;
	return xs;
}
DWORD WINAPI shader1(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);
	CURSORINFO cur;

	while (true) {
		int xs = 0;
		int ys = 0;
		int sel = random() % 4 + 1;

		if (sel == 1) {
			xs = random() % x;

			for (; ys < y; ys += 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs += 2;
				if (xs >= x) {
					ys = y;
				}
				Sleep(1);
			}
		}
		else if (sel == 2) {
			xs = random() % x;
			ys = GetSystemMetrics(SM_CYSCREEN);

			for (; ys > 0; ys -= 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs += 2;
				if (xs >= x) {
					ys = 0;
				}
				Sleep(1);
			}
		}
		else if (sel == 3) {
			xs = random() % x;

			for (; ys < y; ys += 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs -= 2;
				if (xs <= 0) {
					ys = y;
				}
				Sleep(1);
			}
		}
		else if (sel == 4) {
			xs = random() % x;
			ys = GetSystemMetrics(SM_CYSCREEN);

			for (; ys > 0; ys -= 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs -= 2;
				if (xs <= 0) {
					ys = 0;
				}
				Sleep(1);
			}
		}
	}
	
}
DWORD WINAPI IconWave(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	double i;
	double wave;
	int xs;
	int ys;

	while (true) {
		int sel = random() % 4 + 1;
		wave = 0;
		i = 0;

		if (sel == 1) {
			xs = 0;
			ys = random() % y;

			for (; xs < x; xs += 3) {
				DrawIcon(hdc, xs, ys + wave * cos(i), LoadIconW(0, IDI_ERROR));
				i += 0.05;
				wave += 0.32;
				Sleep(10);
			}
		}
		else if (sel == 2) {
			xs = x;
			ys = random() % y;

			for (; xs > 0; xs -= 3) {
				DrawIcon(hdc, xs, ys + wave * cos(i), LoadIconW(0, IDI_WARNING));
				i += 0.05;
				wave += 0.32;
				Sleep(10);
			}
		}
		else if (sel == 3) {
			xs = random() % x;
			ys = 0;

			for (; ys < y; ys += 3) {
				DrawIcon(hdc, xs + wave * cos(i), ys, LoadIconW(0, IDI_INFORMATION));
				i += 0.05;
				wave += 0.32;
				Sleep(10);
			}
		}
		else if (sel == 4) {
			xs = random() % x;
			ys = y;

			for (; ys > 0; ys -= 3) {
				DrawIcon(hdc, xs + wave * cos(i), ys, LoadIconW(0, IDI_QUESTION));
				i += 0.05;
				wave += 0.32;
				Sleep(10);
			}
		}
	}
	
}
DWORD WINAPI woye(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		int xs = random() % x;
		int ys = random() % y;

		int rnd = random() % 400;

		if (random() % 2 + 1 == 1) {
			for (int i = 0; i < rnd; i += 30) {
				HRGN circle = CreateEllipticRgn(xs - i, ys - i, xs + i, ys + i);
				SelectClipRgn(hdc, circle);

				BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, NOTSRCCOPY);
				Sleep(1);
			}
		}
		else {
			for (int i = 0; i < rnd; i += 30) {
				HRGN square = CreateRectRgn(xs - i, ys - i, xs + i, ys + i);
				SelectClipRgn(hdc, square);

				BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, NOTSRCCOPY);
				Sleep(1);
			}
		}
		Sleep(1);
	}
	
}
DWORD WINAPI mile(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		int xs = random() % x;
		int ys = random() % y;
		int sel = random() % 4 + 1;
		int size = random() % 300 + 200;
		int rnd = random() % 50 + 20;

		if (sel == 1) {
			for (int i = 0; i < rnd; i += 10) {
				BitBlt(hdc, xs + i, ys + i, size, size, hdc, xs, ys, SRCCOPY);
				Sleep(100);
			}
		}
		else if (sel == 2) {
			for (int i = 0; i < rnd; i += 10) {
				BitBlt(hdc, xs + i, ys - i, size, size, hdc, xs, ys, SRCCOPY);
				Sleep(100);
			}
		}
		else if (sel == 3) {
			for (int i = 0; i < rnd; i += 10) {
				BitBlt(hdc, xs - i, ys + i, size, size, hdc, xs, ys, SRCCOPY);
				Sleep(100);
			}
		}
		else if (sel == 4) {
			for (int i = 0; i < rnd; i += 10) {
				BitBlt(hdc, xs - i, ys - i, size, size, hdc, xs, ys, SRCCOPY);
				Sleep(100);
			}
		}
	}
	
}
DWORD WINAPI fangkuai(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	int xs = random() % x;
	int ys = random() % y;

	HBRUSH circle = CreateSolidBrush(RGB(255, 0, 0));
	HPEN border = CreatePen(0, 1, RGB(255, 255, 255));

	int color = 0;

	while (true) {
		if (color == 1) {
			circle = CreateSolidBrush(RGB(255, 165, 0));
		}
		else if (color == 2) {
			circle = CreateSolidBrush(RGB(255, 255, 0));
		}
		else if (color == 3) {
			circle = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if (color == 4) {
			circle = CreateSolidBrush(RGB(0, 255, 255));
		}
		else if (color == 5) {
			circle = CreateSolidBrush(RGB(0, 0, 255));
		}
		else if (color == 6) {
			circle = CreateSolidBrush(RGB(148, 0, 211));
		}
		else if (color == 7) {
			circle = CreateSolidBrush(RGB(255, 0, 255));
		}
		else if (color == 8) {
			circle = CreateSolidBrush(RGB(255, 0, 0));
			color = 0;
		}

		SelectObject(hdc, circle);
		SelectObject(hdc, border);

		if (xs >= x) {
			xs = random() % x;
			ys = random() % y;
		}
		else if (ys >= y) {
			xs = random() % x;
			ys = random() % y;
		}
		else if (xs <= 0) {
			xs = random() % x;
			ys = random() % y;
		}
		else if (ys <= 0) {
			xs = random() % x;
			ys = random() % y;
		}

		int sel = random() % 4 + 1;

		for (int runtime = 0; runtime < 10; runtime++) {
			if (sel == 1) {
				Ellipse(hdc, xs - 60, ys - 60, xs + 60, ys + 60);
				xs += 20;
				ys += 20;
				Sleep(130);
			}
			else if (sel == 2) {
				Ellipse(hdc, xs - 60, ys - 60, xs + 60, ys + 60);
				xs += 20;
				ys -= 20;
				Sleep(130);
			}
			else if (sel == 3) {
				Ellipse(hdc, xs - 60, ys - 60, xs + 60, ys + 60);
				xs -= 20;
				ys += 20;
				Sleep(130);
			}
			else if (sel == 4) {
				Ellipse(hdc, xs - 60, ys - 60, xs + 60, ys + 60);
				xs -= 20;
				ys -= 20;
				Sleep(130);
			}
		}
		color++;
	}
	
}
DWORD WINAPI payload08(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	float alg[50], r[50];
	for (int a = 0; a < 50; a++) {
		alg[a] = (Xorshift32() % 360) * (PI / 180);
		r[a] = Xorshift32() % (((int)ceil(sqrt(pow(w, 2) + pow(h, 2)))) / 2);
	}

	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hcdc, hBitmap);
	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

	for (int t = 0; ; t += 3) {
		hdc = GetDC(NULL);
		HDC hdcTemp = CreateCompatibleDC(hdc);
		HBITMAP hBitmapTemp = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hdcTemp, hBitmapTemp);
		BitBlt(hdcTemp, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);

		for (int tm = 0; tm < 50; tm++) {
			DrawIcon(hdcTemp, (cos(alg[tm]) * r[tm]) + t, (sin(alg[tm]) * r[tm]) + ((h / 2) - (cos(t * (PI / (w / 2))) * (h / 2))), LoadIcon(NULL, IDI_ERROR));
			alg[tm] += PI / 180;
		}

		BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcTemp);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdcTemp);
		DeleteObject(hBitmapTemp);
		DeleteObject(hdc);
		Sleep(10);
	}
	ReleaseDC(NULL, hcdc);
	DeleteDC(hcdc);
	DeleteObject(hBitmap);
	return 0;
}
DWORD WINAPI majiaqi(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	double i = 0;

	while (true) {
		for (int ys = 0; ys < y; ys++) {
			BitBlt(hdc, 20 * sin(i), ys, x, 1, hdc, 0, ys, SRCCOPY);
			i += 0.04;
		}
		Sleep(40);
	}
	
}
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (3 + (1 ^ t >> 10 & 5)) * (5 + (3 & t >> 14)) >> (t >> 8 & 3));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t << 2 | t >> 7));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> (t >> 10 & 7) & t >> 12));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * ((t >> 12 | t >> 9) & 241 & t >> 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(3 * ((t >> 1) + 20) * t >> 14 * t >> 18);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound6() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t / 91 & t ^ t / 90 & t) - 1);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound7() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> (t >> 10 & 7) & t >> 12));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound8() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t << 1 & t * 3 & t >> 5 & t >> 10) - 1);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound9() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (1 + (t >> 10) * (43 + 2 * (t >> 15 - (t >> 16) % 13) % 8) % 8) * (1 + (t >> 14) % 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound10() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * ((t >> 9 | t >> 13) & 15) & 129);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound11() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t / 401 ^ t / 400));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
POINT mkp(int x, int y) {
	POINT p;
	p.x = x;
	p.y = y;
	return p;
}
void _DrawError(bool x) {
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	int icnsz = GetSystemMetrics(SM_CXICON);
	HDC hdc = GetDC(NULL);
	POINT p;
	if (x) {
		p = mkp(0, random() % h);
	}
	else {
		p = mkp(random() % w, 0);
	}
	for (;;) {
		if (p.x >= w || p.y >= h) {
			return;
		}
		DrawIcon(hdc, p.x, p.y, LoadIcon(NULL, IDI_WARNING));
		p.x += icnsz;
		p.y += icnsz;
		Sleep(50);
	}
	
	return;
}
DWORD WINAPI qiersi(LPVOID lpParameter) {
	for (int i = 0; i < 30; i++) {
		_DrawError(random() % 2);
	}
    
	return 0;
}
DWORD WINAPI paylixo(LPVOID lpvd)
{
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);

	INT i = 0;

	while (1)
	{
		StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				double fractalX = (2.5f / w);
				double fractalY = (1.90f / h);

				double cx = x * fractalX - 2.f;
				double cy = y * fractalY - 0.95f;

				double zx = 0;
				double zy = 0;

				int fx = 0;

				while (((zx * zx) + (zy * zy)) < 10 && fx < 50)
				{
					double fczx = zx * zx - zy * zy + cx;
					double fczy = 2 * zx * zy + cy;

					zx = fczx;
					zy = fczy;
					fx++;

					rgbquad[index].rgbRed += fx;
					rgbquad[index].rgbGreen += fx;
					rgbquad[index].rgbBlue += fx;
				}
			}
		}

		i++;
		StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
	}

	return 0x00;
}
DWORD WINAPI paylixo1(LPVOID lpvd)
{
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);

	INT i = 0;

	while (1)
	{
		StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;
				int j = 4 * i;

				//Old-School Plasma effect
				int fx = (int)(j + (j * sin(x / 16.0)) + j + (j * sin(y / 8.0)) + j + (j * sin((x + y) / 16.0)) + j + (j * sin(sqrt((double)(x * x + y * y)) / 8.0))) / 4;

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
	}

	return 0x00;
}
DWORD WINAPI textout(LPVOID lpParam)
{
	HDC hdc;
	int sx = 0, sy = 0;
	LPCWSTR lpText = L"Chils";
	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(0);
		sy = GetSystemMetrics(1);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}
DWORD WINAPI juanzi(LPVOID lpvd)
{
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);

	//Counter variable
	INT i = 0;

	while (1)
	{
		StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				FLOAT fx = (x + i) ^ (y + i);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
	}

	return 0x00;
}
DWORD WINAPI BB1(LPVOID lpvd)
{
	while (1)
	{
		for (int x = 0; x <= w; x++)
		{
			for (int y = 0; y <= h; y++)
			{
				int fx = x ^ y;
				COLORREF color = RGB(fx, fx, fx);
				HBRUSH brush = CreateSolidBrush(color);
				SelectObject(dc, brush);

				PatBlt(dc, 0, 0, w, h, PATINVERT);
				Sleep(rand() % 50);
			}
		}
	}

	return 0x00;
}

DWORD WINAPI BB2(LPVOID lpstart) {
	HDC hdc = GetDC(0);
	RECT rekt;
	POINT rotate[3];

	while (true) {
		int rnd = random() % 100;

		for (int i = 0; i < rnd; i += 20) {
			GetWindowRect(GetDesktopWindow(), &rekt);

			rotate[0].x = rekt.left + i;
			rotate[0].y = rekt.top - i;
			rotate[1].x = rekt.right + i;
			rotate[1].y = rekt.top + i;
			rotate[2].x = rekt.left - i;
			rotate[2].y = rekt.bottom - i;

			PlgBlt(hdc, rotate, hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
			Sleep(40);
		}
		for (int i = 0; i < rnd; i += 20) {
			GetWindowRect(GetDesktopWindow(), &rekt);

			rotate[0].x = rekt.left - i;
			rotate[0].y = rekt.top + i;
			rotate[1].x = rekt.right - i;
			rotate[1].y = rekt.top - i;
			rotate[2].x = rekt.left + i;
			rotate[2].y = rekt.bottom + i;

			PlgBlt(hdc, rotate, hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
			Sleep(40);
		}
	}
}
DWORD WINAPI shanxiani(LPVOID lpParameter) {
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	for (;;) {
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 50, 50, w - 100, h - 100, PATINVERT);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 100, 100, w - 200, h - 200, PATINVERT);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 150, 150, w - 300, h - 300, PATINVERT);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 200, 200, w - 400, h - 400, PATINVERT);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 250, 250, w - 500, h - 500, PATINVERT);
	}
	return 0;
}

DWORD WINAPI ooyeye(LPVOID lpvd)
{

	HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
	SelectObject(dcCopy, bmp);

	while (1)
	{
		SetStretchBltMode(dcCopy, COLORONCOLOR);
		SetStretchBltMode(dc, COLORONCOLOR);

		StretchBlt(dcCopy, 0, 0, w / 3, h / 3, dc, 0, 0, w, h, SRCCOPY);
		StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w / 3, h / 3, SRCCOPY);

		if (rand() % 5 == 4) StretchBlt(dc, 1, 1, w, h, dc, 0, 0, w, h, SRCAND);
	}

	return 0x00;
}

DWORD WINAPI kuaikuai(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	int ys = 0;

	while (true) {
		HBRUSH brush = CreateSolidBrush(RGB(random() % 255, random() % 255, random() % 255));
		SelectObject(hdc, brush);

		for (int i = 0; i < x; i += 100) {
			Rectangle(hdc, i, ys + 100, 100 + i, ys);
			Sleep(10);
		}

		ys += 100;
		if (ys >= y) {
			ys = 0;
		}

		Sleep(30);
	}
}
DWORD WINAPI oli(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hcdc, hBitmap);

	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCINVERT);
	BitBlt(hcdc, 1, 1, w, h, hcdc, 0, 0, SRCERASE);
	BitBlt(hdc, -1, -1, w, h, hcdc, 0, 0, SRCAND);
	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

	for (int t = 0; ; t++) {
		hdc = GetDC(NULL);
		HDC hdcCopy = CreateCompatibleDC(hdc);
		HBITMAP hBitmapCopy = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hdcCopy, hBitmapCopy);
		BitBlt(hdcCopy, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);

		POINT pos[3];
		pos[0].x = 0, pos[0].y = 0;
		pos[1].x = t % w, pos[1].y = 0;
		pos[2].x = w - (t % w), pos[2].y = h;
		PlgBlt(hdcCopy, pos, hcdc, 0, 0, w, h, 0, 0, 0);
		BitBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, SRCCOPY);

		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hdcCopy);
		DeleteObject(hdc);
		DeleteObject(hdcCopy);
		DeleteObject(hBitmapCopy);

		Sleep(10);
	}

	ReleaseDC(NULL, hcdc);
	DeleteObject(hcdc);
	DeleteObject(hBitmap);

	return 0;
}
DWORD WINAPI obscure(LPVOID lpstart)
{//唯一一个自己写的（
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(0);
    while (true)
	{
		BitBlt(hdc, random() % 2, random() % 2, x, y, hdc, random() % 2, random() % 2, SRCAND);
		BitBlt(hdc, random() % 10, random() % 10, x, y, hdc, random() % 12, random() % 12, SRCPAINT);
	}
	Sleep(1000);
}
DWORD WINAPI abc(LPVOID lpvd)//勉强能用
{
	HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
	SelectObject(dcCopy, bmp);

	while (1)
	{
		int fx = rand() % h;

		if (rand() % 3 == 2)
		{
			StretchBlt(dcCopy, rand() % 3, rand() % 3, w, h, dc, rand() % 3, rand() % 3, w, h, SRCCOPY);
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
		}

		if (rand() % 3 == 2)
		{
			if (rand() % 25 == 24) BitBlt(dc, 10, 0, w, h, dc, 0, 10, SRCPAINT);
			if (rand() % 25 == 24) BitBlt(dc, -10, 0, w, h, dc, 0, -10, SRCAND);
			if (rand() % 25 == 24) BitBlt(dc, -10, -10, w, h, dc, 0, 0, SRCPAINT);
			if (rand() % 25 == 24) BitBlt(dc, 10, 10, w, h, dc, 0, 0, SRCAND);
		}

		BitBlt(dc, -10, fx, w, -10, dc, 0, fx, SRCCOPY);
		BitBlt(dc, 10, fx, w, 10, dc, 0, fx, SRCCOPY);

		if (rand() % 25 == 24);
	}
	return 0x00;
}
DWORD WINAPI drawiconex(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	while (true)
	{
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		DrawIconEx(hdc, rand() % w, rand() % h, LoadIcon(0, IDI_ERROR), rand() % 300, rand() % 300, 0, 0, DI_NORMAL);
		Sleep(100);
	}
}
DWORD WINAPI ad1(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

	BLENDFUNCTION blf = { 0 };
	blf.BlendOp = AC_SRC_OVER;
	blf.BlendFlags = 0;
	blf.SourceConstantAlpha = 200;
	blf.AlphaFormat = 0;

	int bl = 1;
	for (int t = 0; ; t++) {
		bl = -bl;

		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		int sx = 0, sy = 0;
		LPCWSTR lpText = L"Chils";
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

		if (t % 25 == 0) {
			SetBkColor(hcdc, Xorshift32() % 0xffffff);
			SetTextColor(hcdc, Xorshift32() % 0xffffff);
			HFONT font = CreateFont(10 * (Xorshift32() % 5), 10 * (Xorshift32() % 5), 0, 0, FW_BOLD, 0, 1, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Baby Kruffy");
			SelectObject(hcdc, font);
			TextOut(hcdc, Xorshift32() % w, Xorshift32() % h, L"majiaqi", 7);
			TextOut(hcdc, Xorshift32() % w, Xorshift32() % h, L"jiaqi", 5);
		}

		POINT ps[3];
		ps[0].x = (w / 2) - (cos(PI / 180) * (w / 2)), ps[0].y = sin(PI / 180) * (w / 2) * bl;
		ps[1].x = (w / 2) + (cos(PI / 180) * (w / 2)), ps[1].y = -(sin(PI / 180) * (w / 2) * bl);
		ps[2].x = (w / 2) - ((cos(PI / 180) * (w / 2)) - ((sin(PI / 180) * h) * bl)), ps[2].y = (cos(PI / 180) * h) + ((sin(PI / 180) * (w / 2) * bl));
		PlgBlt(hcdc, ps, hcdc, 0, 0, w, h, 0, 0, 0);
		AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blf);

		ReleaseDC(NULL, hcdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(20);
	}
	return 0;
}
DWORD WINAPI te(LPVOID lpParam)
{
	HDC hdc;
	int sx = 0, sy = 0;
	LPCWSTR lpText = L"Chils";
	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(0);
		sy = GetSystemMetrics(1);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
		ReleaseDC(0, hdc);
		Sleep(50);
	}
}
DWORD WINAPI nihong(LPVOID lpParam)
{//有点好看像霓虹灯
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

	BLENDFUNCTION blf = { 0 };
	blf.BlendOp = AC_SRC_OVER;
	blf.BlendFlags = 0;
	blf.SourceConstantAlpha = 200;
	blf.AlphaFormat = 0;

	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);

	HDC hdcCopy = CreateCompatibleDC(hdc);
	HBITMAP hBitmapCopy = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hdcCopy, hBitmapCopy);
	BitBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

	for (int t = 0; ; t += 40) {
		hdc = GetDC(NULL);

		HDC hdcTemp = CreateCompatibleDC(hdc);
		HBITMAP hBitmapTemp = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hdcTemp, hBitmapTemp);
		BitBlt(hdcTemp, 0, 0, w, h, hdcCopy, 0, 0, SRCCOPY);

		for (int i = 0; i < h; i++) {
			for (int l = 0; l < w; l++) {
				int pos = i * w + l;
				prgbScreen[pos].r = sin((l + t) * (PI / (w / 10))) * 127 + 127;
				prgbScreen[pos].g = 0;
				prgbScreen[pos].b = sin((i + t) * (PI / (w / 10))) * 127 + 127;
			}
		}

		AlphaBlend(hdcTemp, 0, 0, w, h, hcdc, 0, 0, w, h, blf);
		BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY);

		ReleaseDC(NULL, hdcTemp);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdcTemp);
		DeleteObject(hBitmapTemp);
		DeleteObject(hdc);
		Sleep(10);
	}
	ReleaseDC(NULL, hcdc);
	ReleaseDC(NULL, hdcCopy);
	DeleteDC(hcdc);
	DeleteDC(hdcCopy);
	DeleteObject(hBitmap);
	DeleteObject(hBitmapCopy);
	return 0;
}
	DWORD WINAPI niuniu(LPVOID lpParam) {//扭扭扭
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

		BLENDFUNCTION blf = { 0 };
		blf.BlendOp = AC_SRC_OVER;
		blf.BlendFlags = 0;
		blf.SourceConstantAlpha = 200;
		blf.AlphaFormat = 0;

		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);

		HDC hdcCopy = CreateCompatibleDC(hdc);
		HBITMAP hBitmapCopy = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hdcCopy, hBitmapCopy);
		BitBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

		for (int t = 0; ; t += 20) {
			hdc = GetDC(NULL);

			HDC hdcTemp = CreateCompatibleDC(hdc);
			HBITMAP hBitmapTemp = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(hdcTemp, hBitmapTemp);

			for (int i = -1; i < 2; i += 2) {
				BitBlt(hdcTemp, 0, 0, w, h, hdcCopy, 0, 0, SRCCOPY);
				for (float y = 0; y < h; y++) {
					float x = sin((y + t) * (PI / (w / 10))) * (w / 20);
					BitBlt(hdcTemp, i * x, y, w, 1, hdcCopy, 0, y, SRCCOPY);
				}
				AlphaBlend(hcdc, 0, 0, w, h, hdcTemp, 0, 0, w, h, blf);
			}

			BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
			ReleaseDC(NULL, hdcTemp);
			ReleaseDC(NULL, hdc);
			DeleteObject(hdcTemp);
			DeleteObject(hBitmapTemp);
			DeleteObject(hdc);
			Sleep(10);
		}
		ReleaseDC(NULL, hcdc);
		ReleaseDC(NULL, hdcCopy);
		DeleteDC(hcdc);
		DeleteDC(hdcCopy);
		DeleteObject(hBitmap);
		DeleteObject(hBitmapCopy);
		return 0;
	}
	DWORD WINAPI Cop(LPVOID lpParameter) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		for (;;) {
			CURSORINFO pci;
			pci.cbSize = sizeof(pci);
			GetCursorInfo(&pci);
			for (int i = 1; i <= 20; i++)
				DrawIcon(hdc, random() % w, random() % h, pci.hCursor);
			Sleep(500);
		}
		return 0;
	}
int main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
    if (MessageBoxW(NULL, L"Are you sure you want to open this program? Yes for confirmation, no for misopening.", L"Justinbieber_warning", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"This is the last warning.", L"Justinbieber_warning", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else {
            HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, IconWave, 0, 0, 0);
            sound1();
            Sleep(20000);
			HANDLE thread3 = CreateThread(0, 0, woye, 0, 0, 0);

			Sleep(10000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			
			HANDLE thread4 = CreateThread(0, 0, mile, 0, 0, 0);
			HANDLE thread6 = CreateThread(0, 0, fangkuai, 0, 0, 0);
			sound3();
			Sleep(20000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
		
			HANDLE thread5 = CreateThread(0, 0,majiaqi, 0, 0, 0);
			sound4();
			Sleep(10000);
		    HANDLE thread7 = CreateThread(0, 0,qiersi, 0, 0, 0);
			HANDLE thread12 = CreateThread(0, 0, ooyeye, 0, 0, 0);
			Sleep(5000);
		    TerminateThread(thread12, 0);
			CloseHandle(thread12);
			HANDLE thread19 = CreateThread(0, 0, ad1, 0, 0, 0);//19
			HANDLE thread20 = CreateThread(0, 0, te, 0, 0, 0);//20
			Sleep(15000);//weizhi14
			TerminateThread(thread19, 0);
			CloseHandle(thread19);
			TerminateThread(thread20, 0);
			CloseHandle(thread20);
			sound8();
			HANDLE thread17 = CreateThread(0, 0, abc, 0, 0, 0);//1777
			HANDLE thread18 = CreateThread(0, 0, drawiconex, 0, 0, 0);//18
			Sleep(10000);
			HANDLE thread16 = CreateThread(0, 0, obscure, 0, 0, 0);//16
			
			Sleep(5000);
			TerminateThread(thread17, 0);
			CloseHandle(thread17);
			TerminateThread(thread18, 0);
			CloseHandle(thread18);
			HANDLE thread15 = CreateThread(0, 0, oli, 0, 0, 0);//15
			Sleep(5000);
			TerminateThread(thread15, 0);
			CloseHandle(thread15);
			TerminateThread(thread16, 0);
			CloseHandle(thread16);
			sound11();
			HANDLE thread14 = CreateThread(0, 0,kuaikuai, 0, 0, 0);//分界点前Basic-方块是为了能够让后面的分形更好体现从而达到视觉效果
			Sleep(20000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			TerminateThread(thread14, 0);
			CloseHandle(thread14);
			HANDLE thread11 = CreateThread(0, 0, juanzi, 0, 0, 0);//zhiweihehe
			
			sound7();
			Sleep(20000);
			TerminateThread(thread11, 0);
			CloseHandle(thread11);
		
			HANDLE thread8 = CreateThread(0, 0,paylixo, 0, 0, 0);
			sound5();
			Sleep(20000);
			TerminateThread(thread8, 0);
			CloseHandle(thread8);
			HANDLE thread9 = CreateThread(0, 0, paylixo1, 0, 0, 0);
			HANDLE thread10 = CreateThread(0, 0, textout, 0, 0, 0);
			sound6();
			Sleep(30000);
			TerminateThread(thread9, 0);
			CloseHandle(thread9);
			TerminateThread(thread10, 0);
			CloseHandle(thread10);	
			sound9();
			HANDLE thread21 = CreateThread(0, 0, nihong, 0, 0, 0);//21
			HANDLE thread23 = CreateThread(0, 0, Cop, 0, 0, 0);//23
			Sleep(10000);
			sound10();
			TerminateThread(thread21, 0);
			CloseHandle(thread21);
			HANDLE thread22 = CreateThread(0, 0, niuniu, 0, 0, 0);//22
			Sleep(10000);
			TerminateThread(thread22, 0);
			CloseHandle(thread22);
			TerminateThread(thread23, 0);
			CloseHandle(thread23);
			
        }
    }
}
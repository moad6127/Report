#include "BitmapExample.h"
#include <cmath>
HRESULT BitmapExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	D2DFramework::Initialize(hInstance, title, width, height);


	mspBackBuffer = std::make_unique<UINT8[]>(BITMAP_WIDTH*BITMAP_HEIGHT*BITMAP_BYTECOUNT);

	HRESULT hr;
	hr = mspRenderTarget->CreateBitmap(
		D2D1::SizeU(BITMAP_WIDTH, BITMAP_HEIGHT),
		D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)),
		mspFramBitmap.GetAddressOf()
	);
	ThrowIfFailed(hr);

	return hr;
}

void BitmapExample::Render()
{
	mspRenderTarget->BeginDraw();
	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	//DrawPixelToBuffer(10, 10, D2D1::ColorF::White);
	ClearBuffer(D2D1::ColorF::LawnGreen);
	FillRectToBuffer(10, 10, 100, 100, D2D1::ColorF::Black);
	DrawCircleToBuffer(200, 200, 100,  D2D1::ColorF::Black);
	DrawCircleToBuffer(200, 200, 50, D2D1::ColorF::Black);
	DrawLineToBuffer(500, 10, 1000, 20, D2D1::ColorF::Black);
	DrawLineToBuffer(500, 10, 1000, 30, D2D1::ColorF::Black);

	PresentBuffer();

	mspRenderTarget->DrawBitmap(mspFramBitmap.Get());

	mspRenderTarget->EndDraw();
}

void BitmapExample::PresentBuffer()
{
	mspFramBitmap->CopyFromMemory(nullptr, mspBackBuffer.get(),BITMAP_WIDTH*BITMAP_BYTECOUNT);

}

void BitmapExample::DrawPixelToBuffer(int x, int y, D2D1::ColorF color)
{
	int pitch = BITMAP_WIDTH * BITMAP_BYTECOUNT;
	int index = x * BITMAP_BYTECOUNT + y * pitch;

	mspBackBuffer[index] = static_cast<UINT8>(color.r *255);
	mspBackBuffer[index +1] = static_cast<UINT8>(color.g * 255);
	mspBackBuffer[index +2] = static_cast<UINT8>(color.b * 255);
	mspBackBuffer[index +3] = static_cast<UINT8>(color.a * 255);

}

void BitmapExample::ClearBuffer(D2D1::ColorF color)
{
	//for (int x = 0; x < BITMAP_WIDTH; x++)
	//{
	//	for (int y = 0; y < BITMAP_HEIGHT; y++)
	//	{
	//		DrawPixelToBuffer(x, y, color);
	//	}
	//}
	UINT8* pCurrent = &mspBackBuffer[0];

	for (int i = 0; i < BITMAP_WIDTH * BITMAP_HEIGHT; i++)
	{
		*pCurrent = static_cast<UINT8>(color.r * 255);
		*(pCurrent+1)=static_cast<UINT8>(color.g * 255);
		*(pCurrent + 2) = static_cast<UINT8>(color.b * 255);
		*(pCurrent + 3) = static_cast<UINT8>(color.a * 255);

		pCurrent += BITMAP_BYTECOUNT;
	}
}

void BitmapExample::FillRectToBuffer(int left, int top, int width, int height, D2D1::ColorF color)
{
	for (int x = left; x < left + width; x++)
	{
		for (int y = top; y < top + height; y++)
		{
			DrawPixelToBuffer(x, y, color);
		}
	}
}

void BitmapExample::DrawCircleToBuffer(int a, int b, int r, D2D1::ColorF color)
{
	const double PI{ 3.141592 };
	for (double set = 0; set <= 2*PI; set += 0.01)
	{
		int x = a + r * cos(set);
		int y = b + r * sin(set);

		DrawPixelToBuffer(x, y, color);

	}
}

void BitmapExample::DrawLineToBuffer(int x1, int y1, int x2, int y2, D2D1::ColorF color)
{
	int x{min(x1,x2)};
	int maxX{max(x1,x2)};

	for (x; x <= maxX; x++)
	{
		int y = ((double(y2 - y1) / (x2 - x1)) * (x - x1)) + y1;

		DrawPixelToBuffer(x, y, color);
	}

}



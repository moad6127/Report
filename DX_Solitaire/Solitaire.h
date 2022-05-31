#pragma once

#include<memory>
#include<list>

#include"D2DFramework.h"
#include"Actor.h"

class Solitaire : public D2DFramework
{
protected:

	std::unique_ptr<Actor> mActor_BG;
	std::list<std::unique_ptr<Actor>> mCardList;
	const int BORAD_COLUM = 8;
	const int BORAD_ROW = 5;

	int mFlipCount;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"Buggy House",
		UINT width = 1024, UINT height = 768) override;

	virtual void Release() override;
	virtual void Render() override;

	void onClick(int mouseX, int mouseY);

	void CreateCards();


};

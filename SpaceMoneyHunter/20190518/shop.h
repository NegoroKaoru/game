#ifndef __SHOP_H__
#define __SHOP_H__

#include "main.h"

struct shopStates
{
	bool EnterShop;
	int selecting;
	int price[3];
};


HRESULT Initshop(void);
void Uninitshop(void);
void Updateshop(void);
void Drawshop(void);

shopStates GetShopInfo(void);
void SetShopInfo();
#endif
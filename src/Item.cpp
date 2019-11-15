#include "Item.h"

Item::Item(){
    bought = false;
}

Item::~Item() {
}

int Item::getPrice() {
    return price;
}

void Item::setPrice(int itemPrice) {
    price = itemPrice;
}
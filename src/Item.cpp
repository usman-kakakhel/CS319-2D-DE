#include "Item.h"

Item::Item(int amount, int price){
    this->amount = amount;
    this->price = price;
    bought = false;
}

Item::~Item() {
}

int Item::getAmount() {
    return amount;
}

bool Item::getBought() {
    return bought;
}

int Item::getPrice() {
    return price;
}

void Item::setPrice(int price) {
    this->price = price;
}

void Item::setAmount(int amount) {
    this->amount = amount;
}

void Item::setBought(bool bought) {
    this->bought = bought;
}

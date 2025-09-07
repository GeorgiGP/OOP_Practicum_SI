#pragma once

enum class State {
    OK,
    NegativeBalance,
    NegativeQuantity,
    UserFull,
    ProductFull,
    PriceFull,
    UserNotFound,
    ProductNotFound,
    ShortOnMoney,
    NotEnoughItems,
    UserInDB,
    ProductInDB,
    PriceInDB,
};
#pragma once
#include <type_traits>
#include <memory>
#include "Item.h"
#include "Enemy.h"

template<typename T>
concept ItemDerived = std::is_base_of_v<Item, std::remove_cv_t<std::remove_reference_t<T>>>;

template<typename T>
concept EnemyDerived = std::is_base_of_v<Enemy, std::remove_cv_t<std::remove_reference_t<T>>>;

template<ItemDerived T, typename... Args>
std::unique_ptr<T> make_item(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<EnemyDerived T, typename... Args>
std::unique_ptr<T> make_enemy(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

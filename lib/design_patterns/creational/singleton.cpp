//
// Created by user on 1/12/21.
//

#include "singleton.h"

Singleton &Singleton::get_instance() {
    static Singleton instance;
    return instance;
}
/*
** EPITECH PROJECT, 2020
** Object
** File description:
** Object
*/

#ifndef OBJECT_CLASS_HPP_
#define OBJECT_CLASS_HPP_

#include <string>

enum objectStatus {
    TRAVERSABLE,
    BREAKABLE,
    SOLID,
    MOVEABLE,
};

namespace Bomberman {
    namespace Game {
        class ObjectClass {
            public:
                ObjectClass(const objectStatus status, const std::string &name);
                ~ObjectClass();

                objectStatus getStatus() const;
                void damageObject();
                bool isBreak();

            protected:
            private:
                objectStatus _status;
                std::string _name;
                bool _alive = true;
        };
    }
}

#endif /* !OBJECT_CLASS_HPP_ */

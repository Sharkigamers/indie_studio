
#ifndef AGAMEOBJECT_HPP_
#define AGAMEOBJECT_HPP_

#ifdef _MSC_VER
// We'll also define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include "driverChoice.h"
#include "DataType.hpp"
#include <vector>
#include <memory>
#include <filesystem>


namespace Bomberman {
    namespace Graphics {

        using pos_t = std::pair<float, float>;
        using namespace irr;

        class AGameObject {
            std::shared_ptr<scene::ISceneNode> _sceneNode;
            scene::ISceneManager *_scnMng;
            gui::IGUIEnvironment *_guienv;
            video::IVideoDriver *_driver;
            pos_t _pos;
            pos_t _sizeSquare;
            std::string _asset;
            std::string _type;

        public:
            AGameObject(IrrlichtDevice *device, pos_t pos, const std::string &texture, const std::string &type, pos_t sizeSquare = {10, 10});
            AGameObject(IrrlichtDevice *device, pos_t pos, const std::string &texture, const std::string &type, const std::string &asset, pos_t sizeSquare = {10, 10});
            AGameObject(AGameObject &&cpy) {
            //    std::cout << "CPY CTOR" << std::endl;
                _scnMng = cpy._scnMng;
                _sceneNode = cpy._sceneNode;
                _guienv = cpy._guienv;
                _driver = cpy._driver;
                _pos = cpy._pos;
                _sizeSquare = cpy._sizeSquare;
                _asset = cpy._asset;
                _type = cpy._type;
            }
            AGameObject &operator=(AGameObject &&obj)
            {
//                std::cout << "MOVE ASSIGNEMENT\n";
                _scnMng = std::move(obj._scnMng);
                _sceneNode = std::move(obj._sceneNode);
                _guienv = std::move(obj._guienv);
                _driver = std::move(obj._driver);
                _pos = std::move(obj._pos);
                _sizeSquare = std::move(obj._sizeSquare);
                _asset = std::move(obj._asset);
                _type = std::move(obj._type);
                return *this;
            }
            ~AGameObject() = default;

            void setPosition(pos_t new_pos);
            void setScale (const core::vector3df &vect);
            void addAnimator(irr::scene::ISceneNodeAnimator *anim);
            // void setRotation (pos_t rotation);
            void setRotation(const core::vector3df &vect);
            void setAnimationSpeed(const irr::f32 &);
            void setVisible (bool isVisible);

            pos_t getPosition();
            pos_t getPositionInMap();
            std::string getType() const;
            char getTypeChar() const;
            const core::vector3df &getRotation() const;
        };
    }
}

#endif
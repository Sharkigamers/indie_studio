#include "AGameObject.hpp"

using namespace Bomberman;
using namespace Graphics;

AGameObject::AGameObject(IrrlichtDevice *device, pos_t pos, const std::string &texture, const std::string &type, pos_t sizeSquare) : _driver(device->getVideoDriver()),
    _scnMng(device->getSceneManager()), _guienv(device->getGUIEnvironment()), _pos({pos.first * sizeSquare.first, pos.second * sizeSquare.second}),
    _type(type), _sizeSquare(sizeSquare)
{
    scene::ISceneNode *sceneNode = device->getSceneManager()->addCubeSceneNode();
    std::shared_ptr<scene::ISceneNode> cpy(sceneNode, [device] (scene::ISceneNode *sceneNode) {device->getSceneManager()->addToDeletionQueue(sceneNode);});
//    std::cerr << "_pos.first = " << _pos.first << std::endl;
//    std::cerr << "_pos.second = " << _pos.second << std::endl;

    _sceneNode = cpy;
    _sceneNode->setMaterialTexture(0, device->getVideoDriver()->getTexture(texture.c_str()));
    _sceneNode->setPosition(core::vector3df(_pos.first, _pos.second, 0));
}

AGameObject::AGameObject(IrrlichtDevice *device, pos_t pos, const std::string &texture, const std::string &type, const std::string &asset, pos_t sizeSquare) : _driver(device->getVideoDriver()),
    _scnMng(device->getSceneManager()), _guienv(device->getGUIEnvironment()), _pos({pos.first * sizeSquare.first, pos.second * sizeSquare.second}),
    _type(type), _sizeSquare(sizeSquare), _asset(asset)
{
    scene::ISceneNode *sceneNode = _scnMng->addAnimatedMeshSceneNode(_scnMng->getMesh(_asset.c_str()), 0, -1, core::vector3df(_pos.first, _pos.second, 0), {-100, 0, 0}, {6, 6, 6});
    std::shared_ptr<scene::ISceneNode> cpy(sceneNode, [device] (scene::ISceneNode *sceneNode) {  device->getSceneManager()->addToDeletionQueue(sceneNode);});
//    std::cerr << "_pos.first = " << _pos.first << std::endl;
//    std::cerr << "_pos.second = " << _pos.second << std::endl;

    _sceneNode = cpy;
    _sceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
    _sceneNode->setMaterialTexture(0, _driver->getTexture(texture.c_str()));
    _sceneNode->setPosition(core::vector3df(_pos.first, _pos.second, 0));
}

void AGameObject::setPosition(pos_t new_pos)
{
    _sceneNode->setPosition(core::vector3df(new_pos.first * _sizeSquare.first, new_pos.second * _sizeSquare.second, 0));
}

pos_t AGameObject::getPosition()
{
    return _pos;
}

pos_t AGameObject::getPositionInMap()
{
    return {_pos.first / _sizeSquare.first, _pos.second / _sizeSquare.second};
}

std::string AGameObject::getType() const
{
    return _type;
}

char AGameObject::getTypeChar() const
{
    if (_type == "Wall")
        return 'W';
    if (_type == "Box")
        return 'O';
    if (_type == "Bomb")
        return 'B';
    return 0;
}

void AGameObject::setScale(const core::vector3df &vect)
{
    _sceneNode->setScale(vect);
}

void AGameObject::setRotation(const core::vector3df &vect)
{
    _sceneNode->setRotation(vect);
}

const core::vector3df &AGameObject::getRotation() const
{
    return _sceneNode->getRotation();
}


void AGameObject::addAnimator(irr::scene::ISceneNodeAnimator *anim)
{
    _sceneNode->addAnimator(anim);
}

void AGameObject::setAnimationSpeed(const irr::f32 &value)
{
    (static_cast<irr::scene::IAnimatedMeshSceneNode *>(_sceneNode.get()))->setAnimationSpeed(value);
    (static_cast<irr::scene::IAnimatedMeshSceneNode *>(_sceneNode.get()))->setFrameLoop(0, 20);
}

void AGameObject::setVisible(bool isVisible)
{
    _sceneNode->setVisible(isVisible);
}

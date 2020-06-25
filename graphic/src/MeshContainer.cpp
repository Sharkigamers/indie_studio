#include "MeshContainer.hpp"

namespace Bomberman {
    namespace Graphics {

            MeshContainer::MeshContainer(
            irr::IrrlichtDevice *device,
            const std::string &texture,
            std::vector<std::string> assets,
            pos_t pos,
            const irr::core::vector3df &scale,
            const irr::core::vector3df &rotation,
            const std::string &type,
            std::chrono::milliseconds timeInterval
            ): _device(device), _index(0), _sign(1), _pos(pos), _type(type), _timeInterval(timeInterval) {
                for (auto asset : assets) {
                    _meshes.emplace_back(new AGameObject(device, pos, texture, type, asset));
                    (*_meshes.rbegin())->setVisible(false);
                    (*_meshes.rbegin())->setRotation(rotation);
                    (*_meshes.rbegin())->setScale(scale);
                }
                (*_meshes.begin())->setVisible(true);
                _captionTime = std::chrono::system_clock::now();
            }
            void MeshContainer::refreshAnimation() {
                auto duration =  std::chrono::system_clock::now() - _captionTime;

                if (std::chrono::
                    duration_cast<std::chrono::
                    milliseconds>(duration).count() >= _timeInterval.count()) {
                    int size = (int) _meshes.size();
                    _meshes[_index]->setVisible(false); 
                    if ((_index + _sign) >= size) {
                        _sign = -1; 
                    } else if ((_index + _sign) < 0) {
                        _sign = 1;
                    }
                    // _index = (_index + 1) % (int) _meshes.size();
                    _index += _sign; 
                    _meshes[_index]->setVisible(true);
                    
                    _captionTime = std::chrono::system_clock::now();
                }
            }
            MeshContainer::MeshContainer(const MeshContainer &cpy)
            {
                _type = cpy._type;
                _sign = cpy._sign;
                _device = cpy._device;
                _timeInterval = cpy._timeInterval;
                _captionTime = cpy._captionTime;
                _meshes = cpy._meshes;
                _index = cpy._index;
                // return *this; 
            }
            MeshContainer::MeshContainer(MeshContainer &&cpy)
            {
                _type = cpy._type;
                _sign = cpy._sign;
                _device = cpy._device;
                _timeInterval = cpy._timeInterval;
                _captionTime = cpy._captionTime;
                _meshes = cpy._meshes;
                _index = cpy._index;
                // return *this; 
            }
            // pos_t MeshContainer::getPosition(void)
            // {
            //     return _pos;
            // }
            std::string MeshContainer::getType()
            {
                return _type;
            }
            MeshContainer &MeshContainer::operator=(const MeshContainer &cpy)
            {
                _type = cpy._type;
                _sign = cpy._sign;
                _device = cpy._device;
                _timeInterval = cpy._timeInterval;
                _captionTime = cpy._captionTime;
                _meshes = cpy._meshes;
                _index = cpy._index;
                return *this; 
            }
    }
}
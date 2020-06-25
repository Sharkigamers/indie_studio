#ifndef MESH_CONTAINER_H_
#define MESH_CONTAINER_H_

#include "AGameObject.hpp"
#include <irrlicht.h>
#include <chrono>

namespace Bomberman {
    namespace Graphics {
        class MeshContainer {
            irr::IrrlichtDevice *_device;
            std::chrono::milliseconds _timeInterval;
            std::chrono::time_point<std::chrono::system_clock> _captionTime;

            std::vector <std::shared_ptr<AGameObject>> _meshes;
            int _index;
            int _sign;
            pos_t _pos;
            std::string _type;

            public:
            MeshContainer(
                irr::IrrlichtDevice *device,
                const std::string &texture,
                std::vector<std::string> assets,
                pos_t pos,
                const irr::core::vector3df &scale,
                const irr::core::vector3df &rotation,
                const std::string &type,
                std::chrono::milliseconds timeInterval
            );
            MeshContainer &operator=(const MeshContainer &cpy);
            MeshContainer(const MeshContainer &cpy);
            MeshContainer(MeshContainer &&cpy);
            ~MeshContainer()= default;
            MeshContainer() {};

            void refreshAnimation();

            // pos_t getPosition(void);
            std::string getType();
        };
    }
}

#endif
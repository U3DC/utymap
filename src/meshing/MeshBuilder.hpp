#ifndef MESHING_MESHBUILDER_HPP_DEFINED
#define MESHING_MESHBUILDER_HPP_DEFINED

#include "heightmap/ElevationProvider.hpp"
#include "mapcss/Color.hpp"
#include "mapcss/ColorGradient.hpp"
#include "meshing/MeshTypes.hpp"
#include "meshing/Polygon.hpp"

#include <memory>

namespace utymap { namespace meshing {

// Provides the way to build mesh in 3D space.
// Stateless
class MeshBuilder
{
public:
    struct Options
    {
        // Max area of triangle in refined mesh.
        double area;

        // Elevation noise
        double eleNoiseFreq;

        // Gradient data
        const utymap::mapcss::ColorGradient& gradient;

        // Flag indicating whether to suppress boundary segment splitting.
        //     0 = split segments (default)
        //     1 = no new vertices on the boundary
        //     2 = prevent all segment splitting, including internal boundaries
        int segmentSplit;
    };

    // Creates builder with given elevation provider.
    MeshBuilder(utymap::heightmap::ElevationProvider<double>& eleProvider);
    ~MeshBuilder();

    // Builds mesh from given 2D polygon
    Mesh<double> build(Polygon<double>& polygon, const MeshBuilder::Options& options);

private:
    class MeshBuilderImpl;
    std::unique_ptr<MeshBuilderImpl> pimpl_;
};

}}

#endif // MESHING_MESHBUILDER_HPP_DEFINED

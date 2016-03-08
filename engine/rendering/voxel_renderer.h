#pragma once
#include "../core/renderer.h"

#include <oglplus/texture.hpp>
#include <glm/mat4x4.hpp>
#include <oglplus/vertex_array.hpp>
#include <oglplus/buffer.hpp>

class BoundingBox;
class VoxelDrawerProgram;
class VoxelizationProgram;

class VoxelRenderer : public Renderer
{
    public:
        static bool ShowVoxels;
        /// <summary>
        /// Voxelizes the current scene. It can also be used to show the
        /// result volume.
        /// </summary>
        void Render() override;
        /// <summary>
        /// Sets the matrices uniforms.
        /// </summary>
        /// <param name="node">The node.</param>
        void SetMatricesUniforms(const Node &node) const override;
        /// <summary>
        /// Sets the material uniforms.
        /// </summary>
        /// <param name="material">The material.</param>
        void SetMaterialUniforms(const Material &material) const override;
        /// <summary>
        /// Sets the voxelization update frequency, voxelize scene will be called
        /// every framestep number of frames.
        /// </summary>
        /// <param name="framestep">The framestep.</param>
        void SetUpdateFrequency(const unsigned int framestep);
        /// <summary>
        /// Initializes a new instance of the <see cref="VoxelRenderer"/> class.
        /// </summary>
        /// <param name="window">The window.</param>
        explicit VoxelRenderer(RenderWindow * window);
        /// <summary>
        /// Finalizes an instance of the <see cref="VoxelRenderer"/> class.
        /// </summary>
        ~VoxelRenderer();
    private:
        /// <summary>
        /// Returns the voxelization program shader.
        /// </summary>
        /// <returns></returns>
        static VoxelizationProgram &VoxelizationPass();
        /// <summary>
        /// Returns the voxelization program shader.
        /// </summary>
        /// <returns></returns>
        static VoxelDrawerProgram &VoxelDrawerShader();
        /// <summary>
        /// Creates the view projection matrices per x, y and z axis.
        /// depending on the voxel volume grid size.
        /// </summary>
        void UpdateProjectionMatrices(const BoundingBox &sceneBox);
        /// <summary>
        /// Creates the voxel volume, a 3D texture meant to contain the
        /// voxelization result.
        /// </summary>
        void GenerateVolumes() const;
        /// <summary>
        /// Generates the atomic buffer. Used for average atomic operations
        /// during voxelization fragment shader.
        /// </summary>
        void GenerateAtomicBuffer() const;
        /// <summary>
        /// Voxelizes the scene.
        /// </summary>
        void VoxelizeScene();
        /// <summary>
        /// Draws the resulting voxels.
        /// </summary>
        void DrawVoxels();

        void ResetAtomicBuffer() const;

        // atomic buffer for average atomic in fragment voxelizer
        oglplus::Buffer atomicCounter;

        // output textures
        oglplus::Texture voxelAlbedo;

        // vertex buffer object for 3d texture visualization
        oglplus::VertexArray voxelDrawerArray;

        std::array<glm::mat4x4, 3> viewProjectionMatrix;
        unsigned int volumeDimension;
        unsigned int framestep;
        float volumeGridSize;
        unsigned int voxelCount;

        void SetVoxelizationPassUniforms() const;
};
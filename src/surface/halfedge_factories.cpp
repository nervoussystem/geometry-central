#include "geometrycentral/surface/halfedge_factories.h"


namespace geometrycentral {
namespace surface {


std::tuple<std::unique_ptr<ManifoldSurfaceMesh>, std::unique_ptr<VertexPositionGeometry>>
makeHalfedgeAndGeometry(const std::vector<std::vector<size_t>>& polygons, const std::vector<Vector3> vertexPositions) {

  return makeHalfedgeAndGeometry(polygons, {}, vertexPositions);
}

std::tuple<std::unique_ptr<ManifoldSurfaceMesh>, std::unique_ptr<VertexPositionGeometry>>
makeHalfedgeAndGeometry(const std::vector<std::vector<size_t>>& polygons,
                        const std::vector<std::vector<std::tuple<size_t, size_t>>>& twins,
                        const std::vector<Vector3> vertexPositions) {

  // Construct
  std::unique_ptr<ManifoldSurfaceMesh> mesh;
  if (twins.empty()) {
    mesh.reset(new ManifoldSurfaceMesh(polygons));
  } else {
    mesh.reset(new ManifoldSurfaceMesh(polygons, twins));
  }
  std::unique_ptr<VertexPositionGeometry> geometry(new VertexPositionGeometry(*mesh));
  for (Vertex v : mesh->vertices()) {
    // Use the low-level indexers here since we're constructing
    (*geometry).inputVertexPositions[v] = vertexPositions[v.getIndex()];
  }

  return std::make_tuple(std::move(mesh), std::move(geometry));
}


std::tuple<std::unique_ptr<SurfaceMesh>, std::unique_ptr<VertexPositionGeometry>>
makeGeneralHalfedgeAndGeometry(const std::vector<std::vector<size_t>>& polygons,
                                   const std::vector<Vector3> vertexPositions) {

  return makeGeneralHalfedgeAndGeometry(polygons, {}, vertexPositions);
}


std::tuple<std::unique_ptr<SurfaceMesh>, std::unique_ptr<VertexPositionGeometry>>
makeGeneralHalfedgeAndGeometry(const std::vector<std::vector<size_t>>& polygons,
                                   const std::vector<std::vector<std::tuple<size_t, size_t>>>& twins,
                                   const std::vector<Vector3> vertexPositions) {

  // Construct
  std::unique_ptr<SurfaceMesh> mesh;
  if (twins.empty()) {
    mesh.reset(new SurfaceMesh(polygons));
  } else {
    mesh.reset(new SurfaceMesh(polygons, twins));
  }
  std::unique_ptr<VertexPositionGeometry> geometry(new VertexPositionGeometry(*mesh));
  for (Vertex v : mesh->vertices()) {
    // Use the low-level indexers here since we're constructing
    (*geometry).inputVertexPositions[v] = vertexPositions[v.getIndex()];
  }

  return std::make_tuple(std::move(mesh), std::move(geometry));
}



} // namespace surface
} // namespace geometrycentral

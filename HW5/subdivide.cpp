#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include "common.h"

namespace loop_subdivision {

// Function to build adjacency information
void buildAdjacency(const std::vector<Face>& faces, std::vector<Vertex>& vertices, std::set<Edge>& edges) {
    for (size_t i = 0; i < faces.size(); ++i) {
        const Face& f = faces[i];
        for (int i = 0; i < 3; ++i) {
            int v1 = f.v[i];
            int v2 = f.v[(i + 1) % 3];
            vertices[v1].addNeighbor(v2);
            vertices[v2].addNeighbor(v1);

            Edge edge(v1, v2);
            auto it = edges.find(edge);
            if (it == edges.end()) {
                edge.oppositeVertices[0] = f.v[(i + 2) % 3];
                edge.oppositeVertices[1] = -1;
                edges.insert(edge);
            } else {
                Edge e = *it;
                e.oppositeVertices[1] = f.v[(i + 2) % 3];
                edges.erase(it);
                edges.insert(e);
            }
        }
    }
}

// Function to compute new edge points
void computeNewEdgePoints(const std::vector<Vertex>& vertices,
                       std::set<Edge>& edges,
                       std::vector<Vertex>& newVertices) {
    for (auto it=edges.begin(); it!=edges.end(); ++it) {
        Edge e = *it;
        Vertex v1 = vertices[e.v1];
        Vertex v2 = vertices[e.v2];
        Vertex newEdgePoint;

        // TODO: Compute new edge point
        if (e.oppositeVertices[1] != -1) { 
            // interior edge
            Vertex ov1 = vertices[e.oppositeVertices[0]];
            Vertex ov2 = vertices[e.oppositeVertices[1]];
            newEdgePoint.x = (3.0 / 8.0) * (v1.x + v2.x) + (1.0 / 8.0) * (ov1.x + ov2.x);
            newEdgePoint.y = (3.0 / 8.0) * (v1.y + v2.y) + (1.0 / 8.0) * (ov1.y + ov2.y);
            newEdgePoint.z = (3.0 / 8.0) * (v1.z + v2.z) + (1.0 / 8.0) * (ov1.z + ov2.z);

        } else {
            // Boundary edge
            newEdgePoint.x = 0.5 * (v1.x + v2.x);
            newEdgePoint.y = 0.5 * (v1.y + v2.y);
            newEdgePoint.z = 0.5 * (v1.z + v2.z);
        }

        int index = newVertices.size();
        newVertices.push_back(newEdgePoint); // Add new vertex
        e.new_edgepoint_id = index;
        edges.erase(it);
        edges.insert(e);
    }
}

// Function to compute new positions for original vertices
void updateOldVertices(const std::vector<Vertex>& oldVertices, std::vector<Vertex>& newVertices) {
    for (size_t i = 0; i < oldVertices.size(); ++i) {
        // TODO: Compute new positions for old vertices, save the result in newVertices to avoid iterative update
        const Vertex& oldVertex = oldVertices[i];
        int n = oldVertex.neighbors.size();
        float beta;
        if (n > 3) {
            beta = 3.0f / (8.0f * n);
        }
        else {
            beta = 3.0f / 16.0f;
        }
        // Compute weighted average of neighbor positions
        float x_sum = 0.0f, y_sum = 0.0f, z_sum = 0.0f;
        for (int neighborIndex : oldVertex.neighbors) {
            const Vertex& neighbor = oldVertices[neighborIndex];
            x_sum += neighbor.x;
            y_sum += neighbor.y;
            z_sum += neighbor.z;
        }

        Vertex newVertex;
        newVertex.x = (1.0f - n * beta) * oldVertex.x + beta * x_sum;
        newVertex.y = (1.0f - n * beta) * oldVertex.y + beta * y_sum;
        newVertex.z = (1.0f - n * beta) * oldVertex.z + beta * z_sum;

        newVertices[i] = newVertex;
        
    }
}

// Function to build new subdivided faces
void buildNewFaces(const std::vector<Face>& oldFaces, const std::set<Edge>& edges, std::vector<Face>& newFaces) {
    for (const Face& f : oldFaces) {
        // TODO: Build new faces. hint: use (*edges.find(Edge(v1, v2))) to get an edge. The order of vertices in a face is important.

        int v1 = f.v[0], v2 = f.v[1], v3 = f.v[2];
        int e1 = (*edges.find(Edge(v1, v2))).new_edgepoint_id;
        int e2 = (*edges.find(Edge(v2, v3))).new_edgepoint_id;
        int e3 = (*edges.find(Edge(v3, v1))).new_edgepoint_id;

        newFaces.push_back(Face({ v1, e1, e3 }));
        newFaces.push_back(Face({ v2, e2, e1 }));
        newFaces.push_back(Face({ v3, e3, e2 }));
        newFaces.push_back(Face({ e1, e2, e3 })); 
    }
}

int subdivideMesh(std::string inputFilename, std::string outputFilename) {
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    std::set<Edge> edges;

    if (!readOBJ(inputFilename, vertices, faces)) {
        return -1;
    }

    buildAdjacency(faces, vertices, edges);
    // Compute new vertices
    std::vector<Vertex> newVertices = vertices;
    computeNewEdgePoints(vertices, edges, newVertices);
    updateOldVertices(vertices, newVertices);
    // Build new faces
    std::vector<Face> newFaces;
    buildNewFaces(faces, edges, newFaces);

    // Write the new mesh
    if (!writeOBJ(outputFilename, newVertices, newFaces)) {
        return -1;
    }
    std::cout << "Subdivided mesh saved to " << outputFilename << std::endl;

    return 0;
}

}

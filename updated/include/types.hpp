#pragma once

#include <string>
#include <vector>

#include "vec2.hpp"


using vertex_t = unsigned;

/**
 * Object representing a vertex in the final layout.
 */
struct node {
    vertex_t u;  /**< the corresponding vertex identifier */
    vec2 pos;    /**< the position in space */
    float size;  /**< the radius */
};

/**
 * Object representing an edge in the final layout.
 */
struct path {
    vertex_t from, to;          /**< the vertex identifiers of endpoints of the corresponding edge */
    std::vector< vec2 > points; /**< control points of the poly-line representing the edge */
    bool bidirectional = false; /**< is the edge bidirectional? */
};

/**
 * Contains the parameters of the desired graph layout.
 */
struct attributes {
    float node_size = 15;        /**< radius of all nodes */
    float node_dist = 10;        /**< minimum distance between borders of 2 nodes */
    float layer_dist = 30;       /**< minimum distance between borders of nodes in 2 different layers */
    float loop_angle = 55;       /**< angle determining the point on the node where a loop connects to it */
    float loop_size = node_size; /**< distance which the loop extends from the node*/
};

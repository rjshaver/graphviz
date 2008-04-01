/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

#ifndef _HIERARCHY_H_
#define _HIERARCHY_H_

#include "defs.h"

typedef struct {
    int nedges;       // degree, including self-loop
    int *edges;       // neighbors; edges[0] = self
    int size;         // no. of original nodes contained
    int active_level; // Node displayed iff active_level == node's level
    int globalIndex;  // Each node has a unique ID over all levels

    // position of node in universal coordinate system
    float x_coord;
    float y_coord;

    // position of node in physical (device) coordinate system
    float physical_x_coord;
    float physical_y_coord;	
} ex_vtx_data;


typedef struct {
    int nlevels;
    vtx_data ** graphs;
    ex_vtx_data ** geom_graphs;
    int * nvtxs;
    int * nedges;
    /* Node i on level k is mapped to coarse node v2cv[k][i] on level k+1
     */
    int ** v2cv;
    /* Coarse node i on level k contains nodes cv2v[k][2*i] and 
     * cv2v[k][2*i+1] on level k-1. If it contains only 1 node, then
     * cv2v[k][2*i+1] will be -1
     */
    int ** cv2v;
    int maxNodeIndex;
} Hierarchy;

void release(Hierarchy*);
Hierarchy* create_hierarchy(vtx_data * graph, int nvtxs, int nedges, 
    ex_vtx_data* geom_graph, int ngeom_edges, int min_nvtxs);
	
void set_active_levels(Hierarchy*, int*, int);
double find_closest_active_node(Hierarchy*, double x, double y, int*);

int extract_active_logical_coords(Hierarchy * hierarchy, int node, int level, 
    double *x_coords, double *y_coords, int counter);
int set_active_physical_coords(Hierarchy *, int node, int level,
    double *x_coords, double *y_coords, int counter);

int count_active_nodes(Hierarchy *);
void init_active_level(Hierarchy* hierarchy, int level);

// creating a geometric graph:
int init_ex_graph(vtx_data * graph1, vtx_data * graph2, int n,
   double *x_coords, double *y_coords, ex_vtx_data ** gp);

vtx_data *delaunay_triangulation(double *x, double *y, int n);

vtx_data *UG_graph(double *x, double *y, int n, int accurate_computation);

// layout distortion:
void rescale_layout(double *x_coords, double *y_coords,
    int n, int interval, double width, double height,
    double margin);
void rescale_layout_polar(double * x_coords, double * y_coords, 
    double * x_foci, double * y_foci, int num_foci,
    int n, int interval, double width, double height, double margin);

void find_physical_coords(Hierarchy*, int, int, double *x, double *y);
int find_active_ancestor(Hierarchy*, int, int);
int locateByIndex(Hierarchy*, int, int*);
int findGlobalIndexesOfActiveNeighbors(Hierarchy*, int, int**);

void freeGraph(vtx_data * graph);

#endif

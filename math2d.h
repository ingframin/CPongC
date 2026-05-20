/* 
Vocabs2 - velocity obstacle for drones simulator
Copyright (C) 2023  Franco Minucci

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef MATH2D_H
#define MATH2D_H

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// 2D Vector struct
typedef struct vec2 {
    double x;
    double y;
} vec2;

// Barycentric coordinates struct
typedef struct barycoords {
    double alpha;
    double beta;
    double gamma;
} barycoords;

// Obstacle struct (for velocity obstacle calculations)
typedef struct Obstacle {
    double radius;
    vec2 position;
    vec2 T1;
    vec2 T2;
} Obstacle;

// ======================
// vec2 Functions
// ======================

double vec2_mod(vec2 v);
vec2 vec2_normalize(vec2 v);
double vec2_distanceTo(vec2 v, vec2 other);
double vec2_angleTo(vec2 v, vec2 other);
double vec2_dot(vec2 v, vec2 other);
vec2 vec2_rotate(vec2 v, double angle);
vec2 vec2_rotateLeftHalfPI(vec2 v);
vec2 vec2_rotateRightHalfPI(vec2 v);
vec2 vec2_reverse(vec2 v);
bool vec2_isZero(vec2 v, double epsilon);
vec2 vec2_add(vec2 v, vec2 other);
vec2 vec2_sub(vec2 v, vec2 other);
vec2 vec2_mul_scalar(vec2 v, double k);
vec2 vec2_add_scalar(vec2 v, double k);
bool vec2_equal(vec2 v, vec2 other);

// ======================
// Vector Operations (free functions)
// ======================

double v2_dot(vec2 v1, vec2 v2);

// ======================
// Geometric Transformations
// ======================

vec2 v2_rotate_free(vec2 v, double angle);
vec2 v2_rotateLeftHalfPI_free(vec2 v);
vec2 v2_rotateRightHalfPI_free(vec2 v);
vec2 v2_reverse_free(vec2 v);

// ======================
// Distance and Angle Calculations
// ======================

double v2_distance(vec2 v1, vec2 v2);
double v2_angle_between(vec2 v1, vec2 v2);

// ======================
// Interpolation
// ======================

vec2 v2_lerp(vec2 p1, vec2 p2, double t);
vec2 v2_qspline(vec2 p1, vec2 p2, vec2 p3, double t);
vec2 v2_cspline(vec2 p1, vec2 p2, vec2 p3, vec2 p4, double t);
vec2* v2_interpolate(const vec2 vs[], size_t vs_len, double t);
void v2_free_interpolated(vec2* points);

// ======================
// Barycentric Coordinates
// ======================

barycoords v2_barycentric(vec2 A, vec2 B, vec2 C, vec2 P);

// ======================
// Obstacle Calculations (Velocity Obstacle Method)
// ======================

Obstacle compute_obstacle(vec2 pos1, vec2 pos2, double size1, double size2);
Obstacle compute_velocity_obstacle(vec2 pos1, vec2 vel1, 
                                   vec2 pos2, vec2 vel2, 
                                   double size1, double size2);

#endif

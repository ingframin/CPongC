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

#include "math2d.h"
#define _USE_MATH_DEFINES
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288419716939937510
#endif

// ======================
// vec2 Functions
// ======================

double vec2_mod(vec2 v)
{
  __m256d vec = _mm256_set_pd(0, 0, v.y, v.x);
  __m256d squared = _mm256_mul_pd(vec, vec);
  __m128d sum128 = _mm_add_pd(_mm256_extractf128_pd(squared, 0), _mm256_extractf128_pd(squared, 1));
  return sqrt(_mm_cvtsd_f64(sum128));
}

vec2 vec2_normalize(vec2 v)
{
  if(vec2_isZero(v, 1e-12)) {
    // Return zero vector for zero-length input
    return (vec2){0.0, 0.0};
  }
  
  double m = vec2_mod(v);
  return (vec2){v.x / m, v.y / m};
}

vec2 vec2_add(vec2 v, vec2 other)
{
  
  __m256d v1 = _mm256_loadu_pd(&v.x);  // Load x,y (upper 128 bits unused)
  __m256d v2 = _mm256_loadu_pd(&other.x);
  __m256d result = _mm256_add_pd(v1, v2);
  vec2 r;
  _mm256_storeu_pd(&r.x, result);
  return r;
}

vec2 vec2_sub(vec2 v, vec2 other)
{
  
  __m256d v1 = _mm256_loadu_pd(&v.x);
  __m256d v2 = _mm256_loadu_pd(&other.x);
  __m256d result = _mm256_sub_pd(v1, v2);
  vec2 r;
  _mm256_storeu_pd(&r.x, result);
  return r;
}

vec2 vec2_mul_scalar(vec2 v, double k)
{
  
  __m256d vec = _mm256_loadu_pd(&v.x);
  __m256d scale = _mm256_set1_pd(k);
  __m256d result = _mm256_mul_pd(vec, scale);
  vec2 r;
  _mm256_storeu_pd(&r.x, result);
  return r;
}

vec2 vec2_add_scalar(vec2 v, double k)
{
  return (vec2){v.x + k, v.y + k};
}

bool vec2_equal(vec2 v, vec2 other)
{
  return v.x == other.x && v.y == other.y;
}

bool vec2_isZero(vec2 v, double epsilon)
{
  return fabs(v.x) < epsilon && fabs(v.y) < epsilon;
}

double vec2_distanceTo(vec2 v, vec2 other)
{
  
  __m256d dx = _mm256_set_pd(0, 0, other.y - v.y, other.x - v.x);
  __m256d squared = _mm256_mul_pd(dx, dx);
  
  // Horizontal add: dx^2 + dy^2
  __m128d low = _mm256_castpd256_pd128(squared);
  __m128d high = _mm256_extractf128_pd(squared, 1);
  __m128d sum128 = _mm_add_pd(low, high);
  return sqrt(_mm_cvtsd_f64(sum128));
}

double vec2_angleTo(vec2 v, vec2 other)
{
  double dot = vec2_dot(v, other);
  double mod1 = vec2_mod(v);
  double mod2 = vec2_mod(other);
  
  // Handle division by zero
  if (mod1 < 1e-12 || mod2 < 1e-12) {
    return 0.0;
  }
  
  double cos_theta = dot / (mod1 * mod2);
  
  // Clamp to avoid floating point errors
  if (cos_theta > 1.0) cos_theta = 1.0;
  if (cos_theta < -1.0) cos_theta = -1.0;
  
  return acos(cos_theta);
}

double vec2_dot(vec2 v, vec2 other)
{
  
  __m256d v1 = _mm256_loadu_pd(&v.x);
  __m256d v2 = _mm256_loadu_pd(&other.x);
  __m256d product = _mm256_mul_pd(v1, v2);
  
  // Horizontal add: (x1*y1 + x2*y2) where x2,y2 are 0
  __m128d low = _mm256_castpd256_pd128(product);
  __m128d high = _mm256_extractf128_pd(product, 1);
  __m128d sum128 = _mm_add_pd(low, high);
  return _mm_cvtsd_f64(sum128);
}

vec2 vec2_rotate(vec2 v, double angle)
{
  double cos_theta = cos(angle);
  double sin_theta = sin(angle);
  
  return (vec2){
    v.x * cos_theta - v.y * sin_theta,
    v.x * sin_theta + v.y * cos_theta
  };
}

vec2 vec2_rotateLeftHalfPI(vec2 v)
{
  return (vec2){-v.y, v.x};
}

vec2 vec2_rotateRightHalfPI(vec2 v)
{
  return (vec2){v.y, -v.x};
}

vec2 vec2_reverse(vec2 v)
{
  return (vec2){-v.x, -v.y};
}


double v2_dot(vec2 v1, vec2 v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}

// ======================
// Geometric Transformations
// ======================

vec2 v2_rotate_free(vec2 v, double angle)
{
  double cos_theta = cos(angle);
  double sin_theta = sin(angle);
  
  return (vec2){
    v.x * cos_theta - v.y * sin_theta,
    v.x * sin_theta + v.y * cos_theta
  };
}

vec2 v2_rotateLeftHalfPI_free(vec2 v)
{
  return (vec2){-v.y, v.x};
}

vec2 v2_rotateRightHalfPI_free(vec2 v)
{
  return (vec2){v.y, -v.x};
}

vec2 v2_reverse_free(vec2 v)
{
  return (vec2){-v.x, -v.y};
}

// ======================
// Distance and Angle Calculations
// ======================

double v2_distance(vec2 v1, vec2 v2)
{
  double dx = v2.x - v1.x;
  double dy = v2.y - v1.y;
  return hypot(dx, dy);
}

double v2_angle_between(vec2 v1, vec2 v2)
{
  double dot = v2_dot(v1, v2);
  double mod1 = vec2_mod(v1);
  double mod2 = vec2_mod(v2);
  
  // Handle division by zero
  if (mod1 < 1e-12 || mod2 < 1e-12) {
    return 0.0;
  }
  
  double cos_theta = dot / (mod1 * mod2);
  
  // Clamp to avoid floating point errors
  if (cos_theta > 1.0) cos_theta = 1.0;
  if (cos_theta < -1.0) cos_theta = -1.0;
  
  return acos(cos_theta);
}

// ======================
// Interpolation
// ======================

vec2 v2_lerp(vec2 p1, vec2 p2, double t)
{
  // Clamp t to [0, 1] range
  if (t < 0.0) t = 0.0;
  if (t > 1.0) t = 1.0;
  
  return (vec2){
    p1.x + t * (p2.x - p1.x),
    p1.y + t * (p2.y - p1.y)
  };
}

vec2 v2_qspline(vec2 p1, vec2 p2, vec2 p3, double t)
{
  // Clamp t to [0, 1] range
  if (t < 0.0) t = 0.0;
  if (t > 1.0) t = 1.0;
  
  // Quadratic spline: P(t) = (1-t)^2 * P1 + 2*(1-t)*t * P2 + t^2 * P3
  double t2 = t * t;
  double one_minus_t = 1.0 - t;
  double one_minus_t2 = one_minus_t * one_minus_t;
  
  return (vec2){
    one_minus_t2 * p1.x + 2 * one_minus_t * t * p2.x + t2 * p3.x,
    one_minus_t2 * p1.y + 2 * one_minus_t * t * p2.y + t2 * p3.y
  };
}

vec2 v2_cspline(vec2 p1, vec2 p2, vec2 p3, vec2 p4, double t)
{
  // Clamp t to [0, 1] range
  if (t < 0.0) t = 0.0;
  if (t > 1.0) t = 1.0;
  
  // Cubic spline using Catmull-Rom formula
  double t2 = t * t;
  double t3 = t2 * t;
  
  double b0 = -0.5 * t3 + t2 - 0.5 * t;
  double b1 = 1.5 * t3 - 2.5 * t2 + 1.0;
  double b2 = -1.5 * t3 + 2.0 * t2 + 0.5 * t;
  double b3 = 0.5 * t3 - 0.5 * t2;
  
  return (vec2){
    b0 * p1.x + b1 * p2.x + b2 * p3.x + b3 * p4.x,
    b0 * p1.y + b1 * p2.y + b2 * p3.y + b3 * p4.y
  };
}

vec2* v2_interpolate(const vec2 vs[], size_t vs_len, double t)
{
  if (vs_len == 0) return NULL;
  
  // Clamp t to [0, 1] range
  if (t < 0.0) t = 0.0;
  if (t > 1.0) t = 1.0;
  
  // Allocate array for interpolated points
  vec2* result = (vec2*)malloc(vs_len * sizeof(vec2));
  if (result == NULL) return NULL;
  
  // Use de Casteljau's algorithm for each segment
  for (size_t i = 0; i < vs_len - 1; i++) {
    vec2 p0 = vs[i];
    vec2 p1 = vs[i + 1];
    
    // Linear interpolation for now (could be enhanced)
    result[i] = v2_lerp(p0, p1, t);
  }
  
  // Last point is the same as input
  if (vs_len > 0) {
    result[vs_len - 1] = vs[vs_len - 1];
  }
  
  return result;
}

void v2_free_interpolated(vec2* points)
{
  if (points != NULL) {
    free(points);
  }
}

// ======================
// Barycentric Coordinates
// ======================

barycoords v2_barycentric(vec2 A, vec2 B, vec2 C, vec2 P)
{
  // Compute vectors
  vec2 v0 = vec2_sub(B, A);
  vec2 v1 = vec2_sub(C, A);
  vec2 v2 = vec2_sub(P, A);
  
  // Compute dot products
  double dot00 = v2_dot(v0, v0);
  double dot01 = v2_dot(v0, v1);
  double dot02 = v2_dot(v0, v2);
  double dot11 = v2_dot(v1, v1);
  double dot12 = v2_dot(v1, v2);
  
  // Compute barycentric coordinates
  double inv_denom = 1.0 / (dot00 * dot11 - dot01 * dot01);
  double beta = (dot11 * dot02 - dot01 * dot12) * inv_denom;
  double gamma = (dot00 * dot12 - dot01 * dot02) * inv_denom;
  double alpha = 1.0 - beta - gamma;
  
  return (barycoords){alpha, beta, gamma};
}

// ======================
// Obstacle Calculations (Velocity Obstacle Method)
// ======================

Obstacle compute_obstacle(vec2 pos1, vec2 pos2, double size1, double size2)
{
  Obstacle obs;
  
  // Compute center position (midpoint between agents)
  obs.position = (vec2){(pos1.x + pos2.x) / 2.0, (pos1.y + pos2.y) / 2.0};
  
  // Compute radius (sum of agent radii)
  obs.radius = size1 + size2;
  
  // Compute direction vector between agents
  vec2 dir = vec2_sub(pos2, pos1);
  double dist = vec2_mod(dir);
  
  // Handle case where agents are at the same position
  if (dist < 1e-12) {
    // Return a default obstacle
    obs.T1 = (vec2){obs.position.x + obs.radius, obs.position.y};
    obs.T2 = (vec2){obs.position.x - obs.radius, obs.position.y};
    return obs;
  }
  
  // Normalize direction vector
  dir = vec2_normalize(dir);
  
  // Compute tangent points (perpendicular to direction)
  vec2 perp = (vec2){-dir.y, dir.x}; // 90 degree rotation
  vec2 perp_scaled = vec2_mul_scalar(perp, obs.radius);
  vec2 perp_scaled_neg = vec2_mul_scalar(perp, -obs.radius);
  
  obs.T1 = vec2_add(obs.position, perp_scaled);
  obs.T2 = vec2_add(obs.position, perp_scaled_neg);
  
  return obs;
}

// Proper Velocity Obstacle implementation
Obstacle compute_velocity_obstacle(vec2 pos1, vec2 vel1, 
                                   vec2 pos2, vec2 vel2, 
                                   double size1, double size2)
{
  Obstacle vo;
  
  // Compute relative position and velocity
  vec2 rel_pos = vec2_sub(pos2, pos1);
  vec2 rel_vel = vec2_sub(vel2, vel1);
  
  // Combined radius (sum of agent radii)
  vo.radius = size1 + size2;
  
  // Distance between agents
  double dist = vec2_mod(rel_pos);
  
  // Handle special cases
  if (dist < 1e-12) {
    // Agents are at the same position - create a full circle obstacle
    vo.position = (vec2){0, 0}; // Centered at origin in velocity space
    vo.T1 = (vec2){vo.radius, 0};
    vo.T2 = (vec2){-vo.radius, 0};
    return vo;
  }
  
  // Normalize relative position
  vec2 rel_pos_norm = vec2_normalize(rel_pos);
  
  // Compute the apex of the velocity obstacle cone
  // The apex is at (rel_vel • rel_pos_norm) * rel_pos_norm
  double rel_vel_proj = vec2_dot(rel_vel, rel_pos_norm);
  vo.position = vec2_mul_scalar(rel_pos_norm, rel_vel_proj);
  
  // Compute the tangent points of the velocity obstacle
  // These are perpendicular to the line connecting the apex to the origin
  vec2 perp_dir = (vec2){-rel_pos_norm.y, rel_pos_norm.x}; // 90 degree rotation
  
  // The angle of the cone depends on the relative velocity and distance
  // Using the formula: sin(theta) = (r1 + r2) / ||rel_pos|| * ||rel_vel|| / ||rel_vel_proj||
  double rel_vel_mod = vec2_mod(rel_vel);
  double sin_theta = (vo.radius / dist) * (rel_vel_mod / fabs(rel_vel_proj + 1e-12));
  
  // Clamp sin_theta to valid range [-1, 1]
  if (sin_theta > 1.0) sin_theta = 1.0;
  if (sin_theta < -1.0) sin_theta = -1.0;
  
  // Compute the tangent points
  double tangent_length = vo.radius * sqrt(1.0 - sin_theta * sin_theta) / sin_theta;
  vec2 perp_scaled = vec2_mul_scalar(perp_dir, tangent_length);
  vec2 perp_scaled_neg = vec2_mul_scalar(perp_dir, -tangent_length);
  
  vo.T1 = vec2_add(vo.position, perp_scaled);
  vo.T2 = vec2_add(vo.position, perp_scaled_neg);
  
  return vo;
}

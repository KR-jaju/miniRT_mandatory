#ifndef SETTINGS_H
#define SETTINGS_H

/**
 * @brief For User Settings
 * 
 */

# define SMOOTH_SHADING		1 // Shading mode (Flat or Smooth)
# define IMAGE_PUT_INTERVAL	5

// material constants
# define REFLECTIVITY		0.3
# define K_DIFFUSE			0.3 // recommended: K_DIFFUSE + K_SPECULAR <= 1
# define K_SPECULAR			0.7 // recommended: K_DIFFUSE + K_SPECULAR <= 1
# define SHININESS			64

#endif

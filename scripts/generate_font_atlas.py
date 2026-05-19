#!/usr/bin/env python3
"""
Generate a bitmap font atlas from a TrueType font.
Each glyph is rendered into its own rectangle and arranged horizontally.

Usage:
    python generate_font_atlas.py --font path/to/font.ttf --chars "ABC..." --output atlas.png [--size 32] [--color 255,255,255] [--bg 0,0,0,0]
"""

import argparse
import pygame
import sys


def parse_color(color_str):
    """Parse a color string like '255,255,255' or '255,255,255,255' into RGBA tuple."""
    parts = list(map(int, color_str.split(',')))
    if len(parts) == 3:
        parts.append(255)  # Default alpha
    return tuple(parts)


def generate_font_atlas(font_path, chars, output_path, font_size=32, 
                         fg_color=(255, 255, 255), bg_color=(0, 0, 0, 0)):
    """
    Generate a font atlas image with all characters in a horizontal strip.
    
    Args:
        font_path: Path to .ttf font file
        chars: String containing all characters to include
        output_path: Where to save the PNG
        font_size: Size of each glyph in pixels
        fg_color: Text color as (R, G, B) or (R, G, B, A)
        bg_color: Background color as (R, G, B) or (R, G, B, A)
    """
    pygame.init()
    
    # Load font
    font = pygame.font.Font(font_path, font_size)
    
    # Render each character
    glyph_surfaces = []
    max_width = 0
    max_height = 0
    
    for c in chars:
        surf = font.render(c, True, fg_color)
        # Handle transparent background
        if len(bg_color) == 4 and bg_color[3] == 0:
            surf.set_colorkey((0, 0, 0))
            surf.set_alpha(None)
        glyph_surfaces.append(surf)
        max_width = max(max_width, surf.get_width())
        max_height = max(max_height, surf.get_height())
    
    # Calculate total width (all glyphs at max_width)
    total_width = max_width * len(chars)
    atlas_height = max_height
    
    # Create atlas surface with per-pixel alpha
    atlas = pygame.Surface((total_width, atlas_height), pygame.SRCALPHA, 32)
    
    # Blit each glyph centered in its cell
    for i, surf in enumerate(glyph_surfaces):
        x = i * max_width
        y = 0
        # Center the glyph in its cell
        x_offset = (max_width - surf.get_width()) // 2
        atlas.blit(surf, (x + x_offset, y))
    
    # Save
    pygame.image.save(atlas, output_path)
    print(f"Font atlas saved to {output_path}")
    print(f"  Size: {total_width}x{atlas_height}")
    print(f"  Glyphs: {len(chars)}")
    print(f"  Each glyph: {max_width}x{max_height} pixels")
    print(f"  Character order: {chars}")
    
    pygame.quit()


def main():
    parser = argparse.ArgumentParser(
        description='Generate a bitmap font atlas from a TrueType font.')
    parser.add_argument('--font', required=True, 
                        help='Path to .ttf font file')
    parser.add_argument('--chars', required=True,
                        help='String of characters to include in the atlas')
    parser.add_argument('--output', required=True,
                        help='Output PNG file path')
    parser.add_argument('--size', type=int, default=32,
                        help='Font size in pixels (default: 32)')
    parser.add_argument('--color', default='255,255,255',
                        help='Text color as R,G,B or R,G,B,A (default: 255,255,255)')
    parser.add_argument('--bg', default='0,0,0,0',
                        help='Background color as R,G,B or R,G,B,A (default: transparent)')
    
    args = parser.parse_args()
    
    fg_color = parse_color(args.color)
    bg_color = parse_color(args.bg)
    
    generate_font_atlas(
        args.font,
        args.chars,
        args.output,
        args.size,
        fg_color,
        bg_color
    )


if __name__ == '__main__':
    main()

#!/usr/bin/env python3
import numpy as np
from stl import mesh
import sys
import os

def scale_stl(input_file, output_file, scale_factor=0.001):
    """Scale STL file by factor"""
    try:
        # Load the STL file
        your_mesh = mesh.Mesh.from_file(input_file)
        
        # Scale all vertices
        your_mesh.vectors *= scale_factor
        
        # Save the scaled mesh
        your_mesh.save(output_file)
        print(f"✓ Converted: {input_file} -> {output_file}")
        return True
    except Exception as e:
        print(f"✗ Error with {input_file}: {e}")
        return False

# Convert all STL files in current directory
for filename in os.listdir('.'):
    if filename.endswith('.STL') and not filename.startswith('converted_'):
        input_path = filename
        output_path = f"converted_{filename}"
        scale_stl(input_path, output_path, 0.001)

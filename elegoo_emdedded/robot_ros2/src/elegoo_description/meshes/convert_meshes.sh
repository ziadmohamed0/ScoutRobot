#!/bin/bash
# تحويل كل STL من mm إلى m

for file in *.STL; do
    echo "Converting $file..."
    meshlabserver -i "$file" -o "converted_$file" -s /tmp/scale.mlx
done
